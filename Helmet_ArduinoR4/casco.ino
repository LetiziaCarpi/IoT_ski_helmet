#include "DHT.h"
#include <Arduino_Modulino.h>
#include <ArduinoBLE.h>
#include <math.h>

ModulinoMovement movement;

/* ---------- SENSORI ---------- */
#define DHTPIN 2
#define DHTTYPE DHT11
#define LDR_PIN A0

DHT dht(DHTPIN, DHTTYPE);

/* ---------- ATTUATORI ---------- */
int buzzer = 9;
int led = 7;          // LED CADUTA
int sogliaLuce = 150;

/* ---------- BLE ---------- */
BLEService infoService("180A");
BLEByteCharacteristic infoChar("2A57", BLERead | BLEWrite);
bool isConnected = false;

/* ---------- MOVIMENTO ---------- */
float x, y, z;
bool inCaduta = false;

/* soglie caduta (in g) */
#define FREE_FALL 0.6
#define IMPACT    1.2

void setup() {
  Serial.begin(9600);
  Serial.println("Avvio sensori...");

  dht.begin();
  Modulino.begin();
  movement.begin();

  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  /* ---------- BLE ---------- */
  if (!BLE.begin()) {
    Serial.println("Errore avvio BLE");
    while (1);
  }

  BLE.setLocalName("UNO_R4_BLE");
  BLE.setAdvertisedService(infoService);
  infoService.addCharacteristic(infoChar);
  BLE.addService(infoService);
  BLE.advertise();

  Serial.println("BLE pronto, in attesa di connessione...");
}

void loop() {

  /* ---------- DHT + LDR ---------- */
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int luce = analogRead(LDR_PIN);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Errore DHT11");
    return;
  }


 // Stampa valori 
  Serial.print("Umidita': "); 
  Serial.print(humidity); 
  Serial.print(" % "); 
  Serial.print("Temperatura: "); 
  Serial.print(temperature); 
  Serial.print(" °C "); 
  Serial.print("Luce (raw): "); 
  Serial.print(luce); 
  Serial.print(" --> "); 
  
  // LUCE / BUIO 
  bool buio = false; 
  if (luce > sogliaLuce) { 
    Serial.println("BUIO"); 
    buio = true; 
    } else { 
      Serial.println("LUCE");
    } 
    
    // CONDIZIONE NEBBIA 
    if (buio && temperature < 10 && humidity > 85) { 
      Serial.println("⚠ ATTENZIONE: NEBBIA PRESENTE"); 
      digitalWrite(led, HIGH); 
      } else { 
        Serial.println("Condizioni meteo normali"); 
        digitalWrite(led, LOW);
      }


  /* ---------- MOVIMENTO ---------- */
  movement.update();

  x = movement.getX();
  y = movement.getY();
  z = movement.getZ();

  float accTot = sqrt(x*x + y*y + z*z);

  Serial.print("Acc totale: ");
  Serial.println(accTot, 2);

  /* ---------- RILEVAMENTO CADUTA (CORRETTO) ---------- */

  // Fase 1: quasi assenza di gravità
  if (accTot < FREE_FALL) {
    inCaduta = true;
  }

  // Fase 2: impatto
  if (inCaduta && accTot > IMPACT) {
    Serial.println("🚨 CADUTA RILEVATA!");

    digitalWrite(led, HIGH);
    tone(buzzer, 1000);

    delay(3000);

    digitalWrite(led, LOW);
    noTone(buzzer);

    inCaduta = false;
  }

  /* ---------- BLE ---------- */
  BLE.poll();
  BLEDevice central = BLE.central();

  if (central && !isConnected) {
    isConnected = true;
    Serial.print("Connesso a: ");
    Serial.println(central.address());
  }

  if (!central && isConnected) {
    isConnected = false;
    Serial.println("Disconnesso");
  }

  Serial.println("-----------------------------");
  delay(500);
}
