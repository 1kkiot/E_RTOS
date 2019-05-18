#include "OSCmd.h"
#include "stmflash.h"

const u8 jump_app1_buf[4] = {0xa1,0xaa,0x55,0x1a};
const u8 jump_app2_buf[4] = {0xa2,0x55,0xaa,0x2a};
const u8 jump_appbackup_buf[4] = {0xa3,0xaa,0x33,0x3a};

void rebootsys(uint8_t argc, char **argv) 
{
	__set_FAULTMASK(1);//关闭所有中断
	NVIC_SystemReset();//复位函数
}
MSH_CMD_EXPORT(rebootsys, Reboot System);

void app1()
{
	rt_kprintf("restart app1 system!\r\n");
	STMFLASH_Write(JUMP_FLAG_ADDRESS,(uint32_t *)jump_app1_buf,1);
	rt_kprintf("please input reboot restart system!\r\n");
}
MSH_CMD_EXPORT(app1, restart app1 System);

void app2()
{
	rt_kprintf("restart app2 system!\r\n");
	STMFLASH_Write(JUMP_FLAG_ADDRESS,(uint32_t *)jump_app2_buf,1);
	rt_kprintf("please input reboot restart system!\r\n");
}
MSH_CMD_EXPORT(app2, restart app2 System);

void restore_factory()
{
	rt_kprintf("Restore Factory app system!\r\n");
	STMFLASH_Write(JUMP_FLAG_ADDRESS,(uint32_t *)jump_appbackup_buf,1);
	rt_kprintf("please input reboot restart system!\r\n");
}
MSH_CMD_EXPORT(restore_factory, Restore Factory app System);

