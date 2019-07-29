# Project 1: Analogue Sensors—The Thermistor

*Table of contents*
  * [Theory](#theory)
    * [Thermistors](#thermistors)
    * [How we take readings](#how-we-take-readings)
      * [Analogue to digital conversion: How to read a voltage](#analogue-to-digital-conversion-how-to-read-a-voltage)
      * [Converting from voltage to resistance](#converting-from-voltage-to-resistance)
      * [Converting resistance to temperature](#converting-resistance-to-temperature)
  * [Building the circuit](#building-the-circuit)
  * [The code](#the-code)
  * [Further reading](#further-reading)

This tutorial will introduce you to using analogue sensors. We'll also look at basic sensor code structure, the Arduino IDE, and how to view sensor data from your Arduino on your computer.

First, I will tell the story of the thermistor: what it does, how we can use it, and why we use it the way we do. If you're eager to get wiring and coding, feel free to jump down to the "Building the circuit" section.

## Theory

(i.e. the fun stuff)

### Thermistors

The thermistor is a resistor whose resistance changes with temperature. This simple property makes it an effective, durable, and cheap temperature sensor.

<img align="right" alt="A thermistor" width="30%" src="images/therm-photo.JPG">

Thermistors come in two types:

* Negative temperature coefficient (NTC) thermistors decrease in resistance as the temperature rises.
* Positive temperature coefficient (PTC) thermistors increase in resistance as the temperature rises.

We will use an NTC thermistor for our temperature sensor.

### How we take readings

Using the thermistor to sense temperature is a three-step process. First, we read the voltage across the thermistor. Second, we use Ohm's law to calculate the resistance of the thermistor. Finally, we use the Steinhart-Hart equation to convert this resistance into a temperature.

Here is the schematic for this circuit:

![Circuit schematic](images/proj1-schem.svg)

A few points of note:

* We have put a 10 kΩ resistor in series with the thermistor. If we measure how much of the total voltage difference occurs across the thermistor, we can determine what fraction of the total resistance occurs through the thermistor and so calculate the thermistor's resistance. We do this by measuring the voltage between the thermistor and the resistor; hence the connection to pin A5 on the Arduino. (Any analogue pin could be used.) I will discuss this more below.
* The circuit as shown is set up to run on 3.3 V, not the usual 5 V. Either voltage will work, but [using 3.3 V may reduce noise](https://learn.adafruit.com/thermistor/using-a-thermistor).
* Connecting the 3.3 V pin to the AREF pin tells the Arduino that we are going to measure a voltage between 0 V and 3.3 V instead of between 0 V and 5 V like we normally do. If you were running on 5 V, you could omit this connection.

#### Analogue to digital conversion: How to read a voltage

In the digital world, things are either on or off, `HIGH` or `LOW`, 5 V or 0 V. With analogue components, however, voltages can take infinite values; in this case, somewhere between 0 V and 3.3 V. The Arduino represents voltages like these as a natural number between 0 and 1023, placing it on a scale between two voltages it knows. The 0 end of the scale is at 0 V. Normally, the 1023 end of the scale is at 5 V, but we will change this to 3.3 V by connecting the 3.3 V power supply to the AREF pin.

Thus, the resistance across the thermistor is given by

<p align="center"><img src="/proj1-thermistor/tex/a90ee0679a6c7d8df6e6ca0a34411040.svg?invert_in_darkmode&sanitize=true" align=middle width=182.8122021pt height=33.62942055pt/></p>

where <img src="/proj1-thermistor/tex/63eb65b785f79a992f866b3f2ae66ec1.svg?invert_in_darkmode&sanitize=true" align=middle width=36.25685579999999pt height=22.465723500000017pt/> is the number from 0 to 1023 that we get for our analogue reading and <img src="/proj1-thermistor/tex/516a2805cc41de3e691585b03ef0fd14.svg?invert_in_darkmode&sanitize=true" align=middle width=30.05803844999999pt height=22.465723500000017pt/> is the power supply voltage (for us, 3.3 V).

This process is known as [Analogue to Digital Conversion (ADC)](https://en.m.wikipedia.org/wiki/Analog-to-digital_converter).

(The Arduino is said to have 10-bit ADC because there are 2^10 (1024) possible values a voltage can take.)

#### Converting from voltage to resistance

We can use [Ohm's law](https://en.m.wikipedia.org/wiki/Ohm%27s_law) to convert this voltage reading into a resistance. To do this, we will come up with two equations then combine them with the powers of algebra.

To start with, the voltage difference across the thermistor and the resistor must total <img src="/proj1-thermistor/tex/516a2805cc41de3e691585b03ef0fd14.svg?invert_in_darkmode&sanitize=true" align=middle width=30.05803844999999pt height=22.465723500000017pt/>, the voltage supplied by the power supply.

<p align="center"><img src="/proj1-thermistor/tex/109dd43860ea67a9331ca822b6b41f94.svg?invert_in_darkmode&sanitize=true" align=middle width=206.34240164999997pt height=13.698590399999999pt/></p>

This is our first equation.

Next, we know that the current through the thermistor is the same as the current through the resistor.

<p align="center"><img src="/proj1-thermistor/tex/b76f8681670bfb5dd84d560e29ea108b.svg?invert_in_darkmode&sanitize=true" align=middle width=150.64541415pt height=13.698590399999999pt/></p>

Ohm's law tells us that <img src="/proj1-thermistor/tex/b5faf25b5ac8fe18c2b0e54ada4db22a.svg?invert_in_darkmode&sanitize=true" align=middle width=53.799008999999984pt height=28.670654099999997pt/>, where <img src="/proj1-thermistor/tex/21fd4e8eecd6bdf1a4d3d6bd1fb8d733.svg?invert_in_darkmode&sanitize=true" align=middle width=8.515988249999989pt height=22.465723500000017pt/> is the current through a circuit component, <img src="/proj1-thermistor/tex/1eb263a1361d11fbefc8fb9d6e6af61e.svg?invert_in_darkmode&sanitize=true" align=middle width=26.94070829999999pt height=22.465723500000017pt/> is the voltage change across the component, and <img src="/proj1-thermistor/tex/1e438235ef9ec72fc51ac5025516017c.svg?invert_in_darkmode&sanitize=true" align=middle width=12.60847334999999pt height=22.465723500000017pt/> is the component's resistance. So, we get

<p align="center"><img src="/proj1-thermistor/tex/c9cd0270c89620b3676d7cf53d247428.svg?invert_in_darkmode&sanitize=true" align=middle width=172.46203094999998pt height=36.09514755pt/></p>

This is our second equation.

Putting these two equations together, we reach

<p align="center"><img src="/proj1-thermistor/tex/d251cf4b0b786c01404a746812743ce7.svg?invert_in_darkmode&sanitize=true" align=middle width=209.36167394999998pt height=42.569933999999996pt/></p>

We're almost there! We just need one finishing touch. Adding our ADC equation from the previous section, we get

<p align="center"><img src="/proj1-thermistor/tex/5541537b6c431ce880e9b027328a6475.svg?invert_in_darkmode&sanitize=true" align=middle width=167.63408145pt height=41.84588925pt/></p>

where <img src="/proj1-thermistor/tex/63eb65b785f79a992f866b3f2ae66ec1.svg?invert_in_darkmode&sanitize=true" align=middle width=36.25685579999999pt height=22.465723500000017pt/> is the natural number from 0 to 1023 that we actually read. This is the equation we will use in our code.

#### Converting resistance to temperature

We can use the [Steinhart-Hart equation](https://en.m.wikipedia.org/wiki/Steinhart–Hart_equation) to convert our resistances into temperatures. This equation takes the form

<p align="center"><img src="/proj1-thermistor/tex/52c83b8426ad27d3f3ed0d0d926c26be.svg?invert_in_darkmode&sanitize=true" align=middle width=202.03953495pt height=32.990165999999995pt/></p>

where T is the temperature, R is the thermistor resistance, and A, B, and C are constants. For equations like this, you may be able to find values for your constants on the datasheet for the sensor. Google around a bit. For our code, we will use values from an ELEGOO tutorial using this sensor. I'm not sure where they got them, but they seem to work fairly well.

---

<img alt="Photo of breadboard" width="40%" src="images/proj1-photo.JPG">

## Building the circuit

Let's get cracking.

Here is the circuit diagram for this project:

![Circuit schematic](images/proj1-schem.svg)
![Breadboard diagram](images/proj1-bb.svg)

Go ahead and build the circuit. Then, open `proj1-thermistor.ino` and upload the program to your Arduino.

When the program is finished uploading, click the magnifying glass icon at the top right corner of the screen to open the serial monitor. You should now see temperature readings from your thermistor.

The video below walks through uploading the program to the Arduino.

[<img alt="The Arduino IDE" width="30%" src="https://video-to-markdown.netlify.com/.netlify/functions/image?url=https%3A%2F%2Fyoutu.be%2F960Z6R9w0sA">](https://youtu.be/960Z6R9w0sA "The Arduino IDE")

## The code

In general, I've found that sensor programs have three main parts:

1. The Constants section, where we define constants to hold program parameters (e.g. pin numbers for connections, how long to wait between sensor readings);
2. The Functions section, where we design functions to help us read the sensors, each function doing one job; and
3. The Setup and Main Loop section, where we tell the Arduino what to do, and when.

Try to identify the three parts of sensor programs in `proj1-thermistor.ino`. As you go through the code, be sure to read the comments; use them to guide you as you follow what the code is doing.

Notice how having separate functions for reading sensors keeps the Main Loop clean and makes our code easier to reuse. Remember always the golden rule of function design: each function does one job. It should always be easy to see what the singular purpose of each function is. (What do you think the singular purpose of the Main function is?)

## Further reading

* [A good, practical guide to using thermistors](https://learn.adafruit.com/thermistor/using-a-thermistor)
* [Analogue to digital conversion – Wikipedia](https://en.m.wikipedia.org/wiki/Analog-to-digital_converter)
* [The Steinhart-Hart equation – Wikipedia](https://en.m.wikipedia.org/wiki/Steinhart–Hart_equation)
* [Ohm's Law – Wikipedia](https://en.m.wikipedia.org/wiki/Ohm%27s_law)

