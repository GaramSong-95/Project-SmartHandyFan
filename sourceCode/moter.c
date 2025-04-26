#include "device_driver.h"


#define TIM2_FREQ (200000.)
#define TIM2_SEC  (1./TIM2_FREQ)
enum Moter_mode {Standard,Cds,Auto};

unsigned int freq_state;
unsigned int k;
unsigned int i;
unsigned int modeState;

void Tim2_Pwm_Init()
{
    Macro_Set_Bit(RCC->APB2ENR,2);
    Macro_Write_Block(GPIOA->CRL,0xff,0xbb,8);
    
    Macro_Set_Bit(RCC->APB1ENR,0);

    Macro_Write_Block(TIM2->CCMR2,0xf,0x7,3);  // TIM2 3채널 PWM 모드
    Macro_Write_Block(TIM2->CCMR2,0x3,0x0,0);
    Macro_Write_Block(TIM2->CCER,0x3,0x1,8);
    Macro_Write_Block(TIM2->CCMR2,0xf,0x7,11); // TIM2 4채널 PWM 모드
    Macro_Write_Block(TIM2->CCER,0x3,0x1,12);
    Macro_Write_Block(TIM2->CCMR2,0x3,0x0,8);

    freq_state=200000;
    k=0;
    i=0;
    modeState=Standard;


}

void Tim2_Freq_Generation(unsigned int freq,unsigned int duty)
{
    
    TIM2->PSC = (unsigned int)(TIMXCLK/TIM2_FREQ+0.5) - 1;
    TIM2->ARR = TIM2_FREQ/freq;
    TIM2->CCR3 = TIM2->ARR/duty;
    TIM2->CCR4 = TIM2->ARR/duty;
    
    Macro_Set_Bit(TIM2->DIER,0);
    
    Macro_Set_Bit(TIM2->EGR,0);
    TIM2->CR1 = (1<<4)|(0<<3)|(1<<0);

}

// void Tim2_CCR_Change(unsigned int freq,unsigned int duty)
// {
//     TIM2->CCR3 = TIM2->ARR/duty;
//     TIM2->CCR4 = TIM2->ARR/duty;
// }

void Moter_Right()
{
    Macro_Set_Bit(TIM2->CR1,0);
    Macro_Set_Bit(TIM2->DIER,0);
    Macro_Set_Bit(TIM2->CCER,12);
    Macro_Clear_Bit(TIM2->CCER,8);

}
void Moter_Left()
{
    Macro_Set_Bit(TIM2->CR1,0);
    Macro_Set_Bit(TIM2->DIER,0);
    Macro_Set_Bit(TIM2->CCER,8);
    Macro_Clear_Bit(TIM2->CCER,12);
}

void Moter_Stop()
{
    Macro_Clear_Bit(TIM2->CCER,8);
    Macro_Clear_Bit(TIM2->CCER,12);
    Macro_Clear_Bit(TIM2->CR1,0);
    Macro_Clear_Bit(TIM2->DIER,0);

}

void Moter_Run(char rx)
{
    if(rx == 's')       // 조건을 걸어 두지 않아 cds,auto모드 일 때도 뱡향 전환가능
		{
		Uart1_Printf("\n>정지모드 %c\n", rx);

		Moter_Stop();
        return;
		}
	if(rx == 'f')
		{
		Uart1_Printf("\n>정방향모드 %c\n", rx);
		Moter_Right();
        return;

		}
	if(rx == 'r')
		{
		Uart1_Printf("\n>역방향모드 %c\n", rx);
		Moter_Left();
        return;

		}

        
    if(modeState==Standard)  //기본 모드일때만 단계 변경 가능.
    {
        if(rx == '9')
        {
            
            freq_state=30;
            Uart1_Printf("\n>9단계\n");
            
        }
        else if(rx == '8')
        {
            
            freq_state=50;
            Uart1_Printf("\n>8단계\n");
            
        }
        else if(rx == '7')
        {
        
            freq_state=100;
            Uart1_Printf("\n>7단계\n");
            
        }
        else if(rx == '6')
        {

            freq_state=500;
            Uart1_Printf("\n>6단계\n");
        }
        else if(rx == '5')
        {
            freq_state=10000;
            Uart1_Printf("\n>5단계\n");
            
        }
        else if(rx == '4')
        {
            freq_state=20000;
            Uart1_Printf("\n>4단계\n");
            
        }
        else if(rx == '3')
        {
            freq_state=50000;
            Uart1_Printf("\n>3단계\n");
            
        }
        else if(rx == '2')
        {
            freq_state=100000;
            Uart1_Printf("\n>2단계\n");
            
        }
        else if(rx == '1')
        {
            freq_state=200000;
            Uart1_Printf("\n>1단계\n");
        
        }
    }

    Tim2_Freq_Generation(freq_state,5);   //변경된 주파수를 실시간으로 적용용



}

void Moter_Mode(int key)
{
    
    
    switch(modeState)
    {
        case Standard:
        if(key==1)
        {
            modeState=Cds;
            Uart1_Printf("\n>Cds모드\n");
            Adc_Cds_Start();
        }
        else if(key==2)
        {
            modeState=Auto;
            Uart1_Printf("\n>자동모드\n");
        }
        
        break;

        case Cds:
        if(key==1)
        {
            modeState=Standard;
            Uart1_Printf("\n>기본모드\n");
            Adc_Cds_Stop();
        }
        Cds_Mode();
        break;

        case Auto:
        if(key==2)
        {
            modeState=Standard;
            k=0;
            i=0;
            Uart1_Printf("\n>기본모드\n");
        }
        Auto_Mode();
        break;
    }
}
void Cds_Mode()
{
    while(!(Adc_Cds_Get_Status()!=0)); 
    Tim2_Freq_Generation((unsigned int)Adc_Get_Data()*100,2);
    Uart1_Printf("\n>%X\n",Adc_Get_Data());
    
}

void Auto_Mode()
{
    unsigned int k;
    i = (i + 1) % 2000000;
    k=i/10; // 자동으로 1~200000까지의 주파수를 증가시킴.

    Tim2_Freq_Generation((unsigned int)(k+1), 2); 
    
}
