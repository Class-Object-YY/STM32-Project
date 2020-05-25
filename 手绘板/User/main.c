/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ڽӷ����ԣ����ڽ��յ����ݺ����ϻش���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "hx711.h"
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
	
int main(void)
{	
	unsigned long counter2;
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  Debug_USART_Config();
  HX711_GPIO_Config();
	/* ����һ���ַ��� */
	Usart_SendString( DEBUG_USART,"����һ�������жϽ��ջ���ʵ��\n");
	printf("����һ�������жϽ��ջ���ʵ��\n");
	
  while(1)
	{		
		counter2=handout_read();
		counter2=handout_read();
		printf("%d\n",counter2);
	}	
}



/*********************************************END OF FILE**********************/

