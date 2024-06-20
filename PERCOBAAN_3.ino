
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Inisialisasi LCD I2C (alamat I2C biasanya 0x27 atau 0x3F)
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Definisikan pin untuk relay
const int relayPin = 25;

// Definisikan pin untuk sensor DHT22
#define DHTPIN 4
#define DHTTYPE DHT22

// Inisialisasi sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Pin ADC untuk potensiometer
const int potPin = 34;

void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(115200);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ESP32 Testing");

  // Inisialisasi pin relay sebagai output
  pinMode(relayPin, OUTPUT);

  // Mulai sensor DHT
  dht.begin();

  // Awal relay dalam kondisi mati
  digitalWrite(relayPin, LOW);

}
void loop() {
  // Baca suhu dan kelembaban dari sensor DHT22
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Cek jika pembacaan gagal
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0, 1);
    lcd.print("Failed to read DHT!");
    return;
  }

  // Baca nilai dari potensiometer
  int potValue = analogRead(potPin);

  // Konversi nilai potensiometer (0-4095) ke tegangan (0-3.3V)
  float voltage = potValue * (3.3 / 4095.0);

  // Tampilkan suhu, kelembaban, dan nilai potensiometer pada LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print(" %");

  lcd.setCursor(0, 2);
  lcd.print("Pot: ");
  lcd.print(potValue);

  lcd.setCursor(0, 3);
  lcd.print("Volt: ");
  lcd.print(voltage);
  lcd.print(" V");

  // Tampilkan nilai pada Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C, Hum: ");
  Serial.print(humidity);
  Serial.print(" %, Pot: ");
  Serial.print(potValue);
  Serial.print(", Volt: ");
  Serial.println(voltage);

  // Logika pengendalian relay berdasarkan suhu atau kelembaban
  if (temperature > 25.0) {
    // Jika suhu di atas 25°C, nyalakan relay
    digitalWrite(relayPin, HIGH);
  } else {
    // Jika suhu di bawah atau sama dengan 25°C, matikan relay
    digitalWrite(relayPin, LOW);
  }

  delay(2000);
}
