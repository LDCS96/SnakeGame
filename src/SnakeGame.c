#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "conio.h"
#include "Windows.h"

struct SnakeNode
{
	int x;
	int y;
	SnakeNode* next_sn;
};

struct SnakeHeadAndTail
{
	SnakeNode* snh;
	SnakeNode* snt;
	char direction;
};

/*初始化一条四个单位长的蛇*/
SnakeHeadAndTail init_snake()
{
	SnakeNode* snp = (SnakeNode*)malloc(sizeof(SnakeNode));
	SnakeNode* snh = snp;
	int i;
	for (i = 0; i < 4; i++)
	{
		snp->x = 9;
		snp->y = 8 + i;
		SnakeNode* snq = (SnakeNode*)malloc(sizeof(SnakeNode));
		if (i == 3)
		{
			snp->next_sn = NULL;
		}
		else
		{
			snp->next_sn = snq;
			snp = snq;
		}
	}
	SnakeNode* snt = snp;
	SnakeHeadAndTail shnt;
	shnt.snh = snh;
	shnt.snt = snt;
	shnt.direction = 'l';
	return shnt;
}

SnakeNode generate_point()
{
	srand(time(0));
	int x = rand() % 19;
	int y = rand() % 19;
	SnakeNode* snp = (SnakeNode*)malloc(sizeof(SnakeNode));
	snp->x = x;
	snp->y = y;
	return *snp;
}

/*检测新生成的豆子是否在蛇的身上*/
bool test_point(const SnakeHeadAndTail& shnt, const SnakeNode& point)
{
	SnakeNode* snp = shnt.snh;
	while (snp)
	{
		if (snp->x == point.x && snp->y == point.y)
		{
			return false;
		}
		else
		{
			snp = snp->next_sn;
		}
	}
	return true;
}

/*这个函数有三个功能：*/
/*检查蛇头是否撞墙*/
/*检查蛇头是否咬到自己身体*/
/*检查蛇头前方是否有豆子*/
int test_collision(const SnakeHeadAndTail& shnt, const SnakeNode& point)
{
	SnakeNode* head = shnt.snh;
	int x = head->x;
	int y = head->y;
	if (x < 0 || y < 0 || x>19 || y>19)
	{
		return 0;
	}
	SnakeNode* p = head->next_sn;
	while (p)
	{
		int next_x = p->x;
		int next_y = p->y;
		if (next_x == x && next_y == y)
		{
			return 0;
		}
		p = p->next_sn;
	}
	char direction = shnt.direction;
	if (direction == 'l' && head->y - 1 == point.y && head->x == point.x)
	{
		return 2;
	}
	if (direction == 'r' && head->y + 1 == point.y && head->x == point.x)
	{
		return 2;
	}
	if (direction == 'u' && head->x - 1 == point.x && head->y == point.y)
	{
		return 2;
	}
	if (direction == 'd' && head->x + 1 == point.x && head->y == point.y)
	{
		return 2;
	}
	return 1;
}

