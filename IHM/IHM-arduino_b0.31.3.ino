// Código beta para a IHM utilizando Arduino
// Arduíno dedicado para leitura e controle da IHM, transmissão de dados analógicos.
// Atenção!!! Este código é beta e não foi testado fisicamente pela falta de equipamentos; adicione nos comentários suas opiniões, correções e implementações, podendo ajudar a implementar o código.

/* Componentes necessários:
 * - 1 x Arduino (Uno, Mega, etc.)
 * - 1 x LCD 16x2 com interface I2C ou pinos digitais
 * - 5 x Servos (SG90 ou similares)
 * - Jumpers (cabos de conexão)
 * - Protoboard
 * - Potenciômetro para ajustar o contraste do LCD (opcional, se não usar I2C)
 */

// Bibliotecas
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// Definições de pinos
#define PINO_LCD_RS 2
#define PINO_LCD_EN 3
#define PINO_LCD_D4 4
#define PINO_LCD_D5 5
#define PINO_LCD_D6 6
#define PINO_LCD_D7 7

// Definições de servos
#define NUM_SERVOS 5
#define PINO_SERVO_1 8
#define PINO_SERVO_2 9
#define PINO_SERVO_3 10
#define PINO_SERVO_4 11
#define PINO_SERVO_5 12

// Definições de memória
#define MEMORIA_MAX 3
#define NUM_PASSOS 10

// Estrutura de dados para movimento
struct Movimento {
  int servo1;
  int servo2;
  int servo3;
  int servo4;
  int servo5;
};

// Variáveis globais
Movimento memoria[MEMORIA_MAX][NUM_PASSOS];
int memoriaSel = 0;
char tecla;

// Inicialização do LCD
LiquidCrystal lcd(PINO_LCD_RS, PINO_LCD_EN, PINO_LCD_D4, PINO_LCD_D5, PINO_LCD_D6, PINO_LCD_D7);

// Função setup
void setup() {
  // Inicializa o LCD
  lcd.begin(16, 2);
  lcd.print("Iniciando...");

  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Inicializa os servos
  for (int i = 0; i < NUM_SERVOS; i++) {
    pinMode(PINO_SERVO_1 + i, OUTPUT);
  }

  // Limpa a memória
  for (int i = 0; i < MEMORIA_MAX; i++) {
    for (int j = 0; j < NUM_PASSOS; j++) {
      memoria[i][j].servo1 = 0;
      memoria[i][j].servo2 = 0;
      memoria[i][j].servo3 = 0;
      memoria[i][j].servo4 = 0;
      memoria[i][j].servo5 = 0;
    }
  }

  lcd.clear();
  lcd.print("Pronto!");
  delay(1000);
  lcd.clear();
}

// Função loop
void loop() {
  // Verifica se há dados disponíveis na serial
  if (Serial.available() > 0) {
    tecla = Serial.read();

    if (tecla >= '1' && tecla <= '3') { 
      memoriaSel = tecla - '1'; 
      break;
    }

    for (int i = 0; i < NUM_PASSOS; i++) {
      memoria[memoriaSel][i].servo1 = 0;
      memoria[memoriaSel][i].servo2 = 0;
      memoria[memoriaSel][i].servo3 = 0;
      memoria[memoriaSel][i].servo4 = 0;
      memoria[memoriaSel][i].servo5 = 0;
    }

    lcd.setCursor(0, 0);
    lcd.print("Memoria limpa!");
    delay(1000);
    lcd.clear();
  }
}

// Função para ler ângulo
int lerAngulo() {
  int angulo = 0;
  unsigned long startTime = millis(); // Marca o tempo de início
  while (true) {
    if (Serial.available() > 0) {
      angulo = Serial.parseInt();
      if (angulo >= 0 && angulo <= 180) {
        break;
      }
    }
    // Adiciona um timeout de 5 segundos
    if (millis() - startTime > 5000) {
      break;
    }
  }
  return angulo;
}
