#include <stdio.h>
#include <time.h>
#include <Windows.h>
typedef struct {	//字母结构体
	int x, y;
	char ch;
} RAINDROP;
const int BUFFER_SIZE = 100;
int WIDTH = 80;
int HEIGHT = 30;
const int RAIN_LENGTH = 18;
RAINDROP raindropLine[BUFFER_SIZE];
HANDLE HOUT = GetStdHandle(STD_OUTPUT_HANDLE);	//获得标准输出的句柄
void gotoxy(int x, int y) {
	COORD pos;				//定义表示一个字符在控制台屏幕上的坐标的对象
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(HOUT, pos);	//设置控制台标准输出光标位置
}
void show_cursor(BOOL hide) {
	CONSOLE_CURSOR_INFO cciCursor;
	if (GetConsoleCursorInfo(HOUT, &cciCursor)) {	//获得光标信息
		cciCursor.bVisible = hide;					//隐藏光标		
		SetConsoleCursorInfo(HOUT, &cciCursor);		//重新设置光标
	}
}
void set_color(int color) {
	SetConsoleTextAttribute(HOUT, color);		//设置输出颜色
}
int main() {
	CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 尝试最大化控制台窗口
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);

    // 获取当前屏幕缓冲区信息
    GetConsoleScreenBufferInfo(hConsole, &info);
    
    // 设置缓冲区尺寸为屏幕尺寸
    COORD bufferSize;
    bufferSize.X = info.dwMaximumWindowSize.X; // 屏幕宽度
    bufferSize.Y = info.dwMaximumWindowSize.Y; // 屏幕高度（或根据需要设置一个较大的值）
    SetConsoleScreenBufferSize(hConsole, bufferSize);
	GetConsoleScreenBufferInfo(HOUT, &info);	//获得控制台窗体信息
	HEIGHT = info.srWindow.Bottom;				//根据控制台的宽高设置显示的宽高
	WIDTH = info.srWindow.Right;
	show_cursor(FALSE);
	srand((unsigned int)time(NULL));
	for (int i=0; i<BUFFER_SIZE; i++) {			//随机设置字母下落的位置 
		raindropLine[i].x = rand()%WIDTH;
		raindropLine[i].y = rand()%HEIGHT;
		raindropLine[i].ch = rand() %26 + 97;
	}			
	while(true) {
		GetConsoleScreenBufferInfo(HOUT, &info);	//当窗体大小变化时，重新设置宽高信息
		HEIGHT = info.srWindow.Bottom;
		WIDTH = info.srWindow.Right;
		for (int i=0; i<BUFFER_SIZE; ++i)		{
			if (raindropLine[i].y <= HEIGHT)			{
				gotoxy(raindropLine[i].x, raindropLine[i].y);
				set_color(FOREGROUND_GREEN);				//设置字母颜色
				putchar(raindropLine[i].ch);
			}
			gotoxy(raindropLine[i].x, raindropLine[i].y - RAIN_LENGTH);	//擦除过长的字母 
			putchar(' ');
			raindropLine[i].y++;
			raindropLine[i].ch = rand() % 26 + 97;
			if (raindropLine[i].y > HEIGHT + RAIN_LENGTH)					{
				raindropLine[i].x = rand() % WIDTH;
				raindropLine[i].y = rand() % HEIGHT;
			}
			if ( raindropLine[i].y <= HEIGHT) {
				gotoxy(raindropLine[i].x, raindropLine[i].y);
				set_color(FOREGROUND_GREEN|FOREGROUND_INTENSITY);	//高亮最下方的字母		
				putchar(raindropLine[i].ch);
			}
		}
		Sleep(50);
	}
	getchar();
	return 0;
}
