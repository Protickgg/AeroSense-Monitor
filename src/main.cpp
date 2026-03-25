#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>

const int trigPin = 4;
const int echoPin = 5;
long duration;
int distance;
int gasSensor = A0;
int gasValue;

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(7, DHT11);

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.init();
  lcd.backlight(); 
  lcd.setCursor(0, 0);
  dht.begin();
}

void loop() {
  delay(2000);

  // DIST SENSOR

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
                              
  duration = pulseIn(echoPin, HIGH);
  distance = duration *0.0343 / 2;

  lcd.clear();
  lcd.setCursor(10,1);
  lcd.print(distance); 
  lcd.print("cm");

  // GAS SENSOR

  gasValue = analogRead(gasSensor);
  lcd.setCursor(0, 0);

  if (gasValue <= 600) {
    lcd.print("Very Good AQ");
  } else if (gasValue <= 900) {
    lcd.print("Moderate AQ"); 
  } else if (gasValue <= 1023) {
    lcd.print("Dangerous AQ");
  } else {
    lcd.print("Please Wait for data to load.");
  }

  // DHT SENSOR 

  float t = dht.readTemperature();
  
  lcd.setCursor(0, 1);
  lcd.print(t);
  lcd.print(" C");

  // Data to export: t (temp.), gasValue (gas quality) and distance (dist. from an obj.) 
  Serial.println(t);
  Serial.println(distance);
  Serial.println(gasValue);
} 
