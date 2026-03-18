//for animations and faces
static unsigned long lastDisplay = 0;
uint8_t seznam[101];

void zeroSeznam(){
  for(uint8_t i = 0; i < 101; i++){
    seznam[i] = 0;
  }
}

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

void chart(uint8_t value){    //make a chart of the input value, it creates 1 colum per frame (5hz rn)
  if (millis() - lastDisplay > 200) {  // Timer
    int cislo = constrain(map(value, 0, 100, 0, 30), 0, 30);
    handleSeznam((cislo + seznam[98] + seznam[97] + seznam[96])/4); //the value is average of the last 4 values for smoother chart

    u8g2.clearBuffer();
    for(uint8_t i = 0; i < 100; i++){
      u8g2.drawLine(i + 10, seznam[i] + 20, i + 10, 20);
    }
    u8g2.sendBuffer();

    lastDisplay = millis();
  }
}