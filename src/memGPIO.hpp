/* ----------------------------------------------------------------------
 * GPIO Module Registers
 *	@Source : AM335x Technical Reference Manual ,page 4640~4666 , Table 25-5. GPIO REGISTERS
 *
 *	@note : GPIO_SETDATAOUT is single pin setting , GPIO_DATAOUT is hole pin setting
 */

#ifndef _MEMGPIO_HPP_
#define _MEMGPIO_HPP_

#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/utsname.h>
#include "utils.hpp"

//namespace memGPIO{
class memGPIO {

public:


	memGPIO();
	virtual ~memGPIO();


	void enable_gpio_clocks();
	int initMemGPIO();
	int closeGPIO();

	void mapsMemory();
	void enableClockModules();

	/*SET PIN*/
	int setDir(unsigned char port, unsigned char pin, unsigned char dir);
	int setPinHigh(unsigned char port, unsigned char pin);
	int setPinLow(unsigned char port, unsigned char pin);

	/*SET KERNEL PIN*/
	int setDirKernelPinNumber(unsigned char kernelPin, unsigned char dir);
	int setPinHighKernelPinNumber(unsigned char kernelPin);
	int setPinLowKernelPinNumber(unsigned char kernelPin);
	int setValueKernelPinNumber(unsigned char kernelPin, unsigned char value);

	/* GET VALUE FUNCTIONS */
	int getPin(unsigned char port, unsigned char pin);
	int getValueKernelPinNumber(unsigned char kernelPin);

private:

	//static unsigned int mapped = 0;
// GPIO BANKS
	static const unsigned int GPIO0_ADDR = 0x44E07000;
	static const unsigned int GPIO1_ADDR = 0x4804C000;
	static const unsigned int GPIO2_ADDR = 0x481AC000;
	static const unsigned int GPIO3_ADDR = 0x481AE000;
// GPIO BANKS ARRAY
	unsigned int gpioBaseAddrs[4] = { GPIO0_ADDR, GPIO1_ADDR, GPIO2_ADDR, GPIO3_ADDR };

	static const unsigned int GPIOX_LEN = 0x1000; /* pg. 182 GPIO length , ex: GPIO0 0x44e07000 ~ 0x44e07FFF */

	/* register offset */
	static const unsigned int GPIO_OE = 0x134;
	static const unsigned int GPIO_DATAOUT = 0x13C;
	static const unsigned int GPIO_DATAIN = 0x138;

	/* pin manipulation */
	static const unsigned int GPIO_CLEARDATAOUT = 0x190;
	static const unsigned int GPIO_SETDATAOUT = 0x194;

	static const unsigned char MAX_PORT = 3;
	static const unsigned char MAX_PIN = 31;
	static const unsigned char MAX_KERNEL_PIN = 127;
	static const int GPIO_ERROR = -1;
	static const unsigned char GPIO_SUCCESS = 0;

	static const unsigned char DIR_IN = 0;
	static const unsigned char DIR_OUT = 1;

	static const unsigned char MEM_GPIO_DBG = 1;

	static const unsigned int CM_WKUP = 0x44E00400;
	static const unsigned int CM_PER = 0x44E00000;

	static const unsigned int CM_WKP_FROM_CM_PER = 0x400;

	static const unsigned int CM_PER_LEN = 0x4000;

	static const unsigned int CM_WKP_GPIO0_CLKCTRL = 0x08;
	static const unsigned int CM_MODULE_ENABLED = 0x02;

// MMAP memory registers.
	static const unsigned int MMAP_OFFSET = 0x44C00000;
	static const unsigned int MMAP_SIZE = 0x481AEFFF - MMAP_OFFSET;

// GPIO memory whole 4-byte register.
	static const unsigned int GPIO_REGISTER_SIZE = 4;

// GPIO memory registers.
	static const unsigned int GPIO_BASE = 0x44e10800;
	static const unsigned int GPIO0 = 0x44E07000;
	static const unsigned int GPIO1 = 0x4804C000;
	static const unsigned int GPIO2 = 0x481AC000;
	static const unsigned int GPIO3 = 0x481AE000;

// Clock Module registers.
	static const unsigned int MODULEMODE_ENABLE = 0x02;
	static const unsigned int IDLEST_MASK = (0x03 << 16);

