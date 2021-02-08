/*
 * iic.c
 *
 *  Created on: Feb 5, 2021
 *      Author: Administrator
 */


#include "headfile.h"


//IO��������
#define SDA_IN()  gpio_init(B13, GPI, 1, SPEED_50MHZ | IN_PULLUP);
#define SDA_OUT() gpio_init(B13, GPO, 1, SPEED_50MHZ | OUT_OD);
//IO��������
#define IIC_SCL_High()    gpio_set(B15,1) //SCL
#define IIC_SCL_Low()     gpio_set(B15,0) //SCL
#define IIC_SDA_High()    gpio_set(B13,1) //SCL
#define IIC_SDA_Low()     gpio_set(B13,0) //SCL

#define READ_SDA          gpio_get (B13)

void IIC_Start(void)
{
    SDA_OUT();     //sda�����ģʽ
    IIC_SDA_High();
    IIC_SCL_High();
    systick_delay_us(5);
    IIC_SDA_Low();//��ʼ�ź�,scl=1,sda=1->sda=0��
    systick_delay_us(5);
    IIC_SCL_Low();//scl=0,����ʱ����,׼�����ݵķ���
}

void IIC_Stop(void)
{
    SDA_OUT();//sda�����ģʽ
    IIC_SCL_Low();
    IIC_SDA_Low();
    systick_delay_us(5);
    IIC_SCL_High(); //�����ź�,scl=1,sda=0->sda=1��
    IIC_SDA_High();
    systick_delay_us(5);
}

void IIC_Ack(void)
{
    IIC_SCL_Low();
    SDA_OUT();
    IIC_SDA_Low();
    systick_delay_us(2);
    IIC_SCL_High();
    systick_delay_us(2);
    IIC_SCL_Low();
}

void IIC_NAck(void)
{
    IIC_SCL_Low();
    SDA_OUT();
    IIC_SDA_High();
    systick_delay_us(2);
    IIC_SCL_High();
    systick_delay_us(2);
    IIC_SCL_Low();
}

u8 IIC_Wait_Ack(void)
{
    u8 ucErrTime=0;
    SDA_IN();      //SDA����Ϊ����
    IIC_SDA_High();
    systick_delay_us(1);
    IIC_SCL_High();
    systick_delay_us(1);
    while(READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL_Low();//ʱ�����0
    return 0;
}

void IIC_Send_Byte(u8 txd)
{
    u8 t;
    SDA_OUT();
    IIC_SCL_Low();//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {
        if((txd&0x80)>>7)
            IIC_SDA_High();
        else
            IIC_SDA_Low();
        txd<<=1;
        systick_delay_us(2);   //��TEA5767��������ʱ���Ǳ����
        IIC_SCL_High();
        systick_delay_us(2);
        IIC_SCL_Low();
        systick_delay_us(2);
    }
}

//һ������ ack  ��ack=1������Ӧ���źţ�ack=0������Ӧ���ź�
u8 IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
    {
        IIC_SCL_Low();
        systick_delay_us(5);
        IIC_SCL_High();
        receive<<=1;
        if(READ_SDA)receive++;
        systick_delay_us(1);
    }
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK
    return receive;
}




