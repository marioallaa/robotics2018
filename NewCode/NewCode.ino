/*
  Example sketch for the Xbox Wireless Reciver library - developed by Kristian Lauszus
  It supports up to four controllers wirelessly
  For more information see the blog post: http://blog.tkjelectronics.dk/2012/12/xbox-360-receiver-added-to-the-usb-host-library/ or
  send me an e-mail:  kristianl@tkjelectronics.com
*/

#include <XBOXRECV.h>
#include <Servo.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
XBOXRECV Xbox(&Usb);
Servo lArm, rArm, mArm;
int lArmVal, rArmVal, mArmVal;
bool fireing = false, bumming = false, autonomusOn = false;
int fire = 8, Speed = 2, light = 2;
int rSensor = A8;
int lSensor = A9;
int speedval = 230;
// L298 Controller
int rfPin = 41;
int rbPin = 43;
int lfPin = 45;
int lbPin = 47;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial);
  pinMode(rfPin, OUTPUT);
  pinMode(rbPin, OUTPUT);
  pinMode(lfPin, OUTPUT);
  pinMode(lbPin, OUTPUT);
  pinMode(fire, OUTPUT);
  pinMode(Speed, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(rSensor, INPUT);
  pinMode(lSensor, INPUT);
  rArm.attach(A4);
  lArm.attach(A3);
  mArm.attach(A2);

#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
}
void loop() {
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 1; i++) {
      if (Xbox.Xbox360Connected[i]) {
        analogWrite(Speed, speedval);
        if (Xbox.getButtonPress(L2, i) > 150 && !Xbox.getButtonPress(L1, i)) {
          Serial.print("\t\t Without L1 \t");
          lf();

        } else if (Xbox.getButtonPress(L1, i) && !Xbox.getButtonPress(L2, i)) {
          Serial.print("\t\tL1 Without L2 \t");
          lb();

        } else {
          ls();
        }

        if (Xbox.getButtonPress(R2, i) > 150 && !Xbox.getButtonPress(R1, i)) {
          Serial.print("\t\tR2 Without R1\t");

          rf();
        } else if (Xbox.getButtonPress(R1, i) && !Xbox.getButtonPress(R2, i) ) {
          Serial.print("\t\tR1 Without R2 \t");
          rb();
        } else {
          rs();
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (Xbox.getAnalogHat(LeftHatX, i) > 9000 && lArmVal > 15) {       // //          Mbylle krahun e majte
          Serial.print(F("LeftHatX: "));
          Serial.print(Xbox.getAnalogHat(LeftHatX, i));
          Serial.print("\t Writing Left Arm Value : ");
          delay(10);
          lArmVal -= 2;
          Serial.println(lArmVal);
          lArm.write(lArmVal);

        }
        if (Xbox.getAnalogHat(LeftHatX, i) < -9000 && lArmVal < 180) {      // //          Hape krahun e majte
          Serial.print(F("LeftHatX: "));
          Serial.print(Xbox.getAnalogHat(LeftHatX, i));
          Serial.print("\t Writing Left Arm Value : ");
          delay(10);
          lArmVal += 2;
          Serial.println(lArmVal);
          lArm.write(lArmVal);
        }
        if (Xbox.getAnalogHat(RightHatX, i) > 9000 && rArmVal > 0) {     //          Hape krahun e djathe
          Serial.print(F("RightHatX: "));
          Serial.print(Xbox.getAnalogHat(RightHatX, i));
          Serial.print("\t Writing Right Arm Value : ");
          delay(10);
          rArmVal -= 5;
          Serial.println(rArmVal);
          rArm.write(rArmVal);

        }
        if (Xbox.getAnalogHat(RightHatX, i) < -9000 && rArmVal < 135) {   //          Mbylle krahun e djathe
          Serial.print(F("RightHatX: "));
          Serial.print(Xbox.getAnalogHat(RightHatX, i));
          Serial.print("\t Writing Right Arm Value : ");
          delay(10);
          rArmVal += 5;
          Serial.println(rArmVal);
          rArm.write(rArmVal);
        }
        if (Xbox.getAnalogHat(RightHatY, i) > 9000 && speedval > 100) {     //          Ule Shpejtesine
          Serial.print(F("RightHatX: "));
          Serial.print(Xbox.getAnalogHat(RightHatX, i));
          Serial.print("\t Lowering Speed : ");
          delay(10);
          speedval -= 1;
          analogWrite(Speed, speedval);
          Serial.println(speedval);

        }
        if (Xbox.getAnalogHat(RightHatY, i) < -9000 && speedval < 255) {   //          Ngreje Shpejtesine
          Serial.print(F("RightHatX: "));
          Serial.print(Xbox.getAnalogHat(RightHatX, i));
          Serial.print("\t Rissing Speed : ");
          delay(10);
          speedval += 1;
          Serial.println(speedval);
          analogWrite(Speed, speedval);
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
          autonomusOn = true;
          autonomus();
        }
        if (Xbox.getButtonClick(BACK, i)) {
          Xbox.setLedBlink(ALL, i);
          Serial.println(F("Back"));
        }
      }
      if (Xbox.getButtonClick(L3, i)) {
        Serial.println(F("\n\t\t Fire: "));
        Serial.print(fireing);
        if (fireing) {
          digitalWrite(fire, LOW);
          fireing = false;
        }
        else {
          digitalWrite(fire, HIGH);
          fireing = true;
        }
      }
      if (!Xbox.getButtonPress(BACK, i) && autonomusOn) {
        autonomus();
      } else if (Xbox.getButtonPress(BACK, i)) {
        autonomusOn = false;
        Serial.println(F("\n\t\t\t Not in Autonomus ANYMORE!!!! \n"));
      }

      if (Xbox.getButtonClick(XBOX, i)) {
        Xbox.setLedMode(ROTATING, i);
        Serial.print(F("Xbox (Battery: "));
        Serial.print(Xbox.getBatteryLevel(i));
        Serial.println(F(")"));
        if (Xbox.getBatteryLevel(i) == 1)
          Xbox.setLedOn(LED1, i);
        if (Xbox.getBatteryLevel(i) == 2)
          Xbox.setLedOn(LED2, i);
        if (Xbox.getBatteryLevel(i) == 3)
          Xbox.setLedOn(LED3, i);
        Serial.print(F("Xbox (Battery: "));

      }
      if (Xbox.getButtonClick(SYNC, i)) {
        Serial.println(F("Sync"));
      }

      if (Xbox.getButtonPress(Y, i) && mArmVal < 260) {
        mArmVal += 2;
        delay(10);
        Serial.println("\t\t Closing mArm, \t Value: ");
        Serial.println(mArmVal);
        mArm.write(mArmVal);

      }
      if (Xbox.getButtonPress(A, i) && mArmVal > 0) {
        mArmVal -= 2;
        delay(10);
        Serial.println("\t\t Opening mArm, \t Value: ");
        Serial.println(mArmVal);
        mArm.write(mArmVal);
      }

      if (Xbox.getButtonClick(B, i)) {
        Serial.println(F("B"));
        rArm.write(0);
        delay(150);
        lArm.write(180);
      }
      if (Xbox.getButtonClick(X, i)) {
        Serial.println(F("X"));
        lArm.write(15);
        delay(150);
        rArm.write(135);
      }
    }
  }
}




