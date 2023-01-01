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

	memset(type, 0, sizeof(int) * 36 * 36);//������λ�õ�ֵ��Ϊ0 
	for (index = 0; index < NumberOfRider; index++)//0:��, -1:����, 1:�͹�, 2:ʳ��, 3:�Ϳ�
	{
		type[1 + 2 * rider[index].customer[0]][1 + 2 * rider[index].customer[1]] = -1;
		for (Anime_current = rider[index].Next; Anime_current; Anime_current = Anime_current->Next)
		{
			if (type[1 + 2 * Anime_current->restaurant[0]][1 + 2 * Anime_current->restaurant[1]] == 0)//��Ϊ�գ�����Ϊ�͹� 
				type[1 + 2 * Anime_current->restaurant[0]][1 + 2 * Anime_current->restaurant[1]] = 1;
			else if (type[2 * Anime_current->restaurant[0]][1 + 2 * Anime_current->restaurant[1]] == 2)//������ʳ�ͣ�����Ϊ�Ϳ� 
				type[1 + 2 * Anime_current->restaurant[0]][1 + 2 * Anime_current->restaurant[1]] = 3;
			if (type[1 + 2 * Anime_current->customer[0]][1 + 2 * Anime_current->customer[1]] == 0)//��Ϊ�գ�����Ϊʳ��
				type[1 + 2 * Anime_current->customer[0]][1 + 2 * Anime_current->customer[1]] = 2;
			else if (type[1 + 2 * Anime_current->customer[0]][1 + 2 * Anime_current->customer[1]] == 1)//�����в͹ݣ�����Ϊ�Ϳ� 
				type[1 + 2 * Anime_current->customer[0]][1 + 2 * Anime_current->customer[1]] = 3;
		}
	}
	for (col = 0; col < 36; col++)//row��col����4Ϊ���ڱ仯 
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
					switch (type[row][col])//����λ�õ�ֵ������� 
					{
					case 0:printf("    "); break;
					case 1:printf("�͹�"); break;
					case 2:printf("ʳ��"); break;
					case 3:printf("�Ϳ�"); break;
					}
				if (row % 4 == 3)
					switch (type[row][col])//����λ�õ�ֵ������� 
					{
					case -1:printf("����"); break;
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
					switch (type[row][col])//����λ�õ�ֵ������� 
					{
					case -1:printf("����"); break;
					case 0:printf("    "); break;
					}
				if (row % 4 == 3)
					switch (type[row][col])//����λ�õ�ֵ������� 
					{
					case -1:printf("����"); break;
					case 0:printf("    "); break;
					}
			}
		printf("\n");
	}
}
