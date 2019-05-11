#include "LPC17xx_it.h"



/*********************************************************************************************************
函数名:void EINT0_IRQHandler()
函数功能: EINT0中断通道服务函数
参数:无
返回值:无
*********************************************************************************************************/
void EINT0_IRQHandler()
{
	;
}
//void TIMER0_IRQHandler()
//{
//	static uint8_t flag = 0;
//	flag = !flag;
//	//if(((LPC_TIM0->IR) &(1<<0))==(1<<0))
//	if(TIM_GetIntStatus(LPC_TIM0,TIM_MR0_INT)==SET)
//	{
////		if(flag)
////		{
////			SET_GPIO_H(LED1);
////		}
////		else
////		{
////			SET_GPIO_L(LED1);
////		}
//	}
//	//LPC_TIM0->IR |=(1<<0);
//	TIM_ClearIntPending(LPC_TIM0,TIM_MR0_INT);

//}




