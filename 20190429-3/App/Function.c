/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Function.c
Description		: 主要实现上位机下发指令执行功能
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-27
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Function.h"
#include "Debugprintf.h"
#include "Command.h"
_Run_s RunFlag;

const struct attr_exe_data SysAttrTable[] =
{
	{(u8 *)"inventory",Inv_fun},
	{(u8 *)"alarm",Alarm_fun},
	{(u8 *)"version",Ver_fun},
	{(u8 *)"Read1",Read1_fun},
	{(u8 *)"Read2",Read2_fun},
};

/*******************************************************************************
* @Function		:void Count_time()
* @Description	:统计时间
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void Count_time()
{
	if(RunFlag.ms++ >= 9)
	{
		RunFlag.ms = 0;
		RunFlag.alamet++;
		RunFlag.timt++;
		if(RunFlag.sec++ >= 59)
		{
			RunFlag.sec = 0;
			if(RunFlag.min++ >= 59)
			{
				RunFlag.min = 0;
			}
		}
	}
	if(RunFlag.alamet >= 10)
	{
		RunFlag.alame = false;
	}
	if((RunFlag.timt >= RunFlag.tim)&&(RunFlag.tim >= 2))
	{
		RunFlag.timt = 0;
		RunFlag.autonum++;
		RunFlag.autof = true;
	}
	if(RunFlag.autonum >= 10)
	{
		RunFlag.tim = 0;
		RunFlag.autonum = 0;
		RunFlag.autof = false;
	}
}

/*******************************************************************************
* @Function		:u8 GetAttrNum(void)
* @Description	:获取列表长度
* @Input		:null
* @Output		:null
* @Return		:len
* @Others		:null
*******************************************************************************/
u8 GetAttrNum(void)
{
	return (sizeof(SysAttrTable)/sizeof(struct attr_exe_data));
}

/*******************************************************************************
* @Function		:RunStatus MsgDeal(u8 *data,u32 len)
* @Description	:命令解析并查表执行功能，长度没有用到，以防以后协议变更，故保留长度
* @Input		:u8 *data,u32 len
* @Output		:null
* @Return		:RunStatus
* @Others		:null
*******************************************************************************/
RunStatus MsgDeal(u8 *data,u32 len)
{
	u8 i;
	u8 count;
	_Cmd *Pack;

	const struct attr_exe_data* p_attr_exe = SysAttrTable;

	count = GetAttrNum();
	Pack = (_Cmd *)data;

	for(i=0;i<count;i++)
	{
		if(strcmp((char *)Pack->cmd,(char *)p_attr_exe->cmd)==0)
		{
			if(p_attr_exe->exe_attr != NULL)
			{
				p_attr_exe->exe_attr(Pack->cmd,Pack->cmddata);
			}
			return RUN_OK;
		}
		p_attr_exe++;
	}
	if(i==count)
	{
		return RUN_ERROR;
	}
	return RUN_OK;
}



/*******************************************************************************
* @Function		:RunStatus Inv_fun(u8 *cmd,u8 *data)
* @Description	:执行盘点任务，平时默认是10s盘点，可以设置为实时盘点，5min后恢复自动盘点
* @Input		:u8 *cmd,u8 *data
* @Output		:null
* @Return		:RunStatus
* @Others		:null
*******************************************************************************/
RunStatus Inv_fun(u8 *cmd,u8 *data)
{
	u16 val;
	if(strncmp((char *)cmd,(char *)"inventory",strlen((char *)cmd))!=0)
	{
		return RUN_ERROR;
	}
	val = atoi((char *)data);

	RunFlag.tim = val;
	RunFlag.timt = val;
	RunFlag.autonum = 0;
	if(RunFlag.tim == 1)
	{
		RunFlag.autof = true;
	}
	else
	{
		RunFlag.autof = false;
	}
	
	printf("inventory time %d\r\n",val);
	return RUN_OK;
}

/*******************************************************************************
* @Function		:RunStatus Alarm_fun(u8 *cmd,u8 *data)
* @Description	:执行抱紧功能
* @Input		:u8 *cmd,u8 *data
* @Output		:null
* @Return		:RunStatus
* @Others		:null
*******************************************************************************/
RunStatus Alarm_fun(u8 *cmd,u8 *data)
{
	if(strncmp((char *)cmd,(char *)"alarm",5)!=0)
	{
		return RUN_ERROR;
	}
	if(strncmp((char *)data,(char *)"yes",3)==0)
	{
		//printf("Alarm_fun start");
		RunFlag.alame = true;
		RunFlag.alamet = 0;
		READ_STUATS = STAUTS0;
	}
	else if(strncmp((char *)data,(char *)"no",2)==0)
	{
		printf("Alarm_fun end");
		RunFlag.alame = false;
	}
	return RUN_OK;
}

/*******************************************************************************
* @Function		:RunStatus Ver_fun(u8 *cmd,u8 *data)
* @Description	:执行查询版本功能
* @Input		:u8 *cmd,u8 *data
* @Output		:null
* @Return		:RunStatus
* @Others		:null
*******************************************************************************/
RunStatus Ver_fun(u8 *cmd,u8 *data)
{
	if(strncmp((char *)cmd,(char *)"version",7)!=0)
	{
		return RUN_ERROR;
	}
	if(strncmp((char *)data,(char *)"?",1)==0)
	{
		printf("%s\r\n",VER);
	}
	return RUN_OK;
}

/*******************************************************************************
* @Function		:RunStatus Read1_fun(u8 *cmd,u8 *data)
* @Description	:读命令一
* @Input		:u8 *cmd,u8 *data
* @Output		:null
* @Return		:RunStatus
* @Others		:null
*******************************************************************************/
RunStatus Read1_fun(u8 *cmd,u8 *data)
{
	if(strncmp((char *)cmd,(char *)"Read1",5)!=0)
	{
		return RUN_ERROR;
	}
	RunFlag.read1 = true;
}

/*******************************************************************************
* @Function		:RunStatus Read2_fun(u8 *cmd,u8 *data)
* @Description	:读命令二
* @Input		:u8 *cmd,u8 *data
* @Output		:null
* @Return		:RunStatus
* @Others		:null
*******************************************************************************/
RunStatus Read2_fun(u8 *cmd,u8 *data)
{
	if(strncmp((char *)cmd,(char *)"Read2",5)!=0)
	{
		return RUN_ERROR;
	}
	RunFlag.read2 = true;
}


