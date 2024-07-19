#include <WiFi.h>
#include <ThingSpeak.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 26
#define DHTTYPE DHT21
#define RELAY1_PIN 25 
#define RELAY2_PIN 17  
#define RELAY3_PIN 16

const char* ssid = "UGMURO-INET";           // Ganti dengan SSID WiFi kamu
const char* password = "Gepuk15000";   // Ganti dengan password WiFi kamu
const char* writeAPIKey = "23S6TRRV7BVLQ2QO"; // Ganti dengan Write API Key ThingSpeak kamu
const unsigned long channelID = 2592762; // Ganti dengan Channel ID ThingSpeak kamu

WiFiClient client;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int soilPin = 34;
int soilValue;
int soilPercentage;

void setup() {
  Serial.begin(115200);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Selamat Datang!");
  lcd.setCursor(0, 1);
  lcd.print("WS Agroteknologi IoT");
  lcd.setCursor(3, 3);
  lcd.print("-- UG MURO --");
  delay(5000);
  lcd.clear();
  delay(2000);

  pinMode(soilPin, INPUT);
  dht.begin();

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  digitalWrite(RELAY1_PIN, HIGH);  // HIGH to turn relay OFF
  digitalWrite(RELAY2_PIN, HIGH);  // HIGH to turn relay OFF
  digitalWrite(RELAY3_PIN, HIGH);  // HIGH to turn relay OFF

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  ThingSpeak.begin(client);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soilValue = analogRead(soilPin);                   // Membaca nilai analog dari sensor
  int soilPercentage = map(soilValue, 4095, 0, 0, 100);  // Membalik rentang konversi
  soilPercentage = constrain(soilPercentage, 0, 100);

  // Display data on LCD
  lcd.setCursor(5, 0);
  lcd.print("Monitoring");

  lcd.setCursor(0, 1);
  lcd.print("Suhu   : ");
  lcd.setCursor(9, 1);
  lcd.print(temperature);
  lcd.setCursor(16, 1);
  lcd.print(char(223));
  lcd.print("C");

  lcd.setCursor(0, 2);
  lcd.print("K.Udara: ");
  lcd.setCursor(9, 2);
  lcd.print(humidity);
  lcd.setCursor(17, 2);
  lcd.print("%");

  lcd.setCursor(0, 3);
  lcd.print("K.Tanah: ");
  lcd.setCursor(9, 3);
  lcd.print("       "); //6 spasi
  lcd.setCursor(9, 3);
  lcd.print(soilPercentage);
  lcd.setCursor(17, 3);
  lcd.print("%");

  // Display data on Serial Monitor
  Serial.println("Data Pembacaan Sensor:");
  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Kelembaban: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Kelembaban Tanah: ");
  Serial.print(soilPercentage);
  Serial.println(" %");
  Serial.println("-----------------------");

  // Algoritma untuk menyalakan relay
  if (temperature > 24 && humidity > 70) {
    digitalWrite(RELAY1_PIN, LOW); // Relay 1 menyala
  } else {
    digitalWrite(RELAY1_PIN, HIGH); // Relay 1 mati
  }

  if (soilPercentage < 30) {
    digitalWrite(RELAY3_PIN, LOW); // Relay 2 (pompa) menyala
  } else {
    digitalWrite(RELAY3_PIN, HIGH); // Relay 2 (pompa) mati
  }

  // Kirim data ke ThingSpeak
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, soilPercentage);
  
  int x = ThingSpeak.writeFields(channelID, writeAPIKey);
  if (x == 200) {
    Serial.println("Update successful.");
  } else {
    Serial.println("Update failed. HTTP error code: " + String(x));
  }

  delay(1000);
}
