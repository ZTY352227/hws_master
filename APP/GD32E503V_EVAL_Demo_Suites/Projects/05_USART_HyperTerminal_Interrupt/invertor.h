#ifndef __INVERTOR_H
#define __INVERTOR_H

#include "gd32e50x.h"
#include "gd32e503v_eval.h"



#define AC_BUFFER_LEN     255
#define AC_MODBUS_TIMEOUT  500

#define AC_RS485_RECEIVE()		gpio_bit_reset(GPIOD, GPIO_PIN_0) //开启接收模式
#define AC_RS485_SEND()  	 	gpio_bit_set(GPIOD, GPIO_PIN_0)

//只读寄存器
#define AC_SOC                                0x100
#define AC_CHARGE_POWER                       0x10E
#define AC_DISCHARGE_POWER                    0x21B


#define DC_DC_TEMP					  0x220		//DC-DC散热片温度
#define DC_AC_TEMP					  0x221		//DC-AC散热片温度
#define TRANSFORMER_TEMP			  0x222		//变压器温度


extern uint8_t  AC_Modbus_Recv[AC_BUFFER_LEN];
extern volatile uint8_t AC_RecvOK;
extern volatile uint8_t AC_RecvLen;


typedef struct
{
    uint16_t soc; 					//电池剩余电量百分比
    uint16_t voltage; 				//电池电压 V  0.1倍
    int16_t current; 				//电池电流 A 0.1倍  大于0放电，小于0充电
    uint16_t pv_voltage;			//太阳能板电压 V 0.1倍
    uint16_t pv_current;			//太阳能板电流 A 0.1倍
    uint16_t pv_power;				//太阳能板功率 W
    uint16_t load_charge_state;		//负载状态和充电状态 0x0000：充电关，0x0001：快充，0x0002：恒压充电，0x0004：浮充，0x0006：Li battery acitvate
    uint16_t charge_power;			//充电功率 W

} AC_Information_P01_t; 			//P01 控制器数据区

extern AC_Information_P01_t AC_Info_P01;

typedef struct
{
    uint16_t ac_voltage; 			//逆变电压 0.1V
    uint16_t ac_current; 			//逆变电流 0.1A
    uint16_t ac_frequency;			//逆变频率 0.01Hz
    uint16_t load_current;			//负载电流 0.1A

    uint16_t load_active_power;		//负载有功功率 W
    uint16_t load_apparent_power;	//负载视在功率 VA

} AC_Information_P02_t; 			//P02 逆变器数据区

extern AC_Information_P02_t AC_Info_P02;

typedef struct
{
    uint16_t dc_dc_temp; 				//DC-DC散热片温度 0.1度
    uint16_t dc_ac_temp; 				//DC-AC散热片温度 0.1度
    uint16_t transformer_temp;			//变压器温度 0.1度

} AC_Information_Temp_t; 			//逆变器温度数据

extern AC_Information_Temp_t AC_Info_Temp;


void AC_Handel_Modbus(void);
void AC_Diag(void);

void AC_UartCmd_Send(uint8_t *pbuf, uint8_t len);
void AC_Handle_Multiple(uint16_t addr, uint16_t num, uint8_t *pbuf);

#endif
