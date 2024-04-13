#include<stdio.h>
#include<Windows.h>

//写字
char love[20][43] = {
	"111111111111111111111111111111111111111111",
	"111111111111110000111111100001000111111111",
	"110000000000000000011111100011000111111111",
	"110000111001110001111111000110001111111111",
	"111100010000110000111111100011000000000011",
	"111100001000100011111110000100011111100011",
	"100000000000000000001110000100011111000111",
	"100000000000000000011100000000110001000111",
	"100011100011111000110000000000110001111111",
	"111011100011111100111111000111110001111111",
	"111000000000000000111111000110000000001111",
	"111111000111111111111111000110000000000111",
	"111110001111111111111111000100010001000111",
	"111000000000000001111111000000010001100011",
	"111000000011000011111111000000110001100001",
	"110001110000000111111111000001110001110111",
	"100011111000011111111111000111110001111111",
	"111110000000000000011111000111000001111111",
	"111000000111110000011111000111000011111111",
	"111111111111111111111111111111111111111111"
};

void gotoxy(int x, int y) {
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hout, pos);
}

void SetColor(int color) {
	if (color == 0)color = 0x04;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}



int main() {
	system("color 0c");    //设计程序颜色
	printf("\n\t与君初相识，犹如故人归。天涯明月新，朝暮最相思\n");    //打印文字

	HWND consoleHandle = GetConsoleWindow();

	// 获取系统屏幕分辨率
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// 获取窗口大小
	RECT consoleRect;
	GetWindowRect(consoleHandle, &consoleRect);
	int consoleWidth = consoleRect.right - consoleRect.left;
	int consoleHeight = consoleRect.bottom - consoleRect.top;

	// 计算窗口应该出现的位置
	int x = (screenWidth - consoleWidth) / 2;
	int y = (screenHeight - consoleHeight) / 2;

	// 使用SetWindowPos函数设置新的窗口位置
	SetWindowPos(consoleHandle, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);


	float x1,y1,a;    //定义变量x,y,a
	int i, j;
	int x2, y2 = 3;

	for(y1=1.5f; y1>-1; y1-=0.1f) { //爱心函数
		for(x1=-1.5f; x1<1.5f; x1+=.05f) {
			a=x1*x1+y1*y1-1;
			putchar(a*a*a-x1*x1*y1*y1*y1<0.0f?'*':' ');
		}

		Sleep(150);     //停顿1.5秒钟
		putchar('\n');  //换行
	}

	for (i = 0; i < 19; i++, y2++) {
		x2 = 60;
		for (j = 0; j < 42; j++, x2++) {
			gotoxy(x2, y2);
			if (love[i][j] == '1') {
				putchar(' ');
			} else {
				SetColor(0x04);
				putchar('*');
			}
		}
	}

	putchar('\n');
	putchar('\n');
	putchar('\n');
	putchar('\n');
	putchar('\n');

	return 0;
}
