#include "gps.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "data_frame.h"







/*
 *==============================================================================
 *�������ƣ�Uart_Rece_Pares
 *�������ܣ��������ڽ�������
 *�����������
 *����ֵ����
 *��  ע����
 *==============================================================================
*/
void Uart_Rece_Pares(void)   // ���ڽ������ݽ�������
{
	// ע���������
	char *point = NULL;   // ���ŵĵ�ַָ��
	char *nextPoint = NULL;   // ��һ�����ŵĵ�ַָ��
	uint8_t tempVar = 0;   // ��ʱѭ������
	
	// ������ݽ��ճɹ�
	if (receDataFrame.isGetData)
	{
		receDataFrame.isGetData = 0;   // ������ճɹ���־λ
		
		// forѭ����������֡
		// �ܹ���Ҫ�ҵ�7������
		for (tempVar = 0;tempVar < 7;tempVar ++)
		{
			// ��һ��ѭ��
			if (tempVar == 0)
			{
				// Ѱ�ҵ�һ������
				if ((point = strstr((const char*)receDataFrame.Frame_Buffer,",")) == NULL)
				{
					printf ("Pares Error!\r\n");   // ��������
					return;
				}
			}
			else
			{
				point ++;   // ��ֹ�ظ��ҵ�ͬһ������
				
				// Ѱ����һ������
				// ע��strstr����������������Ǵ���һ������֮��ʼ����һ������
				if ((nextPoint = strstr(point,",")) != NULL)
				{
					// �洢��Ϣ
					switch (tempVar)
					{
						case 1:   // UTCʱ��
							memcpy(receDataFrame.UTCTime,point,nextPoint - point);
							break;
						
						case 2:   // ������Ч��ʶ
							memcpy(receDataFrame.UsefullFlag,point,nextPoint - point);
							break;
						
						case 3:   // γ��
							memcpy(receDataFrame.latitude,point,nextPoint - point);
							break;
						
						case 4:   // γ�ȷ���
							memcpy(receDataFrame.N_S,point,nextPoint - point);
							break;
						
						case 5:   // ����
							memcpy(receDataFrame.longitude,point,nextPoint - point);
							break;
						
						case 6:   // ���ȷ���
							memcpy(receDataFrame.E_W,point,nextPoint - point);
							break;
					}
					
					point = nextPoint;   // ������һ�����ŵ�ַָ��
					
					receDataFrame.isParseData = 1;   // ���ݽ������
					
					// ������Ч
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
					printf ("Pares Error!\r\n");   // ��������
					return;
				}
			}
		}
	}
}

/*
 *==============================================================================
 *�������ƣ�Data_Transfor
 *�������ܣ�����ת��
 *�����������
 *����ֵ����
 *��  ע����
 *==============================================================================
*/
void Data_Transfor (void)
{
	float latitude = 0;   // �洢γ����Ϣ
	uint16_t temp1 = 0;   // ��ʱ����1���洢����
	float longitude = 0;   // �洢������Ϣ
	uint16_t temp2 = 0;   // ��ʱ����2���洢����
	
	latitude = strtod(receDataFrame.latitude,NULL);   // �ַ���ת���ɸ�����
	longitude = strtod(receDataFrame.longitude,NULL);   // �ַ���ת���ɸ�����
	
	// γ����Ϣ����
	// ��λγ����Ϣ
	if ((latitude - 10000.0f) >= 0)
	{
		// ǰ��λ��Ҫ�����ó������һ����
		temp1 = (((uint16_t)latitude / 10000) % 10) * 100 + (((uint16_t)latitude / 1000) % 10) * 10 + ((uint16_t)latitude / 100) % 10;
		latitude = latitude - (float)temp1 * 100;
		latitude = (float)temp1 + latitude / 60;
		printf ("latitude:%.3f\r\n",latitude);
	}
	else   // ��λγ����Ϣ
	{
		// ǰ��λ��Ҫ�����ó������һ����
		temp1 = (((uint16_t)latitude / 1000) % 10) * 10 + ((uint16_t)latitude / 100) % 10;
		latitude = latitude - (float)temp1 * 100;
		latitude = (float)temp1 + latitude / 60;
		printf ("latitude:%.3f\r\n",latitude);
	}
	
	// ������Ϣ����
	// ��λ������Ϣ
	if ((longitude - 10000.0f) >= 0)
	{
		// ǰ��λ��Ҫ�����ó������һ����
		temp2 = (((uint16_t)longitude / 10000) % 10) * 100 + (((uint16_t)longitude / 1000) % 10) * 10 + ((uint16_t)longitude / 100) % 10;
		longitude = longitude - (float)temp2 * 100;
		longitude = (float)temp2 + longitude / 60;
		printf ("longitude:%.3f\r\n",longitude);
	}
	else   // ��λ������Ϣ
	{
		// ǰ��λ��Ҫ�����ó������һ����
		temp2 = (((uint16_t)longitude / 1000) % 10) * 10 + ((uint16_t)longitude / 100) % 10;
		longitude = longitude - (float)temp2 * 100;
		longitude = (float)temp2 + longitude / 60;
		printf ("longitude:%.3f\r\n",longitude);
	}
}
