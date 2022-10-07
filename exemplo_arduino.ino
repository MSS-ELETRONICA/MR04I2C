#include "Arduino.h"
#include "PCF8574.h"

//PARA O ARDUINO UNO SOMENTE OS PINOS 1 E 2 TEM COMO ATIVAR A INTERRUPÇÃO
#define ARDUINO_UNO_INTERRUPTED_PIN 2 //SÓ NECESSÁRIO SE FOR USAR OS 4 PINOS DE I/O LIVRES COMO ENTRADA

//FUNÇÃO PARA A INTERRUPCAO
void keyPressedOnPCF8574();//SÓ NECESSÁRIO SE FOR USAR OS 4 PINOS DE I/O LIVRES COMO ENTRADA

//O ENDEREÇO PADRÃO DE FÁBRICA DO MÓDULO RELÊ I2C MR04I2C É 0x27 (VALOR EM HEXADECIMAL)
PCF8574 pcf8574(0x27, ARDUINO_UNO_INTERRUPTED_PIN, keyPressedOnPCF8574);
//PCF8574 pcf8574(0x27);//SE NÃO FOR UTILIZAR OS PINOS DE I/O COMO ENTRADA OU NÃO DESEJAR USAR A INTERRUPÇÃO, USE ESSA LINHA E COMENTE A ANTERIOR

//ARMAZENA O ESTADO DO PINO DE I/O CONFIGURADO COMO ENTRADA
uint8_t val0 = 0;
uint8_t val1 = 0;
uint8_t val2 = 0;
uint8_t val3 = 0;

void setup(){
  Serial.begin(9600);//INICIALIZA A PORTA SERIAL EM 9600

  pcf8574.pinMode(P7, INPUT_PULLUP);//SÓ NECESSÁRIO SE FOR USAR OS 4 PINOS DE I/O LIVRES COMO ENTRADA
  pcf8574.pinMode(P6, INPUT_PULLUP);//SÓ NECESSÁRIO SE FOR USAR OS 4 PINOS DE I/O LIVRES COMO ENTRADA
  pcf8574.pinMode(P5, INPUT_PULLUP);//SÓ NECESSÁRIO SE FOR USAR OS 4 PINOS DE I/O LIVRES COMO ENTRADA
  pcf8574.pinMode(P4, INPUT_PULLUP);//SÓ NECESSÁRIO SE FOR USAR OS 4 PINOS DE I/O LIVRES COMO ENTRADA

  pcf8574.pinMode(P0, OUTPUT);//P0 ACIONA O RELÊ 01
  pcf8574.pinMode(P1, OUTPUT);//P0 ACIONA O RELÊ 02
  pcf8574.pinMode(P2, OUTPUT);//P0 ACIONA O RELÊ 03
  pcf8574.pinMode(P3, OUTPUT);//P0 ACIONA O RELÊ 04

  pcf8574.begin();
}

bool keyPressed = false;//INDICA QUE TEVE UM PINO DE I/O CONFIGURADO COMO ENTRADA QUE FOI ACIONADO

void loop(){
  //LIGA CADA UM DOS RELÊS EM SEQUÊNCIA E MANTÉM LIGADO POR 0.5S
  pcf8574.digitalWrite(P0, 1);
  pcf8574.digitalWrite(P1, 0);
  pcf8574.digitalWrite(P2, 0);
  pcf8574.digitalWrite(P3, 0);
  delay(500);
  pcf8574.digitalWrite(P0, 0);
  pcf8574.digitalWrite(P1, 1);
  pcf8574.digitalWrite(P2, 0);
  pcf8574.digitalWrite(P3, 0);
  delay(500);
  pcf8574.digitalWrite(P0, 0);
  pcf8574.digitalWrite(P1, 0);
  pcf8574.digitalWrite(P2, 1);
  pcf8574.digitalWrite(P3, 0);
  delay(500);
  pcf8574.digitalWrite(P0, 0);
  pcf8574.digitalWrite(P1, 0);
  pcf8574.digitalWrite(P2, 0);
  pcf8574.digitalWrite(P3, 1);
  delay(500);

  //LIGA TODOS OS RELÊS POR 1S
  pcf8574.digitalWrite(P0, 1);
  pcf8574.digitalWrite(P1, 1);
  pcf8574.digitalWrite(P2, 1);
  pcf8574.digitalWrite(P3, 1);
  delay(1000);

  //DESLIGA TODOS OS RELÊS POR 2S
  pcf8574.digitalWrite(P0, 0);
  pcf8574.digitalWrite(P1, 0);
  pcf8574.digitalWrite(P2, 0);
  pcf8574.digitalWrite(P3, 0);
  delay(2000);

  //SE NÃO FOR USAR OS PINOS DE I/O COMO ENTRADA E USAR INTERRUPÇÃO, PODERÁ REMOVER OU COMENTAR ESSA PARTE DO CÓDIGO
  //A INTERRUPÇÃO É ACIONADA SEMPRE QUE QUALQUER DAS ENTRADA MUDA DE NÍVEL LÓGICO
  if (keyPressed){
    val0 = pcf8574.digitalRead(P4);//LÊ O ESTADO DE CADA UM DOS PINOS DE I/O CONFIGURADOS COMO ENTRADA
    val1 = pcf8574.digitalRead(P5);
    val2 = pcf8574.digitalRead(P6);
    val3 = pcf8574.digitalRead(P7);
    
    //EXIBE OS VALORES NA PORTA SERIAL
    Serial.print("P4 ");
    Serial.print(val0);
    Serial.print(" P5 ");
    Serial.print(val1);
    Serial.print(" P6 ");
    Serial.print(val2);
    Serial.print(" P7 ");
    Serial.println(val3);
    keyPressed= false;
  }
}

void keyPressedOnPCF8574(){
  //CHAMADA DA INTERRUPÇÃO QUANDO ALGUM DOS PINOS CONFIGURADOS COMO ENTRADA SÃO ACIONADOS
  //NÃO USAR COMANDOS COMO SERIAL READ OU WRITE AQUI DENTRO, FUNÇÃO DEBUG DA BIBLIOTECA PCF DESATIVADA
   keyPressed = true;//INDICA O ACIONAMENTO DE UMA TECLA, SEJA QUAL FOR.
}
