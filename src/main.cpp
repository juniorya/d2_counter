#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

volatile unsigned long pulses = 0; //counter
int pulsePin = 2; // D2 pulse pin IRQ0 

/*******Ethernet W5500*******/
#define WIZ_CS 11
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; //MAC
byte ip[] = { 10 ,3 ,254 ,111 }; // ip static
EthernetServer server(80); //Serever port

/*******SD_CARD*******/
#define SDCARD_CS 4
File root;

/*******store errors in flash*******/
#define error(s) error_P(PSTR(s))

void error_P(const char* str){
  Serial.print(F("error: "));
  Serial.println(str);
  while(1);
}

void tic(){
  pulses++; //Counter of pulses
}

void setup() {
  // put your setup code here, to run once:
  
  pinMode(pulsePin, INPUT);
  attachInterrupt(0, tic, RISING); //interupt edge rising on D2

  Serial.begin(115200); //init Serial 115200
  while (!Serial);

  Serial.println(F("Init W5500 Eth"));
  Ethernet.init(WIZ_CS);
  delay(1000); //time to init
  Ethernet.begin(mac, ip);
  Serial.print(F("My IP: "));
  Serial.println(Ethernet.localIP());
  server.begin();

  if (!SD.begin(SDCARD_CS)){
    error("card.init failed!");
  }

  root = SD.open("/");
}

void loop(){

}