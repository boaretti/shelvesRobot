/* ----------------------------------------------------------------------
 * GPIO Module Registers
 *	@Source : AM335x Technical Reference Manual ,page 4640~4666 , Table 25-5. GPIO REGISTERS
 *
 *	@note : GPIO_SETDATAOUT is single pin setting , GPIO_DATAOUT is hole pin setting
 */

#define GPIO0 		0		/* GPIO ID */
#define GPIO1 		1
#define GPIO2 		2
#define GPIO3		3
#define GPIO0_ADDR	0x44e07000
#define GPIO1_ADDR 	0x4804c000
#define GPIO2_ADDR 	0x481AC000
#define GPIO3_ADDR 	0x481AE000
#define GPIOX_LEN 	0x1000		/* pg. 182 GPIO length , ex: GPIO0 0x44e07000 ~ 0x44e07FFF */

/* register offset */
#define GPIO_OE					0x134
#define GPIO_DATAIN 			0x138
#define GPIO_DATAOUT 			0x13C

/* pin manipulation */
#define GPIO_CLEARDATAOUT		0x190
#define GPIO_SETDATAOUT			0x194

#define MAX_PORT 3
#define MAX_PIN 31
#define MAX_KERNEL_PIN 127
#define GPIO_ERROR -1
#define GPIO_SUCCESS 0

#define DIR_IN 	0
#define DIR_OUT 1

#define MEM_GPIO_DBG 1

#define CM_PER 0x44e00000  /* TMC pg. 179 */
#define CM_WKP 0x44e00400
#define CM_WKP_FROM_CM_PER 0x400


#define CM_PER_GPIO1_CLKCTRL  0xAC
#define CM_PER_GPIO2_CLKCTRL  0xB0
#define CM_PER_GPIO3_CLKCTRL  0xB4

#define CM_PER_LEN 0x4000
#define CM_WKP_LEN 0x100

#define CM_WKP_GPIO0_CLKCTRL 0x08
#define CM_MODULE_ENABLED 0x02

/*MACROS FOR COMPATIBILITIE WITH ANOTHER LIBRARY*/
#define gpio_set_dir(kernelPin, direction) setDirKernelPinNumber(kernelPin, direction)
#define gpio_set_value(kernelPin, value) setValueKernelPinNumber(kernelPin, value)
#define gpio_get_value(kernelPin) getValueKernelPinNumber(kernelPin)

void enable_gpio_clocks();
int initMemGPIO();
int closeGPIO();

/*SET PIN*/
int setDir(unsigned char port, unsigned char pin, unsigned char dir);
int setPinHigh(unsigned char port, unsigned char pin);
int setPinLow(unsigned char port, unsigned char pin);

/*SET KERNEL PIN*/
int setDirKernelPinNumber (unsigned char kernelPin, unsigned char dir);
int setPinHighKernelPinNumber(unsigned char kernelPin);
int setPinLowKernelPinNumber(unsigned char kernelPin);
int setValueKernelPinNumber(unsigned char kernelPin, unsigned char value);


/* GET VALUE FUNCTIONS */
int getPin(unsigned char port, unsigned char pin);
int getValueKernelPinNumber(unsigned char kernelPin);


