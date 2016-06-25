#include <stdint.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BMP280.h"

Adafruit_BMP280 bmp; // I2C

Timer timer(5000, checkEnvironment);

// Update to reflect current pressure at sea level
float seaLevelhPa = 1035.7;

// string to output ALL OF THE THINGS!
char readingData[63] = "";

void setup() {

  Particle.publish("DEBUG", "starting...");

  if (bmp.begin()) {
    Particle.publish("DEBUG", "starting the environment timer...");
    timer.start();
  }
  else {
    Particle.publish("WARN", "Could not find a valid BMP280 sensor, check wiring!");
  }

  Particle.publish("DEBUG", "started!");
}

void loop() {

}

void checkEnvironment() {

  Particle.publish("DEBUG", "checking the environment...");
  /*// Particle.publish("environment/temperature", String(cToF(bmp.readTemperature())));
  // Particle.publish("environment/pressure", String(pToHg(bmp.readPressure())));
  // Particle.publish("environment/altitude", String(bmp.readAltitude(seaLevelhPa)));*/

  sprintf(readingData, "Temperature=%.2f°C, Pressure=%.2fhPa", bmp.readTemperature(), bmp.readPressure()/100.0);
  Particle.publish("reading", readingData);
}

// fahrenheit pfff…
float cToF(float c) {
  return c * 9/5 + 32;
}

float pToHg(float p) {
  return p/3389.39;
}
