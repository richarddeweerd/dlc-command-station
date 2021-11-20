// I2Cdev library collection - TCA9534 I2C device class
// Based on Texas Instruments TCA9534 datasheet, 9/2010 (document SCPS193B)
// 7/31/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     2011-07-31 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

#define TCA9534_TIMEOUT 5

#include "TCA9534.h"

/** Default constructor, uses default I2C address.
 * @see TCA9534_DEFAULT_ADDRESS
 */
TCA9534::TCA9534()
{
    devAddr = 0x20;
}

/** Specific address constructor.
 * @param address I2C address
 * @see TCA9534_DEFAULT_ADDRESS
 * @see TCA9534_ADDRESS_ADDR_LOW
 * @see TCA9534_ADDRESS_ADDR_HIGH
 */
TCA9534::TCA9534(TwoWire *Bus, uint8_t address)
{
    I2CBus = Bus;
    devAddr = address;
}

/** Power on and prepare for general usage.
 * The TCA9534 I/O expander requires no preparation after power-on. All pins
 * will be default to INPUT mode, and the device is ready for usage immediately.
 * This is an empty function for consistency and/or future expansion.
 */
void TCA9534::initialize()
{
}

/** Verify the I2C connection.
 * Make sure the device is connected and responds as expected.
 * @return True if connection is valid, false otherwise
 */
bool TCA9534::testConnection()
{
    return I2Cdev::readBytes(devAddr, TCA9534_RA_INPUT0, 3, buffer, TCA9534_TIMEOUT, I2CBus) == 3;
}

// INPUT* registers (x0h - x2h)

/** Get a single INPUT pin's logic level.
 * @return Pin logic level (0 or 1)
 */
bool TCA9534::readPin(uint16_t pin)
{
    I2Cdev::readBit(devAddr, TCA9534_RA_INPUT0 + (pin / 8), pin % 8, buffer, TCA9534_TIMEOUT, I2CBus);
    return buffer[0];
}
/** Get all pin logic levels from one bank.
 * @param bank Which bank to read (0/1/2 for P0*, P1*, P2* respectively)
 * @return 8 pins' logic levels (0 or 1 for each pin)
 */
uint8_t TCA9534::readPort()
{
    I2Cdev::readByte(devAddr, TCA9534_RA_INPUT, buffer, TCA9534_TIMEOUT, I2CBus);
    return buffer[0];
}
/** Get all pin logic levels from all banks.
 * Reads into single 3-byte data container.
 * @param banks Container for all bank's pin values (P00-P27)
 */

// OUTPUT* registers (x4h - x6h)

/** Get a single OUTPUT pin's setting.
 * Note that this returns the level set in the flip-flop, and does not
 * necessarily represent the actual logic level present at the pin.
 * @return Pin output setting (0 or 1)
 */
bool TCA9534::getPinOutputLevel(uint16_t pin)
{
    I2Cdev::readBit(devAddr, TCA9534_RA_OUTPUT0 + (pin / 8), pin % 8, buffer, TCA9534_TIMEOUT, I2CBus);
    return buffer[0];
}
/** Get all pin output settings from one bank.
 * Note that this returns the level set in the flip-flop, and does not
 * necessarily represent the actual logic level present at the pin.
 * @param bank Which bank to read (0/1/2 for P0*, P1*, P2* respectively)
 * @return 8 pins' output settings (0 or 1 for each pin)
 */
uint8_t TCA9534::getBankOutputLevel(uint8_t bank)
{
    I2Cdev::readByte(devAddr, TCA9534_RA_OUTPUT0 + bank, buffer, TCA9534_TIMEOUT, I2CBus);
    return buffer[0];
}
/** Get all pin output settings from all banks.
 * Reads into single 3-byte data container.
 * @param banks Container for all bank's pin values (P00-P27)
 */
void TCA9534::getAllOutputLevel(uint8_t *banks)
{
    I2Cdev::readBytes(devAddr, TCA9534_RA_OUTPUT0, 3, banks);
}
/** Get all pin output settings from all banks.
 * Reads into individual 1-byte containers. Note that this returns the level
 * set in the flip-flop, and does not necessarily represent the actual logic
 * level present at the pin.
 * @param bank0 Container for Bank 0's pin values (P00-P07)
 * @param bank1 Container for Bank 1's pin values (P10-P17)
 * @param bank2 Container for Bank 2's pin values (P20-P27)
 */
void TCA9534::getAllOutputLevel(uint8_t *bank0, uint8_t *bank1, uint8_t *bank2)
{
    I2Cdev::readBytes(devAddr, TCA9534_RA_OUTPUT0, 3, buffer, TCA9534_TIMEOUT, I2CBus);
    *bank0 = buffer[0];
    *bank1 = buffer[1];
    *bank2 = buffer[2];
}
/** Set a single OUTPUT pin's logic level.
 * @param pin Which pin to write (0-23)
 * @param value New pin output logic level (0 or 1)
 */
