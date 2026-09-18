// Pinos do Motor A
const int IN1 = 8;
const int IN2 = 9;
const int ENA = 5;

// Pinos do Motor B
const int IN3 = 10;
const int IN4 = 11;
const int ENB = 6;

void setup() {
  // Configura os pinos como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {

  // =========================
  // MOTORES LIGADOS
  // =========================

  // Motor A para frente
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Motor B para frente
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // Velocidade máxima
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);

  // Mantém os motores ligados por 5 segundos
  delay(5000);


  // =========================
  // MOTORES PARADOS
  // =========================

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  // Mantém os motores parados por 2 segundos
  delay(2000);

  // O loop começa novamente
}