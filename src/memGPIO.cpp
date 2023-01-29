

#include "memGPIO.hpp"

///namespace memGPIO{

volatile unsigned long int *memGPIO::mapAddress = nullptr;

memGPIO::memGPIO() {

	//static unsigned int gpioBaseAddrs[4] = { GPIO0_ADDR, GPIO1_ADDR, GPIO2_ADDR, GPIO3_ADDR };

	this->mapAddress = 0;
	mapsMemory();
	enableClockModules();
}

memGPIO::~memGPIO() {
}


void memGPIO::mapsMemory() {
    int fd = 0;

    // Need to run this as root, using sudo or su.
    if ((fd = open ("/dev/mem", O_RDWR | O_SYNC)) < 0) {
      perror ("Unable to open '/dev/mem', make sure you have sudo privileges");
      exit (EXIT_FAILURE);
    }

    this->mapAddress = (volatile unsigned long int *) mmap(
      // Let kernel choose the address at which to create the mapping.
      nullptr,
      // Length bytes starting at offset in the file.
      MMAP_SIZE,
      // The memory protection of the mapping. Read and Write.
      PROT_READ | PROT_WRITE,
      // Flags: Make the map are visible to other processes mapping the same file and
      // guarante to be resident in RAM when the call returns successfully.
      MAP_SHARED | MAP_LOCKED,
      // The file descriptor.
      fd,
      // The length of the mapping.
      MMAP_OFFSET
    );

    // No need to keep fd open after map.
    if(close (fd) < 0){
      perror ("Unable to close /dev/mem file descriptor");
      exit (EXIT_FAILURE);
    }

    // Check if mmap correctly.
    if(this->mapAddress == MAP_FAILED) {
      perror ("Unable to map /dev/mem");
      exit (EXIT_FAILURE);
    }
  }


void memGPIO::enableClockModules()
{
    // Enable disabled GPIO module clocks.
    if (this->mapAddress[(CM_WKUP_GPIO0_CLKCTRL - MMAP_OFFSET) / GPIO_REGISTER_SIZE] & IDLEST_MASK) {
     this->mapAddress[(CM_WKUP_GPIO0_CLKCTRL - MMAP_OFFSET) / GPIO_REGISTER_SIZE] |= MODULEMODE_ENABLE;
      // Wait for the enable complete.
      while (this->mapAddress[(CM_WKUP_GPIO0_CLKCTRL - MMAP_OFFSET) / GPIO_REGISTER_SIZE] & IDLEST_MASK);
    }
    if (this->mapAddress[(CM_PER_GPIO1_CLKCTRL - MMAP_OFFSET) / GPIO_REGISTER_SIZE] & IDLEST_MASK) {
    	this->mapAddress[(CM_PER_GPIO1_CLKCTRL - MMAP_OFFSET) / GPIO_REGISTER_SIZE] |= MODULEMODE_ENABLE;
      // Wait for the enable complete.
      while (this->mapAddress[(CM_PER_GPIO1_CLKCTRL - MMAP_OFFSET) / GPIO_REGISTER_SIZE] & IDLEST_MASK);
    }
    if (this->mapAddress[(CM_PER_GPIO2_CLKCTRL - MMAP_OFFSET) / GPIO_REGISTER_SIZE] & IDLEST_MASK) {
    	this->mapAddress[(CM_PER_GPIO2_CLKCTRL - MMAP_OFFSET) / GPIO_REGISTER_SIZE] |= MODULEMODE_ENABLE;
      // Wait for the enable complete.
      while (this->mapAddress[(CM_PER_GPIO2_CLKCTRL - MMAP_OFFSET) / GPIO_REGISTER_SIZE] & IDLEST_MASK);
    }
    if (this->mapAddress[(CM_PER_GPIO3_CLKCTRL - MMAP_OFFSET) / GPIO_REGISTER_SIZE] & IDLEST_MASK) {
    	this->mapAddress[(CM_PER_GPIO3_CLKCTRL - MMAP_OFFSET) / GPIO_REGISTER_SIZE] |= MODULEMODE_ENABLE;
      // Wait for the enable complete.
      while (this->mapAddress[(CM_PER_GPIO3_CLKCTRL - MMAP_OFFSET) / GPIO_REGISTER_SIZE] & IDLEST_MASK);
    }

}



