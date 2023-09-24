#include <SPI.h>
#include <string.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(9, 8); // CE, CSN
const byte   addresses [][6] = {"00001", "00002"};  //Setting the two addresses. One for   transmitting and one for receiving
char msgOut[100] = "";
char msgIn[100] = "";
int i = 0;

void setup() {
  radio.begin();   //Starting   the radio communication
  radio.openWritingPipe(addresses[1]);     //Setting   the address at which we will send the data
  radio.openReadingPipe(1, addresses[0]);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);   //You can set it as minimum or maximum depending on the distance between the transmitter   and receiver. 
}

void loop() 
{ 
  delay(5);
  radio.stopListening(); //This sets the module as transmitter
  const char* a = "Hello from Ground Station ";
  for (int i = 0; i < strlen(a); i++) {
    msgOut[i] = a[i];
  }

  radio.write(&msgOut, sizeof(msgOut));   //Sending the data
  delay(5);
  
  radio.startListening();                            //This   sets the module as receiver
  while(!radio.available());                         //Looking   for incoming data
  radio.read(&msgIn, sizeof(msgIn)); //Reading   the data
  Serial.println(msgIn);
}
