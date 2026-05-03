#include <ArduinoJson.h>

void JsonBegin(){ 
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
    JsonDocument jsonDoc;
  
    DeserializationError chyba = deserializeJson(jsonDoc, inputBuffer); //parsovani
    
    if (chyba) {
      Serial.print("CHYBA: ");
      Serial.println(chyba.c_str());
    } else {
      cpu = jsonDoc["cpu"].as<int>();
      ram = jsonDoc["ram"].as<int>();
      disk = jsonDoc["disk"].as<int>();
      gpu =  jsonDoc["gpu"].as<int>();
    }
    
    inputBuffer = "";
    jsonDokonceny = false;
  }
  
}