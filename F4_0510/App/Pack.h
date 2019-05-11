#ifndef _pack_h
#define _pack_h
#include "arm_base_define.h"
#include "Debugprintf.h"
#include "Wifi.h"

#define		plen			256

#pragma pack(push,1)
typedef struct{
	u8 data[plen];
	u8 len;
}_Pack_t;
#pragma pack(pop)

extern _Pack_t Pack_t;

u8 Pack(u8 *tag,u8 len,u8 id);
#endif

