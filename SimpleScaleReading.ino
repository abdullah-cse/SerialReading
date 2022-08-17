#include "HX711.h"
#define calibration_factor 43015

// HX711 circuit wiring
const int LOADCELL_SCK_PIN = 2;
const int LOADCELL_DOUT_PIN = 3;

HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare();
}

void loop() {
  if (scale.is_ready())
    {
      long reading = scale.get_units(5);
      Serial.println(reading);
    }
  else
    {
      Serial.println("HX711 not found.");
    }
  delay(500);
}
