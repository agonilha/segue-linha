// Movimentos iniciais! Testando os motores - Frente...
int motorA_PWM = 10; //Controle de velocidade do motor A (Esquerdo)
int motorB_PWM = 11; //Controle de velocidade do motor B (Direito)

int motorA_EN = 12; //Controle de direção do motor A (Esquerdo)
int motorB_EN = 13; //Controle de direção do motor B (Direito)

int velocidade = 30; //Velocidade de rotação do motor de 0 (velocidade mínima) a 255(velocidade máxima)

void setup() {
    //Configura pinos de saída (OUTPUT)
    pinMode(motorA_PWM, OUTPUT);
    pinMode(motorA_EN, OUTPUT);
    pinMode(motorB_PWM, OUTPUT);
    pinMode(motorB_EN, OUTPUT);
}
void loop() {
    digitalWrite(motorA_EN, HIGH); //Motor Esquerdo - HIGH = Frente - LOW = Ré
    digitalWrite(motorB_EN, HIGH); //Motor Direito - HIGH = Frente - LOW = Ré
    analogWrite(motorA_PWM, velocidade); //PWM do motor esquerdo
    analogWrite(motorB_PWM, velocidade); //PWM do motor direito
}