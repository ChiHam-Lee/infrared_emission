
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
	adcx = GetTemperature(); //ʹ��PC5 ADC1, ͨ��15
	adcValue = GetLightAdc(14);
	LED_SEL = 0; 		//0ѡ������ܣ�1ѡ�������
	SysTickIntInit() ;	//��ʱ���жϳ�ʼ��
	EXTIX_Init() ;		//�ⲿ�жϳ�ʼ��
	uart3_init(36,1200) ;//����3��ʼ�� 


	while(1)
	{		
		i++;
		if( i > 50 ) //��Լÿ��350ms����ɨ��һ��ADC��ֵ
		{
			adcValue = GetLightAdc(14); //��ȡ����ADת��ֵ. ʹ��PC4 ADC1, ͨ��14
			i = 0;
		}
		
		//����
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

