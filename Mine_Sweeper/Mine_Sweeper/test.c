#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define ROW 9
#define COL 9
#define Mine_Count 20

//定义两个全局变量的数组
char mine_map[ROW + 2][COL + 2];//雷阵
char show_map[ROW + 2][COL + 2];//用户看到的界面


//Game()模块逻辑框架
//定义两个二维数组，表示扫雷的地图
//一个表示用户看到的界面
//另一个表示雷的布阵

//扫雷地图大小是9*9,但是我们定义为11*11
//地图的有效范围是[1,ROW],[1,COL]
//对于mine_map,’0‘表示不是地雷，’1‘表示是地雷
//对于show_map,‘*’表示没有被翻开的方块；对于翻开的方块，用具体数字表示翻开了几块



void InitMap(char mine_map[ROW + 2][COL + 2], char show_map[ROW + 2][COL + 2])
{
	//对于mine_map，先把里面所有的方块都初始化为‘0’
	memset(mine_map, '0', (ROW + 2)*(COL + 2));
	//对于show_map，先把里面所有的方块都初始化为‘*’
	memset(show_map, '*', (ROW + 2)*(COL + 2));
	//随机布置雷阵,每布置一颗，mine_count--
	//具体方法->
	//1.用时间当成种子，每一次布雷先随机获取row和col的值
	//2.检测当前块是否是‘0’；
	//a)若是‘0’，则说明还没有布下雷，于是设置为‘1’
	//b)若是‘1’，则说明当前位置已经布过雷，所以得重新获取随机数

	int mine_count = Mine_Count;
	int row = 0;
	int col = 0;
	srand(time(0));
	while (mine_count > 0)
	{
		//随机数范围：[1,9]
		row = rand() % 9 + 1;
		col = rand() % 9 + 1;
		if (mine_map[row][col] == '0')
		{
			mine_map[row][col] = '1';
			mine_count--;
		}
	}
}


void Displaymap(char map[ROW + 2][COL + 2])
{
	//打印最上层的列标号
	printf("    ");
	for (int col = 1; col <= COL; col++)
	{
		printf("%d  ", col);
	}
	printf("\n");
	//打印上边框
	for (int col = 1; col <= COL; col++)
	{
		printf("----");
	}
	printf("\n");
	//打印扫雷的地图布阵
	for (int row = 1; row <= ROW; row++)
	{
		printf("%d|", row);
		for (int col = 1; col <= COL; col++)
		{
			printf("  %c", map[row][col]);
		}
		printf("\n");
	}
}


void UpdateShowmap(char show_map[ROW + 2][COL + 2], int row, int col)
{
	//统计当前方块周围雷的个数，并且把show_map中当前方块的值更新
	int mine_count = 0;
	//[row - 1][col - 1], [row - 1][col], [row][col+1]
	//[row][col - 1], [row][col + 1]
	//[row + 1][col - 1], [row + 1][col], [row + 1][col + 1]
	mine_count = (mine_map[row - 1][col - 1] - '0') + (mine_map[row - 1][col] - '0') + (mine_map[row - 1][col + 1] - '0')
		+ (mine_map[row][col - 1] - '0') + (mine_map[row][col + 1] - '0')
		+ (mine_map[row + 1][col - 1] - '0') + (mine_map[row + 1][col] - '0') + (mine_map[row + 1][col + 1] - '0');
	show_map[row][col] = mine_count + '0';


}

void Game()
{
	//1.初始化2个地图,布置雷阵
	//2.显示出用户看到的界面
	//3.用户输入坐标，检测是否合法;若不合法则提示重新输入
	//4.若合法：
	//判断用户是否踩雷，若踩雷，则所有雷都翻开，提示输，游戏结束
	//若没踩雷，翻开当前块，显示出四周雷的个数
	//判断游戏成功的条件：所有不是雷的方块都被翻开(Mine_count-notmine_count)
	//a)如果不是雷的方块全部被翻开，则打印盘，提示成功，游戏结束
	//b)如果没有全部被翻开，则统计当前方块周围雷的个数，然后打印盘

	InitMap(mine_map, show_map);
	Displaymap(show_map);
	//Displaymap(mine_map);//测试
	int not_mine_count = 0;
	while (1)
	{
		int row, col;
		printf("请输入坐标：");
		scanf("%d %d", &row, &col);
		if (row<1 || row>ROW || col<1 || col>COL)
		{
			printf("您输入的坐标超出边界范围，请重新输入\n");
			continue;
		}
		if (show_map[row][col] != '*')
		{
			printf("当前块已被翻开，请重新输入\n");
			continue;
		}
		if (mine_map[row][col] == '1')
		{
			printf("您踩到雷，游戏结束\n");
			Displaymap(mine_map);//打印雷盘
			break;
		}
		++not_mine_count;
		if (not_mine_count == ROW*COL - Mine_Count)
		{
			printf("恭喜你,扫雷成功\n");
			Displaymap(mine_map);
			break;
		}
		else
		{
			UpdateShowmap(show_map, row, col);
		}
		Displaymap(show_map);
		//Displaymap(mine_map);//测试	
	}
}



void Menu()
{
	printf("---------------------------\n");
	printf("    欢迎进入扫雷游戏       \n");
	printf("---------------------------\n");
	printf("      1.游戏开始           \n");
	printf("      0.退出游戏           \n");
	printf("---------------------------\n");
}




void Start()
{
	//整体框架
	//首先打印出一个菜单：1.游戏开始  0.退出游戏
	//让用户进行选择：
	//若选择1，则进入游戏；若选择0，则退出

	while (1)
	{
		Menu();
		int choice = 0;
		scanf("%d", &choice);
		if (choice == 0)
		{
			printf("退出游戏\n");
			break;
		}
		Game();
	}

}

int main()
{
	Start();//程序入口函数
	system("pause");
	return 0;
}