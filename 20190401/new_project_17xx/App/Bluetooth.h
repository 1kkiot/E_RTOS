/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : Bluetooth.h
Description: 实现蓝牙连接相关头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-12
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _bluetooth_h
#define _bluetooth_h
#include "gpio.h"
#include "base.h"
#include "fifo.h"

#define		BLE_RST							1
#define		BLE_RST_PIN						1<<18
#define		BLE_WAKEUP						1
#define		BLE_WAKEUP_PIN					1<<26
#define		BLE_STATUS						1
#define		BLE_STATUS_PIN					1<<19
#define		GET_BT_STATUS()					(LPC_GPIO1->FIOPIN&BLE_STATUS_PIN)
#define		ACK								"+OK"
#define		BT_NAME							"AT+NAMEzydBLE113"

#define		BLESOF							0xa5



#pragma pack(push,1)
typedef struct
{
	u8 linkf;
	u8 buff[20];
	u8 pass[6];
	u8 ValidCode;//连接蓝牙标志位
	u32 status;
}_BLE;
typedef struct
{
	u8 SOF;
	u8 Addr;
	u8 Len;
	u8 Cmd;
	u8 Parameters[20];
}_Cmd_Frame;
typedef struct
{
	u8 SOF;
	u8 Addr;
	u8 Len;
	u8 Status;
	u8 Response[20];
}_Response_Frame;
#pragma pack(pop)


extern _BLE Blevalue;
void BluetoothProcess(void);
void ble_start(void);
void ble_function(void);
void get_ble_status(void);
void Bluetooth_init(void);
void ble_failed(void);
void send_str(u8 *str);
void send_str_len(u8 *str,u8 len);
u8* ble_check_cmd(u8 *str);
u8 ble_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
u8 ble_target_unpack(u8 ch,u8 *data,u8 len);
u8 out_fifo_data(FIFO_t *fifoytpe,u8 *len,u8 *data);
#endif







