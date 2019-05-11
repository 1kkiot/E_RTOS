#include "ReCmd.h"

u8 Analysis_cmd(u8 *cmd)
{
	char *token;
	char *segment_ptr[15];
	char i;
	for(i = 0; i < 15; i++)
	{
		segment_ptr[i] = NULL;
	}
	i=0;
	token = strtok((char *)cmd, ",=");
	while(token != NULL && i < 15)
	{
		segment_ptr[i] = token;
		printf_dma("%s\n",segment_ptr[i]);
		i++;
		token = strtok(NULL,",=");
	}
	return true;
}















