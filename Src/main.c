/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "nbiot.h"
#include "gps.h"
#include "data_frame.h"
#include "stdio.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
char USART3_RxBuffer[RxBuffer_MaxSize];   //接收数据
uint8_t USART3_aRxBuffer;			//接收中断缓冲
uint8_t UART3_Rx_Cnt = 0;		//接收缓冲计数
char atCommand[RxBuffer_MaxSize];
volatile uint32_t last_heartbeat_time = 0; // 上次心跳时间
volatile uint8_t heartbeat_received = 0;    // 心跳接收标志
const uint32_t timeout = 60000;

uint16_t USART1_RX_STA; 
uint8_t gUart1ReceBuf[UART1RX_MAX_LENGTH]; // 串口1接收缓冲区
uint16_t gReceCount ;
uint8_t suc_rece; // 接收成功标志


uint8_t succ_receive;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

	NB_IOT_Init();
//gps_init();
strcpy((char *)USART3_RxBuffer, "OK");


    uint8_t connectStatus = NB_IotConnect();
    uint8_t NB_IoT_ZDFWStatus = NB_IoT_ZDFW();
	uint8_t NB_IoT_connect_MQTTStatus = NB_IoT_connect_MQTT();
    // 判断返回值并进行相应处理
    if (connectStatus == 1) {
        // 连接成功
        HAL_UART_Transmit(&huart1, (uint8_t*)"连接成功\r\n", 11, HAL_MAX_DELAY);
    } else {
        // 连接失败
        HAL_UART_Transmit(&huart1, (uint8_t*)"连接失败\r\n", 11, HAL_MAX_DELAY);
    }
//	  if (NB_IoT_ZDFWStatus == 1) {
//        // 连接成功
//        HAL_UART_Transmit(&huart1, (uint8_t*)"连接成功\r\n", 11, HAL_MAX_DELAY);
//    } else {
//        // 连接失败
//        HAL_UART_Transmit(&huart1, (uint8_t*)"连接失败\r\n", 11, HAL_MAX_DELAY);
//    }
//	  if (NB_IoT_connect_MQTTStatus == 1) {
//        // 连接成功
//        HAL_UART_Transmit(&huart1, (uint8_t*)"连接成功\r\n", 11, HAL_MAX_DELAY);
//    } else {
//        // 连接失败
//        HAL_UART_Transmit(&huart1, (uint8_t*)"连接失败\r\n", 11, HAL_MAX_DELAY);
//    }
	
//    publishMQTTMessage();
//	  HAL_Delay(1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  //	  if(suc_rece ==1)
//	  { 
//		    Uart_Rece_Pares();
//			Data_Transfor ();
//	  }
	  	  
//    snprintf(atCommand, sizeof(atCommand), "AT+QMTPUB=\"%s\"\r\n", gUart1ReceBuf);
//    // 发送AT指令
//	send_NB_IoT(atCommand);
//	int myVariable = longitude;  
//  publishMQTTMessage(myVariable); 
	  
	  
	  

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */





void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if (huart->Instance == USART3) 
	{

 	if(UART3_Rx_Cnt >= 255)  //溢出判断
	{
		UART3_Rx_Cnt = 0;
		memset(USART3_RxBuffer,0x00,sizeof(USART3_RxBuffer));
		HAL_UART_Transmit(&huart3, (uint8_t *)"数据溢出", 10,0xFFFF); 	
  }
	else
	{
		USART3_RxBuffer[UART3_Rx_Cnt++] =USART3_aRxBuffer;   //接收数据转存
			if(USART3_RxBuffer[UART3_Rx_Cnt-1] == '\n') 
			{
//				HAL_UART_Transmit(&huart3, (uint8_t *)&USART3_RxBuffer, UART3_Rx_Cnt,0xFFFF); //将收到的信息发送出去
				succ_receive = 1;
//				while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//检测UART发送结束
				UART3_Rx_Cnt = 0;
			}
	}
			HAL_UART_Receive_IT(&huart3, (uint8_t *)&USART3_aRxBuffer, 1);   //再开启接收中断
}
	if (huart->Instance == USART1)
	  {
		uint8_t recContent = 0;   // 存储接收内容
	// 如果串口接收到内容
	    if (USART1_RX_STA != 0) 
	{
        USART1_RX_STA = 0;
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&gUart1ReceBuf, 1);
	}
		// 如果接收到的是$（$是一帧信息的开始）
		// 保证每接收到新的一帧信息就从缓冲区起始位置开始存储
		if(recContent == '$')
		{
			gReceCount = 0;   // 清零帧信息计数变量
		}
		
		// 存储接收到的帧信息
		gUart1ReceBuf[gReceCount ++] = recContent;
		
		// 确定是否收到"GPRMC/GNRMC"这一帧数据
		if(gUart1ReceBuf[0] == '$' && gUart1ReceBuf[4] == 'M' && gUart1ReceBuf[5] == 'C')
		{
			// 接收到换行（接收完了一帧信息）
			if(recContent == '\n')									   
			{
				memset(receDataFrame.Frame_Buffer, 0, Frame_Buffer_Length);   // 初始化接收帧信息数组
				memcpy(receDataFrame.Frame_Buffer, gUart1ReceBuf, gReceCount);   // 保存GPRMC/GNRMC这帧的数据
				receDataFrame.isGetData = 1;   // 接收成功
				suc_rece = 1;
				gReceCount = 0;   // 清零接收帧信息接收计数变量
				memset(gUart1ReceBuf, 0, UART1RX_MAX_LENGTH);   // 清空串口1接收Buf				
			}		
		}
		
		// 如果接收内容超出最大长度，不再继续接收
		if(gReceCount >= UART1RX_MAX_LENGTH)
		{
			gReceCount = UART1RX_MAX_LENGTH;
		}
	}

}




void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
if (htim->Instance == TIM2)
{
		send_NB_IoT("AT\r\n");
        last_heartbeat_time = HAL_GetTick(); // 更新心跳时间
        heartbeat_received = 0; // 重置心跳接收标志
	if (NB_IoT_ack_check("OK") == 0) 
	{
            heartbeat_received = 1; // 收到回应
	}
	 if ((heartbeat_received == 0) && (HAL_GetTick() - last_heartbeat_time >= timeout)) 
		 {
            nbiot_reset(); // 重置模块
            HAL_Delay(5000); // 等待重置完成
			NB_IotConnect(); // 重新连接
            NB_IoT_ZDFW(); // 重新配置
			NB_IoT_connect_MQTT(); // 重新连接MQTT
		}
}
}





/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
