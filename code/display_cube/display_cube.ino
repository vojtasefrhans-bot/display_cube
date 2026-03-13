#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, 2, 3, U8X8_PIN_NONE, 1, 0);  //sck=2, sda=3, res=0, dc=1

// for encoder.ino
const int pinA = 29;
const int pinB = 28;
const int pinSW = 27;
volatile long encoderValue = 0;

bool displayFace = 0;

void setup(){
  Serial.begin(115200);
  encoderBegin();
  displayBegin();
}

void loop(){
  static unsigned long lastButton = 0;
  if (digitalRead(pinSW) == LOW && millis() - lastButton > 200) {
    displayFace = !displayFace;
    Serial.print("tlacitko zmacknuto"); Serial.println(displayFace);
    u8g2.clearBuffer();
    u8g2.sendBuffer();
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