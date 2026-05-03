#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, 2, 3, U8X8_PIN_NONE, 1, 0);  //sck=2, sda=3, res=0, dc=1

uint displayFace = 0;
uint lastDisplayFace = 0;
uint8_t amountOfFaces = 3;

// for serialJson.ino
uint cpu;
uint ram;
uint disk;
uint gpu;
String inputBuffer = "";
bool jsonDokonceny = false;
unsigned long posledniJson = 0;

extern uint btnValue;

void setup(){
  Serial.begin(115200);

  BtnInit();
  JsonBegin();
  displayInit();
}

void loop(){
  HandleBtn(amountOfFaces);
  displayFace = btnValue%amountOfFaces;

  if(displayFace == 0){chart(cpu); chartHUD(displayFace + 1, amountOfFaces, "CPU");}
  if(displayFace == 1){chart(ram); chartHUD(displayFace + 1, amountOfFaces, "RAM");}
  if(displayFace == 2){chart(gpu); chartHUD(displayFace + 1, amountOfFaces, "GPU");}
  
  u8g2.sendBuffer();
}