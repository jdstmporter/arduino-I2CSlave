# I2C Slave Library for Arduino #

A simple single-class library wrapping `Wire.h` that turns an Arduino into 
an I2C-slave device using the standard register-based architecture.


This was originally intended for use with the 
[DFRobot Gravity Arduino Shield for Raspberry PI](https://www.dfrobot.com/product-1211.html), which sets up an Arduino Leonardo clone as a slave coprocessor for the Raspberry Pi, 
to handle things like analogue IO, PWM, etc. The documentation suggests
that the Pi should drive the shield using a USB / serial link, but it 
seemed more natural to turn the shield into an I2C peripheral, which the 
Pi drives over its I2C bus, just as it would any other such device.

## Structure ##

The files are set out as a standard Platform IO / CLion project, as follows:

- ### lib folder ###
  The C++ files `I2CSlave.cpp` and `I2CSlave.h` making up the library.
- ### src folder ###
  A sample driver sketch, showing how the library is used to turn an 
  Arduino Leonardo into a very simple I2C device. 
- ### sketches folder ###
  `master.ino` : a simple I2C master sketch that uses `Wire.h` to exercise 
  the slave device.



