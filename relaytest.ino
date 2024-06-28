#define RELAY1_PIN 5 // D1
#define RELAY2_PIN 4 // D2
#define RELAY3_PIN 0 // D3

void setup() {
  // Set the relay pins as outputs
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);

  // Initialize relays to OFF state
  digitalWrite(RELAY1_PIN, HIGH); // HIGH to turn relay OFF
  digitalWrite(RELAY2_PIN, HIGH); // HIGH to turn relay OFF
  digitalWrite(RELAY3_PIN, HIGH); // HIGH to turn relay OFF
}

void loop() {
  // Turn on Relay 1
  digitalWrite(RELAY1_PIN, LOW); // LOW to turn relay ON
  delay(1000); // Wait for 1 second

  // Turn off Relay 1 and turn on Relay 2
  digitalWrite(RELAY1_PIN, HIGH); // HIGH to turn relay OFF
  digitalWrite(RELAY2_PIN, LOW); // LOW to turn relay ON
  delay(1000); // Wait for 1 second

  // Turn off Relay 2 and turn on Relay 3
  digitalWrite(RELAY2_PIN, HIGH); // HIGH to turn relay OFF
  digitalWrite(RELAY3_PIN, LOW); // LOW to turn relay ON
  delay(1000); // Wait for 1 second

  // Turn off Relay 3
  digitalWrite(RELAY3_PIN, HIGH); // HIGH to turn relay OFF
  delay(1000); // Wait for 1 second
}
