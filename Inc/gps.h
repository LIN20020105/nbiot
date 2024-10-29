#ifndef __GPS_H__
#define __GPS_H__

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
extern UART_HandleTypeDef huart1;
void gps_init(void);
void Uart_Rece_Pares(void);
void Data_Transfor (void);
#define UART1RX_MAX_LENGTH 256 
#define Frame_Buffer_Length UART1RX_MAX_LENGTH

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __GPS_H__ */

