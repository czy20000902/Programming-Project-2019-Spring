#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
order rider[MaxPerson];
/*
	�������ֽṹ�����飬�Ӷ������ֵ���Ϣ���и�ֵ
	���У�customer[0],customer[1]�ֱ�������ֵ�λ������
	restaurant[0],restaurant[1]�ֱ�������ֵĴ�����
	Next����������ʾ���ֵĽӵ�
	delivering��ʾ���ֽӵ���״̬�������0����ʾû�й��͹ݣ�1��ʾ������ʳ��
	timingû��ʵ������
*/
order HeadOfOrders;
/*
	��ʾ�����Ķ��У���������һ���սڵ���Ϊͷ�ڵ�
	���У�serial������Ƕ�����
	customer[0],customer[1]��ʾʳ�͵�����
	restaurant[0],restaurant[1]��ʾ�͹ݵ�����
	fine�Ƿ���״̬�����Ϊ1��ʾ�Ѿ�����������Ҫ�ظ�����
	timing��ʾ�������ֵ�ʱ��
	Next�γɶ����Ķ���
*/
const int section9[9][2] =
{
	{2,3},{8,15},{14,3},{2,15},
	{8,9},{14,15},{2,9},{8,3},{14,9}
};//���������ֳ�9�����򣬽����ֵ�ָ��λ��ȷ����9����������
const int startlocation[2] = { 8,9 };
//�̶���ʼ��
int section25[25][2];//��ʱ���ܻ��ֳ�25�����򣬵�ʵ�ֵĿ��ܲ���
int money = 1000;
//��Ǯ��
int NumberOfRider = 0;
//����������
int time = 0;
//��ʱʹ��
int warning_rider = 0;
//�з��յ����ֺ�
int warning_time = -1;
//����ʱ�䣬������ÿ��������Ԥ��ʱ��
int warning_distance[MaxPerson];
//������룬�����ж��Ƿ���Ҫ�¹�Ӷ���֣��Ӷ��������ʱ��
FILE * fPtr = NULL;
int TotalOrder = 0;
//�ӵ���
int accomplished = 0;
//�����
int late = 0;
//�ٵ���
int AllOrders = 0;
//�ܵĶ�����
int condition[MaxPerson];
//condition�������ÿһ�������״̬��0����û���ڲ͹ݻ�ʳ�ͣ�1����ͣ�ڲ͹��Աߣ�2����ͣ��ʳ���Աߣ�3����ͣ�ڲͿ��Ա� 
int late_num = -1;
extern void Input();
extern void Output();
extern void Send();
extern void warning();
extern void distribute();
extern void Anime();
int main(int argc, char *argv[])
{
	money = 100;
	NumberOfRider = 3;
	int index;

	memset(condition, 0, sizeof(int) * NumberOfRider);//��ʼ��condition����Ϊ0
	for (index = 0; index < NumberOfRider; index++)
	{
		rider[index].Next = NULL;
		rider[index].customer[0] = startlocation[0];
		rider[index].customer[1] = startlocation[1];
		rider[index].restaurant[0] = section9[index][0];
		rider[index].restaurant[1] = section9[index][1];
	}//�������ֵĻ�����Ϣ
	Input();
	fPtr = fopen("one_3_output5.txt", "w");
	while (AllOrders > accomplished + late)
	{
		time++;
		warning();
		distribute();
		Send();
		system("cls");
		Anime();
		Output();
		Sleep(2000);
	}
	fclose(fPtr);
	system("pause");
	return 0;
}
