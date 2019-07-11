/images/dht-photo.JPG

# Project 2: The digital humidity-temperature sensor

The digital humidity-temperature (DHT) sensor is an integrated circuit—that is, it contains several components bundled together in a nice, little, mini-circuit bundle for our convenience. Among other things, it contains

* A thermistor to measure temperature,
* A relative humidity sensor, and
* A microcontroller (small computer) to read these on our behalf.

We communicate with the DHT's microcontroller through a digital signal, a series of 5 V and 0 V blips. Here, there is nothing analogue for us to do; the microcontroller handles all the ADC and temperature-conversion stuff for us.

Rather than figuring out how to communicate with the DHT ourself, we will load a *library* onto our Arduino to handle this for us. A library is a bundle of code that someone else develops that we can then load and make reference to in our own programs. Most often, if you're using a digital sensor, you can find a library to help you communicate with it.

The video below shows how to find and install a library. The libraries we will be using are called the Adafruit Unified Sensor Library and the Adafruit DHT Library.

<!!! libraries video>

Notice how I was able to use the example code to figure out what I needed to include in my own program.

## Building the circuit

Here is our circuit diagram.

/images/proj2-schem.svg
/images/proj2-bb.svg
/images/proj2-photo.JPG

As you can see, it is much simpler than the analogue sensor circuit from the previous project. The code is also shorter; we don't have to design functions for reading the DHT as the libraries already give us some!

Go ahead and build this circuit, then load `proj2-dht.ino` onto your Arduino. You should be able to see temperature and humidity readings in the serial monitor.