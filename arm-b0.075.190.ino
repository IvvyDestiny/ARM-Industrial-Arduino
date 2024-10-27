#include <Servo.h>

// Pinos para os servos
const int servoMesaPin = 9;
const int servoOmbroPin = 10;
const int servoCotoveloPin = 11;
const int servoGarraPulsoPin = 12;
const int servoGarraPin = 8;

// Pinos para os joysticks e botões
const int joyPinX1 = A0;
const int joyPinY1 = A1;
const int joyPinX2 = A2;
const int joyPinY2 = A3;
const int botaoHomemMortoPin = 2;
const int botaoGarraClosePin = 3;
const int botaoGarraOpenPin = 4;
const int botaoEmergenciaPin = 5;
const int ledVerdePin = 6;
const int ledAmareloPin = 7;
const int ledVermelhoPin = 13;
const int buzzerPin = 14;  // Importante verificar se este pino está correto

// Objetos Servo
Servo servoMesa;
Servo servoOmbro;
Servo servoCotovelo;
Servo servoGarraPulso;
Servo servoGarra;

unsigned long ultimaLeituraGarra;
bool garraTravada = false;

void setup() {
  // Configuração dos pinos dos servos
  servoMesa.attach(servoMesaPin);
  servoOmbro.attach(servoOmbroPin);
  servoCotovelo.attach(servoCotoveloPin);
  servoGarraPulso.attach(servoGarraPulsoPin);
  servoGarra.attach(servoGarraPin);

  // Configuração dos pinos dos joysticks e botões
  pinMode(joyPinX1, INPUT);
  pinMode(joyPinY1, INPUT);
  pinMode(joyPinX2, INPUT);
  pinMode(joyPinY2, INPUT);
  pinMode(botaoHomemMortoPin, INPUT);
  pinMode(botaoGarraClosePin, INPUT);
  pinMode(botaoGarraOpenPin, INPUT);
  pinMode(botaoEmergenciaPin, INPUT);
  pinMode(ledVerdePin, OUTPUT);
  pinMode(ledAmareloPin, OUTPUT);
  pinMode(ledVermelhoPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(ledVerdePin, LOW);
  digitalWrite(ledAmareloPin, LOW);
  digitalWrite(ledVermelhoPin, LOW);
  digitalWrite(buzzerPin, LOW);

  Serial.begin(9600);
}

void loop() {
  int estadoBotaoHomemMorto = digitalRead(botaoHomemMortoPin);
  if (estadoBotaoHomemMorto == HIGH) {
    digitalWrite(ledVerdePin, HIGH);
    controlarServos();
  } else {
    digitalWrite(ledVerdePin, LOW);
    travarGarra();
    delay(30000);  // Bloqueia comandos por 30 segundos
  }

  verificarGarra();
  verificarEmergencia();
  verificarEnergia();
}

void controlarServos() {
  int joyValX1 = analogRead(joyPinX1);
  int joyValY1 = analogRead(joyPinY1);
  int joyValX2 = analogRead(joyPinX2);
  int joyValY2 = analogRead(joyPinY2);

  if (digitalRead(botaoGarraClosePin) == HIGH) {
    servoGarra.write(map(joyValX2, 0, 1023, 0, 180));
    ultimaLeituraGarra = millis();
  } else if (digitalRead(botaoGarraOpenPin) == HIGH) {
    servoGarra.write(map(joyValX1, 0, 1023, 0, 180));
    ultimaLeituraGarra = millis();
  }

  // Controle dos demais servos
  servoMesa.write(map(joyValX1, 0, 1023, 0, 180));
  servoOmbro.write(map(joyValY1, 0, 1023, 0, 180));
  servoCotovelo.write(map(joyValX2, 0, 1023, 0, 180));
  servoGarraPulso.write(map(joyValY2, 0, 1023, 0, 180));
}

void travarGarra() {
  if (!garraTravada) {
    servoGarra.detach();
    garraTravada = true;
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);
  }
}

void verificarGarra() {
  if (millis() - ultimaLeituraGarra > 300) {
    servoGarra.detach();
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);
  }
}

void verificarEmergencia() {
  if (digitalRead(botaoEmergenciaPin) == HIGH) {
    servoMesa.detach();
    servoOmbro.detach();
    servoCotovelo.detach();
    servoGarraPulso.detach();
    servoGarra.detach();
    delay(30000);
    garraTravada = false;
  }
}

void verificarEnergia() {
  int tensao = analogRead(A4); // Leitura do sensor de tensão
  int corrente = analogRead(A5); // Leitura do sensor de corrente

  float tensaoReal = tensao * (5.0 / 1023.0);
  float correnteReal = corrente * (5.0 / 1023.0);

  if (tensaoReal < 5.0) {
    digitalWrite(ledVermelhoPin, HIGH);
    operarModoSeguranca();
  } else {
    digitalWrite(ledVermelhoPin, LOW);
  }
}

void operarModoSeguranca() {
  digitalWrite(ledAmareloPin, HIGH);
  for (int i = 0; i < 4; i++) {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }

  // Operação de um servo por vez
  servoMesa.attach(servoMesaPin);
  delay(100);
  servoOmbro.attach(servoOmbroPin);
  delay(100);
  servoCotovelo.attach(servoCotoveloPin);
  delay(100);
  servoGarraPulso.attach(servoGarraPulsoPin);
  delay(100);
  servoGarra.attach(servoGarraPin);
  delay(100);

  digitalWrite(ledAmareloPin, LOW);
}
