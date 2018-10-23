#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define ROW 9
#define COL 9
#define Mine_Count 20

//��������ȫ�ֱ���������
char mine_map[ROW + 2][COL + 2];//����
char show_map[ROW + 2][COL + 2];//�û������Ľ���


//Game()ģ���߼����
//����������ά���飬��ʾɨ�׵ĵ�ͼ
//һ����ʾ�û������Ľ���
//��һ����ʾ�׵Ĳ���

//ɨ�׵�ͼ��С��9*9,�������Ƕ���Ϊ11*11
//��ͼ����Ч��Χ��[1,ROW],[1,COL]
//����mine_map,��0����ʾ���ǵ��ף���1����ʾ�ǵ���
//����show_map,��*����ʾû�б������ķ��飻���ڷ����ķ��飬�þ������ֱ�ʾ�����˼���



void InitMap(char mine_map[ROW + 2][COL + 2], char show_map[ROW + 2][COL + 2])
{
	//����mine_map���Ȱ��������еķ��鶼��ʼ��Ϊ��0��
	memset(mine_map, '0', (ROW + 2)*(COL + 2));
	//����show_map���Ȱ��������еķ��鶼��ʼ��Ϊ��*��
	memset(show_map, '*', (ROW + 2)*(COL + 2));
	//�����������,ÿ����һ�ţ�mine_count--
	//���巽��->
	//1.��ʱ�䵱�����ӣ�ÿһ�β����������ȡrow��col��ֵ
	//2.��⵱ǰ���Ƿ��ǡ�0����
	//a)���ǡ�0������˵����û�в����ף���������Ϊ��1��
	//b)���ǡ�1������˵����ǰλ���Ѿ������ף����Ե����»�ȡ�����

	int mine_count = Mine_Count;
	int row = 0;
	int col = 0;
	srand(time(0));
	while (mine_count > 0)
	{
		//�������Χ��[1,9]
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
	//��ӡ���ϲ���б��
	printf("    ");
	for (int col = 1; col <= COL; col++)
	{
		printf("%d  ", col);
	}
	printf("\n");
	//��ӡ�ϱ߿�
	for (int col = 1; col <= COL; col++)
	{
		printf("----");
	}
	printf("\n");
	//��ӡɨ�׵ĵ�ͼ����
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
	//ͳ�Ƶ�ǰ������Χ�׵ĸ��������Ұ�show_map�е�ǰ�����ֵ����
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
	//1.��ʼ��2����ͼ,��������
	//2.��ʾ���û������Ľ���
	//3.�û��������꣬����Ƿ�Ϸ�;�����Ϸ�����ʾ��������
	//4.���Ϸ���
	//�ж��û��Ƿ���ף������ף��������׶���������ʾ�䣬��Ϸ����
	//��û���ף�������ǰ�飬��ʾ�������׵ĸ���
	//�ж���Ϸ�ɹ������������в����׵ķ��鶼������(Mine_count-notmine_count)
	//a)��������׵ķ���ȫ�������������ӡ�̣���ʾ�ɹ�����Ϸ����
	//b)���û��ȫ������������ͳ�Ƶ�ǰ������Χ�׵ĸ�����Ȼ���ӡ��

	InitMap(mine_map, show_map);
	Displaymap(show_map);
	//Displaymap(mine_map);//����
	int not_mine_count = 0;
	while (1)
	{
		int row, col;
		printf("���������꣺");
		scanf("%d %d", &row, &col);
		if (row<1 || row>ROW || col<1 || col>COL)
		{
			printf("����������곬���߽緶Χ������������\n");
			continue;
		}
		if (show_map[row][col] != '*')
		{
			printf("��ǰ���ѱ�����������������\n");
			continue;
		}
		if (mine_map[row][col] == '1')
		{
			printf("���ȵ��ף���Ϸ����\n");
			Displaymap(mine_map);//��ӡ����
			break;
		}
		++not_mine_count;
		if (not_mine_count == ROW*COL - Mine_Count)
		{
			printf("��ϲ��,ɨ�׳ɹ�\n");
			Displaymap(mine_map);
			break;
		}
		else
		{
			UpdateShowmap(show_map, row, col);
		}
		Displaymap(show_map);
		//Displaymap(mine_map);//����	
	}
}



void Menu()
{
	printf("---------------------------\n");
	printf("    ��ӭ����ɨ����Ϸ       \n");
	printf("---------------------------\n");
	printf("      1.��Ϸ��ʼ           \n");
	printf("      0.�˳���Ϸ           \n");
	printf("---------------------------\n");
}




void Start()
{
	//������
	//���ȴ�ӡ��һ���˵���1.��Ϸ��ʼ  0.�˳���Ϸ
	//���û�����ѡ��
	//��ѡ��1���������Ϸ����ѡ��0�����˳�

	while (1)
	{
		Menu();
		int choice = 0;
		scanf("%d", &choice);
		if (choice == 0)
		{
			printf("�˳���Ϸ\n");
			break;
		}
		Game();
	}

}

int main()
{
	Start();//������ں���
	system("pause");
	return 0;
}