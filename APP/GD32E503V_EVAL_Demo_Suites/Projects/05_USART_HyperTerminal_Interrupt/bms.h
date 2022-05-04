#ifndef __BMS_H
#define __BMS_H

#include "gd32e50x.h"
#include "gd32e503v_eval.h"

#define BMS_BUFFER_LEN     255
#define BMS_MODBUS_TIMEOUT  500

#define BMS_RS485_RECEIVE()  	 gpio_bit_reset(GPIOA, GPIO_PIN_15) //��������ģʽ
#define BMS_RS485_SEND()   		 gpio_bit_set(GPIOA, GPIO_PIN_15)

//ֻ���Ĵ���
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
    uint16_t pack_voltage; 			//��ص�ѹ 0.1V
    int16_t pack_current; 			//��ص��� 0.1A  ����0�ŵ磬С��0���
    uint16_t soc; 					//���ʣ������ٷֱ�
    uint16_t soh; 					//���ʣ�������ٷֱ�
    uint16_t charge_voltage;		//����ѹ 0.1V
    uint16_t charge_current;		//������ 0.1A
    uint16_t charge_power;			//��繦�� W
    uint16_t output_power;			//������� W
    uint16_t nominal_capacity;		//����� Ah
    uint16_t error_state;			//�쳣״̬  bit0���¶��쳣������/�澯��bit1����ѹ�쳣������/�澯��bit2�������쳣������/�澯�����쳣Ϊ1������Ϊ0��

} BMS_Information_Pack_t; 			//BMS PACK��Ϣ

extern BMS_Information_Pack_t BMS_Info_Pack;




void BMS_Handel_Modbus(void);
void BMS_Diag(void);
void BMS_UartCmd_Send(uint8_t *pbuf, uint8_t len);
void BMS_Handle_Multiple(uint16_t addr, uint16_t num, uint8_t *pbuf);

#endif