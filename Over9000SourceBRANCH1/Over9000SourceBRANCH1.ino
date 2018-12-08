/*
 *                                               ***
 *                                            OVER 9000
 *                                               ***
 *                                               
 *                                  Take it, Shoot it, never losse it...
 *                                  
 *                                  Ky KODI ESHT ME SERVO > WRITE MICROSECONDS
 *                                  
 *                                    "Harry T.Fultz" Institute
 * 
 */
#include <XBOXRECV.h>
#include <Servo>
#endif

USB Usb;
XBOXRECV x(&Usb);

int reset = 0;
Servo fLeft = 4;
Servo bLeft = 5;
Servo fRight = 6;
Servo bRight = 7;
uint8_t i;
bool fullSpeed = false;
void setup() {
  // put your setup code here, to run once:

  fLeft.attach(4);
  bLeft.attach(5);
  fRight.attach(6);
  bRight.attach(7);

  
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
          
            val = map(x.getAnalogHat(LeftHatX, i), 7500, 32760, 1000, 5000);
            right(val);
            x.setLedOn(LED2, i);
          }
          if (x.getAnalogHat(LeftHatY, i) > 7500 ) {
            val = map(x.getAnalogHat(LeftHatY, i), 7500, 32760, 1000, 5000);
            forward(val);
            x.setLedOn(LED1, i);
          }
        
        if ( x.getAnalogHat(LeftHatX, i) < -7500) {
            val = map(x.getAnalogHat(LeftHatX, i), -7500, -32760, 1000, 5000);
            left(val);
            x.setLedOn(LED3, i);
          }
          if ( x.getAnalogHat(LeftHatY, i) < -7500) {
            val = map(x.getAnalogHat(LeftHatY, i), -7500, -32760, 1000, 5000);
            backward(val);
            x.setLedOn(LED4, i);
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
}}


void forward(int val){
  Serial.print("\tForward: ");
  Serial.print(val);
  Serial.println("");
  fRight.writeMicroseconds(val);
  fLeft.writeMicroseconds(val);
  bLeft.writeMicroseconds(0);
  bRight.writeMicroseconds(0);
}

void backward(int val){
  Serial.print("\t\t\t\tBackward: ");
  Serial.print(val);
  Serial.println("");
  fRight.writeMicroseconds(0);
  fLeft.writeMicroseconds(0);
  bLeft.writeMicroseconds(val);
  bRight.writeMicroseconds(val);
  }
void left(int val){
  Serial.print("\t\tLeft: ");
  Serial.print(val);
  Serial.println("");
  fRight.writeMicroseconds(val);
  fLeft.writeMicroseconds(0);
  bLeft.writeMicroseconds(val);
  bRight.writeMicroseconds(0);
  }

void right(int val){
  Serial.print("\t\t\tRight: ");
  Serial.print(val);
  Serial.println("");
  fRight.writeMicroseconds(0);
  fLeft.writeMicroseconds(val);
  bLeft.writeMicroseconds(0);
  bRight.writeMicroseconds(val);
  }

void STOP(){
  Serial.print("\t\t\t\t\t***STOP*** \n ");
  fRight.writeMicroseconds(0);
  fLeft.writeMicroseconds(0);
  bLeft.writeMicroseconds(0);
  bRight.writeMicroseconds(0);

