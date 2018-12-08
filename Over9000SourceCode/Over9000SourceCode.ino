/*
 *                                               ***
 *                                            OVER 9000
 *                                               ***
 *                                               
 *                                  Take it, Shoot it, never losse it...
 *                                  
 *                                  
 *                                  
 *                                    "Harry T.Fultz" Institute
 * 
 */
#include <XBOXRECV.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
XBOXRECV x(&Usb);

int reset = 0;
int fLeft = 4;
int bLeft = 5;
int fRight = 6;
int bRight = 7;
int val = 0;
uint8_t i;
bool fullSpeed = false;
void setup() {
  // put your setup code here, to run once:

  pinMode(fLeft, OUTPUT);
  pinMode(bLeft, OUTPUT);
  pinMode(fRight, OUTPUT);
  pinMode(bRight, OUTPUT);

  
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); 
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
}

void loop() {
  // put your main code here, to run repeatedly:

  Usb.Task();
  if (x.XboxReceiverConnected) {
    for (i = 0; i < 4; i++) {
      if (x.Xbox360Connected[i]) {
         if (x.getAnalogHat(LeftHatX, i) > 7500 || x.getAnalogHat(LeftHatX, i) < -7500 || x.getAnalogHat(LeftHatY, i) > 7500 || x.getAnalogHat(LeftHatY, i) < -7500){
        if (x.getAnalogHat(LeftHatX, i) > 7500) {
          
            val = map(x.getAnalogHat(LeftHatX, i), 7500, 32760, 0, 35);
            right(val);
          x.setLedOn(LED2, i);
          }
          if (x.getAnalogHat(LeftHatY, i) > 7500 ) {
            val = map(x.getAnalogHat(LeftHatY, i), 7500, 32760, 0, 35);
            forward(val);
          x.setLedOn(LED1, i);
          }
        
        if ( x.getAnalogHat(LeftHatX, i) < -7500) {
            val = map(x.getAnalogHat(LeftHatX, i), -7500, -32760, 0, 35);
            left(val);
          x.setLedOn(LED3, i);
          }
          if ( x.getAnalogHat(LeftHatY, i) < -7500) {
            val = map(x.getAnalogHat(LeftHatY, i), -7500, -32760, 0, 35);
            backward(val);
          x.setLedOn(LED4, i);
          }
         }else if (x.getAnalogHat(LeftHatX, i) > 7500 && x.getButtonPress(L3, i) || x.getAnalogHat(LeftHatX, i) < -7500 && x.getButtonPress(L3, i) 
         || x.getAnalogHat(LeftHatY, i) > 7500 && x.getButtonPress(L3, i) || x.getAnalogHat(LeftHatY, i) < -7500 && x.getButtonPress(L3, i)){
         
         if (x.getAnalogHat(LeftHatX, i) > 7500) {
          
            val = map(x.getAnalogHat(LeftHatX, i), 7500, 32760, 0, 35);
            right(val);
          }
          if (x.getAnalogHat(LeftHatY, i) > 7500 ) {
            val = map(x.getAnalogHat(LeftHatY, i), 7500, 32760, 0, 35);
            forward(val);
          }
        
        if ( x.getAnalogHat(LeftHatX, i) < -7500) {
            val = map(x.getAnalogHat(LeftHatX, i), -7500, -32760, 0, 35);
            Serial.print(x.getAnalogHat(LeftHatX, i));
            left(val);
          }
          if ( x.getAnalogHat(LeftHatY, i) < -7500) {
            val = map(x.getAnalogHat(LeftHatY, i), -7500, -32760, 0, 35);
            backward(val);
          }
         } else {
          val = 0;
          STOP();
          x.setLedMode(ROTATING, i);
         }
        if ( x.getButtonPress(L3, i))
            fullSpeed = true;
            x.setLedMode(ROTATING, i);
      }else {
            fullSpeed = false;
      }
      }
    }
}


void forward(int voltage){
  Serial.print("\n\n FORWARD:   ");
  Serial.print(voltage);
  int PWM = (voltage * 100)/35;
  delay(PWM);
  digitalWrite(fRight, LOW);
  digitalWrite(bRight, LOW);
  digitalWrite(bLeft, LOW);
  digitalWrite(fLeft, LOW);
  delay(100-PWM);
  digitalWrite(bLeft, LOW);
  digitalWrite(fLeft, HIGH);
  digitalWrite(fRight, HIGH);
  digitalWrite(bRight, LOW);
  }

void backward(int voltage){
  Serial.print("\n\n\t\t\t\t BACKWARDS:   ");
  Serial.print(voltage);
  int PWM = (voltage * 100)/35;
  delay(PWM);
  digitalWrite(fRight, LOW);
  digitalWrite(bRight, LOW);
  digitalWrite(bLeft, LOW);
  digitalWrite(fLeft, LOW);
  delay(100-PWM);
  digitalWrite(bLeft, HIGH);
  digitalWrite(fLeft, LOW);
  digitalWrite(fRight, LOW);
  digitalWrite(bRight, HIGH);
  }
void left(int voltage){
  Serial.print("\n\n\t\t\t\t\t\t\t LEFT:   ");
  Serial.print(voltage);
  int PWM = (voltage * 100)/35;
  delay(PWM);
  digitalWrite(fRight, LOW);
  digitalWrite(bRight, LOW);
  digitalWrite(bLeft, LOW);
  digitalWrite(fLeft, LOW);
  delay(100-PWM);
  digitalWrite(bLeft, HIGH);
  digitalWrite(fLeft, LOW);
  digitalWrite(fRight, HIGH);
  digitalWrite(bRight, LOW);
  }

void right(int voltage){
  Serial.print("\n\n\t\t\t\t\t\t\t\t\t\t RIGHT:   ");
  Serial.print(voltage);
  int PWM = (voltage * 100)/35;
  delay(PWM);
  digitalWrite(fRight, LOW);
  digitalWrite(bRight, LOW);
  digitalWrite(bLeft, LOW);
  digitalWrite(fLeft, LOW);
  delay(100-PWM);
  digitalWrite(bLeft, LOW);
  digitalWrite(fLeft, HIGH);
  digitalWrite(fRight, LOW);
  digitalWrite(bRight, HIGH);
  }

void STOP(){
  Serial.print("\n\t STOP:   ");
  digitalWrite(fRight, LOW);
  digitalWrite(bRight, LOW);
  digitalWrite(bLeft, LOW);
  digitalWrite(fLeft, LOW);}

