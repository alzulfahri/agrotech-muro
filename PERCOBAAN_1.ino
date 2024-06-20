//PERCOBAAN 1 AGROTEK UGMURO (WOKWI ONLY)

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
const int potPin = 34;

void setup() {

  Serial.begin(115200);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LCD 20x4 & Potensiometer");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Baca nilai dari potensiometer
  int potValue = analogRead(potPin);

  // Konversi nilai potensiometer (0-4095) ke tegangan (0-3.3V)
  float voltage = potValue * (3.3 / 4095.0);

  lcd.setCursor(0, 0);
  lcd.print("Pot Value: ");
  lcd.print(potValue);

  lcd.setCursor(0, 1);
  lcd.print("Voltage: ");
  lcd.print(voltage);
  lcd.print(" V");

  Serial.print("Pot Value: ");
  Serial.print(potValue);
  Serial.print(" | Voltage: ");
  Serial.println(voltage);

  delay(500);
}