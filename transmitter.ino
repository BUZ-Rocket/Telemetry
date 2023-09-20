#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN); // Transmitter RF Power Setting
  radio.stopListening();
}

void loop() {
  //Send message to receiver
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  delay(500);
}
