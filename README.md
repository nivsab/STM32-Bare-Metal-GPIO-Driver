# STM32F4 Bare Metal: Interrupt-Driven GPIO Driver & FSM

A professional, high-performance **Bare Metal C++** implementation of a GPIO driver for the STM32F407 (Cortex-M4). This project demonstrates direct register manipulation, hardware interrupt handling (NVIC/EXTI), and an asynchronous Finite State Machine (FSM), developed without relying on vendor-provided abstraction layers (HAL/LL).



## 🚀 Key Features

* **Bare Metal C++ (OOP):** Object-oriented driver architecture with zero-overhead abstraction, providing direct access to hardware registers.
* **Interrupt-Driven Execution:** Utilizing the **Nested Vectored Interrupt Controller (NVIC)** and **External Interrupt Controller (EXTI)** for asynchronous event handling, significantly reducing CPU load compared to polling.
* **Finite State Machine (FSM):** A robust logic controller managing three primary states: `OFF` ➔ `ON` ➔ `BLINK`. 
* **Deep Hardware Analysis:** Developed based on detailed schematic verification, including edge-trigger optimization and external pull-down resistor considerations.
* **Non-Blocking Application:** The `BLINK` state is implemented via cycle-counting logic, ensuring the system remains responsive to user input at all times.

## 🛠️ Hardware Specifications

The implementation is specifically optimized for the **STM32F407G-DISC1** development board.

| Peripheral | Pin | Configuration | Electrical Logic |
| :--- | :--- | :--- | :--- |
| **User LED (Green)** | **PD12** | Output (Push-Pull) | Active High |
| **User Button** | **PA0** | Input (EXTI0) | Active High (Ext. Pull-Down) |



## 🧩 Architectural Insights

### 1. Interrupt Service Routine (ISR) Implementation
The project implements the `EXTI0_IRQHandler` using `extern "C"` to ensure correct linkage with the microcontroller's Vector Table. This allows for near-instantaneous state transitions upon button press.

### 2. Software Debouncing Challenge
Based on the official schematics (`MB997`), the hardware debounce capacitor **C38 is "Not Fitted"** as a default factory configuration. To counter mechanical contact bounce, a precise software-based stabilization delay is integrated into the ISR.



### 3. Register Mapping
Direct manipulation of the following register sets:
* **RCC:** Peripheral clock gating and management.
* **GPIOx:** Configuration of `MODER`, `PUPDR`, `OSPEEDR`, and `OTYPER`.
* **SYSCFG:** Mapping EXTI lines to specific GPIO ports.
* **EXTI:** Managing rising-edge triggers and pending interrupt flags.
* **NVIC:** Core-level interrupt priority and enabling.



## 📂 Project Structure

* `GpioDriver.h/cpp`: The core hardware abstraction logic.
* `main.cpp`: FSM implementation and ISR handling.
* `stm32_startup.c`: Custom startup script and vector table (Bare Metal).

## 🛠️ Build & Flash
1. Ensure `arm-none-eabi-gcc` and `openocd` (or ST-Link) are installed.
2. Compile using the provided `Makefile`.
3. Flash the binary to the STM32F407 Discovery board.
