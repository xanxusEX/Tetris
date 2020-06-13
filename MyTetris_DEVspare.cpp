#include <windows.h>
#include <conio.h>
#include <time.h>
#include <cstdlib>
#include <cstdio>
#include <iostream> 
#include <stdio.h>
#include <stdarg.h>
#include <string> 
#include <Mmsystem.h>
#pragma comment(lib,"winmm.lib")
//#include "resource.h";
using namespace std;

#define W_SINGLE 20
#define H_SINGLE 20
#define F_X0 4
#define F_Y0 4
#define F_X1 4
#define F_Y1 25
#define P1_Next_x 50
#define P1_Next_y 12
#define P2_Next_x 50
#define P2_Next_y 33
#define P1_Cur_x 18
#define P1_Cur_y 5
#define P2_Cur_x 18
#define P2_Cur_y 26

int i, j, temp, temp1, temp2; //temp,temp1,temp2���ڼ�ס��ת�����������ֵ

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;  //������
	pos.Y = y;  //������
	SetConsoleCursorPosition(hOut, pos);
}


void rand_color(int& color) //�������һ����ɫ
{
	color = rand() % 15;
	while (color == 0) color = rand() % 15;
}

void print_color(string str, WORD color, ...) //��ɫ���
{
	WORD colorOld;
	HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	colorOld = csbi.wAttributes;
	SetConsoleTextAttribute(handle, color);
	cout << str;
	SetConsoleTextAttribute(handle, colorOld);
}

struct matrix {
	int matr[4][4];
};

class Block {
public:
	int directions;
	matrix matrix_block[4];
	int color;
	Block() {}
	friend class Game;
	friend class Render;
	friend void InitBlocks();
	friend void print_block(Block* p, int x, int y, int cur_direction);
	friend void clear_block(Block* p, int x, int y, int cur_direction);

}block_arr[7];

void print_block(Block* p, int x, int y, int cur_direction);
void clear_block(Block* p, int x, int y, int cur_direction);

void InitBlocks()
{
	//z�η���A
	block_arr[0].matrix_block[0] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 1, 0, 0,
		0, 1, 1, 0,
	};
	block_arr[0].matrix_block[1] =
	{
		0, 0, 0, 0,
		0, 1, 0, 0,
		1, 1, 0, 0,
		1, 0, 0, 0,
	};
	block_arr[0].matrix_block[2] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 1, 0, 0,
		0, 1, 1, 0,
	};
	block_arr[0].matrix_block[3] =
	{
		0, 0, 0, 0,
		0, 1, 0, 0,
		1, 1, 0, 0,
		1, 0, 0, 0,
	};
	block_arr[0].directions = 0;
	//1���η���
	block_arr[1].matrix_block[0] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 1, 1, 1,
	};
	block_arr[1].matrix_block[1] =
	{
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
	};
	block_arr[1].matrix_block[2] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 1, 1, 1,
	};
	block_arr[1].matrix_block[3] =
	{
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
	};
	block_arr[1].directions = 1;
	//z�η���B
	block_arr[2].matrix_block[0] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 1, 1, 0,
		1, 1, 0, 0,
	};
	block_arr[2].matrix_block[1] =
	{
		0, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 0, 0,
		0, 1, 0, 0,
	};
	block_arr[2].matrix_block[2] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 1, 1, 0,
		1, 1, 0, 0,
	};
	block_arr[2].matrix_block[3] =
	{
		0, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 0, 0,
		0, 1, 0, 0,
	};
	block_arr[0].directions = 2;
	//�����η���
	block_arr[3].matrix_block[0] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
	};
	block_arr[3].matrix_block[1] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
	};
	block_arr[3].matrix_block[2] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
	};
	block_arr[3].matrix_block[3] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
	};
	block_arr[3].directions = 3;
	//L�η���A
	block_arr[4].matrix_block[0] =
	{
		0, 0, 0, 0,
		1, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 0, 0,
	};
	block_arr[4].matrix_block[1] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 1, 1, 0,
		1, 0, 0, 0,
	};
	block_arr[4].matrix_block[2] =
	{
		0, 0, 0, 0,
		1, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
	};
	block_arr[4].matrix_block[3] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 1, 0,
		1, 1, 1, 0,
	};
	block_arr[4].directions = 4;
	//L�η���B
	block_arr[5].matrix_block[0] =
	{
		0, 0, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		1, 1, 0, 0,
	};
	block_arr[5].matrix_block[1] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 1, 0,
	};
	block_arr[5].matrix_block[2] =
	{
		0, 0, 0, 0,
		1, 1, 0, 0,
		1, 0, 0, 0,
		1, 0, 0, 0,
	};
	block_arr[5].matrix_block[3] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 1, 1, 0,
		0, 0, 1, 0,
	};
	block_arr[5].directions = 5;
	//�����η���
	block_arr[6].matrix_block[0] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 1, 0, 0,
		1, 1, 1, 0,
	};
	block_arr[6].matrix_block[1] =
	{
		0, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 0, 0,
		1, 0, 0, 0,
	};
	block_arr[6].matrix_block[2] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 1, 1, 0,
		0, 1, 0, 0,
	};
	block_arr[6].matrix_block[3] =
	{
		0, 0, 0, 0,
		0, 1, 0, 0,
		1, 1, 0, 0,
		0, 1, 0, 0,
	};
	block_arr[6].directions = 6;
}

