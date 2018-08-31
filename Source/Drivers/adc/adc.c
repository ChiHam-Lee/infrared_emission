
#include "adc.h"
#include "math.h"

/****************³õÊ¼»¯º¯Êý********************
* ³õÊ¼»¯
* IO¿Ú³õÊ¼»¯¡¢ADC1³õÊ¼»¯¡¢ADC2³õÊ¼»¯
******************************************************/
void VoltageAdcInit(void)
{
	//³õÊ¼»¯IO¿Ú
	RCC->APB2ENR |= 1<<2; //Ê¹ÄÜPORTA¿ÚÊ±ÖÓ
	GPIOA->CRL &= 0xffffff00; //PA0 1  Ä£ÄâÊäÈë
	
	RCC->CFGR &= ~(3<<14); //·ÖÆµÒò×ÓÇåÁã
	RCC->CFGR |= 2<<14; //6·ÖÆµ  SYSCLK/DIV2=12M ADCÊ±ÖÓÉèÖÃÎª12M,ADC1×î´óÊ±ÖÓ²»ÄÜ³¬¹ý14M!
	
	VoltageAdc1Init();
	VoltageAdc2Init();
	
}

/****************³õÊ¼»¯º¯Êý********************
* ADC1³õÊ¼»¯
******************************************************/
void VoltageAdc1Init(void)
{
	RCC->APB2ENR |= 1<<9; //ADC1Ê±ÖÓÊ¹ÄÜ
	RCC->APB2RSTR |= 1<<9; //ADC1¸´Î»
	RCC->APB2RSTR &= ~(1<<9); //¸´Î»½áÊø
	
	ADC1->CR1 &= 0xf0ffff; //¹¤×÷Ä£Ê½ÇåÁã
	ADC1->CR1 |= 0<<16; //¶ÀÁ¢¹¤×÷Ä£Ê½
	ADC1->CR1 &= ~(1<<8); //·ÇÉ¨ÃèÄ£Ê½
	ADC1->CR2 &= ~(1<<1); //µ¥´Î×ª»»Ä£Ê½
	ADC1->CR2 &= ~(7<<17); 
	ADC1->CR2 |= 7<<17; //SWSTART£ºÈí¼þ¿ØÖÆ×ª»»
	ADC1->CR2 |= 1<<20; //Ê¹ÓÃÍâ²¿´¥·¢£¨SWSTART£©£¬±ØÐëÊ¹ÓÃÒ»¸öÊÂ¼þÀ´´¥·¢
	ADC1->CR2 &= ~(1<<11); //ÓÒ¶ÔÆë
	ADC1->SQR1 &= ~(0xf<<20);
	ADC1->SQR1 &= 0<<20; //1¸ö×ª»»ÔÚ¹æÔòÐòÁÐÖÐ£¬Ò²¾ÍÊÇÖ»×ª»»¹æÔòÐòÁÐ1
	
	ADC1->SMPR2 &= 0xfffffff0; //Í¨µÀ0²ÉÑùÊ±¼äÇå¿Õ
	ADC1->SMPR2 |= 7<<0; //Í¨µÀ0 239.5ÖÜÆÚ£¬Ìá¸ß²ÉÓÃÊ±¼ä¿ÉÒÔÌá¸ß¾«È·¶È
	
	ADC1->CR2 |= 1<<0; //¿ªÆôAD×ª»»Æ÷
	ADC1->CR2 |= 1<<3; //Ê¹ÄÜ¸´Î»Ð£×¼
	while( ADC1->CR2 & 1<<3 )
		; //µÈ´ýÐ£×¼½áÊø
	ADC1->CR2 |= 1<<2; //¿ªÆôADÐ£×¼
	while( ADC1->CR2 & 1<<2 )
		; //µÈ´ýÐ£×¼½áÊø
}

