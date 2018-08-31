
#include "sys.h"
#include "led.h"
#include "delay.h"

#include "adc.h"
#include "exti.h"
#include "usart.h"


u8 num ;

int main()
{
	float adcx ;
	u16 adcValue ;
	u8 i = 0;
	int key,a,b;
	num = 1 ;
	Stm32_Clock_Init( 6 ); 
	delay_init( 72 );
	LED_Init();
 TemperatureAndLightAdcInit();	
	adcx = GetTemperature(); //使用PC5 ADC1, 通道15
	adcValue = GetLightAdc(14);
	LED_SEL = 0; 		//0选择数码管，1选择二极管
	SysTickIntInit() ;	//定时器中断初始化
	EXTIX_Init() ;		//外部中断初始化
	uart3_init(36,1200) ;//串口3初始化 


	while(1)
	{		
		i++;
		if( i > 50 ) //大约每隔350ms重新扫描一次ADC的值
		{
			adcValue = GetLightAdc(14); //获取光照AD转换值. 使用PC4 ADC1, 通道14
			i = 0;
		}
		
		//光照
		SetLed(0, adcValue/1000);
		delay_ms(1);
		SetLed(1, adcValue%1000/100);
		delay_ms(1);
		SetLed(2, adcValue%100/10);
		delay_ms(1);
		SetLed(3, adcValue%10);
		delay_ms(1);
		
		if(adcValue<100)
		{
			num = 1;
		}else
		{
			num = 0;
		}
	}
}

