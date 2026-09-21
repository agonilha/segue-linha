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

<<<<<<< HEAD
int leituraDireito;
int leituraCentro;
int leituraEsquerdo;

=======
>>>>>>> 1a87191a3af37c85ca1802db13b6a5a88d9c0153
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

<<<<<<< HEAD
void leitura() {
=======
leitura() {
>>>>>>> 1a87191a3af37c85ca1802db13b6a5a88d9c0153
    leituraDireito = digitalRead(SENSOR_DIREITO); // Leitura do sensor direito
    leituraCentro = digitalRead(SENSOR_CENTRO); // Leitura do sensor central
    leituraEsquerdo = digitalRead(SENSOR_ESQUERDO); // Leitura do sensor esquerdo
}

void seguidor() {
    // Linha no meio ou em todos os sensores
<<<<<<< HEAD
    if (((leituraDireito == 0) && (leituraCentro == 1) && (leituraEsquerdo == 0)) ||
        ((leituraDireito == 1) && (leituraCentro == 1) && (leituraEsquerdo == 1)) ||
        ((leituraDireito == 0) && (leituraCentro == 1) && (leituraEsquerdo == 1)) ||
        ((leituraDireito == 1) && (leituraCentro == 1) && (leituraEsquerdo == 0))) {
=======
    if (((leituraDireito == 0) && (leituraCentro == 1) && (leituraEsquerdo == 0)) || ((leituraDireito == 1) && (leituraCentro == 1) && (leituraEsquerdo == 1))) {
>>>>>>> 1a87191a3af37c85ca1802db13b6a5a88d9c0153
        frente();
    }

    // Linha na direita ou no centro e direita
<<<<<<< HEAD
    if (((leituraDireito == 1) && (leituraCentro == 0) && (leituraEsquerdo == 0))) {
=======
    if (((leituraDireito == 1) && (leituraCentro == 0) && (leituraEsquerdo == 0)) || ((leituraDireito == 1) && (leituraCentro == 1) && (leituraEsquerdo == 0))) {
>>>>>>> 1a87191a3af37c85ca1802db13b6a5a88d9c0153
        direita();
    }

    // Linha na esquerda ou no centro e esquerda
<<<<<<< HEAD
    if (((leituraDireito == 0) && (leituraCentro == 0) && (leituraEsquerdo == 1))) {
=======
    if (((leituraDireito == 0) && (leituraCentro == 0) && (leituraEsquerdo == 1)) || ((leituraDireito == 0) && (leituraCentro == 1) && (leituraEsquerdo == 1))) {
>>>>>>> 1a87191a3af37c85ca1802db13b6a5a88d9c0153
        esquerda();
    }

    // Se detectar apenas os sensores externos, ele vai para a direita
    if ((leituraDireito == 1) && (leituraCentro == 0) && (leituraEsquerdo == 1)) {
        direita();
    }
<<<<<<< HEAD
}

void frente() {
    // Motor A para frente
    digitalWrite(MOTOR_A_DIR_1, HIGH);
    digitalWrite(MOTOR_A_DIR_2, LOW);
    analogWrite(MOTOR_A_PWM, 255);

    // Motor B para frente
    digitalWrite(MOTOR_B_DIR_1, HIGH);
    digitalWrite(MOTOR_B_DIR_2, LOW);
    analogWrite(MOTOR_B_PWM, 255);
}
void direita() {
    // Motor A parado
    digitalWrite(MOTOR_A_DIR_1, LOW);
    digitalWrite(MOTOR_A_DIR_2, LOW);
    analogWrite(MOTOR_A_PWM, 0);

    // Motor B para frente
    digitalWrite(MOTOR_B_DIR_1, HIGH);
    digitalWrite(MOTOR_B_DIR_2, LOW);
    analogWrite(MOTOR_B_PWM, 255);

}
void esquerda() {
    // Motor A para frente
    digitalWrite(MOTOR_A_DIR_1, HIGH);
    digitalWrite(MOTOR_A_DIR_2, LOW);
    analogWrite(MOTOR_A_PWM, 255);
    
    // Motor B parado
    digitalWrite(MOTOR_B_DIR_1, LOW);
    digitalWrite(MOTOR_B_DIR_2, LOW);
    analogWrite(MOTOR_B_PWM, 0);
=======
>>>>>>> 1a87191a3af37c85ca1802db13b6a5a88d9c0153
}