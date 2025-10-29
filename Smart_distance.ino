#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create LCD object (I2C address 0x27, 16x2 display)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define pins
#define trigPin A0      // HC-SR04 Trig pin
#define echoPin A1      // HC-SR04 Echo pin
#define buzzerPin 10    // Buzzer connected to digital pin 10

// Variables
long duration;
float distance;
float distanceInch;

void setup() {
  // Pin setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // LCD setup
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Distance");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo duration
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance (in cm and inches)
  distance = (duration * 0.034) / 2;     // distance in cm
  distanceInch = duration * 0.0133 / 2;  // distance in inches (optional)

  // Display distance
  lcd.setCursor(10, 0);
  lcd.print("    "); // clear old reading
  lcd.setCursor(10, 0);
  lcd.print(distance, 1);
  lcd.print("cm");

  // Check distance condition
  if (distance <= 10 && distance > 0) {
    digitalWrite(buzzerPin, HIGH);  // Turn ON buzzer
    lcd.setCursor(0, 1);
    lcd.print("Too Close! Alarm ");
  } else {
    digitalWrite(buzzerPin, LOW);   // Turn OFF buzzer
    lcd.setCursor(0, 1);
    lcd.print("                "); // Clear second line
  }

  delay(300);  // Slight delay for stable readings
}