void rs() {
  digitalWrite(rfPin, LOW);
  digitalWrite(rbPin, LOW);
}
void ls() {
  digitalWrite(lfPin, LOW);
  digitalWrite(lbPin, LOW);
}
void rf() {
  digitalWrite(rfPin, HIGH);
  digitalWrite(rbPin, LOW);
  Serial.print(F("Right Forward !! \t\t Value: "));
}
void rb() {
  digitalWrite(rfPin, LOW);
  digitalWrite(rbPin, HIGH);
  Serial.print(F("Right Backwards !! \t\n "));
}
void lf() {
  digitalWrite(lfPin, HIGH);
  digitalWrite(lbPin, LOW);
  Serial.print(F("Left Forward !! \t\t Value: "));
  Serial.println("\n");
}
void lb() {
  digitalWrite(lfPin, LOW);
  digitalWrite(lbPin, HIGH);
  Serial.println(F("Left Backwards !! \t\n "));
}


void autonomus() {
  int oldRsVal, oldLsVal; // Key Value for the given color...

  int lsVal = analogRead(lSensor);
  int rsVal = analogRead(rSensor);
  oldRsVal = 300;
  oldLsVal = 300;
  lsVal = analogRead(lSensor);
  rsVal = analogRead(rSensor);
  delay(50);
  Serial.print(F("\t\n\t\t\t\tRight Value:\t "));
  Serial.print(rsVal);
  Serial.print(F("\n\t\t\t\tLeft Value: \t "));
  Serial.print(lsVal);
  Serial.print("\n");
  if (lsVal > oldLsVal && rsVal < oldRsVal) { // Roboti ka ecur shum nga ana e majte

    for (int i = 0; i < 5; i++) {
      ls();
      rb();   // Kthehu djathtas
    }
    Serial.print(F("Roboti ka ecur shum nga ana e majte !! \t\n "));

  } else if (rsVal > oldRsVal && lsVal < oldLsVal) { // Roboti ka ecur shum nga ana e djathe

    for (int i = 0; i < 5; i++) {
      rs();
      lb();   // kthehu majtas
    }
    Serial.print(F("Roboti ka ecur shum nga ana e djathe !! \t\n "));

  } else if (rsVal > oldRsVal && lsVal > oldLsVal) {
    autonomusOn = false;
    ls();
    rs();

    Serial.print(F("\t\t\t\tStop !! \t\n "));
  } else {

    for (int i = 0; i < 5; i++) { // ne te kundert ec drejt...
      rb();
      lb();

      Serial.print(F("\t\t\t\t\t\t\tEc Drejt !! \t\n "));
    }
  }

}



