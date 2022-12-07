#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// DHT11 definitions

#define DHT_PIN 7
#define DHT_TYPE DHT11

// LCD_I2C definitions

#define LCD_COL_NUM 16 // LCD columns
#define LCD_LINE_NUM 2 // LCD rows
#define LCD_ADDR 0x27  // LCD I2C address

// RGB LED definitions

#define RED_LED_PIN 2
#define GREEN_LED_PIN 3
#define BLUE_LED_PIN 4

// Buzzer definition

#define BUZZER_PIN 5

// Function prototypes

void initLCD(void);
void showInitialScreen(void);
void showFailScreen(void);

float getDHTTemperature(void);
int getDHTHumidity(void);

void setClimateOption(int);

void showTemperatureOnLCD(float);
void showHumidityOnLCD(int);

DHT dht(DHT_PIN, DHT_TYPE); // creates new DHT instance
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COL_NUM,
                      LCD_LINE_NUM); // creates new LCD_I2C instance

void setup(void) {
  Serial.begin(9600);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  dht.begin();

  initLCD();

  showInitialScreen();
}

void loop(void) {

  float temperature = 30;
  int humidity = 30;

  if (isnan(temperature) || isnan(humidity))

    showFailScreen();

  else {

    lcd.clear();

    showTemperatureOnLCD(temperature);
    showHumidityOnLCD(humidity);

    if ((temperature >= 24 && temperature <= 26) && humidity >= 51)
      setClimateOption(1); // good temperature / humidity
    else if ((temperature >= 20 && temperature <= 23) &&
             (humidity >= 31 && humidity <= 50))
      setClimateOption(2); // average temperature / humidity
    else if ((temperature >= 27 && humidity <= 30))
      setClimateOption(3); // bad temperature / humidity

    delay(1000 * 3 * 1); // 15 seconds
  }
}

// initializes LCD
void initLCD(void) {

  lcd.init();
  lcd.backlight();
  lcd.clear();
}

// get temperature data from sensor
float getDHTTemperature(void) {

  float temperature = 0.00f;

  temperature = dht.readTemperature();

  return temperature;
}

// get humidity data from sensor
int getDHTHumidity(void) {

  int humidity = 0;

  humidity = dht.readHumidity();

  return humidity;
}

// set climate option
void setClimateOption(int option) {

  switch (option) {
  case 1:
    digitalWrite(RED_LED_PIN, 0);
    digitalWrite(GREEN_LED_PIN, 1);
    digitalWrite(BLUE_LED_PIN, 0);
    break;

  case 2:
    digitalWrite(RED_LED_PIN, 1);
    digitalWrite(GREEN_LED_PIN, 1);
    digitalWrite(BLUE_LED_PIN, 0);
    break;

  case 3:
    digitalWrite(RED_LED_PIN, 1);
    digitalWrite(GREEN_LED_PIN, 0);
    digitalWrite(BLUE_LED_PIN, 0);

    for (int i = 0; i < 4; i++) {

      digitalWrite(BUZZER_PIN, 1);
      delay(70);
      digitalWrite(BUZZER_PIN, 0);
      delay(70);
    }

    break;

  default:
    break;
  }
}

// show temperature on lcd screen
void showTemperatureOnLCD(float temperature) {
  lcd.setCursor(0, 0);
  lcd.print("Temp.: ");
  lcd.setCursor(7, 0);
  lcd.print(temperature);
}

// show humidity on lcd screen
void showHumidityOnLCD(int humidity) {
  lcd.setCursor(0, 1);
  lcd.print("Humi.: ");
  lcd.setCursor(7, 1);
  lcd.print(humidity);
}

// show initial screen
void showInitialScreen(void) {
  lcd.setCursor(0, 0);
  lcd.print("  Ativ. Ext. II ");
  lcd.setCursor(0, 1);
  lcd.print("     Uninter    ");

  delay(3000);

  lcd.setCursor(0, 0);
  lcd.print(" Carlos Miranda ");
  lcd.setCursor(0, 1);
  lcd.print("     3793087    ");

  delay(3000);

  lcd.clear();
}

// show fail screen is sensor reading fails
void showFailScreen(void) {
  lcd.setCursor(0, 0);
  lcd.print("  Falha ao ler  ");
  lcd.setCursor(0, 1);
  lcd.print(" dados do DHT11.");
}