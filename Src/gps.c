#include "gps.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "data_frame.h"







/*
 *==============================================================================
 *函数名称：Uart_Rece_Pares
 *函数功能：解析串口接收内容
 *输入参数：无
 *返回值：无
 *备  注：无
 *==============================================================================
*/
void Uart_Rece_Pares(void)   // 串口接收内容解析函数
{
	// 注意变量类型
	char *point = NULL;   // 逗号的地址指针
	char *nextPoint = NULL;   // 下一个逗号的地址指针
	uint8_t tempVar = 0;   // 临时循环变量
	
	// 如果数据接收成功
	if (receDataFrame.isGetData)
	{
		receDataFrame.isGetData = 0;   // 清除接收成功标志位
		
		// for循环解析接收帧
		// 总共需要找到7个逗号
		for (tempVar = 0;tempVar < 7;tempVar ++)
		{
			// 第一次循环
			if (tempVar == 0)
			{
				// 寻找第一个逗号
				if ((point = strstr((const char*)receDataFrame.Frame_Buffer,",")) == NULL)
				{
					printf ("Pares Error!\r\n");   // 解析错误
					return;
				}
			}
			else
			{
				point ++;   // 防止重复找到同一个逗号
				
				// 寻找下一个逗号
				// 注意strstr函数的输入变量，是从上一个逗号之后开始找下一个逗号
				if ((nextPoint = strstr(point,",")) != NULL)
				{
					// 存储信息
					switch (tempVar)
					{
						case 1:   // UTC时间
							memcpy(receDataFrame.UTCTime,point,nextPoint - point);
							break;
						
						case 2:   // 数据有效标识
							memcpy(receDataFrame.UsefullFlag,point,nextPoint - point);
							break;
						
						case 3:   // 纬度
							memcpy(receDataFrame.latitude,point,nextPoint - point);
							break;
						
						case 4:   // 纬度方向
							memcpy(receDataFrame.N_S,point,nextPoint - point);
							break;
						
						case 5:   // 经度
							memcpy(receDataFrame.longitude,point,nextPoint - point);
							break;
						
						case 6:   // 经度方向
							memcpy(receDataFrame.E_W,point,nextPoint - point);
							break;
					}
					
					point = nextPoint;   // 更新上一个逗号地址指针
					
					receDataFrame.isParseData = 1;   // 数据解析完成
					
					// 数据有效
					if (receDataFrame.UsefullFlag[0] == 'A')
					{
						printf ("Data is usefull!\r\n");
					}
					else if (receDataFrame.UsefullFlag[0] == 'V')
					{
						printf ("Data is invalid!\r\n");
					}
				}
				else
				{
					printf ("Pares Error!\r\n");   // 解析错误
					return;
				}
			}
		}
	}
}

/*
 *==============================================================================
 *函数名称：Data_Transfor
 *函数功能：数据转换
 *输入参数：无
 *返回值：无
 *备  注：无
 *==============================================================================
*/
void Data_Transfor (void)
{
	float latitude = 0;   // 存储纬度信息
	uint16_t temp1 = 0;   // 临时变量1，存储整数
	float longitude = 0;   // 存储经度信息
	uint16_t temp2 = 0;   // 临时变量2，存储整数
	
	latitude = strtod(receDataFrame.latitude,NULL);   // 字符串转换成浮点数
	longitude = strtod(receDataFrame.longitude,NULL);   // 字符串转换成浮点数
	
	// 纬度信息处理
	// 五位纬度信息
	if ((latitude - 10000.0f) >= 0)
	{
		// 前三位需要单独拿出来组成一个数
		temp1 = (((uint16_t)latitude / 10000) % 10) * 100 + (((uint16_t)latitude / 1000) % 10) * 10 + ((uint16_t)latitude / 100) % 10;
		latitude = latitude - (float)temp1 * 100;
		latitude = (float)temp1 + latitude / 60;
		printf ("latitude:%.3f\r\n",latitude);
	}
	else   // 四位纬度信息
	{
		// 前两位需要单独拿出来组成一个数
		temp1 = (((uint16_t)latitude / 1000) % 10) * 10 + ((uint16_t)latitude / 100) % 10;
		latitude = latitude - (float)temp1 * 100;
		latitude = (float)temp1 + latitude / 60;
		printf ("latitude:%.3f\r\n",latitude);
	}
	
	// 经度信息处理
	// 五位经度信息
	if ((longitude - 10000.0f) >= 0)
	{
		// 前三位需要单独拿出来组成一个数
		temp2 = (((uint16_t)longitude / 10000) % 10) * 100 + (((uint16_t)longitude / 1000) % 10) * 10 + ((uint16_t)longitude / 100) % 10;
		longitude = longitude - (float)temp2 * 100;
		longitude = (float)temp2 + longitude / 60;
		printf ("longitude:%.3f\r\n",longitude);
	}
	else   // 四位经度信息
	{
		// 前两位需要单独拿出来组成一个数
		temp2 = (((uint16_t)longitude / 1000) % 10) * 10 + ((uint16_t)longitude / 100) % 10;
		longitude = longitude - (float)temp2 * 100;
		longitude = (float)temp2 + longitude / 60;
		printf ("longitude:%.3f\r\n",longitude);
	}
}
