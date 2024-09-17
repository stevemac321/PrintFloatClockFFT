# PrintFloatClockFFT

This project demonstrates how to configure the clocks, ITM tracing, and custom `printf` functionality for the **STM32F401RE** microcontroller, using **Keil uVision** and the **ST-Link onboard debugger**. A key feature of this project is a custom `printf` function with support for both decimal and float output. The project also includes an FFT (Fast Fourier Transform) implementation to demonstrate the configuration.

## Features
- Configures **HSI**, **PLL**, and clock assets for the **STM32F401RE** microcontroller.
- Implements **ITM tracing** using the **ST-Link onboard debugger** in **Keil uVision**.
- Custom `printf` function with decimal and float support.
- Demonstrates an FFT calculation using the configured system clock and tracing.

## System Requirements
- **Keil uVision IDE**
- **STM32F401RE** microcontroller (or similar STM32 device)
- **ST-Link** onboard debugger

## Configuration Steps

### 1. System Clock Configuration (CubeMX)
- **System Clock Mux**: Set to `PLLCLK`.
- **PLL Source Mux**: Set to `HSI` (High-Speed Internal clock).
- **PLL Configuration**:
  - **PLLM**: `/8` (to divide HSI 16 MHz down to 2 MHz).
  - **PLLN**: `x168` (to multiply 2 MHz up to 336 MHz).
  - **PLLP**: `/4` (to divide 336 MHz down to 84 MHz for `SYSCLK`).
- **Final System Clock (SYSCLK)**: `84 MHz`.

### 2. ST-Link Debugger Configuration (uVision)
- **Core Clock**: Set to `84 MHz`.
- **Trace Clock**: Set to `84 MHz`.
- **SWO Clock**: Set to `12 MHz` (to match the system).
- **ITM Port 0**: Enabled for ITM tracing.

### 3. Pin Configuration (CubeMX)
- **PB3**: Configured for `SWO` by selecting **Trace Asynchronous SW** in CubeMX.
- **PA14**: Automatically set as part of the `SWD` interface.

### 4. ITM Tracing and Custom `printf`
- **ITM_SendChar()**: Used for output instead of the standard `printf`.
- **MicroLib**: Enabled to ensure compatibility and proper system operation.
- The custom `printf` supports `%d` for integers and `%f` for floats, providing a flexible output mechanism.

## FFT Demonstration
The project includes an FFT implementation to demonstrate the functionality of the configured clock and ITM tracing setup. The FFT is computed using real and imaginary values stored in a structure, and the results are displayed using the custom `printf`.

## How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/stevemac321/PrintFloatClockFFT.git

License: GPL Version 2.