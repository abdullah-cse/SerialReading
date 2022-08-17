#include "HX711.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define calibration_factor 43015
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const int LOADCELL_SCK_PIN = 2;
const int LOADCELL_DOUT_PIN = 3;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
HX711 scale;

void setup() {
  Serial.begin(9600);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    { // Address 0x3D for 128x64
      Serial.println(F("SSD1306 allocation failed"));
      for(;;);
    }
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Welcome");
    display.display();
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare();
}

void loop() {
  if (scale.is_ready())
    {
      long reading = scale.get_units(5);
      Serial.println(reading);
      
      display.clearDisplay();
      display.setCursor(20,0);
      display.setTextSize(2);
      display.println("Weight");

      
      display.setCursor(0,25);
      display.setTextSize(3);
      display.print(reading);

      display.setCursor(40,25);
      display.setTextSize(3);
      display.print("KG");
      
      display.display();
    }
  else
    {
      Serial.println("HX711 not found.");
    }
  delay(500);
}
