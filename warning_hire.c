#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

extern order rider[MaxPerson];
extern const int section9[9][2];
extern const int startlocation[2];
extern int section25[25][2];
extern int money;
extern int NumberOfRider;
extern int warning_time;
extern int warning_distance[MaxPerson];

void warning()
{
	int i, temp_time;//i�Ǽ�����λ�� 
	int	number = NumberOfRider;
	order *warning_pre, *warning_current;
	order *new_current;//Ϊ�˿����¹�Ӷ�����ֵ�״�� 
	temp_time = 0;
	warning_time = -1;
	for (i = 0; i < number; i++)
	{
		warning_distance[i] = 0;
		warning_pre = &rider[i];
		warning_current = rider[i].Next;
		while (warning_current)
		{
			if (warning_current->delivering == 0)
			{
				temp_time += abs(warning_current->restaurant[0] - warning_pre->customer[0]);
				temp_time += abs(warning_current->restaurant[1] - warning_pre->customer[1]);

				temp_time++;
				//�����Ǽ�������������ֵ��͹ݾ��� 
				temp_time += abs(warning_current->customer[0] - warning_current->restaurant[0]);
				temp_time += abs(warning_current->customer[1] - warning_current->restaurant[1]);
				//�����Ǽ�����ǲ͹ݵ�ʳ�͵ľ���
				temp_time = temp_time / 2;
			}
			else
			{
				temp_time += abs(warning_current->customer[0] - warning_pre->customer[0]);
				temp_time += abs(warning_current->customer[1] - warning_pre->customer[1]);
				temp_time = temp_time / 2 + 1;
				//���ϼ���������ֵ�ʳ�͵ľ��� 
			}
			warning_current->Expectedtime = warning_pre->Expectedtime + temp_time;
			//���Ԥ��ʱ��ϳ������Կ��ǹ�Ӷ�µ����� 
			if (warning_current->Expectedtime >= 27 && money >= 350)//��������
			{
				hire();
				rider[NumberOfRider - 1].Next = warning_current;
				warning_pre->Next = NULL;
				new_current = rider[NumberOfRider - 1].Next;
				new_current->Next = NULL;
			}
			warning_pre = warning_current;
			warning_current = warning_current->Next;
		}
	}
}

void hire()
{
	if (money >= 350)//�������� 
	{
		NumberOfRider++;
		rider[NumberOfRider - 1].Next = (order *)malloc(sizeof(order));
		rider[NumberOfRider - 1].customer[0] = 8;
		rider[NumberOfRider - 1].customer[1] = 9;
		money -= PRICE;
		if (NumberOfRider <= 9)
		{
			rider[NumberOfRider - 1].restaurant[0] = section9[NumberOfRider - 1][0];
			rider[NumberOfRider - 1].restaurant[1] = section9[NumberOfRider - 1][1];
		}
		else if (NumberOfRider <= 25)//�����ò��� 
		{
			rider[NumberOfRider - 1].restaurant[0] = section25[NumberOfRider - 1][0];
			rider[NumberOfRider - 1].restaurant[1] = section25[NumberOfRider - 1][1];
		}
	}
}
