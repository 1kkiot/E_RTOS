#ifndef _boot_h
#define _boot_h
#include "arm_base_define.h"
#include "stmflash.h"

#define		JUMP_FLAG_ADDRESS		(uint32_t)0x08004000
#define		APP1LICATION_ADDRESS	(uint32_t)0x08008000
#define		APP2LICATION_ADDRESS	(uint32_t)0x08010000
#define		APP3LICATION_ADDRESS	(uint32_t)0x08040000


typedef  void (*pFunction)(void);


void boot(void);
void jump_app1(void);
void jump_app2(void);
void jump_backupapp(void);

#endif

