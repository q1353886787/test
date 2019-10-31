// snack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
//1.̰���������ƶ�
//2.̰���߳�ʳ�ﳤ��
//3.̰����ײǽ���Ե��Լ���gg
//4.��Ϸ��������ӡ����
#define MAP_MIDTH 60
#define MAP_HEIGHT 20


typedef struct Postin
{
	int x;
	int	y;

}Position;



//int g_score;


typedef struct Snack
{
	// ����ͼһ�����һ������
	Position pos[MAP_MIDTH * MAP_HEIGHT];

	// ���ӳ���
	int size;
} Snack;
Snack g_snack;

int g_score;


Position g_food;


void initmap()
{
	int i;
	int j;

	for( i = 0;i <= MAP_HEIGHT;i++)
	{
		for( j = 0;j <= MAP_MIDTH;j++)
		{
		
			if(j == MAP_MIDTH)
			{
			printf("|\n");
			}
			else if( i == MAP_HEIGHT)
			{
					printf("-");
			}
			else
			{
				printf(" ");
			}
		}

	}
	printf("���ֵܾ���̰���ߴ�ս\n");
	printf("w:��a:��s:��d:��\n");
	printf("madeby �ֻ�\n");
}


void DrawChar (int x,int y,char c)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	putchar(c);
}


void DrawSnack()
{
	int i;

	for (i = 0; i < g_snack.size; i++)
	{
		// head
		if (i == 0)
		{
			DrawChar(g_snack.pos[i].x, g_snack.pos[i].y, '*');
		}
		else
		{
			DrawChar(g_snack.pos[i].x, g_snack.pos[i].y, '#');
		}
	}
}



void DrawFood()
{
	DrawChar(g_food.x,g_food.y,'#');
}


void InitSnack()
{
	g_snack.size = 2;
	g_snack.pos[0].x = MAP_MIDTH / 2;
	g_snack.pos[0].y = MAP_HEIGHT / 2;

	g_snack.pos[1].x = MAP_MIDTH / 2 - 1;
	g_snack.pos[1].y = MAP_HEIGHT / 2;
}


void Initfood()
{
	srand((unsigned int)time(NULL));
	g_food.x = rand() % MAP_MIDTH;
	g_food.y = rand() % MAP_HEIGHT;
}









//w ��
//S ��
//a��
//d��


void snackmove(int key)
{
	int delta_x = 0;
	int delta_y = 0;
	int i;

	DrawChar(g_snack.pos[g_snack.size-1].x,g_snack.pos[g_snack.size-1].y,'  ');


	for ( i = g_snack.size - 1; i > 0; i--)
	{
		g_snack.pos[i].x = g_snack.pos[i-1].x;
		g_snack.pos[i].y = g_snack.pos[i-1].y;
	}



	switch (key)
	{
	case 'w':
	case 'W':
		delta_x = 0;
		delta_y = -1;
		break;
	case 'A':
	case 'a':
		delta_x = -1;
		delta_y = 0;
		break;
	case 'd':
	case 'D':
		delta_x = 1;
		delta_y = 0;
		break;
	case 's':
	case 'S':
		delta_x = 0;
		delta_y = 1;
		break;
	default:
		delta_x = 0;
		delta_y = 0;
		break;
	}

	g_snack.pos[0].x += delta_x;
	g_snack.pos[0].y += delta_y;



}

int hitwall()
{
	if(g_snack.pos[0].x < 0 ||
		g_snack.pos[0].y < 0 ||
		g_snack.pos[0].x > MAP_MIDTH ||
		g_snack.pos[0].y > MAP_HEIGHT )
	{
		return -1;
	}
	return 0;
}


int hitself()
{
	int i;
	for(i = 1;i < g_snack.size;i++)
	{
		if(g_snack.pos[0].x == g_snack.pos[i].x &&
			g_snack.pos[0].y == g_snack.pos[i].y)
		{
			return -1;
		}
			
	}
	return 0;
}




void UpdateScreen()
{
	DrawSnack();
}

void eatfood()
{
	if (g_snack.pos[0].x == g_food.x && 
		g_snack.pos[0].y == g_food.y)
	{
		Initfood();
		g_snack.pos[g_snack.size - 1].x = g_snack.pos[g_snack.size - 1].x;
		g_snack.pos[g_snack.size - 1].y = g_snack.pos[g_snack.size - 1].y;
		 
		g_snack.size++;
		g_score += 10;
	}
}


void gameloop()
{
	int key = 0;
	while(1)
	{	//�����������

		//����Ƿ��а�������
		if(_kbhit())
		{
			key = _getch();
			
		}
		snackmove(key);
		if (key == 'q' || key == 'Q' )
		{
			return;
		}

		//printf("a\n");
		//	eatfood();
		if (hitwall() < 0)
		{
			return;
		}
	/*	if(hitself() < 0)
		{
			return;
		}*/
		UpdateScreen();
		eatfood();

		DrawFood();
	
		Sleep(100);//��ʱ2

	}
}





void Score()
{
	system("cls");
	printf("GG\n");
	printf("����:%d\n",g_score);
}

int main(int argc, char* argv[])
{
	initmap();//����ͼ
	InitSnack();
	Initfood();
	gameloop();//��ӡ�÷�
	Score();//��Ϸ��ѭ��
	return 0;
}

