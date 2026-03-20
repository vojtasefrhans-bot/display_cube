#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, 2, 3, U8X8_PIN_NONE, 1, 0);  //sck=2, sda=3, res=0, dc=1

// for serialJson.ino
int cpu;
int ram;
String inputBuffer = "";
bool jsonDokonceny = false;
unsigned long posledniJson = 0;


// for encoder.ino
const int pinA = 29;
const int pinB = 28;
const int pinSW = 27;
volatile long encoderValue = 0;

// for this .ino xd
int displayFace = 0;
uint8_t amountOfFaces = 2;
void setup(){
  Serial.begin(115200);

  encoderBegin();
  displayBegin();
  Jsonbegin();
}

void loop(){
  handleSerialBuffer();

  /*static unsigned long lastButton = 0;
  if (digitalRead(pinSW) == LOW && millis() - lastButton > 200) {
    u8g2.clearBuffer();
    u8g2.sendBuffer();
    lastButton = millis();
  }*/

  displayFace = abs(encoderValue%2); //%numberOfDisplays
  //Serial.println(displayFace);

  static uint lastDisplayFace = 0;
  if(lastDisplayFace != displayFace){
    zeroSeznam();
    lastDisplayFace = displayFace;
  }

  if(displayFace == 0){chart(cpu); chartHUD(displayFace + 1, amountOfFaces, "CPU");}
  if(displayFace == 1){chart(ram); chartHUD(displayFace + 1, amountOfFaces, "RAM");}
  
  u8g2.sendBuffer();
}