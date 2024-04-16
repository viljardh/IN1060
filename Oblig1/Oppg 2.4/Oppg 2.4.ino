// Oppg 2.4, jeg gjør utfordringen i samme greia.

/*
Sånn som jeg forstår det leser pullup når kretsen er sluttet og at port 4 har mulighet
til å sende strøm, og vi har mulighet til å lese av dette. Kult!

Dermed kan vi sette if-tester til at Arduinoen skal utføre oppgaver basert på 
om knappen er trykket - altså at port 4 registrerer at kretsen er sluttet (LOW)
eller ikke (HIGH). Jeg hadde gjettet motsatt, men er sånn det registreres. 

For utfordringsoppgaven bruker jeg port 7 som output til LED-pære nummer to. 
Pære #2 er koblet identisk som pæra i hovedoppgaven, bare parallelt et par hakk under. 
*/

void setup() {
  pinMode(4, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  pinMode(7, OUTPUT);
}

/*
Vi leser av port 4 - Hvis den er HIGH, altså at knappen ikke er trykket, 
skal port 2 ikke sende ut strøm, men for utfordringsoppgaven får vi port 7
til å sende ut strøm.

Hvis port 4 leser LOW, kretsen er sluttet fordi knappen er trykket, bytter vi om. 
*/
void loop() {
  if (digitalRead(4) == HIGH) {
    digitalWrite(2, LOW);
    //digitalWrite(7, HIGH);
  }
  if (digitalRead(4) == LOW) {
    digitalWrite(2, HIGH);
    //digitalWrite(7, LOW);
  }
}
