// PWE 09 Smart GreenHouse
#define BLYNK_TEMPLATE_ID "TMPL6pNB9nEwq" //Initializing BLYNK IOT
#define BLYNK_TEMPLATE_NAME "Smart Greenhouse PWE09"
#define BLYNK_AUTH_TOKEN "-uNcuwUXmB5YO8e25SMBr1vtfDiPsa-V"

// WiFi credentials
char ssid[] = "YOUR_WIFI_NAME";      // Replace with your WiFi network name
char pass[] = "YOUR_WIFI_PASSWORD";  // Replace with your WiFi password

//Libraries for the System
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>  // Include Blynk's ESP8266 library

// Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define component pins
#define sensor A0 //soil moisture    
#define waterPump D3 //water pump relay  
#define DHTPIN D5     
#define DHTTYPE DHT11 
#define Coolingfan D4 //cooling fan relay

//Initializing DHT 11 Sensor
DHT dht(DHTPIN, DHTTYPE);

//Screen swapping
int displayState = 0;
unsigned long previousMillis = 0;
const long interval = 2000;

// Blynk timer
BlynkTimer timer;

//Manual overide for Fan,Water pump using a button in the BLYNK interface
bool fanAutoMode = true;  // Variable to control automatic/manual mode for fan
bool pumpAutoMode = true; // Variable to control automatic/manual mode for pump

void setup() {
  Serial.begin(9600);
  
  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(waterPump, OUTPUT); //fan, pump on mode
  digitalWrite(waterPump, HIGH);

  pinMode(Coolingfan, OUTPUT);
  digitalWrite(Coolingfan, HIGH);

  lcd.init();
  lcd.backlight();

  dht.begin();

  lcd.setCursor(1, 0);
  lcd.print("System Loading");
  for (int a = 0; a <= 15; a++) {
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(500);
  }
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Sensors Ready");

  // Setup a function to be called periodically by Blynk
  timer.setInterval(2000L, sendSensorDataToBlynk); //BLYNK delay for new data input
}

void loop() {
  Blynk.run();  // Run Blynk
  timer.run();  // Run the timer
  
  dhtSensorRead();
  soilMoistureSensor();

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    displayState++;
    if (displayState > 3) displayState = 0;
  }

  switch (displayState) {
    case 0:
      displaySoilMoisture();
      break;
    case 1:
      displayTemperatureHumidity();
      break;
    case 2:
      displayFanStatus();
      break;
    case 3:
      displayPumpStatus();
      break;
  }

  delay(500);
}

// Function to send sensor data to Blynk
void sendSensorDataToBlynk() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soilMoisture = analogRead(sensor);
  
  // Map soil moisture value to a percentage, same as the LCD display
  soilMoisture = map(soilMoisture, 0, 1024, 0, 100);
  soilMoisture = (soilMoisture - 100) * -1;
  
  //Virtual Pins
  Blynk.virtualWrite(V1, temperature);  // Send temperature to Blynk app
  Blynk.virtualWrite(V2, humidity);     // Send humidity to Blynk app
  Blynk.virtualWrite(V3, soilMoisture); // Send soil moisture (in percentage) to Blynk app
}

// Function to control cooling fan manually via Blynk switch (V4)
BLYNK_WRITE(V4) {
  int pinValue = param.asInt(); // Get value from Blynk app (0 or 1)

  if (pinValue == 1) {
    fanAutoMode = false;        // Disable automatic mode
    digitalWrite(Coolingfan, LOW);  // Turn on the fan manually
  } else {
    fanAutoMode = true;         // Enable automatic mode
  }
}

// Function to control water pump manually via Blynk switch (V5)
BLYNK_WRITE(V5) {
  int pinValue = param.asInt(); // Get value from Blynk app (0 or 1)

  if (pinValue == 1) {
    pumpAutoMode = false;       // Disable automatic mode
    digitalWrite(waterPump, LOW);  // Turn on the pump manually
  } else {
    pumpAutoMode = true;        // Enable automatic mode
  }
}

// Function to get the temperature and humidity readings
void dhtSensorRead() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Control Coolingfan based on temperature only in automatic mode
  if (fanAutoMode) {
    if (temperature > 30) {
      digitalWrite(Coolingfan, LOW);  // Turn on the fan
    } else {
      digitalWrite(Coolingfan, HIGH); // Turn off the fan
    }
  }

  if (isnan(humidity) || isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
  }
}

// Function to get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  // Control water pump only in automatic mode
  if (pumpAutoMode) {
    if (value < 30) { 
      digitalWrite(waterPump, LOW);  // Turn on the pump
    } else {
      digitalWrite(waterPump, HIGH); // Turn off the pump
    }
  }
}

// Function to display soil moisture on the LCD
void displaySoilMoisture() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture:");
  lcd.setCursor(0, 1);
  lcd.print(value);
  lcd.print(" %");
}

// Function to display temperature and humidity on the LCD
void displayTemperatureHumidity() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity); 
  lcd.print(" %");
}

// Function to display fan status on the LCD
void displayFanStatus() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fan Status:");

  if (digitalRead(Coolingfan) == LOW) {
    lcd.setCursor(0, 1);
    lcd.print("Fan is ON");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Fan is OFF");
  }
}

// Function to display water pump status on the LCD
void displayPumpStatus() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pump Status:");

  if (digitalRead(waterPump) == LOW) {
    lcd.setCursor(0, 1);
    lcd.print("Pump is ON");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Pump is OFF");
  }
}
