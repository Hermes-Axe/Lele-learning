/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            main
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/
//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�

//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//�Ҽ��������̣�ѡ��ˢ��

#include "headfile.h"
//ʹ�����ߵ��Կ����޸�duty�����޸�ռ�ձȵ�ֵ
extern uint8_t value;
float Tem_Value;
float RH_Value;
float lx;
int main(void)
{
    DisableGlobalIRQ();
    board_init();           //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    //�˴���д�û�����(���磺�����ʼ�������)
    gpio_init(A8, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(C9, GPO, 1, GPIO_PIN_CONFIG);
    oled_init();
    simiic_init(); //ģ��IICIO�ڳ�ʼ��
    adc_init(ADC_IN4_A4);
    wifi_protocol_init();
    //���ж������
    uart_rx_irq(DEBUG_UART, ENABLE);
    nvic_init(USART1_IRQn, 2, 1, ENABLE);

    EnableGlobalIRQ();

    SHT3X_WriteCMD(0x88,0x2236);  //���������Զ���������


    while(1)
    {
        SHT_GetValue(0x88);   //��ȡ��ʪ��ֵ
        mcu_dp_value_update(1,Tem_Value*10);
        mcu_dp_value_update(2,RH_Value);
        lx=(adc_convert(ADC_IN4_A4,ADC_8BIT)*3.3/256.0);
        mcu_dp_value_update(16,(20-(lx*10.0)));
        oled_p6x8str(25,0,"Temp=");
        oled_printf_float(55,0,Tem_Value,5,2);
        oled_p6x8str(25,3,"humi=");
        oled_printf_float(55,3,RH_Value,5,2);
        oled_p6x8str(25,6,"lux=");
        oled_printf_float(55,6,lx,5,2);
        systick_delay_ms(500);
        wifi_uart_service();

        wifi_state_get();
    }
}

//A6

