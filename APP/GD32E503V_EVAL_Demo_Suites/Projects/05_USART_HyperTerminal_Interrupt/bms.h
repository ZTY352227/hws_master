#ifndef __BMS_H
#define __BMS_H

#include "gd32e50x.h"
#include "gd32e503v_eval.h"

#define BMS_BUFFER_LEN     255
#define BMS_MODBUS_TIMEOUT  500

#define BMS_RS485_RECEIVE()  	 gpio_bit_reset(GPIOA, GPIO_PIN_15) //开启接收模式
#define BMS_RS485_SEND()   		 gpio_bit_set(GPIOA, GPIO_PIN_15)

//只读寄存器
#define PACK_VOLTAGE 				0x01
#define PACK_CURRENT				0x02
#define SOC 						0x03
#define SOH 						0x04
#define CHARGE_VOLTAGE				0x05
#define CHARGE_CURRENT 				0x06
#define CHARGE_POWER 				0x07
#define OUTPUT_POWER 				0x08
#define NOMINAL_CAPACITY 			0x09
#define ERROR_STATE 				0x0A


extern uint8_t  BMS_Modbus_Recv[BMS_BUFFER_LEN];
extern volatile uint8_t BMS_RecvOK;
extern volatile uint8_t BMS_RecvLen;


typedef struct
{
    uint16_t pack_voltage; 			//电池电压 0.1V
    int16_t pack_current; 			//电池电流 0.1A  大于0放电，小于0充电
    uint16_t soc; 					//电池剩余电量百分比
    uint16_t soh; 					//电池剩余寿命百分比
    uint16_t charge_voltage;		//充电电压 0.1V
    uint16_t charge_current;		//充电电流 0.1A
    uint16_t charge_power;			//充电功率 W
    uint16_t output_power;			//输出功率 W
    uint16_t nominal_capacity;		//额定容量 Ah
    uint16_t error_state;			//异常状态  bit0：温度异常（保护/告警）bit1：电压异常（保护/告警）bit2：电流异常（保护/告警）（异常为1，正常为0）

} BMS_Information_Pack_t; 			//BMS PACK信息

extern BMS_Information_Pack_t BMS_Info_Pack;




void BMS_Handel_Modbus(void);
void BMS_Diag(void);
void BMS_UartCmd_Send(uint8_t *pbuf, uint8_t len);
void BMS_Handle_Multiple(uint16_t addr, uint16_t num, uint8_t *pbuf);

#endif
