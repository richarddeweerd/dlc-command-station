
#include "SignalOutput.h"

SignalOutput::SignalOutput() : TCA6424A()
{
}

SignalOutput::SignalOutput(TwoWire *Bus, uint8_t address) : TCA6424A(Bus, address)
{
}

/** Power on and prepare for general usage.
 * The TCA6424A I/O expander requires no preparation after power-on. All pins
 * will be default to INPUT mode, and the device is ready for usage immediately.
 * This is an empty function for consistency and/or future expansion.
 */
void SignalOutput::initialize()
{
    if (testConnection())
    {
        _initialized = true;
        setBankDirection(0, 0x00);
        setBankDirection(1, 0x00);
        setBankDirection(2, 0x00);
        writeBank(0, 0xFF);
        writeBank(1, 0xFF);
        writeBank(2, 0xFF);
        writeBank(0, 0x00);
        delay(500);
        writeBank(0, 0xFF);
        writeBank(1, 0x00);
        delay(500);
        writeBank(1, 0xFF);
        writeBank(2, 0x00);
        delay(500);
        writeBank(2, 0xFF);
    }
    else
    {
        _initialized = false;
    }
}

bool SignalOutput::initialized()
{
    return _initialized;
}

void SignalOutput::setLight(byte light, byte status)
{
    if (_initialized)
    {

        if (status == 1)
        {
            //red
            writePin(light, false);
            writePin(light + 8, true);
            writePin(light + 16, true);
            return;
        }
        if (status == 2)
        {
            //orange
            writePin(light, true);
            writePin(light + 8, false);
            writePin(light + 16, true);
            return;
        }
        if (status == 3)
        {
            //green
            writePin(light, true);
            writePin(light + 8, true);
            writePin(light + 16, false);
            return;
        }
        //off
        writePin(light, true);
        writePin(light + 8, true);
        writePin(light + 16, true);
        return;
    }
}
