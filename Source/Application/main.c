/******************************����ͨ�Ų���************************
* ���ܣ�����ͨ�ţ�ʹ�ð������������ֵ�Ӽ��ͷ���
* �������������ʾ��ֵ������������ֵ�ļӼ��ͷ��͡�����ʹ�ú��⡣
		KEY3����ֵ��1��KEY2����ֵ��1��KEY3��KEY2�ǰ���ɨ��ʵ�֣�
		KEY1�������ݷ��ͣ���ͨ���ⲿ�ж�ʵ�֡�
* ���ߣ��ܼ�
******************************************************************/

#include "sys.h"
#include "led.h"
#include "delay.h"
//#include "key.h"
#include "adc.h"
#include "exti.h"
#include "usart.h"


u8 num ;
/***************************������*****************************/
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
	//KeyInit() ;			//������ʼ��
	EXTIX_Init() ;		//�ⲿ�жϳ�ʼ��
	uart3_init(36,1200) ;//����3��ʼ�� //ʹ�ú��ⷢ�����ݵ�ʱ�����ʲ���̫��


	while(1)
	{		
		i++;
		if( i > 50 ) //��Լÿ��350ms����ɨ��һ��ADC��ֵ
		{
			adcx = GetTemperature(); //��ȡ�¶�ֵ. ʹ��PC5 ADC1, ͨ��15
			adcValue = GetLightAdc(14); //��ȡ����ADת��ֵ. ʹ��PC4 ADC1, ͨ��14
			i = 0;
		}

		
		//����
		SetLed(4, adcValue/1000);
		delay_ms(1);
		SetLed(5, adcValue%1000/100);
		delay_ms(1);
		SetLed(6, adcValue%100/10);
		delay_ms(1);
		SetLed(7, adcValue%10);
		delay_ms(1);
	}
}

