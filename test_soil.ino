#include <LiquidCrystal_I2C.h>
#include <SoilHygrometer.h> 
// Inisialisasi LCD I2C (alamat I2C biasanya 0x27 atau 0x3F)
LiquidCrystal_I2C lcd(0x27, 20, 4);
const int soilPin = 34;;
int soilValue;
int soilPersentage;

void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(115200);
  pinMode(soilPin, INPUT);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ESP32 Testing");
}
void loop() {
  soilValue = analogRead(soilPin);
  soilPersentage = (0, 4095, 0 , 100);
  
  // Tampilkan suhu, kelembaban, dan nilai potensiometer pada LCD
  lcd.setCursor(0, 0);
  lcd.print("Water Level: ");
  lcd.print(soilPersentage);
  // lcd.print(soilValue);
  lcd.print(" %");

  lcd.setCursor(0, 1);
  lcd.print(soilValue);
  // Tampilkan nilai pada Serial Monitor
  Serial.println("Water Level : ");
  Serial.println(soilValue);
  Serial.println(soilPersentage);

  delay(500);
}