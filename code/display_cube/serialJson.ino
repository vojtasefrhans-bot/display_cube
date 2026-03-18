//should be running on 1 core and the rest of the code on the other thus i can afford to have blocking delay()

#include <ArduinoJson.h>

void Jsonbegin(){ 
  inputBuffer.reserve(200);
  posledniJson = millis();
}

void handleSerialBuffer(){
  while (Serial.available() > 0) {      //čtení Serial COM 
    char bajt = (char)Serial.read();
    inputBuffer += bajt;
    if (bajt == '\n') {
      jsonDokonceny = true;
      posledniJson = millis();
      break;
    }
  }

  if (millis() - posledniJson > 5000 && inputBuffer.length() > 0) {   //timeout
    inputBuffer = "";
  }

  if (jsonDokonceny) {
    JsonDocument jsonDoc;  // Automaticky volí static/dynamic 
    
    //parsovani
    DeserializationError chyba = deserializeJson(jsonDoc, inputBuffer);
    
    if (chyba) {
      Serial.print("CHYBA: ");
      Serial.println(chyba.c_str());
    } else {
      // čtení
      cpu = jsonDoc["cpu"].as<int>();
      ram = jsonDoc["ram"].as<int>();
    }
    
    inputBuffer = "";
    jsonDokonceny = false;
  }
  
}