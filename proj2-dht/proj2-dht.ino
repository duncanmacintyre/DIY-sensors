// proj3-dht.ino
// read data from a digital humidity and temperature sensor
// print sensor readings in this format:
// <DHT temp °C> <DHT % humidity>

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


// we don't need to design functions to read the DHT because the
// DHT library already provides some!


///// SETUP /////

void setup() {
  
  // start the serial monitor
  Serial.begin(9600);
  
  // start the DHT (temperature-humidity) sensor
  dht.begin();
  
}


///// MAIN LOOP /////

void loop() {

  // take and print the readings
  Serial.println(String(dht.readTemperature()) + " " + String(dht.readHumidity()));

  // wait a bit before the next reading
  delay(DELAY_LENGTH);

}
