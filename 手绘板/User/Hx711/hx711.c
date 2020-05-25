
#include "hx711.h"

void HX711_GPIO_Config(void)
{		
		
	
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( SCL_GPIO_CLK|
	                           SDO_GPIO_CLK, ENABLE); 

		/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = SCL_PIN;	

		/*��������ģʽΪ���ģʽ*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*��������Ϊ����ģʽ*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*������������Ϊ2MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

		/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
		GPIO_Init(SCL_GPIO_PORT, &GPIO_InitStructure);	
    
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = SDO_PIN;	
			/*��������ģʽΪ���ģʽ*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
  
    /*�������Ų�����Ҳ������*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
    GPIO_Init(SDO_GPIO_PORT, &GPIO_InitStructure);	
    
}


void SCL_switch(uint8_t a)
{
  if(a==1)
	{
	       digitalHi(SCL_GPIO_PORT,SCL_PIN);
	}
 else
	 
     digitalLo(SCL_GPIO_PORT,SCL_PIN);
}

unsigned long ReadCount(void) 
{
 unsigned long Count;
 unsigned char i;
	SCL_switch(OFF);//ʹ��AD��PD_SCK �õͣ�
 Count=0;
 while(GPIO_ReadInputDataBit(SDO_GPIO_PORT,SDO_PIN)==ON); //ADת��δ������ȴ�������ʼ��ȡ
 for (i=0;i<24;i++)
 {
SCL_switch(ON); //PD_SCK �øߣ��������壩
 Count=Count<<1; //�½�����ʱ����Count����һλ���Ҳಹ��
 SCL_switch(OFF); //PD_SCK �õ�
 if(GPIO_ReadInputDataBit(SDO_GPIO_PORT,SDO_PIN)==ON) 
	 Count++;
 }
 SCL_switch(ON);
 Count=Count^0x800000;//��25�������½�����ʱ��ת������
SCL_switch(OFF);
 //��ʱ�õ���count��ADC�Ĳ��룬������ת����ԭ��
 //�������Ĳ�����ԭ����ͬ
 return(Count);
}

	void delay(uint32_t a)
	{
	  while(a--);
	}
	
unsigned long handout_read(void)
{
 unsigned long counter,counter1=0,a=0;
	for(a=0;a<6;a++)
	{
	  delay(0x8fffff);
		counter=ReadCount();
		counter=counter/100;
	  counter1=counter1+counter;
	}
 counter1=counter1/6;
  return counter1;
}


