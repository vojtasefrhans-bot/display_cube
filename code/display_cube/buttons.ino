//takes care of the encoder input
#include "ezButton.h"

const int btnPlus = 29;
const int btnMinus = 28;
uint btnValue;

ezButton BtnPlus(btnPlus);
ezButton BtnMinus(btnMinus);

void BtnInit(){

  BtnPlus.setDebounceTime(50);
  BtnMinus.setDebounceTime(50);
}

void HandleBtn(int max){
  BtnPlus.loop();
  BtnMinus.loop();

  if(BtnPlus.isPressed()){  //ads 1 or loops btnValue
    if(btnValue < max){
      btnValue++;
    }else{  //pokud btnValue =< max
      btnValue = 0;
    }
  }

  if(BtnMinus.isPressed()){ //subtracts 1 or loops btnValue up
    if(btnValue > 0){
      btnValue--;
    }else{
      btnValue = max;
    }
  }
}