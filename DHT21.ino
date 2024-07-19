// http://arduino.esp8266.com/stable/package_esp8266com_index.json
// https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Tentukan pin yang digunakan untuk DHT21 dan tipe sensor
#define DHTPIN 4
#define DHTTYPE DHT21

// Buat objek DHT
DHT dht(DHTPIN, DHTTYPE);

// Buat objek LCD dengan alamat I2C 0x27 dan ukuran 20x4
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // Inisialisasi serial monitor
  Serial.begin(9600);
  Serial.println(F("DHT21 example!"));

  // Inisialisasi sensor DHT
  dht.begin();

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

  // Tampilkan pesan selamat datang di LCD
  lcd.setCursor(0, 0);
  lcd.print("Selamat Datang!");
  lcd.setCursor(0, 1);
  lcd.print("DHT21 Monitoring");
  delay(2000); // Tampilkan selama 2 detik
  lcd.clear();
}

void loop() {
  // Baca suhu dan kelembaban
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Cek apakah pembacaan berhasil
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    lcd.setCursor(0, 0);
    lcd.print("Error membaca DHT!");
    delay(2000); // Tampilkan pesan error selama 2 detik
    lcd.clear();
    return;
  }

  // Cetak hasil ke serial monitor
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C "));

  // Tampilkan hasil di LCD
  lcd.setCursor(0, 0);
  lcd.print("Monitoring DHT21");
  lcd.setCursor(0, 1);
  lcd.print("Kelembaban: ");
  lcd.print(humidity);
  lcd.print("%");

  lcd.setCursor(0, 2);
  lcd.print("Suhu      : ");
  lcd.print(temperature);
  lcd.print((char)223); // Simbol derajat
  lcd.print("C");

  delay(2000); // Tunggu 2 detik sebelum pembacaan berikutnya
}
