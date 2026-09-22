// Pinos do Motor A
const int MOTOR_A_PWM = 5; // Pino PWM do Motor A
const int MOTOR_A_DIR_1 = 8; // Pino de direção 1 do Motor A
const int MOTOR_A_DIR_2 = 9; // Pino de direção 2 do Motor A

// Pinos do Motor B
const int MOTOR_B_PWM = 6; // Pino PWM do Motor B
const int MOTOR_B_DIR_1 = 10; // Pino de direção 1 do Motor B
const int MOTOR_B_DIR_2 = 11; // Pino de direção 2 do Motor B

// Pinos do Sensor TCRT5000
const int SENSOR_DIREITO = 2; // Pino do sensor TCRT direito
const int SENSOR_CENTRO = 3; // Pino do sensor TCRT central
const int SENSOR_ESQUERDO = 4; // Pino do sensor TCRT esquerdo

int leituraDireito;
int leituraCentro;
int leituraEsquerdo;

void setup() {
    // Configura os pinos dos motores como saída
    pinMode(MOTOR_A_DIR_1, OUTPUT);
    pinMode(MOTOR_A_DIR_2, OUTPUT);
    pinMode(MOTOR_A_PWM, OUTPUT);
    pinMode(MOTOR_B_DIR_1, OUTPUT);
    pinMode(MOTOR_B_DIR_2, OUTPUT);
    pinMode(MOTOR_B_PWM, OUTPUT);

    // Configura os pinos dos sensores como entrada
    pinMode(SENSOR_DIREITO, INPUT);
    pinMode(SENSOR_CENTRO, INPUT);
    pinMode(SENSOR_ESQUERDO, INPUT);
}

void loop() {
    leitura(); // Chama a função de leitura dos sensores
    seguidor(); // Chama a função seguidor de linha
}

void leitura() {
    leituraDireito = digitalRead(SENSOR_DIREITO); // Leitura do sensor direito
    leituraCentro = digitalRead(SENSOR_CENTRO); // Leitura do sensor central
    leituraEsquerdo = digitalRead(SENSOR_ESQUERDO); // Leitura do sensor esquerdo
}

void seguidor() {
    // Linha no meio ou em todos os sensores
    if (leituraCentro == 1) {
        frente(130);
    } else if (leituraDireito == 1) {
        direita(130);
    } else if (leituraEsquerdo == 1) {
        esquerda(130);
    } else if (leituraDireito == 1 && leituraCentro == 0 && leituraEsquerdo == 1) {
        direita(130);
    }
}

void frente(int velocidade) {
    // Motor A para frente
    digitalWrite(MOTOR_A_DIR_1, HIGH);
    digitalWrite(MOTOR_A_DIR_2, LOW);
    analogWrite(MOTOR_A_PWM, velocidade);

    // Motor B para frente
    digitalWrite(MOTOR_B_DIR_1, HIGH);
    digitalWrite(MOTOR_B_DIR_2, LOW);
    analogWrite(MOTOR_B_PWM, velocidade);
}
void direita(int velocidade) {
    // Motor A parado
    digitalWrite(MOTOR_A_DIR_1, LOW);
    digitalWrite(MOTOR_A_DIR_2, LOW);
    analogWrite(MOTOR_A_PWM, 0);

    // Motor B para frente
    digitalWrite(MOTOR_B_DIR_1, HIGH);
    digitalWrite(MOTOR_B_DIR_2, LOW);
    analogWrite(MOTOR_B_PWM, velocidade);

}
void esquerda(int velocidade) {
    // Motor A para frente
    digitalWrite(MOTOR_A_DIR_1, HIGH);
    digitalWrite(MOTOR_A_DIR_2, LOW);
    analogWrite(MOTOR_A_PWM, velocidade);

    // Motor B parado
    digitalWrite(MOTOR_B_DIR_1, LOW);
    digitalWrite(MOTOR_B_DIR_2, LOW);
    analogWrite(MOTOR_B_PWM, 0);
}