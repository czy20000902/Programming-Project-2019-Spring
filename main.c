#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
order rider[MaxPerson];
/*
	声明骑手结构体数组，从而将骑手的信息进行赋值
	其中，customer[0],customer[1]分别代表骑手的位置坐标
	restaurant[0],restaurant[1]分别代表骑手的待命点
	Next后面的链表表示骑手的接单
	delivering表示骑手接单的状态，如果是0，表示没有过餐馆，1表示正在送食客
	timing没有实际意义
*/
order HeadOfOrders;
/*
	表示订单的队列，其中设立一个空节点作为头节点
	其中，serial代表的是订单号
	customer[0],customer[1]表示食客的坐标
	restaurant[0],restaurant[1]表示餐馆的坐标
	fine是罚款状态，如果为1表示已经罚过，不需要重复罚款
	timing表示订单出现的时间
	Next形成订单的队列
*/
const int section9[9][2] =
{
	{2,3},{8,15},{14,3},{2,15},
	{8,9},{14,15},{2,9},{8,3},{14,9}
};//将地区划分成9个区域，将骑手的指定位置确定在9个基本点上
const int startlocation[2] = { 8,9 };
//固定起始点
int section25[25][2];//暂时可能划分成25个区域，但实现的可能不大
int money = 1000;
//总钱数
int NumberOfRider = 0;
//总骑手数量
int time = 0;
//计时使用
int warning_rider = 0;
//有风险的骑手号
int warning_time = -1;
//警戒时间，用于求每个订单的预期时间
int warning_distance[MaxPerson];
//警戒距离，用在判断是否需要新雇佣骑手，从而求出警戒时间
FILE * fPtr = NULL;
int TotalOrder = 0;
//接单数
int accomplished = 0;
//完成数
int late = 0;
//迟到数
int AllOrders = 0;
//总的订单数
int condition[MaxPerson];
//condition数组代表每一个数组的状态，0代表没有在餐馆或食客，1代表停在餐馆旁边，2代表停在食客旁边，3代表停在餐客旁边 
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

	memset(condition, 0, sizeof(int) * NumberOfRider);//初始化condition数组为0
	for (index = 0; index < NumberOfRider; index++)
	{
		rider[index].Next = NULL;
		rider[index].customer[0] = startlocation[0];
		rider[index].customer[1] = startlocation[1];
		rider[index].restaurant[0] = section9[index][0];
		rider[index].restaurant[1] = section9[index][1];
	}//输入骑手的基本信息
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
