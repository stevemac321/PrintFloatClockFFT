/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f4xx.h"
#include "core_cm4.h"   // for ITM access
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SAMPLE_SIZE 32
#define PI 3.14159265358979323846
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
struct Complex {
    float real;
    float imag;
} coefs[32] = {
    {1.1f, 0.0f}, {2.2f, 0.0f}, {3.3f, 0.0f}, {4.4f, 0.0f},
    {5.5f, 0.0f}, {6.6f, 0.0f}, {7.7f, 0.0f}, {8.8f, 0.0f},
    {9.9f, 0.0f}, {10.1f, 0.0f}, {11.2f, 0.0f}, {12.3f, 0.0f},
    {13.4f, 0.0f}, {14.5f, 0.0f}, {15.6f, 0.0f}, {16.7f, 0.0f},
    {17.8f, 0.0f}, {18.9f, 0.0f}, {19.1f, 0.0f}, {20.2f, 0.0f},
    {21.3f, 0.0f}, {22.4f, 0.0f}, {23.5f, 0.0f}, {24.6f, 0.0f},
    {25.7f, 0.0f}, {26.8f, 0.0f}, {27.9f, 0.0f}, {28.1f, 0.0f},
    {29.2f, 0.0f}, {30.3f, 0.0f}, {31.4f, 0.0f}, {32.5f, 0.0f}
};

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void custom_printf(const char* format, ...);
void ftoa(float num, char* buffer, int precision);
// Simple itoa function to convert integers to strings
void itoa(int num, char* str) {
    sprintf(str, "%d", num);  // or write your own integer-to-string conversion logic
}

struct Complex complex_multiply(struct Complex a, struct Complex b);
struct Complex complex_add(struct Complex a, struct Complex b);
struct Complex complex_subtract(struct Complex a, struct Complex b);
void FFT(struct Complex *x, const size_t size);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
	FFT(coefs, SAMPLE_SIZE);
	for(int i=0; i < SAMPLE_SIZE; i++) {
		custom_printf("Real: %f, Imag: %f\n", coefs[i].real, coefs[i].imag);
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}
//#include <stdarg.h>
//#include "stm32f4xx.h"  // or your specific STM32 header file
//#include <math.h>       // for modf()
// Function to multiply two complex numbers
struct Complex complex_multiply(struct Complex a, struct Complex b) {
    struct Complex result;
    result.real = (a.real * b.real) - (a.imag * b.imag);
    result.imag = (a.real * b.imag) + (a.imag * b.real);
    return result;
}

// Function to add two complex numbers
struct Complex complex_add(struct Complex a, struct Complex b) {
    struct Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

// Function to subtract two complex numbers
struct Complex complex_subtract(struct Complex a, struct Complex b) {
    struct Complex result;
    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;
    return result;
}

// Recursive FFT function
void FFT(struct Complex *x, const size_t size) {
    if (size <= 1) return;

    // Divide the array into two halves
	
	 struct Complex even[size/2];
   struct Complex odd[size/2];
    
    for (int i = 0; i < size / 2; i++) {
        even[i] = x[i * 2];
        odd[i] = x[i * 2 + 1];
    }

    // Recursive FFT on both halves
    FFT(even, size / 2);
    FFT(odd, size / 2);

    // Combine
    for (size_t k = 0; k < size / 2; k++) {
        struct Complex t;
        float angle = -2 * PI * k / size;
        struct Complex twiddle = {cos(angle), sin(angle)};
        t = complex_multiply(twiddle, odd[k]);
        x[k] = complex_add(even[k], t);
        x[k + size / 2] = complex_subtract(even[k], t);
    }
		
}
// Helper function to convert float to string (ftoa)
void ftoa(float num, char* buffer, int precision) {
    int integer_part = (int)num;  // Get the integer part
    float fractional_part = num - (float)integer_part;  // Get the fractional part

    // Convert integer part to string
    itoa(integer_part, buffer);

    // Move to the end of the integer string and add decimal point
    while (*buffer != '\0') {
        buffer++;
    }
    *buffer++ = '.';

    // Convert fractional part to string
    for (int i = 0; i < precision; ++i) {
        fractional_part *= 10;
        *buffer++ = (int)fractional_part + '0';
        fractional_part -= (int)fractional_part;
    }
    *buffer = '\0';  // Null-terminate the string
}

char buffer[32];  // Buffer for string conversion

void custom_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    
    const char* ptr;

    for (ptr = format; *ptr != '\0'; ++ptr) {
        if (*ptr == '%') {
            ++ptr;  // Move to the next character after '%'
            if (*ptr == 'd') {  // Handle integer
                int num = va_arg(args, int);
                itoa(num, buffer);
                for (char* p = buffer; *p != '\0'; ++p) {
                    ITM_SendChar(*p);
                }
            } else if (*ptr == 's') {  // Handle string
                char* str = va_arg(args, char*);
                while (*str) {
                    ITM_SendChar(*str++);
                }
            } else if (*ptr == 'f') {  // Handle float
                float num = (float)va_arg(args, double);  // 'float' gets promoted to 'double' in varargs
                ftoa(num, buffer, 2);  // Convert float to string with 2 decimal precision
                for (char* p = buffer; *p != '\0'; ++p) {
                    ITM_SendChar(*p);
                }
            }
        } else {
            ITM_SendChar(*ptr);  // Print regular characters
        }
    }

    va_end(args);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