/****************³õÊ¼»¯º¯Êý********************
* ADC2³õÊ¼»¯
******************************************************/
void VoltageAdc2Init(void)
{
	RCC->APB2ENR |= 1<<10; //ADC1Ê±ÖÓÊ¹ÄÜ
	RCC->APB2RSTR |= 1<<10; //ADC1¸´Î»
	RCC->APB2RSTR &= ~(1<<10); //¸´Î»½áÊ
	
	ADC2->CR1 &= 0xf0ffff; //¹¤×÷Ä£Ê½ÇåÁã
	ADC2->CR1 |= 0<<16; //¶ÀÁ¢¹¤×÷Ä£Ê½
	ADC2->CR1 &= ~(1<<8); //·ÇÉ¨ÃèÄ£Ê½
	ADC2->CR2 &= ~(1<<1); //µ¥´Î×ª»»Ä£Ê½
	ADC2->CR2 &= ~(7<<17); 
	ADC2->CR2 |= 7<<17; //SWSTART£ºÈí¼þ¿ØÖÆ×ª»»
	ADC2->CR2 |= 1<<20; //Ê¹ÓÃÍâ²¿´¥·¢£¨SWSTART£©£¬±ØÐëÊ¹ÓÃÒ»¸öÊÂ¼þÀ´´¥·¢
	ADC2->CR2 &= ~(1<<11); //ÓÒ¶ÔÆë
	ADC2->SQR1 &= ~(0xf<<20);
	ADC2->SQR1 &= 0<<20; //1¸ö×ª»»ÔÚ¹æÔòÐòÁÐÖÐ£¬Ò²¾ÍÊÇÖ»×ª»»¹æÔòÐòÁÐ1
	
	ADC2->SMPR2 &= ~(7<<3); //Í¨µÀ1²ÉÑùÊ±¼äÇå¿Õ
	ADC2->SMPR2 |= 7<<3; //Í¨µÀ1 239.5ÖÜÆÚ£¬Ìá¸ß²ÉÓÃÊ±¼ä¿ÉÒÔÌá¸ß¾«È·¶È
	
	ADC2->CR2 |= 1<<0; //¿ªÆôAD×ª»»Æ÷
	ADC2->CR2 |= 1<<3; //Ê¹ÄÜ¸´Î»Ð£×¼
	while( ADC2->CR2 & 1<<3 )
		; //µÈ´ýÐ£×¼½áÊø
	ADC2->CR2 |= 1<<2; //¿ªÆôADÐ£×¼
	while( ADC2->CR2 & 1<<2 )
		; //µÈ´ýÐ£×¼½áÊø
}

/****************»ñÈ¡µçÑ¹Öµº¯Êý********************
* ADC×ª»¯ÎªµçÑ¹Öµ
* adcx: 1±íÊ¾ADC1; 2±íÊ¾ADC2
* ch: Í¨µÀÖµ
* ·µ»ØµçÑ¹Öµ
******************************************************/
float GetVoltage(u8 adcx, u8 ch)
{
	u16 adcValue = 0;
	float vol = 0;
	adcValue = GetAdc( adcx, ch );
	vol = 3.3*(float)adcValue/4096;
	return vol;
}

/****************ÏÔÊ¾¶ÔÓ¦¶Ë¿ÚµÄµçÑ¹Öµº¯Êý********************
* ÏÔÊ¾£¬Õ¼ÈýÎ»
* adcx: 1±íÊ¾ADC1; 2±íÊ¾ADC2
* vol: µçÑ¹Öµ
* PA0²âÁ¿µÄµçÑ¹ÏÔÊ¾Óë×ó±ß£¬PA1²âÁ¿µÄµçÑ¹ÖµÏÔÊ¾ÓëÓÒ±ß
******************************************************/
void VoltageDisplay(u8 adcx, float vol)
{
	u8 baiWei, shiWei, geWei;

  baiWei = (u8)vol % 10;
	shiWei = (u8)(vol*10)%10;
	geWei = (u8)(vol*100)%10;
	if( adcx==1 )
	{
		PortationDisplay(0, baiWei);
		delay_ms(1);
		SetLed(1, shiWei);
		delay_ms(1);
		SetLed(2, geWei);
		delay_ms(1);
	}
	else if( adcx==2 )
	{
		PortationDisplay(5, baiWei);
		delay_ms(1);
		SetLed(6, shiWei);
		delay_ms(1);
		SetLed(7, geWei);
		delay_ms(1);
  }
}