void rand_getblock(Block* p)//����õ�һ�ַ���
{
	switch (rand() % 7) {
	case 0:*p = block_arr[0]; break;
	case 1:*p = block_arr[1]; break;
	case 2:*p = block_arr[2]; break;
	case 3:*p = block_arr[3]; break;
	case 4:*p = block_arr[4]; break;
	case 5:*p = block_arr[5]; break;
	case 6:*p = block_arr[6]; break;
	default: *p = block_arr[0];
	}
	rand_color(p->color);
}

class Player
{
	int key_sys;//�б����ʹ��wasd�����Ƿ���� ,�ѷ���
public:
	int score;//��һ��� 
	int a[80][80];//�����Ϸ��Ļ��ͼ����2,1,0�ֱ��ʾ��λ��Ϊ��Ϸ�߿򡢷��顢��ͼ��;��ʼ��Ϊ��ͼ��
	Player(int score0 = 0, int key = 0)
	{
		score = score0;  key_sys = key;
		for (int i = 0; i < 80; i++)
			for (int j = 0; j < 80; j++)
				a[i][j] = 0;
	}

	friend class Game;
};

class Render
{
public:
	Player p;
	Render(int score0, int key) :p(score0, key) {}
	void score_add(int num, int x, int y)//���Ʒ������� 
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		p.score += num;
		gotoxy(hOut, x + 2 * W_SINGLE + 3, y + 5);
		cout << "SCORE :  " << p.score << endl;

	}
	void set_frame(int x0 = F_X0, int y0 = F_Y0);//���ñ߿�  
	bool map_check(Block* p, char key, int cur_direction, int x, int y);//���ָ���Ƿ����
	void map_update(Block* b, int cur_direction, int x, int y);//���º�̨��ͼ 
	friend class Game;
}win1(0, 1), win2(0, 0);

