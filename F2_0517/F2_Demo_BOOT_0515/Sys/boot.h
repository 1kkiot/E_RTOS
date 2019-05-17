#ifndef _boot_h
#define _boot_h
#include "arm_base_define.h"
#include "stmflash.h"
#define	JUMP_FLAG_ADDRESS		0x80E0000

#define APP1LICATION_ADDRESS   (uint32_t)0x08004000
#define APP2LICATION_ADDRESS   (uint32_t)0x0800C000
#define APP3LICATION_ADDRESS   (uint32_t)0x08060000
typedef  void (*pFunction)(void);




void boot(void);
void jump_app1(void);
void jump_app2(void);
void jump_backupapp(void);

#endif

