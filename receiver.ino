#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0, address); // set the address
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening(); //set module as receiver
}

void loop() {
  //Read the data if available in buffer
  Serial.println(radio.available());
  if (radio.available()){
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}
