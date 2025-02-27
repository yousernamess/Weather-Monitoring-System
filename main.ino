#define BLYNK_PRINT Serial 
#define BLYNK_TEMPLATE_ID "TMPL33bzPybNX"
#define BLYNK_TEMPLATE_NAME "Weather Monitoring System"
#define BLYNK_AUTH_TOKEN "1LS_EjZ3iq-vrn2e-JrLcnFufAuP8hLu"

#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h> 
#include <DHT.h> 
#include <Adafruit_Sensor.h> 
#include <Adafruit_BMP085_U.h> 
#include <avr/pgmspace.h> 
 
// #define BLYNK_PRINT Serial 
// #define BLYNK_TEMPLATE_ID "TMPL33bzPybNX"
// #define BLYNK_TEMPLATE_NAME "Weather Monitoring System"
// #define BLYNK_AUTH_TOKEN "1LS_EjZ3iq-vrn2e-JrLcnFufAuP8hLu" 
 
// Initialize the LCD display 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
 
// Create an object for the BMP085 sensor 
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(); 
 
char auth[] = "1LS_EjZ3iq-vrn2e-JrLcnFufAuP8hLu"; // Enter your Auth token 
char ssid[] = "Wifi"; // Enter your WIFI name  
char pass[] = "Rahul123"; // Enter your WIFI password  

 
DHT dht(D4, DHT11); // (sensor pin, sensor type) 
BlynkTimer timer; 
 
// Define component pins 
#define rain A0 
#define light D0 
 
// Create variables for temperature and pressure 
float temperature; 
float pressureValue; // Renamed to avoid conflict with function name 
 
// Store constant messages in PROGMEM 
const char messageWeather[] PROGMEM = "Weather Monitor"; 
const char messageSystem[] PROGMEM = "System"; 
 
void setup() { 
  Serial.begin(9600); 
   
  // Initialize BMP085 sensor 
  if (!bmp.begin()) { 
    Serial.println("Couldn't find BMP085 chip"); 
    while (1); 
  } 
 
  // lcd.begin(); 
  lcd.begin(16, 2);  // For a 16x2 LCD

  lcd.backlight(); 
  pinMode(light, INPUT); 
 
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80); 
  dht.begin(); 
 
  // Display messages from PROGMEM 
  lcd.setCursor(0, 0); 
  lcd.print(F("Weather Monitor"));  // Using F() to keep it in flash 
  lcd.setCursor(4, 1); 
  lcd.print(F("System")); 
  delay(4000); 
  lcd.clear(); 
 
  // Set timer intervals 
  timer.setInterval(100L, updateSensors); 
} 
 
// Update all sensor readings 
void updateSensors() { 
  readDHT11sensor(); 
  readRainSensor(); 
  readPressure(); 
  readLDRsensor(); 
 
  delay(2000); 
} 
 
// Get the DHT11 sensor values 
void readDHT11sensor() { 
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 
 
  if (isnan(h) || isnan(t)) { 
    Serial.println("Failed to read from DHT sensor!"); 
    return; 
  } 
  Blynk.virtualWrite(V0, t); 
  Blynk.virtualWrite(V1, h); 
 
  // Print temperature and humidity to Serial Monitor 
  Serial.print("Temperature: "); 
  Serial.print(t, 2); 
  Serial.print(" °C, Humidity: "); 
  Serial.print(h, 2); 
  Serial.println(" %"); 
 
  // Update the LCD 
  lcd.setCursor(0, 0); 
   lcd.print("T:"); 
  lcd.print(t); 
  lcd.setCursor(8, 0); 
  lcd.print("H:"); 
  lcd.print(h); 
} 
 
// Get the rain sensor values 
void readRainSensor() { 
  int value = analogRead(rain); 
  value = map(value, 0, 1024, 100, 0); 
  Blynk.virtualWrite(V2, value); 
 
  // Print rain sensor value to Serial Monitor 
  Serial.print("Rainfall: "); 
  Serial.print(value); 
  Serial.println(" %"); 
 
  // Update the LCD 
  lcd.setCursor(0, 1); 
  lcd.print("R:"); 
  lcd.print(value); 
  lcd.print(""); 
} 
 
// Get the pressure values 
void readPressure() { 
  sensors_event_t event; 
  bmp.getEvent(&event); // Get pressure event 
 
  if (event.pressure) { 
    pressureValue = event.pressure; // Store pressure 
    Blynk.virtualWrite(V3, pressureValue); 
 
    // Print pressure to Serial Monitor 
    Serial.print("Pressure: "); 
    Serial.print(pressureValue, 2); 
    Serial.println(" hPa"); 
 
    lcd.setCursor(8, 1); 
    lcd.print("P:"); 
    lcd.print(pressureValue); 
  } else { 
    Serial.println("Sensor error"); 
  } 

   bmp.getTemperature(&temperature); // Get temperature from BMP 
} 
 
// Get the LDR sensor values 
void readLDRsensor() { 
  bool value = digitalRead(light); 
  WidgetLED LED(V4); 
  if (value == 0) { 
    LED.on(); 
    Serial.println("Light Sensor: Bright"); 
 
    // Update the LCD for Bright 
    lcd.setCursor(4, 1);  // Set LCD position 
    lcd.print("L:");  
    lcd.print("B");  // Bright = B 
    lcd.print(" "); 
  } else { 
    LED.off(); 
    Serial.println("Light Sensor: Dark"); 
 
    // Update the LCD for Dark 
    lcd.setCursor(4, 1);  // Set LCD position 
    lcd.print("L:");  
    lcd.print("D");  // Dark = D 
    lcd.print(" "); 
  } 
} 
 
void loop() { 
  Blynk.run(); // Run the Blynk library 
  timer.run(); // Run the Blynk timer 
} 