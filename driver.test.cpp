#if 0
extern "C"{
#include "driver.h"
#include "registers.h"
}
#include <igloo/igloo.h>
#include <map>
#include <iostream>

using namespace igloo;

extern "C"{
static uint8_t readVal;
static int readCalled;
static uint32_t readRegister;
uint8_t IO_MEM_RD8(uint32_t reg)
{
    readRegister = reg;
    readCalled++;
    return readVal;
}

static uint32_t writeRegister;
static uint8_t writeVal;
static int writeCalled;
void IO_MEM_WR8(uint32_t reg, uint8_t val)
{
    writeRegister = reg;
    writeVal = val;
    writeCalled++;
}
}

Context(AHardwareDriver)
{
	Spec(WritesDataToCorrectRegister)
	{
	    driver_write(0x34);
		Assert::That(writeCalled, Equals(1));
		Assert::That(writeVal, Equals(0x34));
		Assert::That(writeRegister, Equals(DRIVER_OUTPUT_REGISTER));
	}

	Spec(ReadsDataFromCorrectRegister)
	{
	    readVal = 0x55;
	    uint8_t returnedValue = driver_read();
	    Assert::That(readCalled, Equals(1));
	    Assert::That(returnedValue, Equals(readVal));
	    Assert::That(readRegister, Equals(DRIVER_INPUT_REGISTER));
	}

};
#endif
