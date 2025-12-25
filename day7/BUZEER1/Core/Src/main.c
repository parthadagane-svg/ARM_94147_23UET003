#include "stm32f4xx_hal.h"

/* -------------------- Notes (Hz) -------------------- */
#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494
#define C5 523
#define D5 587
#define E5 659

/* -------------------- Buzzer Pin -------------------- */
#define BUZZER_PORT GPIOD
#define BUZZER_PIN  GPIO_PIN_12

/* -------------------- Prototypes ------------------- */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void playTone(uint16_t freq, uint16_t duration_ms);
void iplSong(void);

/* -------------------- Main ------------------------- */
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1)
    {
        iplSong();
        HAL_Delay(2500);
    }
}

/* -------------------- Tone (GPIO Toggle) ----------- */
void playTone(uint16_t freq, uint16_t duration_ms)
{
    uint32_t delay = 1000000 / freq / 2;
    uint32_t cycles = (duration_ms * 1000) / (delay * 2);

    for (uint32_t i = 0; i < cycles; i++)
    {
        HAL_GPIO_TogglePin(BUZZER_PORT, BUZZER_PIN);
        for (volatile uint32_t j = 0; j < delay; j++);
    }
}

/* -------------------- IPL-STYLE TUNE --------------- */
void iplSong(void)
{
    /* Energetic intro */
    playTone(E4,200); playTone(G4,200); playTone(A4,300);
    playTone(A4,200); playTone(G4,200); playTone(E4,300);

    /* Rising chant */
    playTone(E4,200); playTone(G4,200); playTone(A4,200);
    playTone(C5,400);

    /* Stadium hook */
    playTone(C5,200); playTone(B4,200); playTone(A4,200);
    playTone(G4,300); playTone(E4,300);

    /* Finish */
    playTone(G4,200); playTone(A4,200); playTone(C5,400);
    playTone(D5,400); playTone(C5,600);
}

/* -------------------- GPIO Init -------------------- */
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = BUZZER_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
}

/* -------------------- Clock Config ----------------- */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
        RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}
