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
#define BgColor RGB(0xF5,0xF5,0xDC) //米色
#define FgColor RGB(255,153,204) //粉红
#define RED RGB(255,0,0)
#define ORANGE RGB(250,128,10)
#define YELLOW RGB(255,255,0)
#define GREEN RGB(0,255,0)
#define CYAN RGB(0,255,255)
#define LIGHT_BLUE RGB(0xA6,0xCA,0xF0) //天蓝色
int i,j,temp,temp1,temp2; //temp,temp1,temp2用于记住和转换方块变量的值
int a[80][80]={0};   //标记游戏屏幕的图案：2,1,0分别表示该位置为游戏边框、方块、无图案;初始化为无图案

class Block
{
	int shape[2][4];//方块形状 
	int color;//方块颜色 
	public:
		Block(int s1=0,int s2=0,int s3=0,int s4=0,int s5=0,int s6=0,int s7=0,int s8=0,int col=RGB(255,255,255))
		{
			shape[0][0]=s1; shape[0][1]=s2; shape[0][2]=s3; shape[0][3]=s4; shape[1][0]=s5; shape[1][1]=s6; shape[1][2]=s7; shape[1][3]=s8;
			color=col;
		}
		void generate_random(Block *tetris);//随机产生一种方块 
	    void block_trans_direction();// 控制方块方向旋转 
	    void block_falling();//控制方块自然下落 
	    void block_acceleration();//控制方块加速下落 
	    void block_move();	//控制方块水平左右移动 
};
void Block::generate_random(Block *tetris)
{
	
}
class Player
{
	int key_sys;//判别玩家使用wasd，还是方向键 
	public:
		int score;//玩家积分 
		Player (int score0=0,int key=0)
		{
			score=score0;  key_sys=key;
		}
		void score_add(int num);//控制分数增加 
		
};

class Game_window
{
	Player p1;//设置玩家p1 
	Player p2;//设置玩家p2 
	int Main_map[H_SINGLE][W_SINGLE];//主地图 
	public:
		void Game_start(); //开始游戏 
		void Map_iniyialization();//地图初始化 
		void Block_touch_check();//检测方块是否与其他方块或边界接触 
		void Line_check();//检测是否满行 
		void Delete_line();//消除一行方块 
		void Duel_penalization();//对战模式中的惩罚判定 
		void Game_process_check();//对游戏进度进行判定 
		void Game_pause();//游戏暂停 
		void Game_over();//胜负已分，结束游戏 
}; 

class Render
{
	Player p;
	public:
		Render(int score0,int key):p(score0,key){} 
		void gotoxy(HANDLE hOut, int x, int y);
		void set_background();//设置背景 
		void set_frame(int x0=F_X0,int y0=F_Y0);//设置边框 
		void show_score();//显示玩家分数 
		void window_update();//更新窗口显示 
		void exit_game();//退出游戏 
}win1(0,1),win2(0,0);
void Render::gotoxy(HANDLE hOut, int x, int y)
{
 COORD pos;
 pos.X = x;  //横坐标
 pos.Y = y;  //纵坐标
 SetConsoleCursorPosition(hOut, pos);
}
void Render::set_frame(int x0,int y0 )
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //定义显示器句柄变量
	if(y0==F_Y0)
    {
    	gotoxy(hOut,x0+W_SINGLE-5,y0-2);   //打印游戏名称
        cout<<"我罗斯方块"<<endl;
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
    gotoxy(hOut,x0+2*W_SINGLE+3,y0+7);  //打印选择菜单
    cout<<"**********下一个方块："<<endl;
    gotoxy(hOut,x0+2*W_SINGLE+3,y0+13);
    cout<<"**********"<<endl;
    gotoxy(hOut,x0+2*W_SINGLE+3,y0+17);
    if(y0==F_Y0) cout<<"↑键：变体"<<endl;
    else cout<<"W 键：变体"<<endl;
    gotoxy(hOut,x0+2*W_SINGLE+3,y0+19);
    cout<<"空格：暂停游戏"<<endl;
    gotoxy(hOut,x0+2*W_SINGLE+3,y0+15);
    cout<<"Esc ：退出游戏"<<endl;
    gotoxy(hOut,x0,y0);       //打印框角并记住该处已有图案
    cout<<"╔"<<endl;
    gotoxy(hOut,x0+2*W_SINGLE-2,y0);
    cout<<"╗"<<endl;
    gotoxy(hOut,x0,y0+H_SINGLE); 
    cout<<"╚"<<endl;
    gotoxy(hOut,x0+2*W_SINGLE-2,y0+H_SINGLE);
    cout<<"╝"<<endl;
    a[x0][y0+H_SINGLE]=2;     
    a[x0+2*W_SINGLE-2][y0+H_SINGLE]=2;
 for(i=2;i<2*W_SINGLE-2;i+=2)
 {
  gotoxy(hOut,x0+i,y0);
 cout<<"═"<<endl;         //打印上横框
 }
 for(i=2;i<2*W_SINGLE-2;i+=2)
 {
  gotoxy(hOut,x0+i,y0+H_SINGLE);
 cout<<"═"<<endl;         //打印下横框
  a[x0+i][y0+H_SINGLE]=2;    //记住下横框有图案
 }
 for(i=1;i<H_SINGLE;i++)
 {
  gotoxy(hOut,x0,y0+i); 
 cout<<"║"<<endl;         //打印左竖框
  a[x0][y0+i]=2;       //记住左竖框有图案
 }
 for(i=1;i<H_SINGLE;i++)
 {
  gotoxy(hOut,x0+2*W_SINGLE-2,y0+i); 
 cout<<"║"<<endl;         //打印右竖框
  a[x0+2*W_SINGLE-2][y0+i]=2;   //记住右竖框有图案
} 
}

int  WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hprevInstance,PSTR szCmdLine,int iCmdShow)
{
	win1.set_frame(F_X0,F_Y0);
	win2.set_frame(F_X1,F_Y1);
	return 0;
}






