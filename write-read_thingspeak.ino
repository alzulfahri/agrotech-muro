#include <WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
#include <elapsedMillis.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 4
#define DHTTYPE DHT21
#define HYGRO 34
#define RELAY_1 26
#define RELAY_2 25
#define RELAY_3 17
#define RELAY_4 16

#define WIFI_SSID "UGMURO-INET"
#define WIFI_PASSWORD "Gepuk15000"

unsigned long thingSpeakInterval  = 15000;
unsigned long sensorInterval      = 5000;
unsigned long controlInterval     = 5000; 
unsigned long displayInterval     = 5000; 

unsigned int lampField    = 4;
unsigned long channelNum  = 2593423;
const char* ReadAPIKey    = "FFRWJ6PFFLFCXIZZ";
const char* WriteAPIKey   = "UYFUNLQMWU4ZTC2Y";

float h, c, f, hi;
int lampStatus, soil, soilPercentage;

DHT dht (DHTPIN, DHTTYPE);
elapsedMillis thingSpeakMillis;
elapsedMillis sensorMillis;
elapsedMillis controlMillis;
elapsedMillis displayMillis;
WiFiClient client;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C (0x27, 20, 4);

void setup() 
{
  Serial.begin (115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  lcd.init();
  lcd.backlight();

  pinMode (HYGRO, INPUT);

  pinMode (RELAY_1, OUTPUT);
  pinMode (RELAY_2, OUTPUT);
  pinMode (RELAY_3, OUTPUT);
  pinMode (RELAY_4, OUTPUT);
  
  dht.begin();
  ThingSpeak.begin(client);

  lcd.setCursor (0, 0);
  lcd.print (" IoT & MCS | AGR-05 ");
  lcd.setCursor (0, 1);
  lcd.print ((char)223);
  lcd.print ("C Air  :");
  lcd.setCursor (0, 2);
  lcd.print ("%  Air  :");
  lcd.setCursor (0, 3);
  lcd.print ("%  Soil :");

  lcd.setCursor (15, 1);
  lcd.print("|");
  lcd.setCursor (15, 2);
  lcd.print("|");
  lcd.setCursor (15, 3);
  lcd.print("|");

  lcd.setCursor (16, 1);
  lcd.print("R1=");
  lcd.setCursor (16, 2);
  lcd.print("R2=");
  lcd.setCursor (16, 3);
  lcd.print("R3=");
}

void loop() 
{
  if (sensorMillis >= sensorInterval)
  {
    h = dht.readHumidity();
    c = dht.readTemperature();

    soil = analogRead (HYGRO);
    soilPercentage = map (soil, 0, 4095, 100, 0);

    Serial.print("Humidity    : "); 
    Serial.print(h);
    Serial.println("%");
    Serial.print("Temperature : "); 
    Serial.print(c);
    Serial.println("*C");
    Serial.print("Soil        : "); 
    Serial.print(soilPercentage);
    Serial.println("%");
    Serial.println("=========================");
    Serial.print("Lamp Status : "); 
    if (lampStatus == -1)
    {
      lampStatus = 0;
    }
    Serial.println(lampStatus);
    Serial.println("=========================");

    sensorMillis = 0;
  }

  if (thingSpeakMillis >= thingSpeakInterval)
  {
    ThingSpeak.setField (1, c);
    ThingSpeak.setField (2, h);
    ThingSpeak.setField (3, soilPercentage);

    ThingSpeak.writeFields (channelNum, WriteAPIKey);

    lampStatus = ThingSpeak.readIntField (channelNum, lampField, ReadAPIKey);

    thingSpeakMillis = 0;
  }

  if (displayMillis >= displayInterval)
  {
    lcd.setCursor (10, 1);
    lcd.print("     ");
    lcd.setCursor (10, 1);
    lcd.print(c);
    lcd.setCursor (10, 2);
    lcd.print("     ");
    lcd.setCursor (10, 2);
    lcd.print(h);
    lcd.setCursor (10, 3);
    lcd.print("     ");
    lcd.setCursor (10, 3);
    lcd.print(soilPercentage);

    lcd.setCursor (19, 2);
    lcd.print(lampStatus);

    displayMillis = 0;
  }

  if (controlMillis >= controlInterval)
  {
    if (lampStatus == 1)
    {
      digitalWrite (RELAY_2, HIGH);
    }
    else
    {
      digitalWrite (RELAY_2, LOW);
    }

    controlMillis = 0;
  }
}
