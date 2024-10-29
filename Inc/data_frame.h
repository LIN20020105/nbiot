#ifndef __DATA_FRAME_H
#define __DATA_FRAME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>
#include "gps.h"


typedef struct {
    uint8_t Frame_Buffer[UART1RX_MAX_LENGTH]; // ����֡��Ϣ����
    uint8_t isGetData; // ���ճɹ���־
    char UTCTime[20]; // ���� UTC ʱ�����󳤶�Ϊ 20
    char UsefullFlag[2]; // ������Ч��ʶ����󳤶�Ϊ 2
    char latitude[15]; // ����γ�ȵ���󳤶�Ϊ 15
    char N_S[2]; // γ�ȷ���
    char longitude[15]; // ���辭�ȵ���󳤶�Ϊ 15
    char E_W[2]; // ���ȷ���
    uint8_t isParseData; // ���ݽ�����־
} DataFrame;

extern DataFrame receDataFrame; // �����ⲿ����












#ifdef __cplusplus
}
#endif
#endif /* __DATA_FRAME_H__ */
