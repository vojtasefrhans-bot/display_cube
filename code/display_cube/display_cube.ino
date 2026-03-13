// for encoder.ino
const int pinA = 29;
const int pinB = 28;
const int pinSW = 27;
volatile long encoderValue = 0;

bool displayFace = 0;

void setup(){
  Serial.begin(9600);
  encoderBegin();
  displayBegin();
}

void loop(){
  static unsigned long lastButton = 0;
  if (digitalRead(pinSW) == LOW && millis() - lastButton > 200) {
    displayFace = !displayFace;
    lastButton = millis();
  }
  static unsigned long lastDisplay = 0;
  if (millis() - lastDisplay >= 30){
    if(displayFace){
      displayTest1();
    }else{
      displayTest2(encoderValue%15);
    }
    
  }
}