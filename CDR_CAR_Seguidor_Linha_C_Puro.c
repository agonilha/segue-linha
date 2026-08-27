/* =========================================================
 * CDR CAR - SEGUIDOR DE LINHA OTIMIZADO - VERSAO EM C PURO (AVR-GCC)
 * Microcontrolador: ATmega328 (Placa UNO SMD R3 do kit CDR CAR)
 * Hardware: Shield Ponte H L298P + Modulo Seguidor de Linha 3x TCRT5000
 *           (saida digital via LM393) + 2x Motor DC 3-6V, reducao 48:1
 *           + Alimentacao 6 pilhas AA
 *
 * Esta versao NAO usa o framework Arduino (sem pinMode, digitalRead,
 * analogWrite etc.). Todo o controle e feito por escrita direta nos
 * registradores do ATmega328, usando o compilador AVR-GCC.
 *
 * Mapeamento de pinos Arduino -> ATmega328 usado no kit CDR CAR:
 *   Pino digital 5  (sensor esquerdo) -> PD5
 *   Pino digital 6  (sensor centro)   -> PD6
 *   Pino digital 7  (sensor direito)  -> PD7
 *   Pino digital 10 (PWM motor A)     -> PB2 (OC1B - Timer1)
 *   Pino digital 11 (PWM motor B)     -> PB3 (OC2A - Timer2)
 *   Pino digital 12 (EN motor A)      -> PB4
 *   Pino digital 13 (EN motor B)      -> PB5
 *
 * Compilar (exemplo via avr-gcc para ATmega328 a 16MHz):
 *   avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -o seguidor.elf seguidor.c
 *   avr-objcopy -O ihex seguidor.elf seguidor.hex
 *   avrdude -c arduino -p atmega328p -P COMx -b 115200 -U flash:w:seguidor.hex
 * ========================================================= */

#include <avr/io.h>
#include <stdint.h>

/* ---------- Definicoes de pinos (registradores do ATmega328) ---------- */
#define SENSOR_ESQ_PIN   PD5
#define SENSOR_CEN_PIN   PD6
#define SENSOR_DIR_PIN   PD7

#define MOTOR_A_EN_PIN   PB4   /* direcao motor A (esquerdo) */
#define MOTOR_B_EN_PIN   PB5   /* direcao motor B (direito)  */

/* ---------- Parametros de velocidade (PWM 0-255) ---------- */
/* Ajuste estes valores durante os testes de pista */
static uint8_t VELOC_RETA        = 210;
static uint8_t VELOC_CURVA_LEVE  = 150;
static uint8_t VELOC_CURVA_FORTE = 90;
static uint8_t VELOC_PIVOT       = 60;
static uint8_t VELOC_BUSCA       = 120;

/* Rampa de suavizacao de PWM (evita picos de corrente / trepidacao) */
#define RAMPA_MAX 25

static uint8_t pwmAtualA = 0;
static uint8_t pwmAtualB = 0;
static int8_t  ultimoLado = 0; /* -1 = esquerda, 0 = centro, 1 = direita */

/* ---------- Inicializacao dos pinos digitais dos sensores ---------- */
static void sensores_init(void) {
    /* PD5, PD6, PD7 como entrada */
    DDRD &= (uint8_t)~((1 << SENSOR_ESQ_PIN) | (1 << SENSOR_CEN_PIN) | (1 << SENSOR_DIR_PIN));
}

/* ---------- Inicializacao dos pinos de direcao dos motores (EN) ---------- */
static void motores_dir_init(void) {
    DDRB |= (1 << MOTOR_A_EN_PIN) | (1 << MOTOR_B_EN_PIN);
    /* Motores sempre "para frente": a curva e feita variando o PWM
       relativo entre os dois motores (skid steering), nunca invertendo
       o sentido - isso evita a freada brusca de inverter+zerar juntos. */
    PORTB |= (1 << MOTOR_A_EN_PIN) | (1 << MOTOR_B_EN_PIN);
}