int move_elongate_snake(SnakeHeadAndTail* shnt, const SnakeNode& point)
{
	/*如果头顶上有豆子，新头就是豆子，其他不变*/
	if (test_collision(*shnt, point) == 2)
	{
		SnakeNode* snp = (SnakeNode*)malloc(sizeof(SnakeNode));
		snp->x = point.x;
		snp->y = point.y;
		snp->next_sn = shnt->snh;
		shnt->snh = snp;
		return 2;
	}
	int kb_input = 0;
	int useless = 0;
	time_t start_time = time(0);
	while (1)
	{
		/*等一定的时间，这段时间内没有输出就跳出；这个时间可以调整*/
		if (_kbhit())
		{
			useless = _getch();
			kb_input = _getch();
			break;
		}
		time_t end_time = time(0);
		double diff_time = difftime(end_time, start_time);
		if (diff_time >= 1)
		{
			break;
		}
	}
	/*按上下方向键的变化*/
	if (kb_input == 72 || kb_input == 80)
	{
		if (shnt->direction == 'u' || shnt->direction == 'd');
		else
		{
			SnakeNode* snp = (SnakeNode*)malloc(sizeof(SnakeNode));
			snp->y = shnt->snh->y;
			if (kb_input == 72)
			{
				shnt->direction = 'u';
				snp->x = shnt->snh->x - 1;
			}
			else
			{
				shnt->direction = 'd';
				snp->x = shnt->snh->x + 1;
			}
			snp->next_sn = shnt->snh;
			shnt->snh = snp;
			SnakeNode* p = shnt->snh;
			while (p->next_sn->next_sn)
			{
				p = p->next_sn;
			}
			p->next_sn = NULL;
			p = shnt->snh;
		}
	}
	/*按左右方向键的变化*/
	else if (kb_input == 75 || kb_input == 77)
	{
		if (shnt->direction == 'l' || shnt->direction == 'r');
		else
		{
			SnakeNode* snp = (SnakeNode*)malloc(sizeof(SnakeNode));
			snp->x = shnt->snh->x;
			if (kb_input == 75)
			{
				shnt->direction = 'l';
				snp->y = shnt->snh->y - 1;
			}
			else
			{
				shnt->direction = 'r';
				snp->y = shnt->snh->y + 1;
			}
			snp->next_sn = shnt->snh;
			shnt->snh = snp;
			SnakeNode* p = shnt->snh;
			while (p->next_sn->next_sn)
			{
				p = p->next_sn;
			}
			p->next_sn = NULL;
			p = shnt->snh;
		}
	}
	else
	{
		if (shnt->direction == 'l')
		{
			SnakeNode* snp = (SnakeNode*)malloc(sizeof(SnakeNode));
			snp->x = shnt->snh->x;
			snp->y = shnt->snh->y - 1;
			snp->next_sn = shnt->snh;
			shnt->snh = snp;
		}
		else if (shnt->direction == 'r')
		{
			SnakeNode* snp = (SnakeNode*)malloc(sizeof(SnakeNode));
			snp->x = shnt->snh->x;
			snp->y = shnt->snh->y + 1;
			snp->next_sn = shnt->snh;
			shnt->snh = snp;
		}
		else if (shnt->direction == 'u')
		{
			SnakeNode* snp = (SnakeNode*)malloc(sizeof(SnakeNode));
			snp->y = shnt->snh->y;
			snp->x = shnt->snh->x - 1;
			snp->next_sn = shnt->snh;
			shnt->snh = snp;
		}
		else
		{
			SnakeNode* snp = (SnakeNode*)malloc(sizeof(SnakeNode));
			snp->y = shnt->snh->y;
			snp->x = shnt->snh->x + 1;
			snp->next_sn = shnt->snh;
			shnt->snh = snp;
		}
		SnakeNode* p = shnt->snh;
		while (p->next_sn->next_sn)
		{
			p = p->next_sn;
		}
		p->next_sn = NULL;
		shnt->snt = p;
	}
	return 1;
}

/*这个函数的功能是打印蛇到控制台*/
void show_snake(const SnakeHeadAndTail& shnt, const SnakeNode& point)
{
	system("cls");
	int i, j;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			SnakeNode* p = shnt.snh;
			while (p)
			{
				if (p->x == i && p->y == j && p == shnt.snh)
				{
					printf("H ");
					break;
				}
				else if (p->x == i && p->y == j)
				{
					printf("S ");
					break;
				}
				else
				{
					p = p->next_sn;
				}
			}
			if (!p)
			{
				if (point.x == i && point.y == j)
				{
					printf("O ");
				}
				else
				{
					printf("- ");
				}
			}
		}
		printf("\n");
	}
}

int main()
{
	SnakeHeadAndTail shnt = init_snake();
	/*printf("蛇地址为%p\n", &shnt);*/
	/*printf("蛇头地址：%p\n", shnt.snh);*/
	/*printf("蛇尾地址：%p\n", shnt.snt);*/
	/*printf("这条蛇的方向为：%c\n", shnt.direction);*/
	while (1)
	{
		SnakeNode point = generate_point();
		/*这个while检查新生成的豆子是否在蛇身上，调用上面的test_point()函数*/
		while (1)
		{
			if (!test_point(shnt, point))
			{
				point = generate_point();
			}
			else
			{
				break;
			}
		}
		/*这个while用test_collision检查蛇头的情况*/
		while (test_collision(shnt, point))
		{
			show_snake(shnt, point);
			if (move_elongate_snake(&shnt, point) == 2)
			{
				break;
			}
		}
		if (!test_collision(shnt, point))
		{
			break;
		}
		printf("游戏结束\n");
	}
	return 0;
}











