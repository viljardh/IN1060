/*
Programmet kontrollerer en radar festet paa en servo som scanner en 90 +/- 7.5 graders vinkel 
etter gjenstander som er naermere enn en gitt avstand. Hvis den detekterer noe innen den avstanden
vil radaren stoppe, et lys vil blinke og lydsignal vil bli sendt. 
Lyden kan skrus av. 
Varslingen kan ogsaa startes av en knapp. 
*/

//Bibliotek for styring av servoen
#include <Servo.h>

// *** DEKLARERING ***

// Deklarering av pins som skal brukes
int varselLed = 10;  // LED-lampe som styrer varsling
int trigPin = 13;   // Sender radarens lydsignal (trigger) Hbit
int echoPin = 12;    // Mottar det reflekterte signalet (echo) Svart
int servoPin = 11;   // Styre servoen
int potPin = A0;    // Lese analogt signal fra potmeter
int piezoOut = 9;   // Lyd til piezoen
int varsleKnapp = 7;// Knapp for aa iverksette varslingssignal

// Deklarering av variable og konstanter 
double duration, dist;
int varsleDist = 25;  // Varsledistanse paa 25 cm
int varsleTid = 10;    // Varsler i 30 sekunder
int servoA = 0;       // Variabel for servoen sin vinkel i grader
int direction = 0;    // Variabel som holder styr paa rotasjonsretning til servo
int buttCount = 0;    // Teller for hvor lenge knapp holdes inne
int potV;             // Styr paa spenningen som gaar gjennom potmeter
int pos;              // Int saa vi vet om lyden skal vaere av eller paa

Servo servis; // Lager servoobjekt

// *** SETUP ***

void setup() {
  // Deklarerer outputs, inputs og pullup
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); // Sender lydsignal
  pinMode(echoPin, INPUT);  // Tar imot lydisgnal
  pinMode(varselLed, OUTPUT);
  pinMode(varsleKnapp, INPUT_PULLUP); // Liker pullup
  pinMode(piezoOut, OUTPUT);

  // Vekker servo
  servis.attach(servoPin);

  // Lydfeedback paa at enheten er i live, hvis lydbryter er paa
  if (volumKontroll() == 1) {
    // Spiller en temperert A4 i 100 millisekunder
    tone(piezoOut, 440, 100);
  }
}

// *** MAIN ***

void loop() {
  if (digitalRead(varsleKnapp) == LOW) { // Varsleknapp trykkes
    buttCount += 1;           // Oeker teller
    if (buttCount >= 60) {    // Knapp holdes i ca to sek
      varsle(0,0, varsleTid); // Starter varsel
      buttCount = 0;
    }
  } else {
    // Knappen slippes, teller nullstilles
    buttCount = 0;
  }

    radarPulse();                       // Sender ut radarpuls
    dist = distCalc(echoPin);           // Leser radarpuls og kalkulerer avstand
    varsle(dist, varsleDist, varsleTid);// Varsler om noe er innen viss avstand
    //printDist(dist);                    // Skriver maalt avstand til monitor

  // Beveger seg med klokken naar direction = 0
  if (direction == 0) {
    servoA++;            // Oeker vinkelteller
    if (servoA == 90) {  // Servoen haar naadd 90 grader
      direction = 1;     // Bytter retning
    }

  // Beveger seg motsatt, teller ned, bytter retning naar vinkel lik 0
  } else {
    servoA--;       
    if (servoA == 0) {
      direction = 0;
    }
  }
  servis.write(servoA); // Endrer vinkel til servoen med tellerenr
  delay(15);            // Oppdaterer hvert 15 ms

}

// *** METODER ***

// Returnerer distanse i cm, cm er mest beleilig pga
// smaa tall og avrundingsfeil som oppstaar med for mange floating points
double distCalc(int echoPin) {
  duration = pulseIn(echoPin, HIGH)/100; // pulseIn() gir pr 10 mikrosek, gaar over til millisek
  dist = (duration/2) * (343/100);       // Bare interessert i halve avstanden lyden har reist
  return dist;
}

// Printer ut distansen i cm 
// Radaren oppgir maks avstand den kan maale
// brukbart som fire meter, saa tar ikke stilling til ting lengre unna
void printDist(int dist) {
if (dist <= 400) { 
  Serial.print(dist);
  Serial.print("cm");
  Serial.println();
  } else {
    Serial.print("Over ");
    Serial.print(400);
    Serial.print("cm");
    Serial.println();
  }
}

// Varslefunksjonen tar lest avstand, avstand det skal varsles innen og 
// hvor lenge det skal varsles som argument
void varsle(int dist, int varsleAvst, int sek) {

  // Maalt avstand til et objekt er innenfor varsleavstand
   if (dist <= varsleAvst) {
    for (int i = 0; i < sek; i++) {
      // Lampen blinker i gitt antall sekunder
      digitalWrite(varselLed, HIGH);
      // Hvis lydbryter er paa faar vi lydsignal ogsaa
      if (volumKontroll() == 1) { 
        tone(piezoOut, 440, 100);
      }
      delay(500);
      digitalWrite(varselLed, LOW);
      delay(500);
     }
    } 
}

// Funksjon for aa sende en radarpuls pulseIn() kan lese
// Sender foerst en liten puls i 5 mikrosek, anbefalt for aa 
// faa et renest mulig signal. 
void radarPulse() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

// Leser fra potmeter om bruker oensker lyd eller ikke
// Har bare av eller paa for naa
int volumKontroll() {
  potV = analogRead(potPin);
  pos = map(potV, 0, 1023, 0, 1);
  return pos;
}