/***************ÎÂ¶ÈºÍ¹âÕÕADCµÄ³õÊ¼»¯º¯Êý********************
* ³õÊ¼»¯ADC1£¬Í¨µÀ14 15
******************************************************/
void TemperatureAndLightAdcInit(void) //¶Ë¿Ú£¬ADC1³õÊ¼»¯£¬Í¨µÀ14¡¢15
{
	//³õÊ¼»¯IO¿Ú
	RCC->APB2ENR |= 1<<4; //Ê¹ÄÜPORTC¿ÚÊ±ÖÓ
	GPIOA->CRL &= 0xff00ffff; //PC4 5  Ä£ÄâÊäÈë
	RCC->CFGR &= ~(3<<14); //·ÖÆµÒò×ÓÇåÁã
	RCC->CFGR |= 2<<14; //6·ÖÆµ  SYSCLK/DIV2=12M ADCÊ±ÖÓÉèÖÃÎª12M,ADC1×î´óÊ±ÖÓ²»ÄÜ³¬¹ý14M!
	RCC->APB2ENR |= 1<<9; //ADC1Ê±ÖÓÊ¹ÄÜ
	RCC->APB2RSTR |= 1<<9; //ADC1¸´Î»
	RCC->APB2RSTR &= ~(1<<9); 
	ADC1->CR1 &= 0xf0ffff; //¹¤×÷Ä£Ê½ÇåÁã
	ADC1->CR1 |= 0<<16; //¶ÀÁ¢¹¤×÷Ä£Ê½
  ADC1->CR1 &= ~(1<<8);//·ÇÉ¨ÃèÄ£Ê½
	ADC1->CR2 &= ~(1<<1); //µ¥´Î×ª»»Ä£Ê½
	ADC1->CR2 &= ~(7<<17); 
	ADC1->CR2 |= 7<<17; //SWSTART£ºÈí¼þ¿ØÖÆ×ª»»
	ADC1->CR2 |= 1<<20; //Ê¹ÓÃÍâ²¿´¥·¢£¨SWSTART£©£¬±ØÐëÊ¹ÓÃÒ»¸öÊÂ¼þÀ´´¥·¢
	ADC1->CR2 &= ~(1<<11); //ÓÒ¶ÔÆë
	ADC1->SQR1 &= ~(0xf<<20);
	ADC1->SQR1 &= 0<<20;//1¸ö×ª»»ÔÚ¹æÔòÐòÁÐÖÐ£¬Ò²¾ÍÊÇÖ»×ª»»¹æÔòÐòÁÐ1
	ADC1->SMPR1 &= 0xfffc0fff; //Í¨µÀ14,15²ÉÑùÊ±¼äÇå¿Õ
	ADC1->SMPR1 |= 7<<12;//Í¨µÀ14 239.5ÖÜÆÚ
	ADC1->SMPR1 |= 7<<15;//Í¨µÀ15 239.5ÖÜÆÚ
	ADC1 -> CR2 |= 1<<0;//¿ªÆôAD×ª»»Æ÷
	ADC1->CR2 |= 1<<3; //Ê¹ÄÜ¸´Î»Ð£×¼
	while( ADC1->CR2 & 1<<3 )
		; //µÈ´ýÐ£×¼½áÊø
	ADC1->CR2 |= 1<<2; //¿ªÆôADÐ£×¼
	while( ADC1->CR2 & 1<<2 )
		; //µÈ´ýÐ£×¼½áÊø
}

/****************»ñÈ¡ADCÖµº¯Êý********************
* »ñÈ¡ADCµÄÖµ£¬²âÁ¿µÄµçÑ¹Ó¦<3.3  PA0»òPA1½ÓÕý¼«£¬¸º¼«½ÓµØ
* adcx: 1±íÊ¾ADC1; 2±íÊ¾ADC2
* ch: Í¨µÀÖµ
* ·µ»ØµÃµ½µÄADCµÄÖµ
***********************  *******************************/
u16 GetAdc(u8 adcx, u8 ch)
{
	u16 adcValue = 0;
	if( adcx == 1 )
	{
		//ÉèÖÃ×ª»»ÐòÁÐ
		ADC1->SQR3 &= 0xffffffe0; //¹æÔòÐòÁÐ1 Í¨µÀch
		ADC1->SQR3 |= ch;
		
		ADC1 -> CR2 |= 1<<22;//Æô¶¯¹æÔò×ª»»Í¨µÀ

		while( !(ADC1->SR & 1<<1) )
			; //µÈ´ý×ª»»½áÊø
		
	adcValue = ADC1 -> DR;	// ¶ÁÈ¡ADC×ª»»½á¹û

	}
	else if( adcx == 2 )
	{
		//ÉèÖÃ×ª»»ÐòÁÐ
		ADC2->SQR3 &= 0xffffffe0; //¹æÔòÐòÁÐ1 Í¨µÀch
		ADC2->SQR3 |= ch;
		ADC2->CR2 |= 1<<22; //Æô¶¯¹æÔò×ª»»Í¨µÀ
		while( !(ADC2->SR & 1<<1) )
			; //µÈ´ý×ª»»½áÊø

		adcValue = ADC2 -> DR;// ¶ÁÈ¡ADC×ª»»½á¹û

	}
	return adcValue; //·µ»ØADCµÄÖµ
}

/***************»ñÈ¡ÎÂ¶ÈµÄADCµÄÖµº¯Êý********************
* »ñÈ¡ADC1µÄADCÖµ
* chÎªÍ¨µÀÖµ
* ·µ»ØADC1µÄADCÖµ
******************************************************/
u16 GetTemperatureAdc(u8 ch)
{
	u16 adcValue = 0;
	adcValue = GetAdc( 1,ch );
	return adcValue;
}

