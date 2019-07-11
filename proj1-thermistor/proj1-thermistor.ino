// proj1-thermistor.ino
// read the resistance across a thermistor and calculate associated temperature
// print sensor readings in this format:
// <therm resistance ohms> <therm temp °C>

// in C++, comments begin with two slashes


///// CONSTANTS /////

// how long to wait between readings, in ms
const int DELAY_LENGTH = 1000;

// the thermistor pin
const int THERM_PIN = A5;


///// FUNCTIONS FOR THERMISTOR /////

// readThermistor();
// void -> float   // this means the function will take in nothing (void) and return a float
// return the resistance across the thermistor, in ohms
float readThermistor() {
  
  // CONSTANTS
  
  const int pin = THERM_PIN;
  // the thermistor pin
  
  const float resistor = 10000.0;
  // the resistance of the accompanying resistor, in ohms
  // should be very close to thermistor resistance

  // TAKE READING
  
  // read the voltage, convert to resistance, and return it
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
  
  // calculate the ln of the resistance value given
  const double lnr = log(r);
  
  // return the temperature in °C, calculating it using the Steinhart-Hart equation
  return 1 / (A + B * lnr + C * pow(lnr, 3)) - 273.15;
  
}


///// SETUP /////

// this will run once, when the Arduino starts

void setup() {

  // start the serial monitor (connection to computer)
  Serial.begin(9600);

  // use an external voltage reference
  // using a 3.3 V reference should reduce noise
  analogReference(EXTERNAL);

}


///// MAIN LOOP /////

// this runs over and over

void loop() {

  // read the thermistor resistance
  float r = readThermistor();

  // print the resistance and temperature to the serial monitor
  Serial.println(String(r) + " " + String(temp(r)));

  // wait a bit before the next reading
  delay(DELAY_LENGTH);

}
