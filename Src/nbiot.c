#include "nbiot.h"
#include "usart.h"	
#include "string.h"	
#include "tim.h"	
#include "stdio.h"

extern char USART3_RxBuffer[RxBuffer_MaxSize];   
extern uint8_t succ_receive;


void send_NB_IoT(const char* cmd) {

	HAL_UART_Transmit_IT(&huart3,(uint8_t*)cmd,strlen(cmd));

	HAL_Delay(100);
}



uint8_t NB_IoT_ack_check(const char* str) {
    HAL_Delay(100);
//	if(succ_receive == 1)
//	{
//		succ_receive = 0;
        if (strstr((const char*)USART3_RxBuffer, str)) 
			{
            memset(USART3_RxBuffer, 0, strlen((const char*)USART3_RxBuffer));
            return 1;
			} 
		else 
			{
            memset(USART3_RxBuffer, 0, strlen((const char*)USART3_RxBuffer));
            return 0;
			}
//	else
//		{
//		memset(USART3_RxBuffer, 0, strlen((const char*)USART3_RxBuffer));
//		return 1;
//		}
//	}
}


uint8_t NB_IotConnect(void) 
{
	send_NB_IoT("AT\r\n");
	HAL_Delay(100);  
	if(NB_IoT_ack_check("OK") == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void nbiot_reset(void) {
    send_NB_IoT("AT+QRST=1\r\n");
    HAL_Delay(100);
}

uint8_t NB_IoT_ZDFW(void) {
//    uint8_t success_count = 0;
//    uint8_t cmd_index = 1;
//    int command_success = 0; 

//    while (cmd_index <= 5) {
//        switch (cmd_index) {
//			 case 1:
//                send_NB_IoT("AT+QSCLK=0\r\n");
//                command_success = NB_IoT_ack_check("OK");
//                break;
//            case 2:
//                send_NB_IoT("AT+CFUN=1\r\n");
//                command_success = NB_IoT_ack_check("OK");
//                break;
//            case 3:
//                send_NB_IoT("AT+CIMI\r\n");
//                command_success = NB_IoT_ack_check("460");
//                break;
//            case 4:
//                send_NB_IoT("AT+CSQ\r\n");
//                HAL_Delay(10);
//                if (USART3_RxBuffer[6] >= '1' && USART3_RxBuffer[6] < '4') {
//                    command_success = 1;
//                } 
//                break;
//            case 5:
//                send_NB_IoT("AT+CGATT?\r\n");
//                command_success = NB_IoT_ack_check("+CGATT:1");
//                break;
//        }

//     if (command_success==1) {
//            success_count++;
//            cmd_index++;
//        }
//	 else {
//                return 0;
//			}
//    }
//    return (success_count == 5) ? 1 : 0; 
}

uint8_t NB_IoT_connect_MQTT(void) {
//    uint8_t success_count = 0;
//    uint8_t cmd_index = 1;
//    int command_success = 0; 

//    while (cmd_index <= 4) {
//        switch (cmd_index) {
//            case 1:
//                // 打开MQTT客户端网络
//                send_NB_IoT("AT+QMTOPEN=0,\"47.92.146.210\",1883\r\n");
//			command_success = NB_IoT_ack_check("+OMTOPEN:0,0");
//                break;
//            case 2:
//                // 连接客户端到MQTT服务器
//                send_NB_IoT("AT+QMTCONN=0,\"861428040040199\"\r\n");
//			command_success = NB_IoT_ack_check("+QMTCONN:0,0,0");
//                break;
//            case 3:
//                // 发布测试消息
//			    send_NB_IoT("AT+QMTPUB=0,0,0,0,\"bc25\",\"Hello MQTT\"\r\n");
//                command_success = NB_IoT_ack_check("OK");
//         
//                break;
//            case 4:
//                // 订阅主题
//               send_NB_IoT("AT+QMTSUB=0,1,\"bc25\",0\r\n");
//                command_success = NB_IoT_ack_check("OK");
//                break;	
//        }

//        if (command_success==1) {
//            success_count++;
//            cmd_index++;
//        }
//		else {
//                return 0;
//			}
//		}
//    return (success_count == 4) ? 1 : 0; 
}





void publishMQTTMessage(void) {
//    // 定义 AT 指令和要发送的数据
//    const char *atCommand = "AT+QMTPUB=0,0,0,0,\"bc25\"\r\n";
//    const char *message = "This is test data, hello MQTT.";
//    const char endChar = 0x1A;  // Ctrl+Z 的 ASCII 码

//    // 发送 AT 指令
//    HAL_UART_Transmit(&huart3, (uint8_t*)atCommand, strlen(atCommand), HAL_MAX_DELAY);

//    // 等待一段时间以确保 AT 指令被处理
//    HAL_Delay(100);  

//    // 发送消息
//    HAL_UART_Transmit(&huart3, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);

//    // 发送 Ctrl+Z 作为结束符
//    HAL_UART_Transmit(&huart3, (uint8_t*)&endChar, 1, HAL_MAX_DELAY);
	send_NB_IoT("AT+QMTPUB=0,0,0,0,\"bc25\"\r\n");
	HAL_Delay(100);  
	if(NB_IoT_ack_check(">")==0){
	send_NB_IoT("This is test data, hello MQTT.");
	HAL_Delay(100);  
	send_NB_IoT("\x1A");}
}




void NB_IOT_Init(void)
{
nbiot_reset(); // 调用复位函数
HAL_Delay(100); // 等待复位完成
NB_IotConnect();
HAL_Delay(100);
NB_IoT_ZDFW();
HAL_Delay(100);
NB_IoT_connect_MQTT();
HAL_Delay(100);
}






