/***************ADCÖµ×ª»»³ÉÎÂ¶ÈÖµº¯Êý********************
* Í¨¹ýADCÖµ¼ÆËãÎÂ¶ÈÖµ
* ·µ»ØÎÂ¶ÈÖµ
******************************************************/
float GetTemperature( void )
{
	u16 temperatureAdc = 0;
	float temperature = 0.0;
 	temperatureAdc = GetTemperatureAdc(  15 ); //Í¨µÀ15×¢ÈëµÄADÖµ
	temperature = (float)temperatureAdc*(3.3/4096); //µ±Ç°ÎÂ¶ÈµçÑ¹Öµ
	temperature = temperature *10000/(3.3-temperature)/1000; //ÎÂ¶Èµç×è×èÖµ
	temperature = (float)1.0/( (float)log(temperature*1000/10000)/3950 + 1.0/(273.16+25) ) - 273.16; //¼ÆËãÎÂ¶È
	
	return temperature;
}

/***************¹âÕÕÇ¿¶ÈµÄADCÖµº¯Êý********************
* ¹âÕÕÇ¿¶ÈµÄADCÖµ
* chÎªÍ¨µÀÖµ
* ·µ»Ø¹âÕÕµÄADCÖµ
******************************************************/
u16 GetLightAdc(u8 ch)
{
	u16 adcValue = 0;
	adcValue = GetAdc(1, ch);	 
	return adcValue;
}

float GetInternalTemperature( void )
{
	u16 temperatureAdc = 0;
	float temperature = 0.0;
 	temperatureAdc = GetTemperatureAdc( 16 );
	temperature = (float)temperatureAdc*(3.3/4096); //µ±Ç°ÎÂ¶ÈµçÑ¹Öµ
	temperature = temperature *10000/(3.3-temperature)/1000; //ÎÂ¶Èµç×è×èÖµ
	temperature = (float)1.0/( (float)log(temperature*1000/10000)/3950 + 1.0/(273.16+25) ) - 273.16; //¼ÆËãÎÂ¶È
	
	return temperature;
}

void AdcInitForInternalChannels(void) //¶Ë¿Ú£¬ADC1³õÊ¼»¯ÄÚ²¿Í¨µÀ16¡¢17
{
	RCC->CFGR &= ~(3<<14); //·ÖÆµÒò×ÓÇåÁã
	RCC->CFGR |= 2<<14; //6·ÖÆµ  SYSCLK/DIV2=12M ADCÊ±ÖÓÉèÖÃÎª12M,ADC1×î´óÊ±ÖÓ²»ÄÜ³¬¹ý14M!
	
	RCC->APB2ENR |= 1<<9; //ADC1Ê±ÖÓÊ¹ÄÜ
	RCC->APB2RSTR |= 1<<9; //ADC1¸´Î»
	RCC->APB2RSTR &= ~(1<<9); //¸´Î»½áÊø
	
	ADC1->CR1 &= 0xf0ffff; //¹¤×÷Ä£Ê½ÇåÁã
	ADC1->CR1 |= 0<<16; //¶ÀÁ¢¹¤×÷Ä£Ê½
	ADC1->CR1 &= ~(1<<8); //·ÇÉ¨ÃèÄ£Ê½
	ADC1->CR2 &= ~(1<<1); //µ¥´Î×ª»»Ä£Ê½
	ADC1->CR2 &= ~(7<<17); 
	ADC1->CR2 |= 7<<17; //SWSTART£ºÈí¼þ¿ØÖÆ×ª»»
	ADC1->CR2 |= 1<<20; //Ê¹ÓÃÍâ²¿´¥·¢£¨SWSTART£©£¬±ØÐëÊ¹ÓÃÒ»¸öÊÂ¼þÀ´´¥·¢
	ADC1->CR2 &= ~(1<<11); //ÓÒ¶ÔÆë
	ADC1->SQR1 &= ~(0xf<<20);
	ADC1->SQR1 &= 0<<20; //1¸ö×ª»»ÔÚ¹æÔòÐòÁÐÖÐ£¬Ò²¾ÍÊÇÖ»×ª»»¹æÔòÐòÁÐ1
	
	ADC1->SMPR1 &= 0xffc0ffff;
	ADC1->SMPR1 |= 7<<18; //239.5ÖÜÆÚ£¬Ìá¸ß²ÉÓÃÊ±¼ä¿ÉÒÔÌá¸ß¾«È·¶È
	ADC1->SMPR1 |= 7<<21; //239.5ÖÜÆÚ£¬Ìá¸ß²ÉÓÃÊ±¼ä¿ÉÒÔÌá¸ß¾«È·¶È
	
	ADC1->CR2 |= 1<<0; //¿ªÆôAD×ª»»Æ÷
	ADC1->CR2 |= 1<<3; //Ê¹ÄÜ¸´Î»Ð£×¼
	while( ADC1->CR2 & 1<<3 )
		; //µÈ´ýÐ£×¼½áÊø
	ADC1->CR2 |= 1<<2; //¿ªÆôADÐ£×¼
	while( ADC1->CR2 & 1<<2 )
		; //µÈ´ýÐ£×¼½áÊø
}


