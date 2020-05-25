#ifndef __hx711_H
#define	__hx711_H

#include "stm32f4xx.h"

//ʱ�ӿ�������
#define  SCL_PIN                            GPIO_Pin_10                                 
#define  SCL_GPIO_PORT                      GPIOH                              
#define  SCL_GPIO_CLK                       RCC_AHB1Periph_GPIOH             


//�ź��������

#define  SDO_PIN                            GPIO_Pin_11                                 
#define  SDO_GPIO_PORT                      GPIOH                              
#define  SDO_GPIO_CLK                       RCC_AHB1Periph_GPIOH   


//����������Ĵ������ƣ�
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//����Ϊ�ߵ�ƽ
#define digitalLo(p,i)			 {p->BSRRH=i;}		//����͵�ƽ
#define digitalToggle(p,i)	 {p->ODR ^=i;}		//�����ת״̬

#define  ON              1
#define  OFF             0

void delay(uint32_t a);
void HX711_GPIO_Config(void);
void SCL_switch(uint8_t a);
unsigned long ReadCount(void);
unsigned long handout_read(void);


#endif /* __HX711_H */








