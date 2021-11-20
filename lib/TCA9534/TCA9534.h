// I2Cdev library collection - TCA9534 I2C device class header file
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

#ifndef _TCA9534_H_
#define _TCA9534_H_

#include "I2Cdev.h"
#include "Wire.h"

#define TCA9534_RA_INPUT 0x00
#define TCA9534_RA_OUTPUT 0x01
#define TCA9534_RA_POLARITY 0x02
#define TCA9534_RA_CONFIG 0x03

#define TCA9534_LOW 0
#define TCA9534_HIGH 1

#define TCA9534_POLARITY_NORMAL 0
#define TCA9534_POLARITY_INVERTED 1

#define TCA9534_OUTPUT 0
#define TCA9534_INPUT 1

class TCA9534
{
public:
    TCA9534();
    TCA9534(TwoWire *I2CBus, uint8_t address);

    void initialize();
    bool testConnection();

    // INPUT* registers (x0h - x2h)
    bool readPin(uint16_t pin);
    uint8_t readPort(uint8_t bank);

    // OUTPUT* registers (x4h - x6h)
    bool getPinOutputLevel(uint16_t pin);
    uint8_t getBankOutputLevel(uint8_t bank);
    void getAllOutputLevel(uint8_t *banks);
    void getAllOutputLevel(uint8_t *bank0, uint8_t *bank1, uint8_t *bank2);
    void writePin(uint16_t pin, bool polarity);
    void writeBank(uint8_t bank, uint8_t value);
    void writeAll(uint8_t *banks);
    void writeAll(uint8_t bank0, uint8_t bank1, uint8_t bank2);

    // POLARITY* registers (x8h - xAh)
    bool getPinPolarity(uint16_t pin);
    uint8_t getBankPolarity(uint8_t bank);
    void getAllPolarity(uint8_t *banks);
    void getAllPolarity(uint8_t *bank0, uint8_t *bank1, uint8_t *bank2);
    void setPinPolarity(uint16_t pin, bool polarity);
    void setBankPolarity(uint8_t bank, uint8_t polarity);
    void setAllPolarity(uint8_t *banks);
    void setAllPolarity(uint8_t bank0, uint8_t bank1, uint8_t bank2);

    // CONFIG* registers (xCh - xEh)
    bool getPinDirection(uint16_t pin);
    uint8_t getBankDirection(uint8_t bank);
    void getAllDirection(uint8_t *banks);
    void getAllDirection(uint8_t *bank0, uint8_t *bank1, uint8_t *bank2);
    void setPinDirection(uint16_t pin, bool direction);
    void setBankDirection(uint8_t bank, uint8_t direction);
    void setAllDirection(uint8_t *banks);
    void setAllDirection(uint8_t bank0, uint8_t bank1, uint8_t bank2);

private:
    uint8_t devAddr;
    uint8_t buffer[3];
    TwoWire *I2CBus;
};

#endif /* _TCA9534_H_ */
