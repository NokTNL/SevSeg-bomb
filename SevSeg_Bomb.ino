 // Adpated from: SevSegShiftOne_Counter.ino @ https://github.com/bridystone/SevSegShift/examples

#include <SevSegShift.h>
#include <Servo.h>
#include "functions.h";

//Set up the SevSegShift object
const int dataPin = 2; // Data Pin  (pin 14 (DS)   on 74HC595 --> pin on Arduino)
const int latchPin = 3; // Latch Pin (pin 12 (STCP) on 74HC595 --> pin on Arduino)
const int clockPin = 4; // Clock Pin (pin 11 (SHCP) on 74HC595 --> pin on Arduino)

SevSegShift mySevSeg(
      dataPin, clockPin, latchPin,
      1,    // number of shift registers, default = 2
      true  // Digits are connected to Arduino directly, default value = false
);

//Set up the servo object
const int servoPin = 10;
Servo myServo;


void setup() {

  // Initialise the SevSeg object
  byte numDigits = 4;                             // number of digits on the SevSeg
  byte digitPins[] = {5, 6, 7, 8};                // What ARDUINO pins are connected to the DIGIT pins on the SevSeg,
                                                      // in the order (D1, D2, D3, D4) 
  byte segmentPins[] = {0, 1, 2, 3, 4, 5, 6, 7};  // What 74HC595 pins (Q0-Q7) are connected to the SEGMENT pins on the SevSeg,
                                                      // in the order (A, B, C, D, E, F, G, DP) 
  bool resistorsOnSegments = true;                // 'true' if resistors are connected to the SEGMENT pins, 'false' if to the DIGIT pins
  byte hardwareConfig = COMMON_CATHODE;           // COMMON_CATHODE: digit pins on low voltage (sink), COMMON_CATHODE: " " on high voltage (source)
  bool updateWithDelays = false;                  // Default 'false' is Recommended
  bool leadingZeros = false;                      // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false;                   // Use 'true' if your decimal point doesn't exist or isn't connected.
                                                      // Then, you only need to specify 7 segmentPins[] 
  mySevSeg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);

  // Initialise the servo object
  myServo.attach(servoPin);
  myServo.write(0);

  Serial.begin(38400);

}

void loop() {

  //Timer variables *** Except timer, all time units are centiseconds = 0.01 sec
  static unsigned long timer = millis();  // log time of Arduino prgramme starts running & keep track on millis() later, every 10 centisec
  static int centiSec = 1100;             // For storing how many centiseconds are left; can go to -ve
  static const int bombSec = -200;        // When to enter the "BOMB" programme, in centiseconds

  //Counter
  if (millis() - timer >= 10)   {     // Every time when 1 centisec = 10 ms has passed
    timer += 10;                    // Update timer = present time
    centiSec--;                     // minus one centisec
  }

  //Series of actions
  if (centiSec > 0) {               // When countodown not yet done
    mySevSeg.setNumber(centiSec, 2);
    buzzer(timer, centiSec, 50);
  }
  else if (centiSec > bombSec && centiSec <= 0) {
    if (centiSec == 0) {        // When the countdown is done
      mySevSeg.setChars("BYE_");
    }
    buzzer(timer, centiSec, 12);
  }
  else if (centiSec == bombSec) {
    mySevSeg.setChars("6666");
    buzzer("", "", "", 1);      // Swtich off the buzzer
    myServo.write(180);
  }
  else if (centiSec < bombSec) {
    static const unsigned int servoInterval = 50;
    if (abs(centiSec - bombSec) % servoInterval == 0) {
      if (abs(centiSec - bombSec) % (servoInterval*2) == 0){
        myServo.write(180);
      }
      else {
        myServo.write(0);
      }
    }
  }

  mySevSeg.refreshDisplay(); // Must run repeatedly, display one digit in one loop()
}
