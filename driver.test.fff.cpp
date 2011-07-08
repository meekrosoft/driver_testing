extern "C"{
#include "driver.h"
#include "registers.h"
}
#include "fff.h"
#include <igloo/igloo.h>
#include <map>
#include <iostream>

using namespace igloo;

FAKE_VOID_FUNC(IO_MEM_WR8, uint32_t, uint8_t);
FAKE_VALUE_FUNC(uint8_t, IO_MEM_RD8, uint32_t);

Context(AHardwareDriver)
{
    void SetUp()
    {
        RESET_FAKES();
        RESET_HISTORY();
    }

	Spec(WritesDataToCorrectRegister)
	{
	    driver_write(0x34);
		Assert::That(IO_MEM_WR8_call_count, Equals(1u));
		Assert::That(IO_MEM_WR8_arg1_val, Equals(0x34u));
		Assert::That(IO_MEM_WR8_arg0_val, Equals(0xFFAAu));
	}

	Spec(ReadsDataFromCorrectRegister)
	{
	    IO_MEM_RD8_return_val = 0x55;
	    uint8_t returnedValue = driver_read();
	    Assert::That(IO_MEM_RD8_call_count, Equals(1u));
	    Assert::That(returnedValue, Equals(0x55));
	    Assert::That(IO_MEM_RD8_arg0_val, Equals(0xFFABu));
	}

    Context(DuringSetupOfRevisionBHardware)
    {
        Spec(EnablesPeripheralBeforeInitializingIt)
        {
            IO_MEM_RD8_return_val = HARDWARE_REV_B;
            driver_init_device();
            // Gets the hardware revision
            Assert::That(call_history[0], Equals((void*) IO_MEM_RD8));
            Assert::That(IO_MEM_RD8_arg0_history[0], Equals(HARDWARE_VERSION_REGISTER));
            // Enables Peripheral
            Assert::That(call_history[1], Equals((void*) IO_MEM_WR8));
            Assert::That(IO_MEM_WR8_arg0_history[0], Equals(DRIVER_PERIPHERAL_ENABLE_REG));
            Assert::That(IO_MEM_WR8_arg1_history[0], Equals(1));
            // Initializes Peripheral
            Assert::That(call_history[2], Equals((void*) IO_MEM_WR8));
            Assert::That(IO_MEM_WR8_arg0_history[1], Equals(DRIVER_PERIPHERAL_INITIALIZE_REG));
            Assert::That(IO_MEM_WR8_arg1_history[1], Equals(1));
        }
    };
};
