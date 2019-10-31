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



//int g_score;


typedef struct Snack
{
	// 跟地图一样大的一个数组
	Position pos[MAP_MIDTH * MAP_HEIGHT];

	// 身子长度
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
	printf("是兄弟就来贪吃蛇大战\n");
	printf("w:上a:左s:下d:右\n");
	printf("madeby 胖虎\n");
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









//w 上
//S 下
//a左
//d右


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
	{	//处理键盘输入

		//检测是否有按键输入
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
	
		Sleep(100);//延时2

	}
}





void Score()
{
	system("cls");
	printf("GG\n");
	printf("分数:%d\n",g_score);
}

int main(int argc, char* argv[])
{
	initmap();//画地图
	InitSnack();
	Initfood();
	gameloop();//打印得分
	Score();//游戏主循环
	return 0;
}

