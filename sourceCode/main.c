#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();
}

void Main(void)
{
	Sys_Init();
	Tim2_Pwm_Init();
	
	Adc_Cds_Init();
	for(;;)
	{

		char rx;
		int  key;
		
		if((rx=Uart1_Get_Pressed())!=0)
		{
			Moter_Run(rx);
		}
		if((key=Key_Get_Pressed()) != 0)
		{
			Key_Wait_Key_Released();
		}
		Moter_Mode(key);
	}
}
