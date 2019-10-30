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



int g_score;


typedef struct Snack
{
	// ����ͼһ�����һ������
	Position pos[MAP_MIDTH * MAP_HEIGHT];

	// ���ӳ���
	int size;
} Snack;
Snack g_snack;


Position g_food;

void DrawChar (int x,int y,char ch)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	putchar(ch);
}


void initmap()
{
	for(int i = 0;i <= MAP_HEIGHT;i++)
	{
		for(int j = 0;j <= MAP_MIDTH;j++)
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
}

void DrawFood()
{
	DrawChar(g_food.x,g_food.y,'#');
}

void Initfood()
{
	srand((unsigned int)time(NULL));
	g_food.x = rand() % MAP_MIDTH;
	g_food.y = rand() % MAP_HEIGHT;
}






void InitSnack()
{
	g_snack.size = 3;
	g_snack.pos[0].x = MAP_MIDTH / 2;
	g_snack.pos[0].y = MAP_HEIGHT / 2;

	g_snack.pos[1].x = MAP_MIDTH / 2 - 1;
	g_snack.pos[1].y = MAP_HEIGHT / 2;

	g_snack.pos[1].x = MAP_MIDTH / 2 - 2;
	g_snack.pos[1].y = MAP_HEIGHT / 2;
}

void DrawSnack()
{
	

	for (int i = 0; i < g_snack.size; i++)
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


void UpdateScreen()
{
	DrawSnack();
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
		if (key == 'q' || key == 'Q' )
		{
			return;
		}

		//printf("a\n");

		UpdateScreen();
		Sleep(100);//��ʱ2

	}
}




void init()
{	
	initmap();
	InitSnack();
	DrawSnack();
}



void Score()
{
}

int main(int argc, char* argv[])
{
	
	init();//����ͼ
	Score();//��Ϸ��ѭ��
	gameloop();//��ӡ�÷�
	initmap();
	DrawFood();
	Initfood();
	return 0;
}

