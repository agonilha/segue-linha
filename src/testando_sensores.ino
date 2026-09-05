//Detectando a linha! Testando o módulo seguidor de linha

int sensordireito = 7; //Pino do sensor TCRT direito
int sensorcentro = 6; //Pino do sensor TCRT central
int sensoresquerdo = 5; //Pino do sensor TCRT esquerdo

void setup() {
    Serial.begin(9600); //Inicializa a comunicação serial
    pinMode(sensordireito, INPUT);
    pinMode(sensorcentro, INPUT);
    pinMode(sensoresquerdo, INPUT);
}

void loop() {
    Serial.print("Sensor Direito:"); //Imprime mensagem "Sensor Direito:" no monitor serial
    Serial.println(digitalRead(sensordireito)); //Imprime a leitura do sensor direito no monitor serial

    Serial.print("Sensor Central:"); //Imprime mensagem "Sensor Central:" no monitor serial
    Serial.println(digitalRead(sensorcentro)); //Imprime a leitura do sensor central no monitor serial
    
    Serial.print("Sensor Esquerdo:"); //Imprime mensagem "Sensor Esquerdo:" no monitor serial
    Serial.println(digitalRead(sensoresquerdo)); //Imprime a leitura do sensor esquerdo no monitor serial
    
    if (digitalRead(sensordireito) == 1) { //Se o sensor direito detectar a linha
        Serial.println("Linha detectada pelo sensor direito");
    }
    
    if (digitalRead(sensorcentro) == 1) { //Se o sensor central detectar a linha
        Serial.println("Linha detectada pelo sensor central");
    }
    
    if (digitalRead(sensoresquerdo) == 1) { //Se o sensor esquerdo detectar a linha
        Serial.println("Linha detectada pelo sensor esquerdo");
    }
    
    Serial.println("--------------------------------------");
    delay(1000);
}