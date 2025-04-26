#include "device_driver.h"

void Key_Poll_Init(void)
{
	Macro_Set_Bit(RCC->APB2ENR, 3);
	Macro_Write_Block(GPIOB->CRL, 0xff, 0x44, 24);
}

#define COUNT_FOR_CHAT 		20000

static int Key_Check_Input(void)
{
	return ~Macro_Extract_Area(GPIOB->IDR, 0x3, 6) & 0x3;
}

int Key_Get_Pressed(void)
{
	unsigned int i, k;

	for(;;)
	{
		k = Key_Check_Input();

		for(i=0; i<COUNT_FOR_CHAT; i++)
		{
			if(k != Key_Check_Input())
			{
				break;
			}
		}

		if(i == COUNT_FOR_CHAT) break;
	}

	return k;
}

void Key_Wait_Key_Released(void)
{
	while(Key_Get_Pressed());
}

int Key_Wait_Key_Pressed(void)
{
	int k;

	while((k = Key_Get_Pressed()) == 0);
	return k;
}