void TCA9534::writePin(uint16_t pin, bool value)
{
    I2Cdev::writeBit(devAddr, TCA9534_RA_OUTPUT0 + (pin / 8), pin % 8, value, I2CBus);
}
/** Set all OUTPUT pins' logic levels in one bank.
 * @param bank Which bank to write (0/1/2 for P0*, P1*, P2* respectively)
 * @param value New pins' output logic level (0 or 1 for each pin)
 */
void TCA9534::writeBank(uint8_t bank, uint8_t value)
{
    I2Cdev::writeByte(devAddr, TCA9534_RA_OUTPUT0 + bank, value, I2CBus);
}
/** Set all OUTPUT pins' logic levels in all banks.
 * @param banks All pins' new logic values (P00-P27) in 3-byte array
 */
void TCA9534::writeAll(uint8_t *banks)
{
    I2Cdev::writeBytes(devAddr, TCA9534_RA_OUTPUT0 | TCA9534_AUTO_INCREMENT, 3, banks, I2CBus);
}
/** Set all OUTPUT pins' logic levels in all banks.
 * @param bank0 Bank 0's new logic values (P00-P07)
 * @param bank1 Bank 1's new logic values (P10-P17)
 * @param bank2 Bank 2's new logic values (P20-P27)
 */
void TCA9534::writeAll(uint8_t bank0, uint8_t bank1, uint8_t bank2)
{
    buffer[0] = bank0;
    buffer[1] = bank1;
    buffer[2] = bank2;
    I2Cdev::writeBytes(devAddr, TCA9534_RA_OUTPUT0 | TCA9534_AUTO_INCREMENT, 3, buffer, I2CBus);
}

// POLARITY* registers (x8h - xAh)

/** Get a single pin's polarity (normal/inverted) setting.
 * @return Pin polarity setting (0 or 1)
 */
bool TCA9534::getPinPolarity(uint16_t pin)
{
    I2Cdev::readBit(devAddr, TCA9534_RA_POLARITY0 + (pin / 8), pin % 8, buffer, TCA9534_TIMEOUT, I2CBus);
    return buffer[0];
}
/** Get all pin polarity (normal/inverted) settings from one bank.
 * @param bank Which bank to read (0/1/2 for P0*, P1*, P2* respectively)
 * @return 8 pins' polarity settings (0 or 1 for each pin)
 */
uint8_t TCA9534::getBankPolarity(uint8_t bank)
{
    I2Cdev::readByte(devAddr, TCA9534_RA_POLARITY0 + bank, buffer, TCA9534_TIMEOUT, I2CBus);
    return buffer[0];
}
/** Get all pin polarity (normal/inverted) settings from all banks.
 * Reads into single 3-byte data container.
 * @param banks Container for all bank's pin values (P00-P27)
 */
void TCA9534::getAllPolarity(uint8_t *banks)
{
    I2Cdev::readBytes(devAddr, TCA9534_RA_POLARITY0, 3, banks);
}
/** Get all pin polarity (normal/inverted) settings from all banks.
 * Reads into individual 1-byte containers.
 * @param bank0 Container for Bank 0's pin values (P00-P07)
 * @param bank1 Container for Bank 1's pin values (P10-P17)
 * @param bank2 Container for Bank 2's pin values (P20-P27)
 */
void TCA9534::getAllPolarity(uint8_t *bank0, uint8_t *bank1, uint8_t *bank2)
{
    I2Cdev::readBytes(devAddr, TCA9534_RA_POLARITY0, 3, buffer, TCA9534_TIMEOUT, I2CBus);
    *bank0 = buffer[0];
    *bank1 = buffer[1];
    *bank2 = buffer[2];
}
/** Set a single pin's polarity (normal/inverted) setting.
 * @param pin Which pin to write (0-23)
 * @param polarity New pin polarity setting (0 or 1)
 */
void TCA9534::setPinPolarity(uint16_t pin, bool polarity)
{
    I2Cdev::writeBit(devAddr, TCA9534_RA_POLARITY0 + (pin / 8), pin % 8, polarity, I2CBus);
}
/** Set all pin polarity (normal/inverted) settings in one bank.
 * @param bank Which bank to write (0/1/2 for P0*, P1*, P2* respectively)
 * @return New pins' polarity settings (0 or 1 for each pin)
 */
void TCA9534::setBankPolarity(uint8_t bank, uint8_t polarity)
{
    I2Cdev::writeByte(devAddr, TCA9534_RA_POLARITY0 + bank, polarity, I2CBus);
}
/** Set all pin polarity (normal/inverted) settings in all banks.
 * @param banks All pins' new logic values (P00-P27) in 3-byte array
 */
