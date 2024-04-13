#include <graphics.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <vector>

using namespace std;

#define MAXSnow 1314	// 设置雪花总数

struct Snow
{
	double x;		// 雪花横坐标
	int y;          // 雪花纵坐标
	int r;		    // 雪花的大小
	double	speed;	// 雪花下落速度
	int	 color;	    // 雪花的颜色
};

Snow snow[MAXSnow]; // 保存所有雪花

// 初始化雪花
void InitSnow(int i, int width, int height)
{
	snow[i].x = rand() % width;
	snow[i].y = rand() % height - height;
	snow[i].r = rand() % 4 + 1;
	snow[i].speed = (rand() % 3333) / 1000.0 + 1;
	snow[i].color = (int)(255);	// 设置雪花颜色
	snow[i].color = RGB(snow[i].color, snow[i].color, snow[i].color);
}

// 雪花的下落函数
void MoveSnow(int i, int width, int height)
{
	setlinecolor(RGB(0, 0, 0));
	setfillcolor(RGB(0, 0, 0));
	// 删除原来的雪花
	fillcircle((int)snow[i].x, snow[i].y, snow[i].r);

	// 计算雪花新位置
	snow[i].y += snow[i].speed;
	if (snow[i].y > height)	InitSnow(i, width, height);

	// 画新雪花
	setfillcolor(snow[i].color);
	setlinecolor(snow[i].color);
	fillcircle((int)snow[i].x, snow[i].y, snow[i].r);

}

// 主函数
int main()
{
	srand((unsigned)time(NULL));// 设置随机种子
	int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	initgraph(ScreenWidth, ScreenHeight);// 创建绘图窗口

	HWND hwnd = GetHWnd(); // 获取绘图窗口句柄
	int x = 0; // 窗口左上角横坐标
	int y = 0; // 窗口左上角纵坐标
	SetWindowPos(hwnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE); // 设置窗口位置

	// 初始化所有雪花
	for (int i = 0; i < MAXSnow; i++)
	{
		InitSnow(i, ScreenWidth, ScreenHeight);
		snow[i].x = rand() % ScreenWidth;
	}

	// 绘制雪花，按任意键退出
	while (!_kbhit())
	{
		for (int i = 0; i < MAXSnow; i++)
			MoveSnow(i, ScreenWidth, ScreenHeight);
		Sleep(0);
	}

	closegraph();// 关闭绘图窗口
}
