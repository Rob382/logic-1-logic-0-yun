#include <Bridge.h>
#include <BridgeClient.h>
#include <BridgeServer.h>
#include <BridgeSSLClient.h>
#include <BridgeUdp.h>
#include <Console.h>
#include <FileIO.h>
#include <HttpClient.h>
#include <Mailbox.h>
#include <Process.h>
#include <YunClient.h>
#include <YunServer.h>

byte entrada1 = 0;
byte entrada_1_prev = 0;
unsigned long currentMillis = 0;
unsigned long duracion_0_logico = 0;
unsigned long duracion_1_logico = 0;
unsigned long logico_0_largo = 0;
unsigned long logico_1_largo = 0;
unsigned long pulsacion_previa = 0;
byte logico_0_pulso_largo_prev = false;
byte logico_1_pulso_largo_prev = false;

void setup() {
  // put your setup code here, to run once:
Bridge.begin();       //Puente entre el MCU y el MPU.
Console.begin();
  pinMode(entrada1, INPUT);          // set buttonPin as input
  Console.println("Press button");
}

void loop() {
  // put your main code here, to run repeatedly:
currentMillis = millis();

if (currentMillis - pulsacion_previa > 50){
  entrada1 = digitalRead(3);

  if(entrada1 == LOW && entrada_1_prev == HIGH && duracion_1_logico < 2000){
    Console.println("short 1 logico");
    logico_1_pulso_largo_prev = false;
    logico_0_pulso_largo_prev = false;
  }
  if(entrada1 == HIGH && entrada_1_prev == LOW && duracion_0_logico < 2000){
    Console.println("short 0 logico");
    logico_1_pulso_largo_prev = false;
    logico_0_pulso_largo_prev = false;
  }
  
  if(entrada1 == HIGH && entrada_1_prev == LOW){
    logico_1_largo = currentMillis;
    Console.println("1 logico pulsado"); 
    entrada_1_prev = HIGH; 
  }
  
  if(entrada1 == LOW && entrada_1_prev == HIGH){
    logico_0_largo = currentMillis;
    Console.println("0 logico pulsado");  
    entrada_1_prev = LOW;
  }
  
  duracion_1_logico = currentMillis - logico_1_largo;
  duracion_0_logico = currentMillis - logico_0_largo;
  
  if (entrada1 == HIGH && logico_1_pulso_largo_prev == false && duracion_1_logico >= 2000){
    Console.println("1 logico pulsacion larga");
    logico_1_pulso_largo_prev = true;
    logico_0_pulso_largo_prev = false;
  }
  if (entrada1 == LOW && logico_0_pulso_largo_prev == false && duracion_0_logico >= 2000){
    logico_1_pulso_largo_prev = false;
    logico_0_pulso_largo_prev = true;
    Console.println("0 logico pulsacion larga");
  }
  
  pulsacion_previa = currentMillis;
}
}
