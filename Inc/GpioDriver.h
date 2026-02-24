

#ifndef GPIODRIVER_H_
#define GPIODRIVER_H_

#include "stm32f405_device.h"

class GpioDriver {
private:
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t pinConfig;

public:
	// Constructor
	explicit GpioDriver(GPIO_RegDef_t *port, GPIO_PinConfig_t config);

	// Methods
	void init();
	void write(bool state);
	void toggle();
	bool read() const;

	static void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
	static void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
	void GPIO_IRQHandling();
};



#endif /* GPIODRIVER_H_ */

