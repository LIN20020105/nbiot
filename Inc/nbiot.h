#ifndef __NBIOT_H__
#define __NBIOT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */


/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */
void send_NB_IoT(const char* cmd);
uint8_t NB_IoT_ack_check(const char* str) ;
uint8_t NB_IotConnect(void);
void nbiot_reset(void);
uint8_t NB_IoT_ZDFW(void);
uint8_t NB_IoT_connect_MQTT(void);
void publishMQTTMessage(void);
void NB_IOT_Init(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __NBIOT_H__ */


