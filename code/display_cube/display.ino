//for animations and faces
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, 2, 3, U8X8_PIN_NONE, 1, 0);  //sck=2, sda=3, res=0, dc=1

void displayBegin(){
  u8g2.begin();
  Serial.println("Start displaye");
}

void displayTest1(uint8_t value){
  u8g2.clearBuffer();
  u8g2.drawFrame(5, 20, 102, 12);
  u8g2.drawBox(6, 21, abs(value%100), 10);
  u8g2.sendBuffer();
}

void displayTest2(uint8_t value){
  u8g2.clearBuffer();
  u8g2.drawCircle(64, 32, 15);
  u8g2.drawDisc(64, 32, abs(value%15));
  u8g2.sendBuffer();
}