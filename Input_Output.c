//付笛A437-3 2019/6/5 18:06:47
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
	//构建订单的链表，形成队列 
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

	fprintf(fPtr, "时间：%d\n", time);
	fprintf(fPtr, "钱：%d\n", money);
	fprintf(fPtr, "接单数：%d\n", TotalOrder);
	fprintf(fPtr, "完成数：%d；", accomplished);
	fprintf(fPtr, "结单：");
	for (index = 0; index < NumberOfRider; index++)
	{
		if (condition[index] == 2 || condition[index] == 3)
			fprintf(fPtr, "%d", rider[index].Next->serial);
	}
	fprintf(fPtr, "；");
	fprintf(fPtr, "\n");
	fprintf(fPtr, "超时数：%d；", late);
	fprintf(fPtr, "罚单：");
	if (late_num != -1)
		fprintf(fPtr, "%d；", late_num);
	else 
		fprintf(fPtr, "；");
	fprintf(fPtr, "\n");
	for (index = 0; index < NumberOfRider; index++)
	{
		fprintf(fPtr, "骑手%d位置：%d，%d；",
			index, rider[index].customer[0], rider[index].customer[1]);
		fprintf(fPtr, "停靠：");
		if (condition[index] == 0)
			fprintf(fPtr, "；\n");
		else if (condition[index] == 1)
			fprintf(fPtr, "餐馆 %d %d；\n", rider[index].Next->restaurant[0], rider[index].Next->restaurant[1]);
		else if (condition[index] == 2)
			fprintf(fPtr, "食客 %d %d；\n", rider[index].Next->customer[0], rider[index].Next->customer[1]);
		else if (condition[index] == 3)
			fprintf(fPtr, "餐客 %d %d；\n", rider[index].Next->customer[0], rider[index].Next->customer[1]);
	}
	if (money < 0)
	{
		fprintf(fPtr, "已负债，结束\n");
		fclose(fPtr);
	}
	fprintf(fPtr, "\n");

	//以下输出的是命令行格式 
	printf("时间：%d\n", time);
	printf("钱数：%d\n", money);
	printf("接单数：%d\n", TotalOrder);
	printf("完成数：%d；", accomplished);
	printf("结单：");
	for (index = 0; index < NumberOfRider; index++)
	{
		if (condition[index] == 2 || condition[index] == 3)
			printf("%d；", rider[index].Next->serial);
	}
	printf("\n");
	printf("超时数：%d；", late);
	printf("罚单：");
	if (late_num != -1)
		printf("%d；", late_num);
	printf("\n");
	for (index = 0; index < NumberOfRider; index++)
	{
		printf("骑手%d的位置：%d，%d；",
			index, rider[index].customer[0], rider[index].customer[1]);
		printf("停靠：");
		if (condition[index] == 0)
			printf("\n");
		else if (condition[index] == 1)
		{
			printf("餐馆 %d %d；\n", rider[index].Next->restaurant[0], rider[index].Next->restaurant[1]);
			condition[index] = 0;
		}
		else if (condition[index] == 2)
		{
			printf("食客 %d %d；\n", rider[index].Next->customer[0], rider[index].Next->customer[1]);
			temp = rider[index].Next;
			rider[index].Next = rider[index].Next->Next;
			free(temp);
			temp = NULL;
			condition[index] = 0;
		}
		else if (condition[index] == 3)
		{
			printf("餐客 %d %d；\n", rider[index].Next->customer[0], rider[index].Next->customer[1]);
			temp = rider[index].Next;
			rider[index].Next = rider[index].Next->Next;
			free(temp);
			temp = NULL;
			condition[index] = 0;
		}
	}
	if (money < 0)
	{
		printf("已负债，结束\n");
		system("pause");
		exit(1);//如果负债，需要强行终止程序
	}
	late_num = -1;
}