	static const unsigned int CM_WKUP_GPIO0_CLKCTRL = (CM_WKUP + 0x8); //  0x44E00408

// Clock Module Control.
	static const unsigned int CM_PER_GPIO1_CLKCTRL = (CM_PER + 0xAC);
	static const unsigned int CM_PER_GPIO2_CLKCTRL = (CM_PER + 0xB0);
	static const unsigned int CM_PER_GPIO3_CLKCTRL = (CM_PER + 0xB4);

// EPWM Module Control.
	static const unsigned int CM_PER_EPWMSS0_CLKCTRL = (CM_PER + 0xD4);
	static const unsigned int CM_PER_EPWMSS1_CLKCTRL = (CM_PER + 0xCC);
	static const unsigned int CM_PER_EPWMSS2_CLKCTRL = (CM_PER + 0xD8);

// ADC Control.
	static const unsigned int ADC_TSC = 0x44E0D000;
	static const unsigned int ADC_SYSCONFIG = (ADC_TSC + 0x10);
	static const unsigned int ADC_SOFTRESET = 0x01;
	static const unsigned int ADC_STEPCONFIG_WRITE_PROTECT_OFF = (0x01 << 2);
	static const unsigned int ADC_STEPENABLE = (ADC_TSC + 0x54);
	static const unsigned int TSC_ADC_SS_ENABLE = 0x01;
	static const unsigned int ADC_CTRL = (ADC_TSC + 0x40);
	static const unsigned int CM_WKUP_ADC_TSC_CLKCTRL = (CM_WKUP + 0xBC);
	static const unsigned int ADC_FIFO0DATA = (ADC_TSC + 0x100);
	static const unsigned int ADC_FIFO_MASK = 0xFFF;

// ADC STEPCONFIG.
	static const unsigned int ADCSTEPDELAY = ((15 & 0xFF) << 24);

	static const unsigned int ADCSTEPCONFIG1 = (ADC_TSC + 0x64);
	static const unsigned int ADCSTEPCONFIG1_VALUE = (0X00 << 19) | (0x01 << 2);
	static const unsigned int ADCSTEPDELAY1 = (ADC_TSC + 0x68);

	static const unsigned int ADCSTEPCONFIG2 = (ADC_TSC + 0x6C);
	static const unsigned int ADCSTEPCONFIG2_VALUE = (0X01 << 19) | (0x01 << 2);
	static const unsigned int ADCSTEPDELAY2 = (ADC_TSC + 0x70);

	static const unsigned int ADCSTEPCONFIG3 = (ADC_TSC + 0x74);
	static const unsigned int ADCSTEPCONFIG3_VALUE = (0X02 << 19) | (0x01 << 2);
	static const unsigned int ADCSTEPDELAY3 = (ADC_TSC + 0x78);

	static const unsigned int ADCSTEPCONFIG4 = (ADC_TSC + 0x7C);
	static const unsigned int ADCSTEPCONFIG4_VALUE = (0X03 << 19) | (0x01 << 2);
	static const unsigned int ADCSTEPDELAY4 = (ADC_TSC + 0x80);

	static const unsigned int ADCSTEPCONFIG5 = (ADC_TSC + 0x84);
	static const unsigned int ADCSTEPCONFIG5_VALUE = (0X04 << 19) | (0x01 << 2);
	static const unsigned int ADCSTEPDELAY5 = (ADC_TSC + 0x88);

	static const unsigned int ADCSTEPCONFIG6 = (ADC_TSC + 0x8C);
	static const unsigned int ADCSTEPCONFIG6_VALUE = (0X05 << 19) | (0x01 << 2);
	static const unsigned int ADCSTEPDELAY6 = (ADC_TSC + 0x90);

	static const unsigned int ADCSTEPCONFIG7 = (ADC_TSC + 0x94);
	static const unsigned int ADCSTEPCONFIG7_VALUE = (0X06 << 19) | (0x01 << 2);
	static const unsigned int ADCSTEPDELAY7 = (ADC_TSC + 0x98);

	static const unsigned int ADCSTEPCONFIG8 = (ADC_TSC + 0x9C);
	static const unsigned int ADCSTEPCONFIG8_VALUE = (0X07 << 19) | (0x01 << 2);
	static const unsigned int ADCSTEPDELAY8 = (ADC_TSC + 0xA0);

// MMAP Address pointer.
	static volatile unsigned long int *mapAddress;

};

//}


#endif
