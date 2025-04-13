//
// Created by Julian Porter on 10/04/2025.
//

#ifndef ARDUINO_I2CSLAVE_H
#define ARDUINO_I2CSLAVE_H

#include <Arduino.h>

enum class Mode : unsigned {
    Reading = 1,
    Writing = 2,
    None = 0
};

class I2CSlave {
private:
    const static int NO_REGISTER = -1;

    Mode mode;
    int reg;

    uint16_t *regs;



    static void tx();
    static void rx(int n);

public:

    I2CSlave();
    virtual ~I2CSlave();

    void begin(uint8_t address);
    void end();

    bool isWritten() const { return mode == Mode::Writing; }
    bool isRead() const { return mode == Mode::Reading && reg != I2CSlave::NO_REGISTER; }
    bool isNOP() const { return mode == Mode::None || reg == I2CSlave::NO_REGISTER; }
    int changed() const { return reg; }
    void clear();
    uint8_t read8() const;
    uint16_t read16() const;

    void set8(int r,uint8_t v);
    void set16(int r,uint16_t v);
    uint8_t get8(int r) const;
    uint16_t get16(int r) const;

};

#endif //ARDUINO_I2CSLAVE_H
