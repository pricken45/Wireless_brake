#include <Servo.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

Servo servo;

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  servo.attach(9);
}

void loop() {
  if (radio.available()) {
    int n;
    radio.read(&n, sizeof(n));
    Serial.println(n);
    servo.write(map(n, 0, 1023, 0, 170));
  }
}