const int switchPin = 8;        // port 8 skal være input for når knappen trykkes
unsigned long previousTime = 0; // holder styr på hvor mye tid som har gått
int switchState = 0;            // hvis knappen blir trykket
int prevSwitchState = 0;        // hvis knappen har blitt trykket
int led = 2;                    // vi starter på port 2
long interval = 1000;           // jeg justerte tidsintervallet ned til 1s 


void setup() {
  // loop som deklarerer at port 2-7 skal være output
  for(int x = 2;x<8;x++){
    pinMode(x, OUTPUT);
  }
  // port 8 skal holde koll på når knappen trykkes
  pinMode(switchPin, INPUT);
}

void loop(){
  // en klokke som holder styr på hvor lang tid det har gått siden start
  unsigned long currentTime = millis();
  // hvis 1000 ms har gått slår if-testen ut, oppdaterer tiden og går videre i portrekka
  if(currentTime - previousTime > interval) {
    previousTime = currentTime;  
    digitalWrite(led, HIGH);
    led++;
    // hvis vi er på port 7 stopper vi, ikke mer å lyse opp.
    if(led == 7){
    }
    // sjekker om knappen er trykket, og hvis så, skrur vi av alle lampene og resetter
    switchState = digitalRead(switchPin);
    if(switchState != prevSwitchState){
      for(int x = 2;x<8;x++){
        digitalWrite(x, LOW);
      }
      led = 2;
      previousTime = currentTime;
    }
  prevSwitchState = switchState;
  }
}
