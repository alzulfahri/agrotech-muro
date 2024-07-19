#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int soilPin = A0; // Ganti dengan pin yang sesuai

// Buat objek LCD dengan alamat I2C 0x27 dan ukuran 20x4
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Serial.begin(9600);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

  // Tampilkan pesan selamat datang di LCD
  lcd.setCursor(0, 0);
  lcd.print("Selamat Datang!");
  lcd.setCursor(0, 1);
  lcd.print("Soil Monitoring");
  delay(2000); // Tampilkan selama 2 detik
  lcd.clear();
}

void loop() {
  int soilValue = analogRead(soilPin); // Membaca nilai analog dari sensor
  int soilPercentage = map(soilValue, 4095, 0, 0, 100); // Mengonversi nilai analog menjadi persentase
  
  // Membatasi nilai agar berada dalam rentang 0 - 100
  soilPercentage = constrain(soilPercentage, 0, 100);

  // Cetak hasil ke serial monitor
  Serial.print("Soil Moisture: ");
  Serial.print(soilPercentage);
  Serial.println("%");

  // Tampilkan hasil di LCD
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture:");
  lcd.setCursor(0, 1);
  lcd.print("Kelembaban: ");
  lcd.print(soilPercentage);
  lcd.print("%");

  delay(1000); // Delay 1 detik sebelum pembacaan berikutnya
}
