#include <SoftwareSerial.h>
SoftwareSerial Blue(0, 1); // 0 is RX pin & 1 is TX pin

//const for Sonar
const byte DistTrigger_1 = 19; //Pin # on our Teensy
const byte DistEcho_1 = 18;

const byte DistTrigger_2 = 38;
const byte DistEcho_2 = 37;

const byte DistTrigger_3 = 3;
const byte DistEcho_3 = 4;


void setup() {
  // put your setup code here, to run once:

   //** Serial1 is for Sonar devices **
   Serial1.begin(9600); // First Serial Port
   while (!Serial1);
   
   pinMode(DistTrigger_1, OUTPUT);
   pinMode(DistEcho_1, INPUT);

   pinMode(DistTrigger_2, OUTPUT);
   pinMode(DistEcho_2, INPUT);

   pinMode(DistTrigger_3, OUTPUT);
   pinMode(DistEcho_3, INPUT);

   // ** Serial2 is for Bluetooth device **
   //Serial2.begin(38400); // Default communication rate of the Bluetooth module 2nd Serial Port
   Blue.begin(9600);
   
   delay(100);
}

float readDistanceSensor(byte DistTrigger, byte DistEcho) {
   digitalWrite(DistTrigger, LOW);
   delayMicroseconds(2);
   digitalWrite(DistTrigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(DistTrigger, LOW);
   float duration = pulseIn(DistEcho, HIGH);  // in microseconds
   float distance = duration * 0.0343 / 2.0;  // in centimeters
   return (distance * 0.3937); // cm to in
}

void loop() {
  // Whatever we need to do with bluetooth communication.....
  while(Blue.available() == 0);
  
  // put your main code here, to run repeatedly:
  float distance_1 = readDistanceSensor(DistTrigger_1, DistEcho_1);
  float distance_2 = readDistanceSensor(DistTrigger_2, DistEcho_2);
  float distance_3 = readDistanceSensor(DistTrigger_3, DistEcho_3);
  
  Serial.print("Distance 1 sensor reads "); Serial.print(distance_1); Serial.println(" in.");
  Blue.write("Distance 1 sensor reads "); Blue.write(distance_1); 
  
  Serial.print("Distance 2 sensor reads "); Serial.print(distance_2); Serial.println(" in.");
  Blue.write("Distance 2 sensor reads "); Blue.write(distance_2); 
  
  Serial.print("Distance 3 sensor reads "); Serial.print(distance_3); Serial.println(" in.");
  Blue.write("Distance 3 sensor reads "); Blue.write(distance_3); 

  delay(3000);
  }
  
