// Oppg 2.2.1

// Lampen vil lyse kontinuerlig da det ikke er noe delay eter digitalWrite(2, LOW);
// og koden går med det rett tilbake til å skru den på hvor den venter i 1000 ms. 
// Den blir med andre ord skrudd av i kun en klokkesyklus. 

void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
}
