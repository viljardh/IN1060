// Oppgave 2.3

// Ville brukt koden under for å ha en stødig strøm. 
// Antar også at oppgaveteksten kretsen skal fullføres slik at LED-pæra skrus på 
// når knappen trykkes. 

/* 
Når knappen trykkes vil strømmen kunne krysse skillet i brødbreddet, eller er strømmen
bare på venstre side og ingenting skjer. 
Så for å koble alt sammen setter jeg en resistor fra J6 ned til J12 sånn at strømmen fra
en av knappens grønne linjer ledes ned til LED-pæra sin anode og strømmen kan gå inn. Deretter
setter jeg en overgang fra J10 på linje med LED-pæra sin katode over til raden som har jording
helt øverst på bildet. Trykk knappen, kretsen sluttees, pæra lyser.  
*/

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

void loop() {
}
