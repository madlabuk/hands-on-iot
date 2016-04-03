// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_BMP085/Adafruit_BMP085.h"

Adafruit_BMP085 bmp;

void InitializeBMP085(){
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {
        Serial.println("Faaaaaale");
    }
  }
}

// Publish Pressure, Altitude
void PublishBMP085Info(){
    char szEventInfo[64];

    sprintf(szEventInfo, "Temperature=%.2f °C, Pressure=%.2f hPa", bmp.readTemperature(), bmp.readPressure()/100.0);

    Serial.println(szEventInfo);
    Spark.publish("reading", szEventInfo);
}

// Initialize applicaiton
void InitializeApplication(){
    Serial.begin(9600);
    pinMode(D7, OUTPUT);
}

// Blink LED and wait for some time
void BlinkLED(){
    digitalWrite(D7, HIGH);
    delay(500);
    digitalWrite(D7, LOW);
}

void setup() {
    BlinkLED();
    InitializeApplication();
    InitializeBMP085();
}

void loop() {
    // Publish events. Wait for 2 seconds between publishes
    PublishBMP085Info();
    BlinkLED();
    delay(2000);
}
