#include <windows.h>
#include <conio.h>
#include <time.h>
#include<stdlib.h>
#include <iostream>
using namespace std;

#define W_SINGLE 20
#define H_SINGLE 20
#define F_X0 4
#define F_Y0 4
#define F_X1 4
#define F_Y1 25
#define BgColor RGB(0xF5,0xF5,0xDC) //��ɫ
#define FgColor RGB(255,153,204) //�ۺ�
#define RED RGB(255,0,0)
#define ORANGE RGB(250,128,10)
#define YELLOW RGB(255,255,0)
#define GREEN RGB(0,255,0)
#define CYAN RGB(0,255,255)
#define LIGHT_BLUE RGB(0xA6,0xCA,0xF0) //����ɫ
int i,j,temp,temp1,temp2; //temp,temp1,temp2���ڼ�ס��ת�����������ֵ
int a[80][80]={0};   //�����Ϸ��Ļ��ͼ����2,1,0�ֱ��ʾ��λ��Ϊ��Ϸ�߿򡢷��顢��ͼ��;��ʼ��Ϊ��ͼ��

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
		void generate_random(Block *tetris);//�������һ�ַ��� 
	    void block_trans_direction();// ���Ʒ��鷽����ת 
	    void block_falling();//���Ʒ�����Ȼ���� 
	    void block_acceleration();//���Ʒ���������� 
	    void block_move();	//���Ʒ���ˮƽ�����ƶ� 
};
void Block::generate_random(Block *tetris)
{
	
}
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
	int Main_map[H_SINGLE][W_SINGLE];//����ͼ 
	public:
		void Game_start(); //��ʼ��Ϸ 
		void Map_iniyialization();//��ͼ��ʼ�� 
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
	Player p;
	public:
		Render(int score0,int key):p(score0,key){} 
		void gotoxy(HANDLE hOut, int x, int y);
		void set_background();//���ñ��� 
		void set_frame(int x0=F_X0,int y0=F_Y0);//���ñ߿� 
		void show_score();//��ʾ��ҷ��� 
		void window_update();//���´�����ʾ 
		void exit_game();//�˳���Ϸ 
}win1(0,1),win2(0,0);
void Render::gotoxy(HANDLE hOut, int x, int y)
{
 COORD pos;
 pos.X = x;  //������
 pos.Y = y;  //������
 SetConsoleCursorPosition(hOut, pos);
}
void Render::set_frame(int x0,int y0 )
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //������ʾ���������
	if(y0==F_Y0)
    {
    	gotoxy(hOut,x0+W_SINGLE-5,y0-2);   //��ӡ��Ϸ����
        cout<<"����˹����"<<endl;
	}
	gotoxy(hOut,x0+2*W_SINGLE+3,y0+3);
	if(y0==F_Y0)
	{
		cout<<"P1"<<endl;
		gotoxy(hOut,x0+2*W_SINGLE+3,y0+5);
		cout<<"SCORE :  "<<p.score<<endl;
	}
	else
	{
		cout<<"P2"<<endl;
		gotoxy(hOut,x0+2*W_SINGLE+3,y0+5);
		cout<<"SCORE :  "<<p.score<<endl;
	}
    gotoxy(hOut,x0+2*W_SINGLE+3,y0+7);  //��ӡѡ��˵�
    cout<<"**********��һ�����飺"<<endl;
    gotoxy(hOut,x0+2*W_SINGLE+3,y0+13);
    cout<<"**********"<<endl;
    gotoxy(hOut,x0+2*W_SINGLE+3,y0+17);
    if(y0==F_Y0) cout<<"����������"<<endl;
    else cout<<"W ��������"<<endl;
    gotoxy(hOut,x0+2*W_SINGLE+3,y0+19);
    cout<<"�ո���ͣ��Ϸ"<<endl;
    gotoxy(hOut,x0+2*W_SINGLE+3,y0+15);
    cout<<"Esc ���˳���Ϸ"<<endl;
    gotoxy(hOut,x0,y0);       //��ӡ��ǲ���ס�ô�����ͼ��
    cout<<"�X"<<endl;
    gotoxy(hOut,x0+2*W_SINGLE-2,y0);
    cout<<"�["<<endl;
    gotoxy(hOut,x0,y0+H_SINGLE); 
    cout<<"�^"<<endl;
    gotoxy(hOut,x0+2*W_SINGLE-2,y0+H_SINGLE);
    cout<<"�a"<<endl;
    a[x0][y0+H_SINGLE]=2;     
    a[x0+2*W_SINGLE-2][y0+H_SINGLE]=2;
 for(i=2;i<2*W_SINGLE-2;i+=2)
 {
  gotoxy(hOut,x0+i,y0);
 cout<<"�T"<<endl;         //��ӡ�Ϻ��
 }
 for(i=2;i<2*W_SINGLE-2;i+=2)
 {
  gotoxy(hOut,x0+i,y0+H_SINGLE);
 cout<<"�T"<<endl;         //��ӡ�º��
  a[x0+i][y0+H_SINGLE]=2;    //��ס�º����ͼ��
 }
 for(i=1;i<H_SINGLE;i++)
 {
  gotoxy(hOut,x0,y0+i); 
 cout<<"�U"<<endl;         //��ӡ������
  a[x0][y0+i]=2;       //��ס��������ͼ��
 }
 for(i=1;i<H_SINGLE;i++)
 {
  gotoxy(hOut,x0+2*W_SINGLE-2,y0+i); 
 cout<<"�U"<<endl;         //��ӡ������
  a[x0+2*W_SINGLE-2][y0+i]=2;   //��ס��������ͼ��
} 
}

int  WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hprevInstance,PSTR szCmdLine,int iCmdShow)
{
	win1.set_frame(F_X0,F_Y0);
	win2.set_frame(F_X1,F_Y1);
	return 0;
}






