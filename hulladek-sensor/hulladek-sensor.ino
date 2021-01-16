const int triggerPin = 2; // Termék lézer
const int buzzerPin = 9; // Buzzer kimenet
const int buzzerFrequency = 2500; // Buzzer frekvenciája, ez állítható tetszés szerint
const int buzzerDuration = 1000; // Buzzer bekapcsolásának időtartama, ez állítható tetszés szerint
const int holePin = 11; // Belső hulladék lézer
bool buzzerState = 0; // Akkor igaz ha sípolnia kell az érzékelőnek
bool buzzeTrigger = 0; // Ez csak akkor igaz ha éppen be kell kapcsolni a sípolást
int buzzerTime = buzzerDuration; // A sípolásból eltelt időt méri

void setup() {
  pinMode(triggerPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(holePin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(triggerPin), product_ISR, FALLING); // A termék lézer pinjére beállít egy megszakítást (lefutó él)
}

void loop() {
  if (buzzeTrigger && !buzzerState) { // Akkor fut le ha be kell kapcsolni a buzzert és éppen nem sípol
    buzzerState = 1;
    buzzerTime = 0;
    tone(buzzerPin, buzzerFrequency);
  }
  
  if (buzzerTime >= buzzerDuration && buzzerState) { // akkor igaz ha a sípolást ki kell kapcsolni és éppen sípol :)
    noTone(buzzerPin);                               // egyépként növeli a számlálót eggyel
    buzzerState = 0;
  } else {
    if (buzzerState) { // Azért kell hogy ha nem sípol ne pörgese a számlálót
      buzzerTime++;
    }
  }
  
  buzzeTrigger = 0; // Alaphelyzetbe állítja a triggert
  delay(1);
}

void product_ISR() {
  if (!digitalRead(holePin)) {
    buzzeTrigger = 1; 
  }
}
