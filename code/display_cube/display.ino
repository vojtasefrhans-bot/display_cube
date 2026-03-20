//for animations and faces
static unsigned long lastDisplay = 0;
uint8_t seznam[101];

void zeroSeznam(){
  for(uint8_t i = 0; i < 101; i++){
    seznam[i] = 0;
  }
}

  void handleSeznam(uint8_t newValue){
    for(uint8_t i = 100; i > 0; i--){
      seznam[i] = seznam[i - 1];
    }
    seznam[0] = newValue;
  }

void displayBegin(){
  u8g2.begin();
  u8g2.setFlipMode(1);
  //Serial.println("Start displaye");
}

void chart(uint8_t value){    //make a chart of the input value (from 0 to 100), it creates 1 colum per frame (5hz rn)
  if (millis() - lastDisplay > 200) {  // Timer
    int cislo = constrain(map(value, 0, 100, 0, 42), 0, 42);
    handleSeznam((cislo + seznam[0] + seznam[1] + seznam[2])/4); //the value is average of the last 4 values for smoother chart

    u8g2.clearBuffer();
    for(uint8_t i = 0; i < 100; i++){   //100px wide
      u8g2.drawLine(i + 28, 43 - seznam[i], i + 28, 43);    // 23px wide padding on left and 0px on right || 5 px down
    }   //max height: 38px -> form 5 to 43px => 0% at 43 px; 50% at 24px; 100% at 5px 

    lastDisplay = millis();
  }
}

void chartHUD(uint8_t actualFace, uint8_t maxFaces, const char* name){
  uint8_t wName = u8g2.getStrWidth(name);
  int xName = (128 - wName) / 2;
  String face = String(actualFace) + "/" + maxFaces;
  uint8_t wFace = u8g2.getStrWidth(face.c_str());

  u8g2.drawBox(0, 48, 128, 64);
  u8g2.setFont(u8g2_font_5x7_tf); //smaller font for the percantage
  u8g2.drawStr(10, 48, "0%"); /*10px wide*/ u8g2.drawLine(28, 43, 24, 43);/*important lines*/ u8g2.drawLine(28, 34, 26, 34);  //les important lines
  u8g2.drawStr(5, 30, "50%"); /*15px wide*/ u8g2.drawLine(28, 24, 24, 24);/*important lines*/ u8g2.drawLine(28, 14, 26, 14);
  u8g2.drawStr(0, 11, "100%");/*20px wide*/ u8g2.drawLine(28, 5, 24, 5);  /*important lines*/

  u8g2.setDrawColor(0);     //creates a negative text
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(xName, 59, name);
  u8g2.drawStr(128 - wFace - 5, 61, face.c_str());
  u8g2.setDrawColor(1); //back to normal
}
