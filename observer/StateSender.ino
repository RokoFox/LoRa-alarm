#include <SPI.h>
#include <LoRa.h>

short counter = 0;
bool implicitHeader = false;
bool state = true;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(868300)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
  LoRa.setTxPower(13);
  LoRa.enableCrc();
  LoRa.setCodingRate4(8);
  
  implicitHeader = false;
  LoRa.setSignalBandwidth(125E3);
  LoRa.setSpreadingFactor(10);
  
  
  //LoRa.setFrequency(868300);
  
}

void sendState() {
  counter++;
  
  LoRa.beginPacket(implicitHeader);
  LoRa.write(*(((void*) &counter) + 1));
  LoRa.write(*((void*) &counter));
  LoRa.write(state ? 0xff : 0x00);
  LoRa.endPacket();
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  sendState();

  //delay(30000);
  delay(5000);
}
