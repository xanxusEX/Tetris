#include <windows.h>
#include <time.h>
#include<stdlib.h>
#include <iostream>

#define W 50
#define H 20
#define BgColor RGB(0xF5,0xF5,0xDC) //米色
#define FgColor RGB(255,153,204) //粉红
#define RED RGB(255,0,0)
#define ORANGE RGB(250,128,10)
#define YELLOW RGB(255,255,0)
#define GREEN RGB(0,255,0)
#define CYAN RGB(0,255,255)
#define LIGHT_BLUE RGB(0xA6,0xCA,0xF0) //天蓝色


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
		void generate_random();//随机产生一种方块 
	    void block_trans_direction();// 控制方块方向旋转 
	    void block_falling();//控制方块自然下落 
	    void block_acceleration();//控制方块加速下落 
	    void block_move();	//控制方块水平左右移动 
};

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
	int Main_map[H][W];//主地图 
	public:
		void Game_start(); //开始游戏 
		void Map_iniyialization();//地图初始化 
		void Show_score();//显示玩家分数 
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
	
	public:
		void set_background();//设置背景 
		void set_frame();//设置边框 
		void window_update();//更新窗口显示 
		void exit_game();//退出游戏 
}; 

int  WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hprevInstance,PSTR szCmdLine,int iCmdShow)
{
	return 0;
}






