/* main.c - STM32CubeIDE (UART Polling, String Manipulation) */

#include "main.h"
#include <string.h>
#include <stdio.h>

UART_HandleTypeDef huart2;

#define RX_BUF_SIZE 150

char rxBuf[RX_BUF_SIZE];
char upperBuf[RX_BUF_SIZE];
char txBuf[150];

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    char ch;
    int i = 0;

    /* Receive string using UART polling */
    while (1)
    {
        HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);

        if (ch == '\r')   // Enter key
        {
            rxBuf[i] = '\0';
            break;
        }
        rxBuf[i++] = ch;

    /* Convert to UPPERCASE */
    for (i = 0; rxBuf[i] != '\0'; i++)
    {
        if (rxBuf[i] >= 'a' && rxBuf[i] <= 'z')
            upperBuf[i] = rxBuf[i] - 32;
        else
            upperBuf[i] = rxBuf[i];
    }
    upperBuf[i] = '\0';

    int len = strlen(rxBuf);

    /* Format and transmit output */
    sprintf(txBuf, "\r\nYou sent : %s\r\nUppercase : %s\r\nLength : %d\r\n",rxBuf, upperBuf, len);

    HAL_UART_Transmit(&huart2, (uint8_t *)txBuf, strlen(txBuf), HAL_MAX_DELAY);
    }
}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart2);
}

/* GPIO init */
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
}

/* System Clock Configuration (default CubeIDE generated) */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                               | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}
