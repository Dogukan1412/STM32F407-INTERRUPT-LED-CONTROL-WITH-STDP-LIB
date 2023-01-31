
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


void Led_Config(void);
void Buton_Config(void);
void EXTI_Config(void);     // external interrupt configuration
void NVIC_Config(void);     // nested vector interrupt configuration
void Delay(uint32_t time);


int main(void)
{
	Led_Config();
	Buton_Config();
	EXTI_Config();
	NVIC_Config();
  while (1)
  {
	  GPIO_ResetBits(GPIOD, GPIO_Pin_12);
  }
}

void Led_Config(void)
{
	GPIO_InitTypeDef Led = {0};

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	Led.GPIO_Mode = GPIO_Mode_OUT;
	Led.GPIO_OType = GPIO_OType_PP;
	Led.GPIO_Pin = GPIO_Pin_12;
	Led.GPIO_PuPd = GPIO_PuPd_NOPULL;
	Led.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &Led);
}


void Buton_Config(void)
{
	GPIO_InitTypeDef Button = {0};

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	Button.GPIO_Mode = GPIO_Mode_IN;
	Button.GPIO_OType = GPIO_OType_PP;
	Button.GPIO_Pin = GPIO_Pin_0;
	Button.GPIO_PuPd = GPIO_PuPd_DOWN;
	Button.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &Button);
}


void EXTI_Config(void)
{
	EXTI_InitTypeDef exti;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);      // exti clock bus is activated

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);    // pin A0 configuration

	exti.EXTI_Line = EXTI_Line0;
	exti.EXTI_LineCmd = ENABLE;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising;

	EXTI_Init(&exti);
}


void NVIC_Config(void)
{
	NVIC_InitTypeDef nvic;

	nvic.NVIC_IRQChannel = EXTI0_IRQn;                // mask is removed
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;       // priority is used for  multiple interrupts
	nvic.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&nvic);
}


void EXTI0_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)        // checked that the interrupt has occurred
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		Delay(21000000);                          // 21000000 = 1 second
		EXTI_ClearITPendingBit(EXTI_Line0);       // interrupt reset
	}
}


void Delay(uint32_t time)
{
	while(time--);
}




/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
