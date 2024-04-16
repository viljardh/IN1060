// Oppg 2.2.2

// Denne kretsen vil blinke med en frekvens på 1000 ms. 
// Koden sier at lyset skal skrus på, vente 1 sek, skru av, vente 1 sek, gjenta. 
void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
}
