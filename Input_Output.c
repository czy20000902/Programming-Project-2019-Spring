//����A437-3 2019/6/5 18:06:47
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
extern order rider[MaxPerson];
extern order HeadOfOrders;
extern const int section9[9][2];
extern const int startlocation[2];
extern int section25[25][2];
extern int money;
extern int NumberOfRider;
extern int time;
extern FILE * fPtr;
extern int TotalOrder;
extern int accomplished;
extern int late;
extern int AllOrders;
extern int condition[MaxPerson];
extern int late_num;
void Input()
{
	order * Input_currentPtr = NULL;
	order * Input_prePtr = &HeadOfOrders;

	fPtr = fopen("sales.txt", "r");
	//���������������γɶ��� 
	Input_currentPtr = (order *)malloc(sizeof(order));
	while (!feof(fPtr))
	{
		fscanf(fPtr, "%d %d %d %d %d %d\n",
			&Input_currentPtr->serial,
			&Input_currentPtr->timing,
			&Input_currentPtr->restaurant[0],
			&Input_currentPtr->restaurant[1],
			&Input_currentPtr->customer[0],
			&Input_currentPtr->customer[1]);
		Input_currentPtr->Next = NULL;
		Input_currentPtr->Expectedtime = 0;
		Input_currentPtr->delivering = 0;
		Input_prePtr->Next = Input_currentPtr;
		Input_prePtr = Input_currentPtr;
		Input_currentPtr = (order *)malloc(sizeof(order));
		AllOrders++;
	}
}

void Output()
{
	int index = 0;
	order * temp;

	fprintf(fPtr, "ʱ�䣺%d\n", time);
	fprintf(fPtr, "Ǯ��%d\n", money);
	fprintf(fPtr, "�ӵ�����%d\n", TotalOrder);
	fprintf(fPtr, "�������%d��", accomplished);
	fprintf(fPtr, "�ᵥ��");
	for (index = 0; index < NumberOfRider; index++)
	{
		if (condition[index] == 2 || condition[index] == 3)
			fprintf(fPtr, "%d", rider[index].Next->serial);
	}
	fprintf(fPtr, "��");
	fprintf(fPtr, "\n");
	fprintf(fPtr, "��ʱ����%d��", late);
	fprintf(fPtr, "������");
	if (late_num != -1)
		fprintf(fPtr, "%d��", late_num);
	else 
		fprintf(fPtr, "��");
	fprintf(fPtr, "\n");
	for (index = 0; index < NumberOfRider; index++)
	{
		fprintf(fPtr, "����%dλ�ã�%d��%d��",
			index, rider[index].customer[0], rider[index].customer[1]);
		fprintf(fPtr, "ͣ����");
		if (condition[index] == 0)
			fprintf(fPtr, "��\n");
		else if (condition[index] == 1)
			fprintf(fPtr, "�͹� %d %d��\n", rider[index].Next->restaurant[0], rider[index].Next->restaurant[1]);
		else if (condition[index] == 2)
			fprintf(fPtr, "ʳ�� %d %d��\n", rider[index].Next->customer[0], rider[index].Next->customer[1]);
		else if (condition[index] == 3)
			fprintf(fPtr, "�Ϳ� %d %d��\n", rider[index].Next->customer[0], rider[index].Next->customer[1]);
	}
	if (money < 0)
	{
		fprintf(fPtr, "�Ѹ�ծ������\n");
		fclose(fPtr);
	}
	fprintf(fPtr, "\n");

	//����������������и�ʽ 
	printf("ʱ�䣺%d\n", time);
	printf("Ǯ����%d\n", money);
	printf("�ӵ�����%d\n", TotalOrder);
	printf("�������%d��", accomplished);
	printf("�ᵥ��");
	for (index = 0; index < NumberOfRider; index++)
	{
		if (condition[index] == 2 || condition[index] == 3)
			printf("%d��", rider[index].Next->serial);
	}
	printf("\n");
	printf("��ʱ����%d��", late);
	printf("������");
	if (late_num != -1)
		printf("%d��", late_num);
	printf("\n");
	for (index = 0; index < NumberOfRider; index++)
	{
		printf("����%d��λ�ã�%d��%d��",
			index, rider[index].customer[0], rider[index].customer[1]);
		printf("ͣ����");
		if (condition[index] == 0)
			printf("\n");
		else if (condition[index] == 1)
		{
			printf("�͹� %d %d��\n", rider[index].Next->restaurant[0], rider[index].Next->restaurant[1]);
			condition[index] = 0;
		}
		else if (condition[index] == 2)
		{
			printf("ʳ�� %d %d��\n", rider[index].Next->customer[0], rider[index].Next->customer[1]);
			temp = rider[index].Next;
			rider[index].Next = rider[index].Next->Next;
			free(temp);
			temp = NULL;
			condition[index] = 0;
		}
		else if (condition[index] == 3)
		{
			printf("�Ϳ� %d %d��\n", rider[index].Next->customer[0], rider[index].Next->customer[1]);
			temp = rider[index].Next;
			rider[index].Next = rider[index].Next->Next;
			free(temp);
			temp = NULL;
			condition[index] = 0;
		}
	}
	if (money < 0)
	{
		printf("�Ѹ�ծ������\n");
		system("pause");
		exit(1);//�����ծ����Ҫǿ����ֹ����
	}
	late_num = -1;
}