void Render::set_frame(int x0, int y0)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //������ʾ���������
	if (y0 == F_Y0)
	{
		gotoxy(hOut, x0 + W_SINGLE - 5, y0 - 2);   //��ӡ��Ϸ����
		cout << "����˹����" << endl;
	}
	gotoxy(hOut, x0 + 2 * W_SINGLE + 3, y0 + 3);
	if (y0 == F_Y0)
	{
		cout << "P1" << endl;
		gotoxy(hOut, x0 + 2 * W_SINGLE + 3, y0 + 5);
		cout << "SCORE :  " << p.score << endl;
	}
	else
	{
		cout << "P2" << endl;
		gotoxy(hOut, x0 + 2 * W_SINGLE + 3, y0 + 5);
		cout << "SCORE :  " << p.score << endl;
	}
	gotoxy(hOut, x0 + 2 * W_SINGLE + 3, y0 + 7);  //��ӡѡ��˵�
	cout << "**********��һ�����飺" << endl;
	gotoxy(hOut, x0 + 2 * W_SINGLE + 3, y0 + 13);
	cout << "**********" << endl;
	gotoxy(hOut, x0 + 2 * W_SINGLE + 3, y0 + 17);
	if (y0 == F_Y0) cout << "����������" << endl;
	else cout << "W ��������" << endl;
	gotoxy(hOut, x0 + 2 * W_SINGLE + 3, y0 + 19);
	if (y0 == F_Y0) cout << "��������������" << endl;
	else cout << "S ������������" << endl;
	gotoxy(hOut, x0 + 2 * W_SINGLE + 3, y0 + 15);
	if (y0 == F_Y0) cout << "����������ˮƽ�ƶ�" << endl;
	else cout << "A��D ����ˮƽ�ƶ�" << endl;;
	gotoxy(hOut, x0, y0);       //��ӡ��ǲ���ס�ô�����ͼ��
	cout << "��" << endl;
	gotoxy(hOut, x0 + 2 * W_SINGLE - 2, y0);
	cout << "��" << endl;
	gotoxy(hOut, x0, y0 + H_SINGLE);
	cout << "��" << endl;
	gotoxy(hOut, x0 + 2 * W_SINGLE - 2, y0 + H_SINGLE);
	cout << "��" << endl;
	p.a[x0][y0 + H_SINGLE] = 2;
	p.a[x0 + 2 * W_SINGLE - 2][y0 + H_SINGLE] = 2;
	for (i = 2; i < 2 * W_SINGLE - 2; i += 2)
	{
		gotoxy(hOut, x0 + i, y0);
		cout << "��" << endl;         //��ӡ�Ϻ��
	}
	for (i = 2; i < 2 * W_SINGLE - 2; i += 2)
	{
		gotoxy(hOut, x0 + i, y0 + H_SINGLE);
		cout << "��" << endl;         //��ӡ�º��
		p.a[x0 + i][y0 + H_SINGLE] = 2;    //��ס�º����ͼ��
	}
	for (i = 1; i < H_SINGLE; i++)
	{
		gotoxy(hOut, x0, y0 + i);
		cout << "��" << endl;         //��ӡ������
		p.a[x0][y0 + i] = 2;       //��ס��������ͼ��
	}
	for (i = 1; i < H_SINGLE; i++)
	{
		gotoxy(hOut, x0 + 2 * W_SINGLE - 2, y0 + i);
		cout << "��" << endl;         //��ӡ������
		p.a[x0 + 2 * W_SINGLE - 2][y0 + i] = 2;   //��ס��������ͼ��
	}
}

bool Render::map_check(Block* b, char key, int cur_direction, int x, int y)
{
	if (key == 72 || key == 'w') //up or w
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 4; j++)
				if (b->matrix_block[(cur_direction + 1) % 4].matr[j][i / 2] == 1 && p.a[x + i][y + j] >= 1)
					return false;
		return true;
	}
	else if (key == 77 || key == 'd')//right or d
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 4; j++)
				if (b->matrix_block[cur_direction % 4].matr[j][i / 2] == 1 && p.a[x + 2 + i][y + j] >= 1)
					return false;
		return true;
	}
	else if (key == 75 || key == 'a')//left or a
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 4; j++)
				if (b->matrix_block[cur_direction % 4].matr[j][i / 2] == 1 && p.a[x - 2 + i][y + j] >= 1)
					return false;
		return true;
	}
	else//down or s
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 4; j++)
				if (b->matrix_block[cur_direction % 4].matr[j][i / 2] == 1 && p.a[x + i][y + j + 1] >= 1)
					return false;
		return true;
	}
}

