//for animations and faces
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, 2, 3, U8X8_PIN_NONE, 1, 0);  //sck=2, sda=3, res=0, dc=1

static unsigned long lastDisplay = 0;  // VENKU! Statická proměnná
static uint8_t lastCislo;
uint8_t seznam[101];

void handleSeznam(uint8_t newValue){
  for(uint8_t i = 0; i < 100; i++){
    seznam[i] = seznam[i + 1];
  }
  seznam[99] = newValue;
}

void displayBegin(){
  u8g2.begin();
  Serial.println("Start displaye");
}

void displayTest1(){
  if (Serial.available() > 0) {
    String cislo_str = Serial.readStringUntil('\n');
    cislo_str.trim();

    if (cislo_str.length() > 0 && cislo_str.toInt() >= 0) {
      int cislo = constrain(map(cislo_str.toInt(), 0, 100, 0, 30), 0, 30);
      
      handleSeznam((cislo + lastCislo)/2);

      if (millis() - lastDisplay > 100) {  // Timer funguje
        u8g2.clearBuffer();
        for(uint8_t i = 0; i < 100; i++){
          u8g2.drawLine(i + 10, seznam[i] + 20, i + 10, 20);
        }
        u8g2.sendBuffer();

        lastCislo = cislo;
        lastDisplay = millis();
      }
    }
  }
}

void displayTest2(uint8_t value){
  u8g2.clearBuffer();
  u8g2.drawCircle(64, 32, 15);
  u8g2.drawDisc(64, 32, abs(value%16));
  u8g2.sendBuffer();
}