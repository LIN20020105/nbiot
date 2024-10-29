#ifndef __DATA_FRAME_H
#define __DATA_FRAME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>
#include "gps.h"


typedef struct {
    uint8_t Frame_Buffer[UART1RX_MAX_LENGTH]; // 接收帧信息数组
    uint8_t isGetData; // 接收成功标志
    char UTCTime[20]; // 假设 UTC 时间的最大长度为 20
    char UsefullFlag[2]; // 假设有效标识的最大长度为 2
    char latitude[15]; // 假设纬度的最大长度为 15
    char N_S[2]; // 纬度方向
    char longitude[15]; // 假设经度的最大长度为 15
    char E_W[2]; // 经度方向
    uint8_t isParseData; // 数据解析标志
} DataFrame;

extern DataFrame receDataFrame; // 声明外部变量












#ifdef __cplusplus
}
#endif
#endif /* __DATA_FRAME_H__ */
