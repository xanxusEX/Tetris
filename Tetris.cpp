#include <windows.h>
#include <time.h>
#include<stdlib.h>
#include <iostream>

#define W 50
#define H 20
#define BgColor RGB(0xF5,0xF5,0xDC) //��ɫ
#define FgColor RGB(255,153,204) //�ۺ�
#define RED RGB(255,0,0)
#define ORANGE RGB(250,128,10)
#define YELLOW RGB(255,255,0)
#define GREEN RGB(0,255,0)
#define CYAN RGB(0,255,255)
#define LIGHT_BLUE RGB(0xA6,0xCA,0xF0) //����ɫ


class Block
{
	int shape[2][4];//������״ 
	int color;//������ɫ 
	public:
		Block(int s1=0,int s2=0,int s3=0,int s4=0,int s5=0,int s6=0,int s7=0,int s8=0,int col=RGB(255,255,255))
		{
			shape[0][0]=s1; shape[0][1]=s2; shape[0][2]=s3; shape[0][3]=s4; shape[1][0]=s5; shape[1][1]=s6; shape[1][2]=s7; shape[1][3]=s8;
			color=col;
		}
		void generate_random();//�������һ�ַ��� 
	    void block_trans_direction();// ���Ʒ��鷽����ת 
	    void block_falling();//���Ʒ�����Ȼ���� 
	    void block_acceleration();//���Ʒ���������� 
	    void block_move();	//���Ʒ���ˮƽ�����ƶ� 
};

class Player
{
	int key_sys;//�б����ʹ��wasd�����Ƿ���� 
	public:
		int score;//��һ��� 
		Player (int score0=0,int key=0)
		{
			score=score0;  key_sys=key;
		}
		void score_add(int num);//���Ʒ������� 
		
};

class Game_window
{
	Player p1;//�������p1 
	Player p2;//�������p2 
	int Main_map[H][W];//����ͼ 
	public:
		void Game_start(); //��ʼ��Ϸ 
		void Map_iniyialization();//��ͼ��ʼ�� 
		void Show_score();//��ʾ��ҷ��� 
		void Block_touch_check();//��ⷽ���Ƿ������������߽�Ӵ� 
		void Line_check();//����Ƿ����� 
		void Delete_line();//����һ�з��� 
		void Duel_penalization();//��սģʽ�еĳͷ��ж� 
		void Game_process_check();//����Ϸ���Ƚ����ж� 
		void Game_pause();//��Ϸ��ͣ 
		void Game_over();//ʤ���ѷ֣�������Ϸ 
}; 

class Render
{
	
	public:
		void set_background();//���ñ��� 
		void set_frame();//���ñ߿� 
		void window_update();//���´�����ʾ 
		void exit_game();//�˳���Ϸ 
}; 

int  WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hprevInstance,PSTR szCmdLine,int iCmdShow)
{
	return 0;
}






