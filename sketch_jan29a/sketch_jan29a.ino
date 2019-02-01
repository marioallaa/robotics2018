#include <hcsr04.h>

// defines pins numbers
const int trigPin = 10;
const int echoPin = 9;
// defines variables
long duration;
int distance;

int fire = 8, bum = 9, light = 10;

int rSensor = A3;
int lSensor = A2;
bool autonomusOn = false;
// L298 Controller 
int rfPin = 4;
int rbPin = 5;
int lfPin = 6;
int lbPin = 7;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(rfPin, OUTPUT);
pinMode(rbPin, OUTPUT);
pinMode(lfPin, OUTPUT);
pinMode(lbPin, OUTPUT);
pinMode(fire, OUTPUT);
pinMode(bum, OUTPUT);
pinMode(light, OUTPUT);
pinMode(rSensor, INPUT);
pinMode(lSensor, INPUT);

pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // put your main code here, to run repeatedly:
autonomusOn = true;

autonomus(analogRead(lSensor), 0);


// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("\n\tDistance: ");
Serial.println(distance);
}



void rs() {
  analogWrite(rfPin, 0);
  analogWrite(rbPin, 0);
}
void ls() {
  analogWrite(lfPin, 0);
  analogWrite(lbPin, 0);
}
void rf(int v) {
  analogWrite(rfPin, 255);
  analogWrite(rbPin, 0);
  Serial.print(F("Right Forward !! \t\n "));
}
void rb() {
  analogWrite(rfPin, 0);
  analogWrite(rbPin, 255);
  Serial.print(F("Right Backwards !! \t\n "));
}
void lf(int v) {
  analogWrite(lfPin, 255);
  analogWrite(lbPin, 0);
  Serial.print(F("Left Forward !! \t\n "));
}
void lb() {
  analogWrite(lfPin, 0);
  analogWrite(lbPin, 255);
  Serial.print(F("Left Backwards !! \t\n "));
}


void autonomus(int lsVal, int rsVal) {
  int keyVal = 350; // Key Value for the given color...
  while (autonomusOn) {
    
  Serial.print(F("\t\n\t\t\t\tRight Value:\t "));
  Serial.print(analogRead(rSensor));
  Serial.print(F("\n\t\t\tL\teft Value: \t "));
  Serial.print(lSensor);
  Serial.print("\n");
  delay(250);
    if (lsVal < keyVal) { // Roboti ka ecur shum nga ana e majte
      lb();
      rf(255);   // Kthehu djathtas
    }
    if (rsVal < keyVal) { // Roboti ka ecur shum nga ana e djathe
      rb();
      lf(255);   // kthehu majtas
    }
    //  if (dist < 10){  // Roboti ka me pak se 10 cm hapsire perpara tij
    //    s(); // Ndalo!!!!!!!!!!!
    if (rsVal < keyVal && lsVal < keyVal) {
      ls();
      rs();
    }

    else {        // ne te kundert ec drejt...
      rf(255);
      lf(255);
    }
  }
  
  for (int p = 0; p < 10; p ++) {
    rb();
    lb();
    delay(250);
    lf(250);
    rf(250);
    delay(250);
  }

}

