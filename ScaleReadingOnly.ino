#include "HX711.h"
#define calibration_factor 43015 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2
HX711 scale;
void setup() {
  Serial.begin(9600);
  Serial.println("HX711 scale demo");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  Serial.println("Readings:");
}
void loop() {
 // Serial.print("Reading: ");
  Serial.print(scale.get_units(5), 1); //scale.get_units() returns a float
  //Serial.print(" KG"); //You can change this to Ibs but you'll need to refactor the calibration_factor
  Serial.println();
  
  scale.power_down();             // put the ADC in sleep mode
  delay(1200);
  scale.power_up();
}