void Render::map_update(Block* b, int cur_direction, int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
		{
			if (b->matrix_block[cur_direction % 4].matr[j][i / 2])
			{
				p.a[x + i][y + j] = 1;
			}
		}
}

void print_block(Block* p, int x, int y, int cur_direction)//��ʾ����,����x��y�Ǹ÷������Ͻǵ�����
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (p->matrix_block[cur_direction % 4].matr[j][i] == 1)
			{
				gotoxy(hOut, x + i * 2, y + j);
				print_color("��", p->color);
			}
		}
}

void clear_block(Block* p, int x, int y, int cur_direction)//�������ۼ�
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (p->matrix_block[cur_direction % 4].matr[j][i] == 1)
			{
				gotoxy(hOut, x + i * 2, y + j);
				print_color("��", 0);
			}
		}
}

class Game
{
public:
	void Game_start(); //��ʼ��Ϸ  
	void Line_check(Render& win, int x, int y, int color1, Render& win2, int x2, int y2, int color2);//����Ƿ����� 
	void Delete_line(Render& win, int x, int y, int color, int line_num);//����һ�з��� 
	void Duel_penalization(Render& win, int x, int y, int color);//��սģʽ�еĳͷ��ж� 
	void Game_over(int flag);//ʤ���ѷ֣�������Ϸ 
}mainctrol;

void Game::Duel_penalization(Render& win, int x, int y, int color)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j, order = rand() % 2;
	for (i = y - 1; i < y + H_SINGLE - 1; i++)
	{
		for (j = x + 2; j < x + 2 * W_SINGLE - 2; j++)
		{
			win.p.a[j][i] = win.p.a[j][i + 1];
		}
	}
	for (j = x + 2; j < x + 2 * W_SINGLE - 2; j += 2)
	{
		win.p.a[j][i] = order % 2;
		win.p.a[j + 1][i] = order % 2;
		order++;
	}
	for (i = y + H_SINGLE - 1; i > y; i--)
	{
		for (j = x + 2; j < x + 2 * W_SINGLE - 2; j += 2)
		{
			gotoxy(hOut, j, i);
			if (win.p.a[j][i] == 1) print_color("��", color);
			else print_color("��", 0);
		}
	}
}

void Game::Delete_line(Render& win, int x, int y, int color, int line_num)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;
	for (i = line_num; i > y; i--)
	{
		for (j = x + 2; j < x + 2 * W_SINGLE - 2; j++)
		{
			win.p.a[j][i] = win.p.a[j][i - 1];
		}
	}
	for (i = line_num; i > y + 1; i--)
	{
		for (j = x + 2; j < x + 2 * W_SINGLE - 2; j += 2)
		{
			gotoxy(hOut, j, i);
			if (win.p.a[j][i] == 1) print_color("��", color);
			else print_color("��", 0);
		}
	}
	sndPlaySound(TEXT("SEB_platinum.wav"), SND_FILENAME | SND_NOSTOP);

}

void Game::Line_check(Render& Win1, int x1, int y1, int color1, Render& Win2, int x2, int y2, int color2)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int flag = 0;
	for (int i = y1 + H_SINGLE - 1; i > y1; i--)
	{
		flag = 0;
		for (int j = x1 + 2; j < x1 + 2 * W_SINGLE - 2; j += 2)
		{
			if (Win1.p.a[j][i] == 0)
			{
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			Delete_line(Win1, x1, y1, color1, i);
			Duel_penalization(Win2, x2, y2, color2);
			Win1.score_add(100, x1, y1);
		}

	}

}

void Game::Game_over(int flag)
{
	int x;
	if (flag)
	{
		x = MessageBox(GetForegroundWindow(), TEXT("P1 Win"), TEXT("Game Over"), 1);

	}
	else
	{
		x = MessageBox(GetForegroundWindow(), TEXT("P2 Win"), TEXT("Game Over"), 1);
	}
	printf("%d\n", x);
}

