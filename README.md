**STM32 Bare Metal GPIO Driver & Interrupt-Driven FSM**
This project demonstrates a high-performance, Bare Metal C++ implementation of a GPIO driver for STM32 microcontrollers (Cortex-M4). It features a custom Hardware Abstraction Layer (HAL) built from the ground up, utilizing an Interrupt-Driven Architecture to manage a Finite State Machine (FSM).

🚀 Key Features
Custom GPIO Driver (OOP): An object-oriented approach to hardware control, providing direct register access for maximum efficiency.

Interrupt-Driven Architecture (EXTI/NVIC): Instead of CPU-heavy polling, this project utilizes External Interrupts (EXTI) and the Nested Vectored Interrupt Controller (NVIC) to handle user inputs asynchronously.

Finite State Machine (FSM): Structured system logic controlling states: OFF -> ON -> BLINK. Transitions are triggered via hardware events.

Low-Level Interrupt Handling: Implementation of extern "C" ISR handlers to interface with the microcontrollers' Vector Table.

Advanced Hardware Configuration: * Rising Edge Detection: Optimized for Active-High hardware circuits.

Volatile Context Switching: Ensuring data integrity between the main loop and asynchronous ISR execution.

Non-Blocking Logic: The "Blink" state uses a cycle-counter approach, allowing the CPU to remain idle or process other tasks while maintaining a responsive UI.

🛠️ Hardware Configuration
The project is tailored for the STM32F407 Discovery Board.

Component	Pin	Configuration	Logic
User LED (Green)	PD12	Output (Push-Pull)	Active High
User Button	PA0	Input (EXTI0 Interrupt)	Active High (External Pull-Down)
🧩 Architectural Implementation
1. Interrupt Service Routine (ISR)
The system utilizes the EXTI0_IRQHandler to catch button presses. This ensures that the state transition logic is executed immediately, regardless of where the main program is in its execution cycle.

2. Debouncing Logic
Due to the mechanical nature of the switch and the absence of a hardware capacitor (C38 Not Fitted in schematics), a software-based debounce algorithm is implemented within the ISR to filter out spurious signals.

3. Register-Level Control
The driver bypasses standard vendor libraries, interacting directly with:

RCC: For peripheral clock management.

SYSCFG: For interrupt line mapping.

EXTI: For edge trigger configuration and pending bit management.

NVIC: For interrupt priority and enabling at the core level.

## 📂 File Structure

* `GpioDriver.h` / `GpioDriver.cpp`: The driver class implementation. Handles all direct register manipulation (RCC, MODER, ODR, IDR, etc.).
* `main.cpp`: System initialization, State Machine logic, and main application loop.

---

### 👨‍💻 Author
Developed as part of a Low-Level Embedded Systems portfolio, demonstrating proficiency in Register-Level programming and C++.

