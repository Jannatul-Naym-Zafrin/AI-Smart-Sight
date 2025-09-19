#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

// === Sensor Pin Definitions ===
#define IR_SENSOR_PIN   2     // IR sensor output
#define TRIG_PIN        14    // Ultrasonic TRIG
#define ECHO_PIN        15    // Ultrasonic ECHO (with voltage divider)
#define BUZZER_PIN      13    // Active buzzer (HIGH = sound)
#define GPS_RX_PIN      16    // From GPS TX
#define GPS_TX_PIN      17    // To GPS RX (optional)

// === Constants ===
#define DISTANCE_THRESHOLD_CM 76
#define BUZZ_DURATION_MS      500

// === GPS Setup ===
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);  // Use UART1

void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);  // GPS on UART1

  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("Smart Stick Initialized: IR + Ultrasonic + Buzzer + GPS");
}

void loop() {
  readGPS();  // Always read GPS in background

  bool irObstacle = detectIRObstacle();
  bool usObstacle = detectUltrasonicObstacle();

  if (irObstacle || usObstacle) {
    Serial.println("⚠️ Obstacle Detected! Activating Buzzer...");
    buzzAlert();
    printLocation();
  }

  delay(200);
}

// === IR Detection ===
bool detectIRObstacle() {
  int irState = digitalRead(IR_SENSOR_PIN);
  if (irState == LOW) {
    Serial.println("IR Sensor: Obstacle Detected");
    return true;
  }
  return false;
}

// === Ultrasonic Detection ===
bool detectUltrasonicObstacle() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 25000);  // Timeout ~25ms
  if (duration == 0) return false;

  float distanceCM = duration * 0.034 / 2;
  Serial.print("Ultrasonic Distance: ");
  Serial.print(distanceCM);
  Serial.println(" cm");

  return (distanceCM > 0 && distanceCM < DISTANCE_THRESHOLD_CM);
}

// === Buzzer Alert ===
void buzzAlert() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(BUZZ_DURATION_MS);
  digitalWrite(BUZZER_PIN, LOW);
}

// === Read GPS Data Continuously ===
void readGPS() {
  while (SerialGPS.available()) {
    gps.encode(SerialGPS.read());
  }
}

// === Print GPS Location if Available ===
void printLocation() {
  if (gps.location.isValid()) {
    Serial.print("📍 Location: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(", ");
    Serial.println(gps.location.lng(), 6);
  } else {
    Serial.println("📡 Waiting for GPS fix...");
  }
}
