extern "C"{
#include "driver.h"
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
    }

	Spec(WritesDataToCorrectRegister)
	{
	    write_to_driver(0x34);
		Assert::That(IO_MEM_WR8_call_count, Equals(1));
		Assert::That(IO_MEM_WR8_arg1_val, Equals(0x34));
		Assert::That(IO_MEM_WR8_arg0_val, Equals(0xFFAAu));
	}

	Spec(ReadsDataFromCorrectRegister)
	{
	    IO_MEM_RD8_return_val = 0x55;
	    uint8_t returnedValue = read_from_driver();
	    Assert::That(IO_MEM_RD8_call_count, Equals(1));
	    Assert::That(returnedValue, Equals(0x55));
	    Assert::That(IO_MEM_RD8_arg0_val, Equals(0xFFABu));
	}
};
