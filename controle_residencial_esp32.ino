// ============================================================
// TCC - ENGENHARIA ELÉTRICA
// Controle remoto de quatro relés utilizando ESP32
// Comunicação pela Internet através do Adafruit IO
//
// GPIO25 -> IN1
// GPIO26 -> IN2
// GPIO27 -> IN3
// GPIO32 -> IN4
//
// Módulo de relés testado:
// LOW  = relé acionado
// HIGH = relé desacionado
// ============================================================

#include "AdafruitIO_WiFi.h"

// ============================================================
// 1. CREDENCIAIS
// ============================================================

// Dados da conta Adafruit IO.
#define IO_USERNAME "Inserir ID cadastrado Adafruit"
#define IO_KEY      "Inserir Chave de acesso IO Key Adafruit"

// Dados da rede Wi-Fi.
#define WIFI_SSID   "Nome da minha Rede Wi-Fi"
#define WIFI_PASS   "Senha da minha rede Wi-Fi"

// Cria a conexão entre ESP32, Wi-Fi e Adafruit IO.
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


// ============================================================
// 2. GPIOs DOS QUATRO RELÉS
// ============================================================

const int RELE1 = 25;
const int RELE2 = 26;
const int RELE3 = 27;
const int RELE4 = 32;

// Nosso módulo trabalha com lógica invertida.
const int RELE_LIGADO    = LOW;
const int RELE_DESLIGADO = HIGH;


// ============================================================
// 3. FEEDS DO ADAFRUIT IO
// ============================================================

// IMPORTANTE:
// Confira no Adafruit IO se estas são realmente as Feed Keys.

AdafruitIO_Feed *feedRele1 = io.feed("rele-1");
AdafruitIO_Feed *feedRele2 = io.feed("rele-2");
AdafruitIO_Feed *feedRele3 = io.feed("rele-3");
AdafruitIO_Feed *feedRele4 = io.feed("rele-4");


// ============================================================
// 4. FUNÇÕES QUE RECEBEM OS COMANDOS
// ============================================================

// Esta função é executada quando o feed do Relé 1 recebe
// um novo valor do Adafruit IO.
void comandoRele1(AdafruitIO_Data *data) {

  int comando = data->toInt();

  if (comando == 1) {
    digitalWrite(RELE1, RELE_LIGADO);
    Serial.println("Rele 1 LIGADO pela Internet");
  }
  else {
    digitalWrite(RELE1, RELE_DESLIGADO);
    Serial.println("Rele 1 DESLIGADO pela Internet");
  }
}


// Relé 2
void comandoRele2(AdafruitIO_Data *data) {

  int comando = data->toInt();

  if (comando == 1) {
    digitalWrite(RELE2, RELE_LIGADO);
    Serial.println("Rele 2 LIGADO pela Internet");
  }
  else {
    digitalWrite(RELE2, RELE_DESLIGADO);
    Serial.println("Rele 2 DESLIGADO pela Internet");
  }
}


// Relé 3
void comandoRele3(AdafruitIO_Data *data) {

  int comando = data->toInt();

  if (comando == 1) {
    digitalWrite(RELE3, RELE_LIGADO);
    Serial.println("Rele 3 LIGADO pela Internet");
  }
  else {
    digitalWrite(RELE3, RELE_DESLIGADO);
    Serial.println("Rele 3 DESLIGADO pela Internet");
  }
}


// Relé 4
void comandoRele4(AdafruitIO_Data *data) {

  int comando = data->toInt();

  if (comando == 1) {
    digitalWrite(RELE4, RELE_LIGADO);
    Serial.println("Rele 4 LIGADO pela Internet");
  }
  else {
    digitalWrite(RELE4, RELE_DESLIGADO);
    Serial.println("Rele 4 DESLIGADO pela Internet");
  }
}


// ============================================================
// 5. SETUP
// ============================================================

void setup() {

  Serial.begin(115200);

  // ----------------------------------------------------------
  // Estado inicial dos relés
  // ----------------------------------------------------------

  // Antes de configurar os pinos como saída,
  // testei mantendo todos em nível HIGH.
  // No nosso módulo, HIGH significa relé desacionado.

  digitalWrite(RELE1, RELE_DESLIGADO);
  digitalWrite(RELE2, RELE_DESLIGADO);
  digitalWrite(RELE3, RELE_DESLIGADO);
  digitalWrite(RELE4, RELE_DESLIGADO);

  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);
  pinMode(RELE3, OUTPUT);
  pinMode(RELE4, OUTPUT);

  // Garante novamente que todos iniciem desligados.
  digitalWrite(RELE1, RELE_DESLIGADO);
  digitalWrite(RELE2, RELE_DESLIGADO);
  digitalWrite(RELE3, RELE_DESLIGADO);
  digitalWrite(RELE4, RELE_DESLIGADO);

  Serial.println();
  Serial.println("Sistema iniciado.");
  Serial.println("Todos os reles inicialmente desligados.");


  // ----------------------------------------------------------
  // Associa cada feed à sua função
  // ----------------------------------------------------------

  feedRele1->onMessage(comandoRele1);
  feedRele2->onMessage(comandoRele2);
  feedRele3->onMessage(comandoRele3);
  feedRele4->onMessage(comandoRele4);


  // ----------------------------------------------------------
  // Conexão com o Adafruit IO
  // ----------------------------------------------------------

  Serial.print("Conectando ao Adafruit IO");

  io.connect();

  // Aguarda a conexão.
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();

  // Mostra no Monitor Serial o estado da conexão.
  Serial.println(io.statusText());

  Serial.println("ESP32 conectado ao Adafruit IO.");
  Serial.println("Sistema pronto para receber comandos.");

  // Solicita ao Adafruit IO o último valor existente
  // em cada feed.
  feedRele1->get();
  feedRele2->get();
  feedRele3->get();
  feedRele4->get();
}


// ============================================================
// 6. LOOP
// ============================================================

void loop() {

  // Esta é a principal função do Adafruit IO durante
  // a execução do programa.
  //
  // Ela mantém a comunicação ativa e verifica se chegaram
  // novos comandos dos feeds.
  //
  // Por isso precisa ser executada continuamente.
  io.run();
}
