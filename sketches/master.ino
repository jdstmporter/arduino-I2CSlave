#include <Wire.h>

void setup() {
    Wire.begin();        // join i2c bus (address optional for master)
    Serial.begin(9600);  // start serial for output
}

byte x = 0;
uint16_t w = 0;

uint16_t readWord() {
    byte h = Wire.read();
    byte l = Wire.read();
    int w16 = (int(h)<<8)|(int(l));
    return (uint16_t)w16;
}

void loop()
{
    /** write to register 8 bit */
    Serial.print("Writing ");
    Serial.print(w, HEX);
    Serial.println(" to 0x11");
    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(0x11);
    Wire.write((w>>8)&0xff);
    Wire.write((w&0xff));
    Wire.endTransmission();    // stop transmitting

    w++;
    delay(500);

    Serial.print("Writing ");
    Serial.print(x, HEX);
    Serial.println(" to 0x12");
    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(0x12);
    Wire.write(x);
    Wire.endTransmission();

    x++;
    delay(500);

    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(0x15);
    Wire.endTransmission(false);
    Wire.requestFrom(4,2,true);
    Serial.print("Read byte ");
    Serial.println(readWord(), HEX);
    Wire.endTransmission();

    delay(500);

    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(0x16);        // register
    Wire.endTransmission(false);
    Wire.requestFrom(4,2,true);
    Serial.print("Read word ");
    Serial.println(readWord(), HEX);
    Wire.endTransmission();

    delay(500);


}