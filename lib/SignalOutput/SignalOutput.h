
#ifndef _SIGNAL_OUTPUT_H_
#define _SIGNAL_OUTPUT_H_

#include "TCA6424A.h"

class SignalOutput : public TCA6424A
{
public:
    SignalOutput();
    SignalOutput(TwoWire *I2CBus, uint8_t address);

    void initialize();

    void setLight(byte light, byte status);
    bool initialized();

private:
    byte _initialized = false;
};

#endif