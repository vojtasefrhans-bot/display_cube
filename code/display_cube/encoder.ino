//takes care of the encoder input
const int pinA = 29;
const int pinB = 28;
const int pinSW = 27;

volatile long encoderValue = 0;

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
void encoderBegin(){
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  pinMode(pinSW, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), encISR, CHANGE);
}