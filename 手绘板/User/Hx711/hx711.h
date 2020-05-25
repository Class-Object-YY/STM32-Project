#ifndef __hx711_H
#define	__hx711_H

#include "stm32f4xx.h"

//时钟控制引脚
#define  SCL_PIN                            GPIO_Pin_10                                 
#define  SCL_GPIO_PORT                      GPIOH                              
#define  SCL_GPIO_CLK                       RCC_AHB1Periph_GPIOH             


//信号输出引脚

#define  SDO_PIN                            GPIO_Pin_11                                 
#define  SDO_GPIO_PORT                      GPIOH                              
#define  SDO_GPIO_CLK                       RCC_AHB1Periph_GPIOH   


//引脚输出（寄存器控制）
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//设置为高电平
#define digitalLo(p,i)			 {p->BSRRH=i;}		//输出低电平
#define digitalToggle(p,i)	 {p->ODR ^=i;}		//输出反转状态

#define  ON              1
#define  OFF             0

void delay(uint32_t a);
void HX711_GPIO_Config(void);
void SCL_switch(uint8_t a);
unsigned long ReadCount(void);
unsigned long handout_read(void);


#endif /* __HX711_H */