void Game::Game_start()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	srand((unsigned)time(0));
	Block b1, * p1 = &b1, next_b1, * next1 = &next_b1;
	Block b2, * p2 = &b2, next_b2, * next2 = &next_b2;

	int  down_flag1 = 1, down_flag2 = 1;

	int isP1wins = 0, isP2wins = 0;

	int point_x1 = P1_Cur_x, point_y1 = P1_Cur_y, point_x2 = P2_Cur_x, point_y2 = P2_Cur_y;

	int cur_direction1 = 0, cur_direction2 = 0, next_direction1 = 0, next_direction2 = 0;

	int down_time = 800;
	int curtick, lasttick;
	unsigned char key;
	rand_getblock(p1);
	rand_getblock(next1);
	rand_getblock(p2);
	rand_getblock(next2);
	print_block(next1, P1_Next_x, P1_Next_y, next_direction1);
	print_block(p1, P1_Cur_x, P1_Cur_y, cur_direction1);
	print_block(next2, P2_Next_x, P2_Next_y, next_direction2);
	print_block(p2, P2_Cur_x, P2_Cur_y, cur_direction2);
	lasttick = GetTickCount();
	while (1)
	{
		
		if (!down_flag1) {
			for (int i = F_X0 + 2; i < F_X0 + 2 * W_SINGLE - 2; i++)
			{
				if (win1.p.a[i][F_Y0 + 2])
				{
					isP2wins = 1; break;
				}
			}
			if (isP2wins) break;
			down_flag1 = 1;
			p1->color = 11;
			print_block(p1, point_x1, point_y1, cur_direction1);

			Line_check(win1, F_X0, F_Y0, 11, win2, F_X1, F_Y1, 12);

			*p1 = *next1; cur_direction1 = next_direction1;
			point_x1 = P1_Cur_x; point_y1 = P1_Cur_y;

			print_block(p1, point_x1, point_y1, cur_direction1);
			clear_block(next1, P1_Next_x, P1_Next_y, next_direction1);
			rand_getblock(next1); next_direction1 = rand() % 4;
			print_block(next1, P1_Next_x, P1_Next_y, next_direction1);
		}

		if (!down_flag2) {
			for (int i = F_X1 + 2; i < F_X1 + 2 * W_SINGLE - 2; i++)
			{
				if (win2.p.a[i][F_Y1 + 2])
				{
					isP1wins = 1; break;
				}
			}
			if (isP1wins) break;
			down_flag2 = 1;
			p2->color = 12;
			print_block(p2, point_x2, point_y2, cur_direction2);

			Line_check(win2, F_X1, F_Y1, 12, win1, F_X0, F_Y0, 11);

			*p2 = *next2; cur_direction2 = next_direction2;
			point_x2 = P2_Cur_x; point_y2 = P2_Cur_y;

			print_block(p2, point_x2, point_y2, cur_direction2);
			clear_block(next2, P2_Next_x, P2_Next_y, next_direction2);
			rand_getblock(next2); next_direction2 = rand() % 4;
			print_block(next2, P2_Next_x, P2_Next_y, next_direction2);
		}

		if (_kbhit()) {
			key = _getch();
			switch (key) {
			case 72://up key
				if (win1.map_check(p1, 72, cur_direction1, point_x1, point_y1))
				{
					clear_block(p1, point_x1, point_y1, cur_direction1); cur_direction1++; print_block(p1, point_x1, point_y1, cur_direction1);
					sndPlaySound(TEXT("down.wav"), SND_FILENAME | SND_ASYNC);

				} break;
			case 77://right key
				if (win1.map_check(p1, 77, cur_direction1, point_x1, point_y1))
				{
					clear_block(p1, point_x1, point_y1, cur_direction1); point_x1 += 2; print_block(p1, point_x1, point_y1, cur_direction1);
					sndPlaySound(TEXT("down.wav"), SND_FILENAME | SND_NOSTOP);
				}break;
			case 75://left key
				if (win1.map_check(p1, 75, cur_direction1, point_x1, point_y1))
				{
					clear_block(p1, point_x1, point_y1, cur_direction1); point_x1 -= 2; print_block(p1, point_x1, point_y1, cur_direction1);
					sndPlaySound(TEXT("down.wav"), SND_FILENAME | SND_NOSTOP);
				}break;
			case 80: //down key
				if (win1.map_check(p1, 80, cur_direction1, point_x1, point_y1))
				{
					clear_block(p1, point_x1, point_y1, cur_direction1); point_y1 += 1; print_block(p1, point_x1, point_y1, cur_direction1);
					sndPlaySound(TEXT("down.wav"), SND_FILENAME | SND_ASYNC);
				}
				break;
			case 119://w key
				if (win2.map_check(p2, 119, cur_direction2, point_x2, point_y2))
				{
					clear_block(p2, point_x2, point_y2, cur_direction2); cur_direction2++; print_block(p2, point_x2, point_y2, cur_direction2);
					sndPlaySound(TEXT("down.wav"), SND_FILENAME | SND_ASYNC);
				}; break;
			case 100://d key
				if (win2.map_check(p2, 100, cur_direction2, point_x2, point_y2))
				{
					clear_block(p2, point_x2, point_y2, cur_direction2); point_x2 += 2; print_block(p2, point_x2, point_y2, cur_direction2);
					sndPlaySound(TEXT("down.wav"), SND_FILENAME | SND_NOSTOP);
				}break;
			case 97://a key
				if (win2.map_check(p2, 97, cur_direction2, point_x2, point_y2))
				{
					clear_block(p2, point_x2, point_y2, cur_direction2); point_x2 -= 2; print_block(p2, point_x2, point_y2, cur_direction2);
					sndPlaySound(TEXT("down.wav"), SND_FILENAME | SND_NOSTOP);
				}break;
			case 115://s key
				if (win2.map_check(p2, 115, cur_direction2, point_x2, point_y2))
				{
					clear_block(p2, point_x2, point_y2, cur_direction2); point_y2 += 1; print_block(p2, point_x2, point_y2, cur_direction2);
					sndPlaySound(TEXT("down.wav"), SND_FILENAME | SND_ASYNC);
				}
				break;
			default:;
			}
		}
		Sleep(30);
		curtick = GetTickCount();
		if (curtick - lasttick >= down_time)
		{
			if (win1.map_check(p1, 80, cur_direction1, point_x1, point_y1))
			{
				clear_block(p1, point_x1, point_y1, cur_direction1); point_y1 += 1; print_block(p1, point_x1, point_y1, cur_direction1);
			}
			else
			{
				win1.map_update(p1, cur_direction1, point_x1, point_y1);
				down_flag1 = 0;
			}
			if (win2.map_check(p2, 115, cur_direction2, point_x2, point_y2))
			{
				clear_block(p2, point_x2, point_y2, cur_direction2); point_y2 += 1; print_block(p2, point_x2, point_y2, cur_direction2);
			}
			else
			{
				win2.map_update(p2, cur_direction2, point_x2, point_y2);
				down_flag2 = 0;
			}
			lasttick = GetTickCount();
		}

	}
	if (isP1wins) Game_over(1);
	else Game_over(0);
}

void ending()//��������
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < 80; i++)
		for (int j = 0; j < 80; j += 2)
		{
			gotoxy(hOut, j, i);
			print_color("��", 0);
		}

}

void HideCursor()//���ع��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
}

int  main()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("mode con cols=80 lines=100");
	HideCursor();
	InitBlocks();
	win1.set_frame(F_X0, F_Y0);
	win2.set_frame(F_X1, F_Y1);
	mainctrol.Game_start();
	ending();
	return 0;
}
