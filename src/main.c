
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIOStructure;

TIM_TimeBaseInitTypeDef TIMBaseStructure;

TIM_OCInitTypeDef TIM_PWM;

uint16_t delay_cnt = 0;

void SysTick_Handler(void)
{

	if(delay_cnt > 0)
	{
		delay_cnt--;
	}
}

void delay_ms(uint16_t time)
{
	delay_cnt = delay_ms;
	while(delay_cnt)
	{

	}
}

void config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);


	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //Alternate function modunun hangi cikis icin kullanilacagi belirttik.pwm modunda bu cikis sekli kullanilir
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);


	GPIOStructure.GPIO_Mode = GPIO_Mode_AF; //PWM uzerinden cýkýs verecegimiz icin Alternate function modu kullandýk
	GPIOStructure.GPIO_OType = GPIO_OType_PP;
	GPIOStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIOStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIOStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIOStructure);

	SysTick_Config(SystemCoreClock/1000); //1ms de bir bize interrupt verecek


	TIMBaseStructure.TIM_ClockDivision = TIM_CKD_DIV4;
	TIMBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIMBaseStructure.TIM_Period = 99;
	TIMBaseStructure.TIM_Prescaler = 4199;
	TIMBaseStructure.TIM_RepetitionCounter = 0;

	TIM_Cmd(TIM4,ENABLE);


	TIM_PWM.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_PWM.TIM_OutputState = TIM_OutputState_Enable;
	TIM_PWM.TIM_OCPolarity = TIM_OCPolarity_High;


int main(void)
{
	config();

  while (1)
  {
	  int i = 19;

	  for(i=19; i<=100; i+=10)
	  {
		  //PD12
		  TIM_PWM.TIM_Pulse = i;
		  TIM_OC1Init(TIM4,&TIM_PWM);
		  TIM_OC1PreloadConfig(TIM4,TIM_OutputState_Enable);

		  //PD13
		  TIM_PWM.TIM_Pulse = i;
		  TIM_OC2Init(TIM4,&TIM_PWM);
		  TIM_OC2PreloadConfig(TIM4,TIM_OutputState_Enable);

		  //PD14
		  TIM_PWM.TIM_Pulse = i;
		  TIM_OC3Init(TIM4,&TIM_PWM);
		  TIM_OC3PreloadConfig(TIM4,TIM_OutputState_Enable);

		  //PD15
		  TIM_PWM.TIM_Pulse = i;
		  TIM_OC4Init(TIM4,&TIM_PWM);
		  TIM_OC4PreloadConfig(TIM4,TIM_OutputState_Enable);
	  }

  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
}
