#include <SPI.h>
#include <string.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(9, 8); // CE, CSN
const byte   addresses [][6] = {"00001", "00002"};  //Setting the two addresses. One for   transmitting and one for receiving
const char* message = "Hello from Ground Station ";

char msgOut[100] = "";
char msgIn[100] = "";
int i = 0;

void setup() {
  radio.begin();   //Starting   the radio communication
  radio.openWritingPipe(addresses[1]);     //Setting   the address at which we will send the data
  radio.openReadingPipe(1, addresses[0]);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_ PA_MIN);   //You can set it as minimum or maximum depending on the distance between the transmitter   and receiver. 
}

void loop() 
{ 
  char msgOut[100] = "";
  delay(500);
  radio.stopListening(); //This sets the module as transmitter
  for (int i = 0; i < strlen(message); i++) {
    msgOut[i] = message[i];
  }

  radio.write(&msgOut, sizeof(msgOut));   //Sending the data
  delay(500);
  
  radio.startListening();                            //This   sets the module as receiver
  while(!radio.available());                         //Looking   for incoming data
  radio.read(&msgIn, sizeof(msgIn)); //Reading   the data
  Serial.println(msgIn);
}
