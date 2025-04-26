#include "stm32f10x.h"
#include "option.h"
#include "macro.h"
#include "malloc.h"

// Uart.c

#define Uart_Init			Uart1_Init
#define Uart_Send_Byte		Uart1_Send_Byte
#define Uart_Send_String	Uart1_Send_String
#define Uart_Printf			Uart1_Printf

extern void Uart1_Init(int baud);
extern void Uart1_Send_Byte(char data);
extern void Uart1_Send_String(char *pt);
extern void Uart1_Printf(char *fmt,...);
extern char Uart1_Get_Char(void);
extern char Uart1_Get_Pressed(void);

// Led.c

extern void LED_Init(void);
extern void LED_Display(unsigned int num);
extern void LED_All_On(void);
extern void LED_All_Off(void);

// Clock.c

extern void Clock_Init(void);

// Key.c

extern void Key_Poll_Init(void);
extern int Key_Get_Pressed(void);
extern void Key_Wait_Key_Released(void);
extern int Key_Wait_Key_Pressed(void);

// Timer.c

extern void TIM2_Delay(int time);
extern void TIM2_Stopwatch_Start(void);
extern unsigned int TIM2_Stopwatch_Stop(void);
extern void TIM4_Repeat(int time);
extern int TIM4_Check_Timeout(void);
extern void TIM4_Stop(void);
extern void TIM4_Change_Value(int time);
extern void TIM3_Out_Init(void);
extern void TIM3_Out_Freq_Generation(unsigned short freq);
extern void TIM3_Out_Stop(void);

// SysTick.c

extern void SysTick_Run(unsigned int msec);
extern int SysTick_Check_Timeout(void);
extern unsigned int SysTick_Get_Time(void);
extern unsigned int SysTick_Get_Load_Time(void);
extern void SysTick_Stop(void);

// Adc.c

extern void Adc_Cds_Start(void);
extern void Adc_Cds_Stop(void);
extern int Adc_Cds_Get_Status(void);
extern int Adc_Cds_Get_Data(void);
extern int Adc_Get_Data(void);
extern void Adc_Cds_Init(void);

//Moter.c

extern void Tim2_Pwm_Init();
extern void Tim2_Freq_Generation(unsigned int freq,unsigned int duty);
extern void Moter_Right();
extern void Moter_Left();
extern void Moter_Stop();
extern void Moter_Run(char rx);
extern void Tim2_CCR_Change(unsigned int freq,unsigned int duty);
extern void Cds_Mode();
extern void Auto_Mode();
extern void Moter_Mode(int key);