/*
  Example sketch for the Xbox Wireless Reciver library - developed by Kristian Lauszus
  It supports up to four controllers wirelessly
  For more information see the blog post: http://blog.tkjelectronics.dk/2012/12/xbox-360-receiver-added-to-the-usb-host-library/ or
  send me an e-mail:  kristianl@tkjelectronics.com
*/

#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif
# include <Servo.h>
USB Usb;
XBOXRECV Xbox(&Usb);

// Servos needed to collect the balls
Servo tounge, rArm, lArm;
bool autunomusOn = false;
int toungeVal, rightVal, leftVal;

// Pin configuration for Movement
int lfPin = 7;
int lbPin = 6;
int rfPin = 5;
int rbPin = 4;
int relay = 8;
// Pin configuration for GrayScale Sensors...
int leftSensor = A0;
int rightSensor = A1;


void setup() {
  Serial.begin(115200);
  pinMode(lfPin , OUTPUT);
  pinMode(lbPin , OUTPUT);
  pinMode(rfPin , OUTPUT);
  pinMode(rbPin , OUTPUT);
  tounge.attach(A2);
  rArm.attach(A3);
  lArm.attach(A4);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));

  pinMode(relay, OUTPUT);
}
void loop() {
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 2; i++) {
      if (Xbox.Xbox360Connected[i]) {
        if (Xbox.getButtonPress(R2, i)  && !Xbox.getButtonClick(R1, i)) {
          Serial.print("\t R2: ");
          Serial.print(Xbox.getButtonPress(R2, i));
          Serial.print("\t Without R1: ");
          rf(Xbox.getButtonPress(R2, i));
        }
        if (Xbox.getButtonPress(L2, i) && !Xbox.getButtonClick(L1, i)) {
          Serial.println(Xbox.getButtonPress(L2, i));
          Serial.print("\t L2: ");
          Serial.print(Xbox.getButtonPress(L2, i));
          Serial.print("\t Without L1: ");
          lf(Xbox.getButtonPress(L2, i));
        }
        if (Xbox.getButtonPress(L1, i) && !Xbox.getButtonPress(L2, i)) {
          Serial.println(F("L1"));
          Serial.print("\tWithout L2: ");
          lb();
        }
        if (Xbox.getButtonPress(R1, i) && !Xbox.getButtonPress(R2, i)) {
          Serial.println(F("R1"));
          Serial.print("\tWithout R2: ");
          rb();
        } 
        if(!Xbox.getButtonPress(L1, i) && !Xbox.getButtonPress(L2, i) ) {
          ls();
        }
        if( !Xbox.getButtonPress(R1, i) && !Xbox.getButtonPress(R2, i)) {
          rs();
        }




        if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500 || Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500 || Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500 || Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) {


          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          if (Xbox.getAnalogHat(LeftHatX, i) > 7500 && leftVal > 0) {       // //          Mbylle krahun e majte
            Serial.print(F("LeftHatX: "));
            Serial.print(Xbox.getAnalogHat(LeftHatX, i));
            Serial.print("\t Writing Left Arm Value : ");
            delay(10);
            leftVal -=2;
            Serial.println(leftVal);
            lArm.write(leftVal);

          }
          if (Xbox.getAnalogHat(LeftHatX, i) < -7500 && leftVal < 160) {      // //          Hape krahun e majte
            Serial.print(F("LeftHatX: "));
            Serial.print(Xbox.getAnalogHat(LeftHatX, i));
            Serial.print("\t Writing Left Arm Value : ");
            delay(10); 
            leftVal +=2;
            Serial.println(leftVal);
            lArm.write(leftVal);
          }
          if (Xbox.getAnalogHat(RightHatX, i) > 7500 && rightVal < 175) {     //          Hape krahun e djathe
            Serial.print(F("RightHatX: "));
            Serial.print(Xbox.getAnalogHat(RightHatX, i));
            Serial.print("\t Writing Right Arm Value : ");
            delay(10);
            rightVal +=2;
            Serial.println(rightVal);
            rArm.write(rightVal);

          }
          if (Xbox.getAnalogHat(RightHatX, i) < -7500 && rightVal > 40) {   //          Mbylle krahun e djathe
            Serial.print(F("RightHatX: "));
            Serial.print(Xbox.getAnalogHat(RightHatX, i));
            Serial.print("\t Writing Right Arm Value : ");
            delay(10);
            rightVal -=2;
            Serial.println(rightVal);
            rArm.write(rightVal);
          }
          //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


          if (Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500) {
            Serial.print(F("LeftHatY: "));
            Serial.print(Xbox.getAnalogHat(LeftHatY, i));
            Serial.print("\t");
          }
          if (Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) {
            Serial.print(F("RightHatY: "));
            Serial.print(Xbox.getAnalogHat(RightHatY, i));
          }
          Serial.println();
        }

        if (Xbox.getButtonClick(UP, i)) {
          Xbox.setLedOn(LED1, i);
          Serial.println(F("Up"));
        }
        if (Xbox.getButtonClick(DOWN, i)) {
          Xbox.setLedOn(LED4, i);
          Serial.println(F("Down"));
        }
        if (Xbox.getButtonClick(LEFT, i)) {
          Xbox.setLedOn(LED3, i);
          Serial.println(F("Left"));
        }
        if (Xbox.getButtonClick(RIGHT, i)) {
          Xbox.setLedOn(LED2, i);
          Serial.println(F("Right"));
        }

        if (Xbox.getButtonClick(START, i)) {
          Xbox.setLedMode(ALTERNATING, i);
          Serial.println(F("Start"));
          autunomusOn = true;
          autonomus(analogRead(leftSensor), analogRead(rightSensor));
        }
        if (Xbox.getButtonClick(BACK, i)) {
          Xbox.setLedBlink(ALL, i);
          Serial.println(F("Back"));
        }
        if (Xbox.getButtonClick(L3, i)){
          Serial.println(F("L3"));
          digitalWrite(relay, HIGH);}
        if (Xbox.getButtonClick(R3, i)){ 
          Serial.println(F("R3"));
          digitalWrite(relay, LOW);}

        if (Xbox.getButtonClick(L1, i))
          Serial.println(F("L1"));
        if (Xbox.getButtonClick(R1, i))
          Serial.println(F("R1"));
        if (Xbox.getButtonClick(XBOX, i)) {
          if (Xbox.getBatteryLevel(i) == 1)
            Xbox.setLedOn(LED1, i);
          if (Xbox.getBatteryLevel(i) == 2)
            Xbox.setLedOn(LED2, i);
          if (Xbox.getBatteryLevel(i) == 3)
            Xbox.setLedOn(LED3, i);
          Serial.print(F("Xbox (Battery: "));
          Serial.print(Xbox.getBatteryLevel(i)); // The battery level in the range 0-3
          Serial.println(F(")"));
        }
        if (Xbox.getButtonClick(SYNC, i)) {
          Serial.println(F("Sync"));
        }



        if (Xbox.getButtonPress(Y, i) && toungeVal < 180) {
          Serial.println(F("Y"));
          toungeVal += 2;
          delay(25);
          tounge.write(toungeVal);
          Serial.print(F("Open \t value: "));
          Serial.println(toungeVal);
        }
        if (Xbox.getButtonPress(A, i) && toungeVal > 0) {
          Serial.println(F("A"));
          delay(25);
          toungeVal -= 2;
          tounge.write(toungeVal);
          Serial.print(F("Close \t value: "));
          Serial.println(toungeVal);
        }
        if (Xbox.getButtonClick(B, i)) {
          Serial.println(F("B"));
        }
        if (Xbox.getButtonClick(X, i)) {
          Serial.println(F("X"));
        }
      }
    }
  }
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
  while (autunomusOn) {
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
    //  }
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

