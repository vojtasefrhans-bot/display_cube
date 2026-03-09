#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, 2, 3, U8X8_PIN_NONE, 1, 0);  //sck=2, sda=3, res=0, dc=1

const int pinA = 29;
const int pinB = 28;
const int pinSW = 27;

volatile long encoderValue = 0;  // Volatile pro ISR

void encISR() {
  static uint8_t lastA = HIGH;
  uint8_t newA = digitalRead(pinA);
  if (lastA == HIGH && newA == LOW) {  // Pad na A (detekce kliku)
    if (digitalRead(pinB) == LOW) {
      encoderValue--;  // CW
    } else {
      encoderValue++;  // CCW
    }
  }
  lastA = newA;
}

void setup() {
  Serial.begin(115200);
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  pinMode(pinSW, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), encISR, CHANGE);  // Změna na pinA

  u8g2.begin();
  Serial.println("Start s ISR");
}

void loop() {
  // Serial výpis
  static long lastPrinted = 0;
  if (encoderValue != lastPrinted) {
    lastPrinted = encoderValue;
    Serial.print("Pozice: ");
    Serial.println(encoderValue);
  }

  // Display non-blocking
  static unsigned long lastDisplay = 0;
  if (millis() - lastDisplay >= 30) {  // 20 Hz max
    u8g2.clearBuffer();
    u8g2.drawFrame(5, 32, 101, 10);
    u8g2.drawBox(6, 32, abs(encoderValue)%100, 9);
    u8g2.sendBuffer();
    lastDisplay = millis();
  }

  // Tlačítko sex
  static unsigned long lastButton = 0;
  if (digitalRead(pinSW) == LOW && millis() - lastButton > 200) {
    Serial.println("Tlacitko!");
    lastButton = millis();
  }

  delay(5);  // Minimální loop
}
