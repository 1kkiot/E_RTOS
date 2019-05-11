#include "main.h"
#include "SysClock.h"
#include "arm_base_define.h"
#include "MyTask.h"
#include "Memory.h"
#include "SysTime.h"
#include "SysGpio.h"
#include "SysUart.h"
#include "Wifi.h"

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	delay_init(168);
	MX_TIM3_Init();
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();
	Init_memory();
	start_system();
//	while(1)
//	{
//		SET_GPIO_H(LED1_GPIO);
//		HAL_Delay(200);
//		SET_GPIO_L(LED1_GPIO);
//		HAL_Delay(200);
//	}
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}






