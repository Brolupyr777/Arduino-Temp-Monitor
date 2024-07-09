#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Liquid Diplay plugged into SDA and SDL
LiquidCrystal_I2C lcd(0x27,16,2);

// Sensor Pin
#define DHTPIN 2     
 
#define DHTTYPE DHT11   

// Btn Pin
int btnpin = 7;

int unit = 0;

DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
  // initialize the LCD
  lcd.init();
  //Turn on the backlight
  lcd.backlight();
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  pinMode(btnpin, INPUT);
  dht.begin();
}
 
void loop() {
  // Wait a few seconds between measurements.
  delay(300);
  bool btnPressed = digitalRead(btnpin);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
 
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
 
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
 
  // Serial.print(F("Humidity: "));
  // Serial.print(h);
  // Serial.print(F("%  Temperature: "));
  // Serial.print(t);
  // Serial.print(F("°C "));
  // Serial.print(f);
  // Serial.print(F("°F  Heat index: "));
  // Serial.print(hic);
  // Serial.print(F("°C "));
  // Serial.print(hif);
  // Serial.println(F("°F"));
  

  if (btnPressed)
  {
    Serial.println("Activated");
    Serial.println(btnPressed);
    lcd.clear();
    lcd.setCursor(0, 0);
    switch (unit)
    {
      case 0:
        lcd.print("Humidity");
        lcd.setCursor(0, 1);
        lcd.print(h); 
        unit++;
        break;
      
      case 1:
        lcd.print("Temp F");
        lcd.setCursor(0, 1);
        lcd.print(f);
        unit++;
        break;
      
      case 2:
        lcd.print("Temp C");
        lcd.setCursor(0, 1);
        lcd.print(t);
        unit++;
        break;

      case 3:
        lcd.print("Heat Index F");
        lcd.setCursor(0, 1);
        lcd.print(hif);
        unit++;
        break;

      case 4:
        lcd.print("Heat Index C");
        lcd.setCursor(0, 1);
        lcd.print(hic);
        unit = 0;
        break;
    }  
  }
}
