#include <DHT.h>

// Definisikan pin untuk relay
const int relay1Pin = 25;
const int relay2Pin = 26;

// Definisikan pin untuk sensor DHT22
#define DHTPIN 4

// Tentukan jenis sensor DHT yang digunakan
#define DHTTYPE DHT22

// Inisialisasi sensor DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(115200);
  
  // Inisialisasi pin relay sebagai output
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);

  // Mulai sensor DHT
  dht.begin();
  
  // Awal relay dalam kondisi mati
  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay2Pin, LOW);
}

void loop() {
  // Baca suhu dan kelembaban dari sensor DHT22
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Cek jika pembacaan gagal
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Gagal membaca sensor DHT22");
    return;
  }

  // Tampilkan suhu dan kelembaban pada Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Logika pengendalian relay berdasarkan suhu atau kelembaban
  if (temperature > 25.0) {
    // Jika suhu di atas 25°C, nyalakan relay 1
    digitalWrite(relay1Pin, HIGH);
  } else {
    // Jika suhu di bawah atau sama dengan 25°C, matikan relay 1
    digitalWrite(relay1Pin, LOW);
  }

  if (humidity > 60.0) {S
    // Jika kelembaban di atas 60%, nyalakan relay 2
    digitalWrite(relay2Pin, HIGH);
  } else {
    // Jika kelembaban di bawah atau sama dengan 60%, matikan relay 2
    digitalWrite(relay2Pin, LOW);
  }

  // Tunggu 2 detik sebelum pembacaan berikutnya
  delay(2000);
}
