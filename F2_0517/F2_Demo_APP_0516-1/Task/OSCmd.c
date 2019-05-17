#include "OSCmd.h"

void reboot(uint8_t argc, char **argv) 
{
	__set_FAULTMASK(1);//关闭所有中断
	NVIC_SystemReset();//复位函数
}
MSH_CMD_EXPORT(reboot, Reboot System);

void restart_app1()
{
	rt_kprintf("restart app1 system!\r\n");
	while(1)
	{
		;
	}
}
MSH_CMD_EXPORT(restart_app1, restart app1 System);
void restart_app2()
{
	rt_kprintf("restart app2 system!\r\n");
}
MSH_CMD_EXPORT(restart_app2, restart app2 System);

void restore_factory()
{
	rt_kprintf("Restore Factory app system!\r\n");
}
MSH_CMD_EXPORT(restore_factory, Restore Factory app System);

