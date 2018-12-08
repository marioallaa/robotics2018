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
Servo tounge, rightArm, leftArm;

int i = 0;

// Pin configuration for Movement 
int lfPin = 4;
int lbPin = 5;
int rfPin = 6;
int rbPin = 7;

// pin configuration for Shotting
int shootP = 8;
int shootM = 9;
int load = 10;
int push = 11;



void setup() {
  Serial.begin(115200);
  pinMode(lfPin , OUTPUT);
  pinMode(lbPin , OUTPUT);
  pinMode(rfPin , OUTPUT);
  pinMode(rbPin , OUTPUT);
  pinMode(shootP , OUTPUT);
  pinMode(shootM , OUTPUT);
  pinMode(load , OUTPUT);
  pinMode(push , OUTPUT);
  tounge.attach(A2);
  rightArm.attach(A3);
  leftArm.attach(A4);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
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
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
        if (Xbox.getButtonPress(R2, i)  && !Xbox.getButtonClick(R1, i)) {
          Serial.print("\t R2: ");
          Serial.print(Xbox.getButtonPress(L2, i));
          Serial.print("\t Without R1: ");
          Serial.println(Xbox.getButtonPress(R2, i));
          Xbox.setRumbleOn(Xbox.getButtonPress(L2, i), Xbox.getButtonPress(R2, i), i);
          rf(Xbox.getButtonPress(R2, i));
        }else if (Xbox.getButtonPress(L2, i) && !Xbox.getButtonClick(L1, i)) {
          Serial.println(Xbox.getButtonPress(R2, i));
          Xbox.setRumbleOn(Xbox.getButtonPress(L2, i), Xbox.getButtonPress(R2, i), i);
          lf(Xbox.getButtonPress(L2, i));
        }else if (Xbox.getButtonPress(L1, i)  && !Xbox.getButtonPress(L2, i)){
          Serial.println(F("L1"));
          Serial.print("\tWithout L2: ");
          lb();
          }else if (Xbox.getButtonPress(R1, i) && !Xbox.getButtonPress(R2, i)){
          Serial.println(F("R1"));
          Serial.print("\tWithout R2: ");
          rb();
        }else{
          s();
          
        }




        

        if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500 || Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500 || Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500 || Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) {
          if (Xbox.getAnalogHat(LeftHatX, i) > 7500) {
            Serial.print(F("LeftHatX: "));
            Serial.print(Xbox.getAnalogHat(LeftHatX, i));
            Serial.print("\t");
            
          }
          if (Xbox.getAnalogHat(LeftHatX, i) < -7500) {
            Serial.print(F("LeftHatX: "));
            Serial.print(Xbox.getAnalogHat(LeftHatX, i));
            Serial.print("\t");
            
          }
          if (Xbox.getAnalogHat(RightHatX, i) > 7500) {
            Serial.print(F("RightHatX: "));
            Serial.print(Xbox.getAnalogHat(RightHatX, i));
            Serial.print("\t");
          
          }
          if (Xbox.getAnalogHat(RightHatX, i) < -7500) {
            Serial.print(F("RightHatX: "));
            Serial.print(Xbox.getAnalogHat(RightHatX, i));
            Serial.print("\t");
          }

          
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
        }
        if (Xbox.getButtonClick(BACK, i)) {
          Xbox.setLedBlink(ALL, i);
          Serial.println(F("Back"));
        }
        if (Xbox.getButtonClick(L3, i))
          Serial.println(F("L3"));
        if (Xbox.getButtonClick(R3, i))
          Serial.println(F("R3"));

        if (Xbox.getButtonClick(L1, i))
          Serial.println(F("L1"));
        if (Xbox.getButtonClick(R1, i))
          Serial.println(F("R1"));
        if (Xbox.getButtonClick(XBOX, i)) {
          Xbox.setLedMode(ROTATING, i);
          Serial.print(F("Xbox (Battery: "));
          Serial.print(Xbox.getBatteryLevel(i)); // The battery level in the range 0-3
          Serial.println(F(")"));
        }
        if (Xbox.getButtonClick(SYNC, i)) {
          Serial.println(F("Sync"));
        }



        if (Xbox.getButtonClick(A, i) && i <= 180){
          Serial.println(F("A"));
          i += 5;
          delay(50);
            tounge.write(i);
          
          Serial.println(F("Open \t\n"));          
          }
        if (Xbox.getButtonPress(Y, i) && i >= 0){
          Serial.println(F("Y"));
          delay(50);
          i -= 5;
            tounge.write(i);
          
          Serial.println(F("Close \t\n"));  
          }


        
        if (Xbox.getButtonClick(B, i)){
          Serial.println(F("B"));
          }
        if (Xbox.getButtonClick(X, i)){
          Serial.println(F("X"));
          }
      }
    }
  }
}


void rf(int v){
  analogWrite(rfPin, v);
  analogWrite(rbPin, 0);
  Serial.print(F("Right Forward !! \t\n "));
}
void rb(){
  analogWrite(rfPin, 0);
  analogWrite(rbPin, 255);
  Serial.print(F("Right Backwards !! \t\n "));
}
void lf(int v){
  analogWrite(lfPin, v);
  analogWrite(lbPin, 0);
  Serial.print(F("Left Forward !! \t\n "));
}
void lb(){
  analogWrite(lfPin, 0);
  analogWrite(lbPin, 255);
  Serial.print(F("Left Backwards !! \t\n "));
}
void s(){
  analogWrite(rfPin, 0);
  analogWrite(rbPin, 0);
  analogWrite(lfPin, 0);
  analogWrite(lbPin, 0);
}

