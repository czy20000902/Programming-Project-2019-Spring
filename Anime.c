#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
extern order rider[MaxPerson];
extern FILE fPtr;
extern int NumberOfRider;

void Anime()
{
	int type[36][36];
	int row;
	int col;
	int index;
	order *Anime_current;

	memset(type, 0, sizeof(int) * 36 * 36);//将所有位置的值设为0 
	for (index = 0; index < NumberOfRider; index++)//0:空, -1:骑手, 1:餐馆, 2:食客, 3:餐客
	{
		type[1 + 2 * rider[index].customer[0]][1 + 2 * rider[index].customer[1]] = -1;
		for (Anime_current = rider[index].Next; Anime_current; Anime_current = Anime_current->Next)
		{
			if (type[1 + 2 * Anime_current->restaurant[0]][1 + 2 * Anime_current->restaurant[1]] == 0)//若为空，则设为餐馆 
				type[1 + 2 * Anime_current->restaurant[0]][1 + 2 * Anime_current->restaurant[1]] = 1;
			else if (type[2 * Anime_current->restaurant[0]][1 + 2 * Anime_current->restaurant[1]] == 2)//若已有食客，则设为餐客 
				type[1 + 2 * Anime_current->restaurant[0]][1 + 2 * Anime_current->restaurant[1]] = 3;
			if (type[1 + 2 * Anime_current->customer[0]][1 + 2 * Anime_current->customer[1]] == 0)//若为空，则设为食客
				type[1 + 2 * Anime_current->customer[0]][1 + 2 * Anime_current->customer[1]] = 2;
			else if (type[1 + 2 * Anime_current->customer[0]][1 + 2 * Anime_current->customer[1]] == 1)//若已有餐馆，则设为餐客 
				type[1 + 2 * Anime_current->customer[0]][1 + 2 * Anime_current->customer[1]] = 3;
		}
	}
	for (col = 0; col < 36; col++)//row，col均以4为周期变化 
	{
		if (col % 4 == 0)
			for (row = 0; row < 35; row++)
			{
				if (row % 2 == 0)
					printf("-");
				if (row % 4 == 1)
					printf("----");
				if (row % 4 == 3)
					printf("    ");
			}
		if (col % 4 == 1)
			for (row = 0; row < 35; row++)
			{
				if (row % 2 == 0)
					printf("|");
				if (row % 4 == 1)
					switch (type[row][col])//按该位置的值进行输出 
					{
					case 0:printf("    "); break;
					case 1:printf("餐馆"); break;
					case 2:printf("食客"); break;
					case 3:printf("餐客"); break;
					}
				if (row % 4 == 3)
					switch (type[row][col])//按该位置的值进行输出 
					{
					case -1:printf("骑手"); break;
					case 0:printf("    "); break;
					}
			}
		if (col % 4 == 2)
			for (row = 0; row < 35; row++)
			{
				if (row % 2 == 0)
					printf("-");
				if (row % 4 == 1)
					printf("----");
				if (row % 4 == 3)
					printf("    ");
			}
		if (col % 4 == 3)
			for (row = 0; row < 35; row++)
			{
				if (row % 2 == 0)
					printf(" ");
				if (row % 4 == 1)
					switch (type[row][col])//按该位置的值进行输出 
					{
					case -1:printf("骑手"); break;
					case 0:printf("    "); break;
					}
				if (row % 4 == 3)
					switch (type[row][col])//按该位置的值进行输出 
					{
					case -1:printf("骑手"); break;
					case 0:printf("    "); break;
					}
			}
		printf("\n");
	}
}
