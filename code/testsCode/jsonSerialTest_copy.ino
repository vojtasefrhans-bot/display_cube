#include <ArduinoJson.h>  // Verze 7: Používá JsonDocument
#include <Adafruit_NeoPixel.h>

#define LED_PIN 16
#define NUM_LEDS 1
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// GLOBÁLNÍ PROMĚNNÉ (stejné)
String inputBuffer = "";
bool jsonDokončený = true;
unsigned long posledníČas = 0;
/*
  {
    "cpu": x,
    "ram": y
  }
*/

void setup() {
  Serial.begin(115200);
  pixels.begin();
  pixels.clear();

  while (!Serial) delay(10);
  delay(500);
  
  inputBuffer.reserve(200);
  
  posledníČas = millis();
}

void loop() {
  // SBÍRÁNÍ DAT (stejné)
  while (Serial.available() > 0) {
    char bajt = (char)Serial.read();  //jak funguje toto - čte to charakter po charakteru ??
    inputBuffer += bajt;
    if (bajt == '\n') {
      jsonDokončený = true;
      posledníČas = millis();
      break;
    }
  }
  
  // TIMEOUT (stejné)
  if (millis() - posledníČas > 5000 && inputBuffer.length() > 0) {
    Serial.println("CHYBA: Timeout!");
    inputBuffer = "";
  }
  
  // ZPRACOVÁNÍ JSONU
  if (jsonDokončený) {
    Serial.print("Prijaty: ");
    Serial.println(inputBuffer);
    
    // NOVINKA VERZE 7: JsonDocument místo StaticJsonDocument
    JsonDocument jsonDoc;  // Automaticky volí static/dynamic podle potřeby
    
    // PARSOVÁNÍ (stejné)
    DeserializationError chyba = deserializeJson(jsonDoc, inputBuffer); //co přesně dělá toto
    
    if (chyba) {
      Serial.print("CHYBA: ");
      Serial.println(chyba.c_str());
    } else {
      // ČTENÍ (nově: as<int>() pro typovou bezpečnost)
      int cpuHodnota = jsonDoc["cpu"].as<int>();    // int
      int ramHodnota = jsonDoc["ram"].as<int>();    // int
      
      // VÝSTUP
      Serial.println("\n=== DATA ===");
      Serial.print("CPU: "); Serial.print(cpuHodnota); Serial.println("%");
      Serial.print("RAM: "); Serial.print(ramHodnota); Serial.println("%");
      
      if (cpuHodnota > 20) {
        Serial.println("VAROVÁNÍ: Vysoká CPU!");
        pixels.setPixelColor(0, 255, 255, 255);
        pixels.show();
      }else{
        pixels.setPixelColor(0, 0, 0, 0);
        pixels.show();
      }
      
      Serial.println("==========\n");
      
      // memoryUsage() odstraněno - v7 vrací vždy 0 (deprecated)
      // Místo toho: arduinojson.org/v7/assistant/ pro velikost
    }
    
    // VYČIŠTĚNÍ
    inputBuffer = "";
    jsonDokončený = false;
  }
  
  delay(10);
}