#include <DHT.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Pinovi za LCD displej
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Pin i inicijalizacija za DHT22 senzor
#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Pin od releja
int RELAYPIN = 9;

// Pinovi za Bluetooth modul
SoftwareSerial bt(10, 11); //Definiranje SoftwareSerial objekta

void setup() {
  // Inicijalizacija LCD displeja
  lcd.begin(16, 2);
  
  // Inicijalizacija Bluetooth modula
  bt.begin(9600);
  
  // Inicijalizacija DHT senzora
  dht.begin();
  
  // Postavljanje relej pina kao izlaznog pina
  pinMode(RELAYPIN, OUTPUT);
  
  // Pocetno stanje releja (ugasen)
  digitalWrite(RELAYPIN, LOW);
}

void loop() {
  // Citaj temperaturu i vlagu sa DHT senzora
  float temperatura = dht.readTemperature();
  
  // Proveri da li je citanje uspesno
  if (isnan(temperatura)) {
    lcd.print("Error");
    return;
  }
  
  // Ispisi temperaturu na LCD displej
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print(" C");
  
  // Proveri da li je temperatura veca od 50 stepeni
  if (temperatura > 50) {
    // Ukljuci relej
    digitalWrite(RELAYPIN, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Fan: ON");
  } else {
    // Iskljuci relej
    digitalWrite(RELAYPIN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Fan: OFF");
  }
  
  // Proveri da li je stigao Bluetooth podatak
  if (bt.available()) {
    char command = bt.read();
    
    // Proveri komandu sa Bluetooth-a
    if (command == '1') {
      // Ukljuci relej
      digitalWrite(RELAYPIN, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("Fan: ON ");
    } else if (command == '0') {
      // Iskljuci relej
      digitalWrite(RELAYPIN, LOW);
      lcd.setCursor(0, 1);
      lcd.print("Fan: OFF");
    }
  }
}
