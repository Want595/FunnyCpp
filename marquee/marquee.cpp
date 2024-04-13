#include <graphics.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <vector>

using namespace std;

// 彩球基础设置
#define MAXLove 999	// 设置彩球总数

// 文字基础设置
#define MAX_TEXT_SIZE 20        // 最小文字大小
#define MAX_TEXT_COUNT 30       // 最大同时显示的文字数量
#define MAX_TEXT_BUFFER 255     // 每一句文字的最大字符个数

struct Love
{
	double x;		// 彩球横坐标
	int y;          // 彩球纵坐标
	int r;		    // 彩球的大小
	double	speed;	// 彩球下落速度
	int	 color;	    // 彩球的颜色
};

// 文字结构体
struct Text
{
	int x;		   // 橫坐标
	int y;         // 纵坐标

	int textWidth;    // 句子长度
	int textHeight;   // 句子高度

	double step;	// 速度
	int color;		// 颜色
	int size;		// 文字大小
	int direction;  // 方向：默认右边滚动到左边   
	WCHAR* content;	    // 文字内容
};

// 定义你想输出的文字，注意句子长度不能超过 MAX_TEXT_BUFFER 个字符，句子数量不能超过 MAX_TEXT_COUNT 
WCHAR TEXT_LIST[MAX_TEXT_COUNT][MAX_TEXT_BUFFER] = {
   _T("我爱你"),
   _T("I Love You!"),
   _T("永远爱你"),
   _T("你是我年少的欢喜"),
   _T("一生一世一双人"),
   _T("余生我陪你走"),
   _T("陪你到来生"),
   _T("春风十里不如你"),
   _T("三生有幸来日方长"),
   _T("夜很长幸有你"),
   _T("爱你的全部"),
   _T("踏过八荒四海只为你"),
   _T("愿得一人心"),
   _T("众里寻他千百度"),
   _T("顶峰相见"),
   _T("等你下课"),
   _T("往后余生"),
   _T("Missing You!"),
   _T("做我女朋友好么"),
   _T("你已经在我的未来里了"),
   _T("陪你到世界之巅"),
   _T("白头偕老"),
   _T("我喜欢你"),
   _T("好想好想你"),
   _T("想你想你想你"),
   _T("今夜月色真美"),
   _T("你是我的唯一")
};

// 存储所有彩球
Love Love[MAXLove]; //保存所有彩球

// 设置字体
LPCTSTR textType = (LPCTSTR)("微软雅黑");

// 存储所有文字数据
Text text[MAX_TEXT_SIZE];

// 初始化彩球
void InitLove(int i, int width, int height)
{
	Love[i].x = rand() % width;
	Love[i].y = rand() % height - height;
	Love[i].r = rand() % 4 + 1;
	Love[i].speed = (rand() % 3333) / 1000.0 + 1;
	Love[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

// 彩球的下落函数
void MoveLove(int i, int width, int height)
{
	setlinecolor(RGB(0, 0, 0));
	setfillcolor(RGB(0, 0, 0));
	// 删除原来的彩球
	fillcircle((int)Love[i].x, Love[i].y, Love[i].r);

	// 计算彩球新位置
	Love[i].y += Love[i].speed;
	if (Love[i].y > height)	InitLove(i, width, height);

	// 画新彩球
	setfillcolor(Love[i].color);
	setlinecolor(Love[i].color);
	fillcircle((int)Love[i].x, Love[i].y, Love[i].r);

}

// 初始化文字
void InitText(int index, int Width, int Height) {
	text[index].x = Width;
	text[index].y = rand() % Height;
	text[index].size = rand() % MAX_TEXT_SIZE + MAX_TEXT_SIZE; // 设置最小文字大小为 20 个像素
	text[index].step = (rand() % 20) + 2;
	text[index].direction = (rand() % 2) + 0.5;
	text[index].content = TEXT_LIST[(rand() % MAX_TEXT_COUNT)];
	text[index].textWidth = textwidth(text[index].content);
	text[index].textHeight = textheight(text[index].content);

	int color = (int)(text[index].step * 255 / 5.0 + 0.5);
	text[index].color = RGB((rand() % 255), (rand() % 255), (rand() % 255));
}

// 初始化文字个数
void InitTexts(int Width, int Height) {
	for (int i = 0; i < MAX_TEXT_COUNT; i++) {
		InitText(i, Width, Height);
	}
}

// 移动文字
void MoveText(int Width, int Height)
{
	for (int i = 0; i < MAX_TEXT_COUNT; i++) {

		// 删除原来的文字
		int textHeight = textheight(text[i].content);
		int textWidth = textwidth(text[i].content);
		settextcolor(RGB(0, 0, 0));
		settextstyle(text[i].size, text[i].size, textType);
		outtextxy(text[i].x, text[i].y, text[i].content);

		// 计算新位置
		text[i].x -= text[i].step;
		if ((text[i].x + textWidth) <= 0) {
			InitText(i, Width, Height);
		}

		settextcolor(text[i].color);
		settextstyle(text[i].size, 0, textType);
		outtextxy(text[i].x, text[i].y, text[i].content);
	}
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

	// 初始化所有彩球
	for (int i = 0; i < MAXLove; i++)
	{
		InitLove(i, ScreenWidth, ScreenHeight);
		Love[i].x = rand() % ScreenWidth;
	}

	// 初始化所有文字
	InitTexts(ScreenWidth, ScreenHeight);

	// 绘制彩球，按任意键退出
	while (!_kbhit())
	{
		for (int i = 0; i < MAXLove; i++)
			MoveLove(i, ScreenWidth, ScreenHeight);

		BeginBatchDraw();
		MoveText(ScreenWidth, ScreenHeight);
		FlushBatchDraw();
		Sleep(5);
	}

	EndBatchDraw();

	closegraph();// 关闭绘图窗口
}
