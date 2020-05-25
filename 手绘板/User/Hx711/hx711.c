
#include "hx711.h"

void HX711_GPIO_Config(void)
{		
		
	
	/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd ( SCL_GPIO_CLK|
	                           SDO_GPIO_CLK, ENABLE); 

		/*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = SCL_PIN;	

		/*设置引脚模式为输出模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*设置引脚为上拉模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*设置引脚速率为2MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

		/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
		GPIO_Init(SCL_GPIO_PORT, &GPIO_InitStructure);	
    
    /*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = SDO_PIN;	
			/*设置引脚模式为输出模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
  
    /*设置引脚不上拉也不下拉*/
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
	SCL_switch(OFF);//使能AD（PD_SCK 置低）
 Count=0;
 while(GPIO_ReadInputDataBit(SDO_GPIO_PORT,SDO_PIN)==ON); //AD转换未结束则等待，否则开始读取
 for (i=0;i<24;i++)
 {
SCL_switch(ON); //PD_SCK 置高（发送脉冲）
 Count=Count<<1; //下降沿来时变量Count左移一位，右侧补零
 SCL_switch(OFF); //PD_SCK 置低
 if(GPIO_ReadInputDataBit(SDO_GPIO_PORT,SDO_PIN)==ON) 
	 Count++;
 }
 SCL_switch(ON);
 Count=Count^0x800000;//第25个脉冲下降沿来时，转换数据
SCL_switch(OFF);
 //此时得到的count是ADC的补码，接下来转换成原码
 //而整数的补码与原码相同
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


