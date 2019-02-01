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
bool fireing =false, bumming = false, autonomusOn = false;
int fire = 8, bum = 9, light = 10, rSensor = A14, lSensor = A15;

// L298 Controller 
int rfPin = 4;
int rbPin = 5;
int lfPin = 6;
int lbPin = 7;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); 
pinMode(rfPin, OUTPUT);
pinMode(rbPin, OUTPUT);
pinMode(lfPin, OUTPUT);
pinMode(lbPin, OUTPUT);
pinMode(fire, OUTPUT);
pinMode(bum, OUTPUT);
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
        
        if (Xbox.getButtonPress(L2, i) && !Xbox.getButtonPress(L1, i)) {
          Serial.print("\t\t Without L1");
          lf(Xbox.getButtonPress(L2, i));
        }
        
        if (Xbox.getButtonPress(R2, i) && !Xbox.getButtonPress(R1, i)) {
          Serial.print("\t\tR2 Without R1");
          
            rf(Xbox.getButtonPress(R2, i));
        }
        if (Xbox.getButtonPress(R1, i) && !Xbox.getButtonPress(R2, i)) {
          Serial.print("\t\tR1 Without R2");
          rb();
        }
        if (Xbox.getButtonPress(L1, i) && !Xbox.getButtonPress(L2, i)) {
          Serial.print("\t\tL1 Without L2");
          lb();
        }
        else{
          rs();
          ls();
        }

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          if (Xbox.getAnalogHat(LeftHatX, i) > 7500 && lArmVal > 0) {       // //          Mbylle krahun e majte
            Serial.print(F("LeftHatX: "));
            Serial.print(Xbox.getAnalogHat(LeftHatX, i));
            Serial.print("\t Writing Left Arm Value : ");
            delay(10);
            lArmVal -=2;
            Serial.println(lArmVal);
            lArm.write(lArmVal);

          }
          if (Xbox.getAnalogHat(LeftHatX, i) < -7500 && lArmVal < 120) {      // //          Hape krahun e majte
            Serial.print(F("LeftHatX: "));
            Serial.print(Xbox.getAnalogHat(LeftHatX, i));
            Serial.print("\t Writing Left Arm Value : ");
            delay(10); 
            lArmVal +=2;
            Serial.println(lArmVal);
            lArm.write(lArmVal);
          }
          if (Xbox.getAnalogHat(RightHatX, i) > 7500 && rArmVal > 40) {     //          Hape krahun e djathe
            Serial.print(F("RightHatX: "));
            Serial.print(Xbox.getAnalogHat(RightHatX, i));
            Serial.print("\t Writing Right Arm Value : ");
            delay(10);
            rArmVal -=2;
            Serial.println(rArmVal);
            rArm.write(rArmVal);

          }
          if (Xbox.getAnalogHat(RightHatX, i) < -7500 && rArmVal < 175) {   //          Mbylle krahun e djathe
            Serial.print(F("RightHatX: "));
            Serial.print(Xbox.getAnalogHat(RightHatX, i));
            Serial.print("\t Writing Right Arm Value : ");
            delay(10);
            rArmVal +=2;
            Serial.println(rArmVal);
            rArm.write(rArmVal);
          }
          //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

       /* if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500 || Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500 || Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500 || Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) {
          if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500) {
            Serial.print(F("LeftHatX: "));
            Serial.print(Xbox.getAnalogHat(LeftHatX, i));
            Serial.print("\t");
          }
          if (Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500) {
            Serial.print(F("LeftHatY: "));
            Serial.print(Xbox.getAnalogHat(LeftHatY, i));
            Serial.print("\t");
          }
          if (Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500) {
            Serial.print(F("RightHatX: "));
            Serial.print(Xbox.getAnalogHat(RightHatX, i));
            Serial.print("\t");
          }
          if (Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) {
            Serial.print(F("RightHatY: "));
            Serial.print(Xbox.getAnalogHat(RightHatY, i));
          }
          Serial.println();
        }*/

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
          autonomus(analogRead(lSensor), analogRead(rSensor));
        }
        if (Xbox.getButtonClick(BACK, i)) {
          Xbox.setLedBlink(ALL, i);
          Serial.println(F("Back"));
          if (bumming)
                digitalWrite(bum, LOW);
          else {
                digitalWrite(bum, HIGH);
                bumming = true;}
        }
        if (Xbox.getButtonClick(L3, i)){
          Serial.println(F("L3"));
          if (fireing){
                digitalWrite(fire, LOW);
                fireing = false;}
          else {
                digitalWrite(fire, HIGH);
                fireing = true;}}
        if (Xbox.getButtonClick(R3, i)){
          Serial.println(F("R3"));}

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

        if (Xbox.getButtonPress(A, i) && mArmVal < 260){
          mArmVal +=5;
          delay(10);
          Serial.println("\t\t Closing mArm, \t Value: ");
          Serial.println(mArmVal);
          mArm.write(mArmVal);
          
          }
        if (Xbox.getButtonPress(Y, i) && mArmVal > 0){
          mArmVal -=5;
          delay(10);
          Serial.println("\t\t Opening mArm, \t Value: ");
          Serial.println(mArmVal);
          mArm.write(mArmVal);
          } 
          
        if (Xbox.getButtonClick(B, i)){
          Serial.println(F("B"));
          lArm.write(0);
          delay(50);
          rArm.write(175);
          }
        if (Xbox.getButtonClick(X, i)){
          Serial.println(F("X"));
          rArm.write(40);
          delay(50);
          lArm.write(160);
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
  int keyVal = 250; // Key Value for the given color...
  while (autonomusOn) {
    
      delay(50);
  Serial.print(F("\t\n\t\t\t\tRight Value:\t "));
  Serial.print(analogRead(rsVal));
  Serial.print(F("\n\t\t\t\tLeft Value: \t "));
  Serial.print(lsVal);
  Serial.print("\n");
    if (lsVal < keyVal) { // Roboti ka ecur shum nga ana e majte
      //lb();
      //rf(255);   // Kthehu djathtas
      
  Serial.print(F("Roboti ka ecur shum nga ana e majte !! \t\n "));
    }
    if (rsVal < keyVal) { // Roboti ka ecur shum nga ana e djathe
      //rb();
      //lf(255);   // kthehu majtas
      
  Serial.print(F("Roboti ka ecur shum nga ana e djathe !! \t\n "));
    }
    //  if (dist < 10){  // Roboti ka me pak se 10 cm hapsire perpara tij
    //    s(); // Ndalo!!!!!!!!!!!
    if (rsVal < keyVal && lsVal < keyVal) {
      //ls();
      //rs();
      
  Serial.print(F("Left Backwards !! \t\n "));
    }

    else {        // ne te kundert ec drejt...
      //rf(255);
      //lf(255);
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

