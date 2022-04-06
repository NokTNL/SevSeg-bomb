//Switch on active buzzer for one interval, then switch off for one interval, continously

void buzzer(long timer, int centiSec, int interval, bool switchOff = 0) {
  
  static const int buzzPin = 9;
  static boolean hasSetPin = 0;
  if (!hasSetPin) {
    pinMode(buzzPin, OUTPUT);
    hasSetPin = 1; 
  }

  if (switchOff) {
    digitalWrite(buzzPin, LOW);
    return;
  }
  
  if (abs(centiSec) % interval == 0) {
    if (abs(centiSec) % (interval*2) == 0){
      digitalWrite(buzzPin, HIGH);
    }
    else {
      digitalWrite(buzzPin, LOW);
    }
  }
}
