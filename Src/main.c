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
char USART3_RxBuffer[RxBuffer_MaxSize];   //��������
uint8_t USART3_aRxBuffer;			//�����жϻ���
uint8_t UART3_Rx_Cnt = 0;		//���ջ������
char atCommand[RxBuffer_MaxSize];
volatile uint32_t last_heartbeat_time = 0; // �ϴ�����ʱ��
volatile uint8_t heartbeat_received = 0;    // �������ձ�־
const uint32_t timeout = 60000;

uint16_t USART1_RX_STA; 
uint8_t gUart1ReceBuf[UART1RX_MAX_LENGTH]; // ����1���ջ�����
uint16_t gReceCount ;
uint8_t suc_rece; // ���ճɹ���־


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
    // �жϷ���ֵ��������Ӧ����
    if (connectStatus == 1) {
        // ���ӳɹ�
        HAL_UART_Transmit(&huart1, (uint8_t*)"���ӳɹ�\r\n", 11, HAL_MAX_DELAY);
    } else {
        // ����ʧ��
        HAL_UART_Transmit(&huart1, (uint8_t*)"����ʧ��\r\n", 11, HAL_MAX_DELAY);
    }
//	  if (NB_IoT_ZDFWStatus == 1) {
//        // ���ӳɹ�
//        HAL_UART_Transmit(&huart1, (uint8_t*)"���ӳɹ�\r\n", 11, HAL_MAX_DELAY);
//    } else {
//        // ����ʧ��
//        HAL_UART_Transmit(&huart1, (uint8_t*)"����ʧ��\r\n", 11, HAL_MAX_DELAY);
//    }
//	  if (NB_IoT_connect_MQTTStatus == 1) {
//        // ���ӳɹ�
//        HAL_UART_Transmit(&huart1, (uint8_t*)"���ӳɹ�\r\n", 11, HAL_MAX_DELAY);
//    } else {
//        // ����ʧ��
//        HAL_UART_Transmit(&huart1, (uint8_t*)"����ʧ��\r\n", 11, HAL_MAX_DELAY);
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
//    // ����ATָ��
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

 	if(UART3_Rx_Cnt >= 255)  //����ж�
	{
		UART3_Rx_Cnt = 0;
		memset(USART3_RxBuffer,0x00,sizeof(USART3_RxBuffer));
		HAL_UART_Transmit(&huart3, (uint8_t *)"�������", 10,0xFFFF); 	
  }
	else
	{
		USART3_RxBuffer[UART3_Rx_Cnt++] =USART3_aRxBuffer;   //��������ת��
			if(USART3_RxBuffer[UART3_Rx_Cnt-1] == '\n') 
			{
//				HAL_UART_Transmit(&huart3, (uint8_t *)&USART3_RxBuffer, UART3_Rx_Cnt,0xFFFF); //���յ�����Ϣ���ͳ�ȥ
				succ_receive = 1;
//				while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//���UART���ͽ���
				UART3_Rx_Cnt = 0;
			}
	}
			HAL_UART_Receive_IT(&huart3, (uint8_t *)&USART3_aRxBuffer, 1);   //�ٿ��������ж�
}
	if (huart->Instance == USART1)
	  {
		uint8_t recContent = 0;   // �洢��������
	// ������ڽ��յ�����
	    if (USART1_RX_STA != 0) 
	{
        USART1_RX_STA = 0;
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&gUart1ReceBuf, 1);
	}
		// ������յ�����$��$��һ֡��Ϣ�Ŀ�ʼ��
		// ��֤ÿ���յ��µ�һ֡��Ϣ�ʹӻ�������ʼλ�ÿ�ʼ�洢
		if(recContent == '$')
		{
			gReceCount = 0;   // ����֡��Ϣ��������
		}
		
		// �洢���յ���֡��Ϣ
		gUart1ReceBuf[gReceCount ++] = recContent;
		
		// ȷ���Ƿ��յ�"GPRMC/GNRMC"��һ֡����
		if(gUart1ReceBuf[0] == '$' && gUart1ReceBuf[4] == 'M' && gUart1ReceBuf[5] == 'C')
		{
			// ���յ����У���������һ֡��Ϣ��
			if(recContent == '\n')									   
			{
				memset(receDataFrame.Frame_Buffer, 0, Frame_Buffer_Length);   // ��ʼ������֡��Ϣ����
				memcpy(receDataFrame.Frame_Buffer, gUart1ReceBuf, gReceCount);   // ����GPRMC/GNRMC��֡������
				receDataFrame.isGetData = 1;   // ���ճɹ�
				suc_rece = 1;
				gReceCount = 0;   // �������֡��Ϣ���ռ�������
				memset(gUart1ReceBuf, 0, UART1RX_MAX_LENGTH);   // ��մ���1����Buf				
			}		
		}
		
		// ����������ݳ�����󳤶ȣ����ټ�������
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
        last_heartbeat_time = HAL_GetTick(); // ��������ʱ��
        heartbeat_received = 0; // �����������ձ�־
	if (NB_IoT_ack_check("OK") == 0) 
	{
            heartbeat_received = 1; // �յ���Ӧ
	}
	 if ((heartbeat_received == 0) && (HAL_GetTick() - last_heartbeat_time >= timeout)) 
		 {
            nbiot_reset(); // ����ģ��
            HAL_Delay(5000); // �ȴ��������
			NB_IotConnect(); // ��������
            NB_IoT_ZDFW(); // ��������
			NB_IoT_connect_MQTT(); // ��������MQTT
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
