#include <Servo.h>

// Definer pinner
const int ESC_PIN = D4;      // Velg en digital pinne (f.eks. D4/GPIO2)
const int POT_PIN = A0;      // Analog inngang A0

// Definer pulsbreddeområde for ESC (i mikrosekunder)
// Disse verdiene må KANSKJE justeres etter ESC-kalibrering!
const int MIN_PULSE = 1000;  // 1000 µs (Stopp/Minimum gass)
const int MAX_PULSE = 2000;  // 2000 µs (Maksimal gass)
const int START_PULSE = 1000; // Puls for armering (ofte MIN_PULSE)

Servo esc; // Opprett et Servo-objekt for ESC-kontrollen

void setup() {
  Serial.begin(115200);
  
  // Koble Servo-objektet til den digitale pinnen
  esc.attach(ESC_PIN, MIN_PULSE, MAX_PULSE);

  Serial.println("Starter ESC armeringssekvens...");
  
  // Første skritt: Armering av ESC (Viktig!)
  // ESC-en må se en "stopp"-kommando (eller lav gass) før den aktiveres.
  esc.writeMicroseconds(START_PULSE); 
  
  Serial.println("Vent 3-5 sekunder mens ESC-en armerer...");
  delay(3000); // Gi ESC-en tid til å starte/armere (ca. 3 sekunder)
  Serial.println("Armering fullført. Klar til kontroll.");
}

void loop() {
  // 1. Les verdien fra potensiometeret
  int analogValue = analogRead(POT_PIN); // Leser 0-1023 (10-bit ADC på ESP8266)

  // 2. Konverter den analoge verdien til ESC-pulsvidden
  // Bruk map() til å konvertere intervallet 0-1023 til 1000-2000 µs.
  int pulseWidth = map(analogValue, 0, 1023, MIN_PULSE, MAX_PULSE);
  
  // 3. Send pulsbredden til ESC-en
  esc.writeMicroseconds(pulseWidth);

  // Valgfritt: Skriv ut verdiene for feilsøking
  Serial.print("Potens: ");
  Serial.print(analogValue);
  Serial.print(" -> Puls: ");
  Serial.print(pulseWidth);
  Serial.println(" µs");

  delay(20); // Kort forsinkelse for å stabilisere syklusen
}