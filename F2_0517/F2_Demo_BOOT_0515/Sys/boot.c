#include "boot.h"
/*

0x8000000
boot
0x8004000
app1
0x800c000
app2
0x8060000
backup
0x80a0000

tmp		0x80e0000
*/



pFunction JumpToApplication;
uint32_t JumpAddress;

/*
read 4byte

0xa1aa551a--->jump app1
0xa255aa2a--->jump app2
0xa3aa333a--->jump backup app

*/
const u8 jump_app1_buf[4] = {0xa1,0xaa,0x55,0x1a};
const u8 jump_app2_buf[4] = {0xa2,0x55,0xaa,0x2a};
const u8 jump_appbackup_buf[4] = {0xa3,0xaa,0x33,0x3a};
u8 buf[4]={0,};

void boot()
{
	//tmp = STMFLASH_ReadWord(JUMP_FLAG_ADDRESS);

	STMFLASH_Read(JUMP_FLAG_ADDRESS,(u32 *)buf,1);

	if(memcmp(jump_app1_buf,buf,4) == 0)
	{
		jump_app1();//jump app1
	}
	else if(memcmp(jump_app2_buf,buf,4) == 0)
	{
		jump_app2();//jump app2
	}
	else if(memcmp(jump_appbackup_buf,buf,4) == 0)
	{
		jump_backupapp();//jump backup app
	}
	else//Ä¬ÈÏÈ¥app
	{
		jump_app2();
	}
}



void jump_app1()
{
	/* execute the new program */
	JumpAddress = *(__IO uint32_t*) (APP1LICATION_ADDRESS + 4);
	/* Jump to user application */
	JumpToApplication = (pFunction) JumpAddress;
	/* Initialize user application's Stack Pointer */
	__set_MSP(*(__IO uint32_t*) APP1LICATION_ADDRESS);
	JumpToApplication();
}
void jump_app2()
{
	/* execute the new program */
	JumpAddress = *(__IO uint32_t*) (APP2LICATION_ADDRESS + 4);
	/* Jump to user application */
	JumpToApplication = (pFunction) JumpAddress;
	/* Initialize user application's Stack Pointer */
	__set_MSP(*(__IO uint32_t*) APP2LICATION_ADDRESS);
	JumpToApplication();
}
void jump_backupapp()
{
	/* execute the new program */
	JumpAddress = *(__IO uint32_t*) (APP3LICATION_ADDRESS + 4);
	/* Jump to user application */
	JumpToApplication = (pFunction) JumpAddress;
	/* Initialize user application's Stack Pointer */
	__set_MSP(*(__IO uint32_t*) APP3LICATION_ADDRESS);
	JumpToApplication();
}




