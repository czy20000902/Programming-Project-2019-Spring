#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
extern order rider[MaxPerson];
extern order HeadOfOrders;
extern int money;
extern int NumberOfRider;
extern int time;
extern int TotalOrder;
extern int accomplished;
extern int late;
extern int condition[MaxPerson];
extern void GetToLocation(int index);
extern int late_num;

void Send()
{
	int index;

	order *accomplishing = NULL;
	for (index = 0; index < NumberOfRider; index++)
		if (rider[index].Next == NULL)
			GetToLocation(index);
	for (index = 0; index < NumberOfRider; index++)
	{
		if (rider[index].Next == NULL)
			continue;
		GetToLocation(index);
		GetToLocation(index);
		if (abs(rider[index].customer[0] - rider[index].Next->restaurant[0]) + abs(rider[index].customer[1] - rider[index].Next->restaurant[1]) < 2)
		{
			rider[index].Next->delivering = 1;
			condition[index] = 1;
		}
		if ((abs(rider[index].customer[0] - rider[index].Next->customer[0]) + abs(rider[index].customer[1] - rider[index].Next->customer[1]) < 2)
			&& rider[index].Next->delivering == 1)
		{
			accomplishing = rider[index].Next;
			if (accomplishing->timing + MAXTIME >= time)
			{
				accomplished++;
				money += PROFIT;
				condition[index] = 2;
			}
			else
			{
				printf("骑手%d已经超时完成从 (%d,%d) 到 (%d,%d)的订单.\n"
					, index, accomplishing->restaurant[0], accomplishing->restaurant[1], accomplishing->customer[0], accomplishing->customer[1]);
				condition[index] = 2;
				late ++;
				money -= FINE;
				late_num = accomplishing->serial;
			}
			if (rider[index].Next->customer[0] == rider[index].Next->restaurant[0] && rider[index].Next->customer[1] == rider[index].Next->restaurant[1])
				condition[index] = 3;
			rider[index].Next->delivering = 0;
		}
	}

}

void distribute()
{
	order *distribute_pre, *distribute_current;
	order *distribute_rider;
	int index;
	int chosen;//决定将单子派给哪位骑手
	int distance[1024];
	int shortest;
	bool IsDistributed = 0;//判断订单是否被配送

	distribute_pre = &HeadOfOrders;//将所有的订单集中在一起，根据条件进行筛选
	for (distribute_current = HeadOfOrders.Next; distribute_current; IsDistributed = 0)
	{
		if (distribute_current->timing > time)
			break;
		for (index = 0; index < NumberOfRider; index++)
		{
			distance[index] = 0;
			distribute_rider = &rider[index];
			while (distribute_rider->Next)
				distribute_rider = distribute_rider->Next;
			distance[index] += abs(distribute_rider->customer[0] - distribute_current->restaurant[0]);
			distance[index] += abs(distribute_rider->customer[1] - distribute_current->restaurant[1]);
			distance[index] += distribute_rider->Expectedtime;
		}
		chosen = 0;
		shortest = distance[0];
		for (index = 0; index < NumberOfRider; index++)
			if (distance[index] < shortest)
			{
				shortest = distance[index];
				chosen = index;
			}
		distribute_rider = &rider[chosen];
		while (distribute_rider->Next)
			distribute_rider = distribute_rider->Next;
		distribute_rider->Next = distribute_current;
		distribute_pre->Next = distribute_current->Next;
		distribute_current->Next = NULL;
		distribute_current = distribute_pre->Next;
		TotalOrder++;
	}
	//考虑所有订单的预期时间，选择预期时间最少的骑手完成，从而时间尽量减少
}