void TCA9534::setAllPolarity(uint8_t *banks)
{
    I2Cdev::writeBytes(devAddr, TCA9534_RA_POLARITY0 | TCA9534_AUTO_INCREMENT, 3, banks, I2CBus);
}
/** Set all pin polarity (normal/inverted) settings in all banks.
 * @param bank0 Bank 0's new polarity values (P00-P07)
 * @param bank1 Bank 1's new polarity values (P10-P17)
 * @param bank2 Bank 2's new polarity values (P20-P27)
 */
void TCA9534::setAllPolarity(uint8_t bank0, uint8_t bank1, uint8_t bank2)
{
    buffer[0] = bank0;
    buffer[1] = bank1;
    buffer[2] = bank2;
    I2Cdev::writeBytes(devAddr, TCA9534_RA_POLARITY0 | TCA9534_AUTO_INCREMENT, 3, buffer, I2CBus);
}

// CONFIG* registers (xCh - xEh)

/** Get a single pin's direction (I/O) setting.
 * @return Pin direction setting (0 or 1)
 */
bool TCA9534::getPinDirection(uint16_t pin)
{
    I2Cdev::readBit(devAddr, TCA9534_RA_CONFIG0 + (pin / 8), pin % 8, buffer, TCA9534_TIMEOUT, I2CBus);
    return buffer[0];
}
/** Get all pin direction (I/O) settings from one bank.
 * @param bank Which bank to read (0/1/2 for P0*, P1*, P2* respectively)
 * @return 8 pins' direction settings (0 or 1 for each pin)
 */
uint8_t TCA9534::getBankDirection(uint8_t bank)
{
    I2Cdev::readByte(devAddr, TCA9534_RA_CONFIG0 + bank, buffer, TCA9534_TIMEOUT, I2CBus);
    return buffer[0];
}
/** Get all pin direction (I/O) settings from all banks.
 * Reads into single 3-byte data container.
 * @param banks Container for all bank's pin values (P00-P27)
 */
void TCA9534::getAllDirection(uint8_t *banks)
{
    I2Cdev::readBytes(devAddr, TCA9534_RA_CONFIG0, 3, banks);
}
/** Get all pin direction (I/O) settings from all banks.
 * Reads into individual 1-byte containers.
 * @param bank0 Container for Bank 0's pin values (P00-P07)
 * @param bank1 Container for Bank 1's pin values (P10-P17)
 * @param bank2 Container for Bank 2's pin values (P20-P27)
 */
void TCA9534::getAllDirection(uint8_t *bank0, uint8_t *bank1, uint8_t *bank2)
{
    I2Cdev::readBytes(devAddr, TCA9534_RA_CONFIG0, 3, buffer, TCA9534_TIMEOUT, I2CBus);
    *bank0 = buffer[0];
    *bank1 = buffer[1];
    *bank2 = buffer[2];
}
/** Set a single pin's direction (I/O) setting.
 * @param pin Which pin to write (0-23)
 * @param direction Pin direction setting (0 or 1)
 */
void TCA9534::setPinDirection(uint16_t pin, bool direction)
{
    I2Cdev::writeBit(devAddr, TCA9534_RA_CONFIG0 + (pin / 8), pin % 8, direction, I2CBus);
}
/** Set all pin direction (I/O) settings in one bank.
 * @param bank Which bank to read (0/1/2 for P0*, P1*, P2* respectively)
 * @param direction New pins' direction settings (0 or 1 for each pin)
 */
void TCA9534::setBankDirection(uint8_t bank, uint8_t direction)
{
    I2Cdev::writeByte(devAddr, TCA9534_RA_CONFIG0 + bank, direction, I2CBus);
}
/** Set all pin direction (I/O) settings in all banks.
 * @param banks All pins' new direction values (P00-P27) in 3-byte array
 */
void TCA9534::setAllDirection(uint8_t *banks)
{
    I2Cdev::writeBytes(devAddr, TCA9534_RA_CONFIG0 | TCA9534_AUTO_INCREMENT, 3, banks, I2CBus);
}
/** Set all pin direction (I/O) settings in all banks.
 * @param bank0 Bank 0's new direction values (P00-P07)
 * @param bank1 Bank 1's new direction values (P10-P17)
 * @param bank2 Bank 2's new direction values (P20-P27)
 */
void TCA9534::setAllDirection(uint8_t bank0, uint8_t bank1, uint8_t bank2)
{
    buffer[0] = bank0;
    buffer[1] = bank1;
    buffer[2] = bank2;
    I2Cdev::writeBytes(devAddr, TCA9534_RA_CONFIG0 | TCA9534_AUTO_INCREMENT, 3, buffer, I2CBus);
}
