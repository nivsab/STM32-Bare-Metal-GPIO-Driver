#include <stdint.h>
#include "GpioDriver.h"

// --- Global variables for ISR access ---
volatile State_t currentState = STATE_OFF; 
GpioDriver* pBtn = nullptr; // Global pointer to share the object with ISR

// --- Simple delay for software debounce ---
void softwareDelay(uint32_t count) {
    for(uint32_t i = 0; i < count; i++);
}

int main(void) {
    
    // 1. LED Initialization (PA5)
    GPIO_PinConfig_t ledConf = {0};
    ledConf.GPIO_PinNumber = LED_PIN;
    ledConf.GPIO_PinMode = GPIO_MODE_OUT;
    ledConf.GPIO_PinSpeed = GPIO_SPEED_LOW;
    ledConf.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    ledConf.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GpioDriver myLed(GPIOA, ledConf);
    myLed.init();

    // 2. Button Initialization (PA0 for EXTI0)
    GPIO_PinConfig_t btnConf = {0};
    btnConf.GPIO_PinNumber = BUTTON_PIN; // Use Pin 0
    btnConf.GPIO_PinMode = GPIO_MODE_IT_FT; // Falling edge
    btnConf.GPIO_PinSpeed = GPIO_SPEED_FAST;
    btnConf.GPIO_PinPuPdControl = GPIO_PIN_PU; // Internal Pull-up

    GpioDriver myBtn(GPIOA, btnConf); 
    myBtn.init();
    pBtn = &myBtn; // Link global pointer to the instance

    // 3. Interrupt Setup in NVIC
    GpioDriver::GPIO_IRQPriorityConfig(IRQ_NO_EXTI0, 15);
    GpioDriver::GPIO_IRQInterruptConfig(IRQ_NO_EXTI0, ENABLE);

    uint32_t blinkCounter = 0;

    while(1) {
        // --- FSM Logic Execution ---
        switch (currentState) {
            case STATE_OFF:
                myLed.write(false);
                break;
            case STATE_ON:
                myLed.write(true);
                break;
            case STATE_BLINK:
                if (++blinkCounter >= 50000) {
                    myLed.toggle();
                    blinkCounter = 0;
                }
                break;
        }
    }
}



extern "C" {
    /**
     * @brief EXTI0 Interrupt Service Routine
     * Handles state transitions based on hardware events.
     */
    void EXTI0_IRQHandler(void) {
        softwareDelay(20000); // Debounce

        if (pBtn->read() == false) { // Validate button press (Active Low)
            if (currentState == STATE_OFF) currentState = STATE_ON;
            else if (currentState == STATE_ON) currentState = STATE_BLINK;
            else currentState = STATE_OFF;
        }

        pBtn->GPIO_IRQHandling(); // Acknowledge and clear interrupt flag
    }
}