int memGPIO::setDir(unsigned char port, unsigned char pin, unsigned char dir)
{
    if ((port <= MAX_PORT) && (pin <= MAX_PIN))
    {

        if (dir == DIR_OUT)
        {
        	this->mapAddress[(gpioBaseAddrs[port] - MMAP_OFFSET + GPIO_OE) / GPIO_REGISTER_SIZE] &= ~ (1 << pin);
        }

        if (dir == DIR_IN)
        {
        	this->mapAddress[(gpioBaseAddrs[port] - MMAP_OFFSET + GPIO_OE) / GPIO_REGISTER_SIZE] |=  (1 << pin);
        }

        return GPIO_SUCCESS;
    } else
    {

#if (memGPIO_DBG)
        printf("ERROR - GPIO DIR - out of boundaries !\n");
#endif

    }
    return GPIO_ERROR;
}

int memGPIO::setPinHigh(unsigned char port, unsigned char pin)
{
    if ((port <= MAX_PORT) && (pin <= MAX_PIN))
    {
    	this->mapAddress[(gpioBaseAddrs[port] - MMAP_OFFSET + GPIO_DATAOUT) / GPIO_REGISTER_SIZE] |= (1 << pin);
        return GPIO_SUCCESS;
    }
    else
    {
#if (memGPIO_DBG)
        printf("ERROR - GPIO SetHigh - out of boundaries !\n");
#endif
    }

    return GPIO_ERROR;
}

int memGPIO::setPinLow(unsigned char port, unsigned char pin)
{
    if ((port <= MAX_PORT) && (pin <= MAX_PIN))
    {
        this->mapAddress[(gpioBaseAddrs[port] - MMAP_OFFSET + GPIO_DATAOUT) / GPIO_REGISTER_SIZE] &= ~ (1 << pin);
        return GPIO_SUCCESS;
    } else
    {
#if (memGPIO_DBG)
        printf("ERROR - GPIO SetLow - out of boundaries !\n");
#endif
    }
    return GPIO_ERROR;
}


int memGPIO::getPin(unsigned char port, unsigned char pin)
{
    if ((port <= MAX_PORT) && (pin <= MAX_PIN))
    {
   	  unsigned char value = (this->mapAddress[(gpioBaseAddrs[port] - MMAP_OFFSET + GPIO_DATAIN) / GPIO_REGISTER_SIZE] & (1 << pin)) >> pin;

   	  return value;
    }
    return GPIO_ERROR;
}

int memGPIO::setDirKernelPinNumber(unsigned char kernelPin, unsigned char dir)
{
    if (kernelPin <= MAX_KERNEL_PIN)
    {
        unsigned char port = (unsigned char) (kernelPin / 32);
        unsigned char pin = (unsigned char) (kernelPin % 32);
        if (setDir(port, pin, dir) == GPIO_SUCCESS)
        {
            return GPIO_SUCCESS;
        }
    }
    return GPIO_ERROR;
}

int memGPIO::setPinHighKernelPinNumber(unsigned char kernelPin)
{
    if (kernelPin <= MAX_KERNEL_PIN)
    {
        unsigned char port = (unsigned char) (kernelPin / 32);
        unsigned char pin = (unsigned char) (kernelPin % 32);
        if (setPinHigh(port, pin) == GPIO_SUCCESS)
        {
            return GPIO_SUCCESS;
        }
    }
    return GPIO_ERROR;
}

int memGPIO::setPinLowKernelPinNumber(unsigned char kernelPin)
{
    if (kernelPin <= MAX_KERNEL_PIN)
    {
        unsigned char port = (unsigned char) (kernelPin / 32);
        unsigned char pin = (unsigned char) (kernelPin % 32);
        return setPinLow(port, pin);
    }
    return GPIO_ERROR;
}

int memGPIO::setValueKernelPinNumber(unsigned char kernelPin, unsigned char value)
{
    if (kernelPin <= MAX_KERNEL_PIN)
    {
        if (value)
        {
            return setPinHighKernelPinNumber(kernelPin);
        } else
        {
            return setPinLowKernelPinNumber(kernelPin);
        }
    }
    return GPIO_ERROR;
}



/* getValueKernelPinNumber(unsigned char kernelPin)
 *
 */
int memGPIO::getValueKernelPinNumber(unsigned char kernelPin)
{
    if (kernelPin <= MAX_KERNEL_PIN)
    {
        unsigned char port = (unsigned char) (kernelPin / 32);
        unsigned char pin = (unsigned char) (kernelPin % 32);

        return getPin(port, pin);
    }else
    {
        return GPIO_ERROR;
    }
}




//}

