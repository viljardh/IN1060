// *** DEKLARASJONER ***

// Deklarerer pins vi skal bruke og hvor de er koblet. 
// Bruker konstanter i tilfelle jeg maa stokke om. 
const int potPin = A0;
const int piezoOut = 10;
const int ledOpen = 2;
const int ledLocked = 3;
const int ledPos0 = 4;
const int ledPos1 = 5;
const int ledPos2 = 6;
const int ledPos3 = 7;
const int buttInput = 8;
const int buttReset = 9;

// Toner for trudelutt
const int G4 = 392;
const int C5 = 523;
const int E5 = 659;
const int G5 = 784;

// Variable til potmeteret sin spenning, posisjon som foelge av
// mapping og en liste over saann at vi kan lage en loekke. 
int potV;
int pos;
int posList [7] = {ledPos0, ledPos1, ledPos2, ledPos3, ledOpen, ledLocked, piezoOut};

// Deklarerer strings for koden og for forsoek
const String code = "0123";
String attempt;

// *** SETUP ***

void setup() {
  Serial.begin(9600);

  // Loekke for aa deklarere outputs
  for (int i = 0; i < 7; i++) {
    pinMode(posList[i], OUTPUT);
  }

  // Pullup for knapper fordi jeg liker pullup
  pinMode(buttInput, INPUT_PULLUP);
  pinMode(buttReset, INPUT_PULLUP);
}

// *** LOOP ***

void loop() {
  // I utgangspunktet laast, lagde en funksjon som viser det
  locked();

  // Map for pin som skal lese potmeteret sitt input, hvilken spenning
  // som kommer inn og hvilken output den skal gi basert paa det. Her 
  // vil den gi output heltall mellom 0 og 5 basert paa input mellom 0
  // og 810, da jeg ikke trenger de resterende 413 verdiene. 
  potV = analogRead(potPin);
  pos = map(potV, 0, 810, 0, 4);

  // Loekke som kjoerer kontinuerlig og skrur av alle LEDs som viser
  // posisjon for input, men lyser opp den som er valgt. 
  // De fire foerste elementene i posList er dedikert til 
  // LEDs som viser posisjon til "skiven". 
  for (int i = 0 ; i < 4; i++) {

    // ok saa
    // Jeg vet ikke hvorfor denne maa vaere her. Men naar den er her funker alt
    // som jeg vil. Ikke >= 4. Ikke == 5. Ikke noe annet. Ellers blir det ikke 
    // riktig mtp at jeg ikke bruker hele rekkevidden til potmeteret og hvilke
    // paerer som lyser. Jeg gir opp. 
    if (pos == 4) {
      break;
      }

    dialOff();
    digitalWrite(posList[pos], HIGH);
    }
  
  // Knappen som brukes for aa lese input, kaller paa funksjonen
  // som leser inputs og lagrer i strengen for kombinasjonsforsoek.
  if (digitalRead(buttInput) == LOW) {
    input(pos);
  }

  // Knappen som brukes for aa resette forsoeket, kaller paa
  // funksjon som toemmer strengen. 
  if (digitalRead(buttReset) == LOW) {
    reset();
  }
  
  // Sjekker kontinerlig om bruker har gitt riktig kode. Aapner i
  // saa fall laasen, skrur av "kodeskiven" og spiller en liten fanfare.
  // Laasen er aapen i 5 sek. 
  if (code == attempt) {
    open();
    dialOff();
    playOpen();
    delay(5000);
    playLock();
    attempt = "";
  }

  // Oppdaterer hvert 1/10 sekund, tilstrekkelig for vaare formaal. 
  Serial.println(pos);

  delay(100);
}

// *** FUNKSJONER ***

// Funksjon for aa trykke inn koden. Lagrer inputposisjon i streng og
// spiller av en liten tone. 
void input(int inp) {
  attempt += inp;
  tone(piezoOut, G4, 100);
  delay(250);
}

// Funksjon for aa resette forsoek. Toemmer strengen og spiller av en 
// sur tone. 
void reset() {
  attempt = "";
  tone(piezoOut, 249, 250);
}

// Funksjon for aa skru av "kodeskiven". 
void dialOff() {
  digitalWrite(ledPos0, LOW);
  digitalWrite(ledPos1, LOW);
  digitalWrite(ledPos2, LOW);
  digitalWrite(ledPos3, LOW);
}

// Funksjon som viser at laasen er laast. 
void locked() {
  digitalWrite(ledOpen, LOW);
  digitalWrite(ledLocked, HIGH);
}

// Funksjon som viser ta laasen er aapen. 
void open() {
  digitalWrite(ledOpen, HIGH);
  digitalWrite(ledLocked, LOW);
}

// Spiller av en liten fanfare. Maatte lages saa vanskelig
// som du ser fordi jeg ville faa til staccato, dessverre ingen
// funksjon for aa forenkle det. 
void playOpen() {
  tone(piezoOut, C5);
  delay(100);
  noTone(piezoOut);
  delay(100);
  tone(piezoOut, E5);
  delay(100);
  noTone(piezoOut);
  delay(100);
  tone(piezoOut, G5);
  delay(300);
  noTone(piezoOut);
  delay(100);
  tone(piezoOut, E5);
  delay(100);
  noTone(piezoOut);
  delay(100);
  tone(piezoOut, G5);
  delay(300);
  noTone(piezoOut);
}

// Liten fanfare for aa vise at den laaser. 
void playLock() {
  tone(piezoOut, G5);
  delay(200);
  tone(piezoOut, E5);
  delay(200);
  tone(piezoOut, C5);
  delay(200);
  noTone(piezoOut);
  }
