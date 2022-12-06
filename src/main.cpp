#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// DHT11 definitions

#define DHT_PIN A0
#define DHT_TYPE DHT11

// LCD_I2C definitions

#define LCD_COL_NUM 16 // LCD columns
#define LCD_LINE_NUM 2 // LCD rows
#define LCD_ADDR 0x27  // LCD I2C address

// LED's definitions

#define RED_LED_PIN 2
#define GREEN_LED_PIN 3
#define BLUE_LED_PIN 4

// Buzzer definition

#define BUZZER_PIN 5

void initLCD(void);
float readTemperature(void);
float readHumidity(void);
void toggleRedLed(int);
void toggleGreenLed(int);
void toggleBlueLed(int);

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COL_NUM, LCD_LINE_NUM);

void setup(void) {
  Serial.begin(9600);

  Serial.println("Atividade Extensionsista II - Carlos E. Miranda (3793087)");

  initLCD();
}

void loop(void) {

  float temperature = readTemperature();
  float humidity = readHumidity();

  if (isnan(temperature) || isnan(humidity))

    Serial.println("Failed trying to read DHT11.");

  else {

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");

    toggleRedLed(2000);
    toggleGreenLed(2000);
    toggleBlueLed(2000);
  }

  delay(1000);
}

void initLCD(void) {

  lcd.init();      // Starts LCD communication
  lcd.backlight(); // Turns on LCD backlight
  lcd.clear();     // Clear LCD screen
}

float readTemperature(void) {

  float temperature = 0.00f;

  temperature = dht.readTemperature();

  return temperature;
}

float readHumidity(void) {

  float humidity = 0.00f;

  humidity = dht.readHumidity();

  return humidity;
}

void toggleRedLed(int delayInMs) {

  digitalWrite(RED_LED_PIN, 1);
  delay(delayInMs);
  digitalWrite(RED_LED_PIN, 0);
}

void toggleGreenLed(int delayInMs) {

  digitalWrite(GREEN_LED_PIN, 1);
  delay(delayInMs);
  digitalWrite(GREEN_LED_PIN, 0);
}

void toggleBlueLed(int delayInMs) {

  digitalWrite(BLUE_LED_PIN, 1);
  delay(delayInMs);
  digitalWrite(BLUE_LED_PIN, 0);
}