/* ---------- Inicializacao do PWM (Timer1 -> pino 10 / OC1B, PB2) ---------- */
static void pwm_motorA_init(void) {
    DDRB |= (1 << PB2);
    /* Fast PWM 8 bits, non-inverting, prescaler = 64 */
    TCCR1A = (1 << COM1B1) | (1 << WGM10) | (1 << WGM11) & 0; /* configurado abaixo */
    TCCR1A = (1 << COM1B1) | (1 << WGM10);
    TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); /* prescaler 64, modo Fast PWM 8-bit (WGM12+WGM10) */
    OCR1B = 0;
}

/* ---------- Inicializacao do PWM (Timer2 -> pino 11 / OC2A, PB3) ---------- */
static void pwm_motorB_init(void) {
    DDRB |= (1 << PB3);
    /* Fast PWM 8 bits, non-inverting, prescaler = 64 */
    TCCR2A = (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << CS22); /* prescaler 64 */
    OCR2A = 0;
}

static inline void pwm_motorA_set(uint8_t valor) { OCR1B = valor; }
static inline void pwm_motorB_set(uint8_t valor) { OCR2A = valor; }

/* ---------- Leitura digital dos sensores ---------- */
static inline uint8_t ler_sensor_esq(void) { return (PIND & (1 << SENSOR_ESQ_PIN)) ? 1 : 0; }
static inline uint8_t ler_sensor_cen(void) { return (PIND & (1 << SENSOR_CEN_PIN)) ? 1 : 0; }
static inline uint8_t ler_sensor_dir(void) { return (PIND & (1 << SENSOR_DIR_PIN)) ? 1 : 0; }

/* ---------- Rampa de suavizacao de PWM ---------- */
static uint8_t aplicar_rampa(uint8_t atual, uint8_t alvo) {
    if (alvo > atual) {
        uint16_t novo = (uint16_t)atual + RAMPA_MAX;
        return (novo > alvo) ? alvo : (uint8_t)novo;
    } else if (alvo < atual) {
        int16_t novo = (int16_t)atual - RAMPA_MAX;
        return (novo < alvo) ? alvo : (uint8_t)novo;
    }
    return atual;
}

int main(void) {
    sensores_init();
    motores_dir_init();
    pwm_motorA_init();
    pwm_motorB_init();

    for (;;) {
        uint8_t esq = ler_sensor_esq();
        uint8_t cen = ler_sensor_cen();
        uint8_t dir = ler_sensor_dir();

        uint8_t pwmA, pwmB;

        if (cen && !esq && !dir) {
            /* Linha centralizada -> reta, velocidade maxima */
            pwmA = VELOC_RETA;
            pwmB = VELOC_RETA;
            ultimoLado = 0;
        }
        else if (dir && !cen && !esq) {
            /* Curva forte para a direita */
            pwmA = VELOC_CURVA_FORTE;
            pwmB = VELOC_PIVOT;
            ultimoLado = 1;
        }
        else if (esq && !cen && !dir) {
            /* Curva forte para a esquerda */
            pwmA = VELOC_PIVOT;
            pwmB = VELOC_CURVA_FORTE;
            ultimoLado = -1;
        }
        else if (cen && dir && !esq) {
            /* Transicao leve para a direita */
            pwmA = VELOC_RETA;
            pwmB = VELOC_CURVA_LEVE;
            ultimoLado = 1;
        }
        else if (cen && esq && !dir) {
            /* Transicao leve para a esquerda */
            pwmA = VELOC_CURVA_LEVE;
            pwmB = VELOC_RETA;
            ultimoLado = -1;
        }
        else if (esq && cen && dir) {
            /* Cruzamento: atravessa em linha reta */
            pwmA = VELOC_RETA;
            pwmB = VELOC_RETA;
        }
        else {
            /* Linha perdida: busca para o ultimo lado detectado */
            if (ultimoLado >= 0) {
                pwmA = VELOC_BUSCA;
                pwmB = 0;
            } else {
                pwmA = 0;
                pwmB = VELOC_BUSCA;
            }
        }

        pwmAtualA = aplicar_rampa(pwmAtualA, pwmA);
        pwmAtualB = aplicar_rampa(pwmAtualB, pwmB);

        pwm_motorA_set(pwmAtualA);
        pwm_motorB_set(pwmAtualB);
    }

    return 0;
}
