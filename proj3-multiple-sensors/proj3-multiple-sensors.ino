// proj3-multiple-sensors.ino
// read data from a thermistor and a DHT11 temperature-humidity sensor
// print sensor readings in this format:
// <therm resistance ohms> <therm temp °C> <DHT temp °C> <DHT % humidity>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


///// CONSTANTS /////

// how long to wait between readings, in ms
const int DELAY_LENGTH = 1000;

// pins
const int THERM_PIN = A5; // thermistor
const int DHT_PIN = 2; // termperature-humidity sensor


///// DHT SETUP /////

DHT dht(DHT_PIN, DHT11);


///// FUNCTIONS FOR THERMISTOR /////

// readThermistor();
// void -> float
// return the resistance across the thermistor, in ohms
float readThermistor() {
  
  // CONSTANTS
  
  const int pin = THERM_PIN;
  // the thermistor pin
  
  const float resistor = 10000.0;
  // the resistance of the accompanying resistor, in ohms
  // should be very close to thermistor resistance

  // TAKE READING
  
  // read the voltage, convert to voltage, and return it
  return resistor / ((1023.0 / analogRead(pin)) - 1);
  
}

// temp(r);
// float -> float
// convert a thermistor resistance in ohms to a temperature in °C
float temp(float r) {

  // CONSTANTS
  
  // thermistor Steinhart–Hart coeffecients
  // 1/T = A + Bln(R) + Cln(R)^3
  // A, B, and C are constants; T is the temperature in K; R is the resistance in ohms
  // the values below were taken from the ELEGOO tutorial Lesson 23
  // often, values can be found on the data sheet for the thermistor
  const float A = 1.129148e-03;
  const float B = 2.34125e-04;
  const float C = 8.76741e-08;

  // CALCULATIONS

  // get the ln of the resistance value given
  const double lnr = log(r);

  // return the temperature in °C, calculating it using the Steinhart–Hart equation
  return 1 / (A + B * lnr + C * pow(lnr, 3)) - 273.15;
  
}


///// SETUP /////

void setup() {
  
  // start the serial monitor
  Serial.begin(9600);
  
  // use an external voltage reference for thermistor
  // using a 3.3 V reference should reduce noise
  analogReference(EXTERNAL);
  
  // start the DHT (temperature-humidity) sensor
  dht.begin();
  
}


///// MAIN LOOP /////

void loop() {

  // take the readings
  float therm_r = readThermistor();
  float therm_t = temp(therm_r);
  float dht_t = dht.readTemperature();
  float dht_h = dht.readHumidity();

  // print the readings
  Serial.println(String(therm_r) + " " + String(therm_t) +
                 " " + String(dht_t) + " " + String(dht_h));

  // wait a bit before the next reading
  delay(DELAY_LENGTH);

}
