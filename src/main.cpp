//
// Created by Julian Porter on 10/04/2025.
//
#include <Arduino.h>
#include <I2CSlave.h>

I2CSlave slave;

void setup()
{
    slave.begin(4);
    slave.set8(0x15,0x17);
    slave.set16(0x16,0x0203);
    Serial.begin(9600);           // start serial for output
}

void loop()
{
    delay(100);
    if(slave.isRead()) {
        Serial.print("Read request for ");
        Serial.println(slave.changed());
        slave.clear();
    }
    else if(slave.isWritten()) {
        Serial.print("Write request for ");
        Serial.print(slave.changed());
        Serial.print(" value = ");
        Serial.println(slave.read16(), HEX);
        slave.clear();
    }
}



