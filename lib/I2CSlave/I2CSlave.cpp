#include <Arduino.h>
#include <Wire.h>

#include <I2CSlave.h>

static I2CSlave *the;

I2CSlave::I2CSlave() {
    mode = Mode::None;
    reg = I2CSlave::NO_REGISTER;
    regs = new uint16_t[256];
    for(auto i=0;i<256;i++) regs[i]=0;
}

I2CSlave::~I2CSlave() {
    delete[] regs;
}

 void I2CSlave::begin(const uint8_t addr) {
    the = this;
    Wire.begin(addr);
    Wire.onRequest(I2CSlave::tx);
    Wire.onReceive(I2CSlave::rx);
}

void I2CSlave::end() {
    Wire.end();
}

void I2CSlave::tx() {
        if(the->isRead()) {
            auto r = the->regs[the->reg];
            Wire.write((r >> 8) & 0xff);
            Wire.write(r & 0xff);
        }
    }

void I2CSlave::rx(int n) {
        if (n == 0) {
            //the->clear();
            return;
        }
        auto r = Wire.read();
        the->reg = r;
        if (n==1) {
            the->mode = Mode::Reading;
        } else if (n == 2) {
            the->mode = Mode::Writing;
            the->regs[r] = (uint16_t) Wire.read();
        } else if (n == 3) {
            the->mode = Mode::Writing;
            auto u = (uint16_t) Wire.read();
            auto l = (uint16_t) Wire.read();
            the->regs[r] = (u << 8) | l;
        } else {
            the->mode = Mode::None;
            while (Wire.available()) Wire.read();
        }
    }

void I2CSlave::clear() {
    mode = Mode::None;
    reg = I2CSlave::NO_REGISTER;
}

uint8_t I2CSlave::read8() const {
        if(isNOP()) { return 0xff; }
        return (uint8_t)(regs[reg]&0xff);
    }

uint16_t I2CSlave::read16() const {
    if(isNOP()) { return 0xffff; }
    return regs[reg];
}




    void I2CSlave::set8(const int r,const uint8_t v) { regs[r]=((uint16_t)v)<<8; }
    void I2CSlave::set16(const int r,const uint16_t v) { regs[r]=v; }

    uint8_t I2CSlave::get8(const int r) const { return (uint8_t)(regs[r]&0xff); }
    uint16_t I2CSlave::get16(const int r) const { return regs[r]; }



