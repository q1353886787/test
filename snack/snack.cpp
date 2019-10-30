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
//1.贪吃蛇上下移动
//2.贪吃蛇吃食物长大
//3.贪吃蛇撞墙，吃到自己，gg
//4.游戏结束，打印分数
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
	// 跟地图一样大的一个数组
	Position pos[MAP_MIDTH * MAP_HEIGHT];

	// 身子长度
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
	{	//处理键盘输入

		//检测是否有按键输入
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
		Sleep(100);//延时2

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
	
	init();//画地图
	Score();//游戏主循环
	gameloop();//打印得分
	initmap();
	DrawFood();
	Initfood();
	return 0;
}

