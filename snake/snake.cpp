#include<stdio.h>               //头文件
#include<windows.h>
#include<conio.h>
#include<time.h>

void gotoxy(int x, int y);                                          //声明光标转移函数
void fontcolor(int x);                                  //声明字体颜色函数
void IF();                                              //声明开始界面
void START();                                           //声明开始选择函数
void Snake();                                           //声明蛇的控制函数
void food_f();                                          //声明食物的随机出现函数
void END();                                             //声明游戏结束函数

int body_x[300],body_y[300];                            // 定义蛇身数组，最大长度为300
int score=0,max=0,num=0,head_x=28,head_y=8;             // 定义得分数及最高分、吃的食物数量、蛇头的初始位置
int food_x,food_y;                                      // 定义食物坐标 
int flag1=1,flag2=1,flag3=1,flag4=1;                    // 定义标志变量、接受按键字符变量以及循环变量
int key3='w',key2='d',key1;                             // 定义移动变量 
int i;                         




int main()
{	
    system("mode con cols=100 lines=40");                 // 调整屏幕大小
    
	HWND consoleWindow = GetConsoleWindow();              // 调整屏幕位置 
    RECT consoleRect; 
    GetWindowRect(consoleWindow, &consoleRect);

    int consoleWidth = consoleRect.right - consoleRect.left;
    int consoleHeight = consoleRect.bottom - consoleRect.top;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int windowX = (screenWidth - consoleWidth) / 2;
    int windowY = (screenHeight - consoleHeight) / 2;

    SetWindowPos(consoleWindow, NULL, windowX, windowY, consoleWidth, consoleHeight, SWP_SHOWWINDOW);

    IF();                                                 // 调用初始界面
	START();                                              // 调用用户选择函数

    if(flag1==0) return 0;                                // 根据用户选择，开始开始执行      
	else
	{
		for(i=13;i<=16;i++)                               //消除选择界面,开始游戏
		{
			gotoxy(40,i);
			printf("               ");
		}

        food_f();				             	         // 食物的出现
		Snake();                                         // 蛇的控制(包括吃到食物的判定等等），主要函数
		END();                                           //结束函数
	}

	return 0;
}



void gotoxy(int x,int y)                                 //光标转移函数
{
    COORD pos={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    printf("\e[?25l"); // 隐藏光标
}

void HideCursor()                                       //隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void fontcolor(int x)                                  //字体颜色函数
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|x);
}

void fresh()                                           //数据初始化函数，继续游戏的话，数据要初始化
{
	 score=0;
	 num=0;
	 head_x=28;
	 head_y=8;                                
	 flag3=1;
	 flag4=1;                     
	 key3='w';
	 key2='d';
	 system("cls");
}

void rule()
{
	gotoxy(10,32);
	fontcolor(7);
	for(i=1;i<=40;i++)
	{
		printf("--");
	}	
	gotoxy(10,33);printf("☆游戏规则：");
	gotoxy(10,34);printf("1.W,S,A,D键分别代表上下左右，回车键（'enter'）代表确定");
	gotoxy(10,35);printf("2.碰墙或碰到自己即死亡，游戏中除了wasd键按其他键也会死");
	gotoxy(10,36);printf("3.蛇移动的速度会随着身体增长而加快，最大长度300，超过则游戏结束");
	gotoxy(10,37);
	for(i=1;i<=40;i++)
	{
		printf("--");
	}	
}





void IF()                                              //初始界面函数
{
    fontcolor(9);
    
    for(i=1;i<=100;i+=2)                   // 画行
    {
        printf("■");   
    }
    for(i=2;i<=96;i+=2)
    {
        gotoxy(i,30);
        printf("■");
    }
    for(i=1;i<=30;i++)                    //画列
    {
        gotoxy(0,i);
        printf("■");
    }
    for(i=1;i<=30;i++)
    {
        gotoxy(98,i);
        printf("■");
    }
    for(i=2;i<=96;i+=2)                 //画数据显示区
    {
        fontcolor(9);
        gotoxy(i,4);
        printf("■");
    }

    rule();

    gotoxy(30,2);                      //画得分情况
    fontcolor(7);
    printf("Your Score: %d\t\tMax Score: %d",score,max);   
}

void START()                           // 用户选择是否开始游戏函数
{
	
    gotoxy(30,2);                                                 
    fontcolor(7);
    printf("Your Score: %d\t\tMax Score: %d",score,max);
	gotoxy(40,13);
	fontcolor(6);                 
	printf("Are you ready ?");       //初始化 
	gotoxy(42,15);
	printf("→  GO");
	gotoxy(42,16);
	printf("    EXIT");
	

	while(1)                       //用户按键
	{
		key1=getch();

		if(key1=='w') 
		{
			Beep(800,150);
			gotoxy(42,15);
			printf("→  GO");
			gotoxy(42,16);
			printf("    EXIT");
			flag1=1;
		}

		if(key1=='s')
		{
			Beep(800,150);
			gotoxy(42,15);
			printf("    GO");
			gotoxy(42,16);
			printf("→  EXIT");
			flag1=0;
		}

		if(key1=='\r') {Beep(800,150);gotoxy(40,18);fontcolor(13);break;}
	}

}


void food_f()                      //定义食物的出现函数
{
	srand(time(0));                //设定随机数种子为time(0)
	do
	{
		food_x=rand()%95+2;       //食物横坐标的范围为2到96
	    food_y=rand()%25+5;       //食物纵坐标的范围为5,29

		if(num>0)                 //使食物不出现在蛇的身体上，即食物坐标不能与身体坐标相等          
		{
			for(i=0;i<=num;i++)            
			{
				if(body_x[i]==food_x&&body_y[i]==food_y)            //如果有相等的那么，循环，重新产生
				{	
					flag3=1;break;
				}
				else flag3=0;
			}
		}
		else flag3=0;
	} while(flag3);

	if(food_x%2!=0) food_x++;              //使食物出现的横坐标为偶数，不然有可能吃不到
	gotoxy(food_x,food_y);   
	Beep(600,150);fontcolor(14);           //输出食物
	printf("■");        
}
 
void MOVE()                     //实现蛇的移动函数，最难的地方
{ 
	gotoxy(head_x,head_y);fontcolor(12);printf("●");        //在蛇头前面输出一个
	gotoxy(body_x[num],body_y[num]); printf("  ");           //在蛇尾减去一个
	if(num<=27) Sleep(300-num*10);else Sleep(30);            //使蛇的移动速度改变
	if(num>0)                                                //将蛇身体的后一个坐标与前一个坐标相等，实现移动，关键
	{
		for(i=num;i>=1;i--)
		{
			body_x[i]=body_x[i-1];body_y[i]=body_y[i-1];
		}
	}
}

void JUDGE()                                         //定义吃到食物的判定
{
		if((head_x==food_x)&&(head_y==food_y))
		{
			Beep(100,150);                          //数据发生改变                 
			score+=100;		
			num++;

			if(key2=='w')                           //不同方向吃到食物，坐标变换情况不同
			{
				if(num>1)                           //  num>1和<1的情况有所不同，分开讨论
				{
					body_x[num]=body_x[num-1];      //如果num>1,且从上吃到食物，那么新增的身体的坐标是前一个身体的坐标的纵坐标+1，横坐标不变
					body_y[num]=body_y[num-1]+1;        
				}
				else                               // 如果<1的话，是不变的
				{ 
					body_x[num]=body_x[num-1];                
					body_y[num]=body_y[num-1];
				}
			}
			if(key2=='s')                           //其他情况类似
			{
				if(num>1)
				{	
					body_x[num]=body_x[num-1];
					body_y[num]=body_y[num-1]-1;}
				else
				{
					body_x[num]=body_x[num-1];
					body_y[num]=body_y[num-1];
				}
			}
			if(key2=='a')
			{
				if(num>1)
				{
					body_x[num]=body_x[num-1]+2;
					body_y[num]=body_y[num-1];}
				else
				{
					body_x[num]=body_x[num-1];
					body_y[num]=body_y[num-1];
				}
			}
			if(key2=='d')
			{
				if(num>1)
				{	
					body_x[num]=body_x[num-1]-2;
					body_y[num]=body_y[num-1];}
				else 
				{
					body_x[num]=body_x[num-1];
					body_y[num]=body_y[num-1];
				}
			}

			gotoxy(30,2);                             //刷新得分情况
			fontcolor(2);
			printf("Your Score: %d",score);  
			
			food_f();                                // 使食物再次出现
		}
}

void Snake()                                 //实现蛇的控制，使游戏顺利进行
{
    while(1)
	{

        body_x[0]=head_x;body_y[0]=head_y;     
		if(kbhit()) key2=getch();           //kbhit()函数可以非阻塞的得到一个字符
		switch(key2)                        //蛇的移动方向的控制
		{
			case 'w': head_y--;break;
			case 's': head_y++;break;
			case 'a': head_x-=2;break;
			case 'd': head_x+=2;;break;
		}
		for(i=0;i<=num;i++)               //判断是否碰到自己
		{
			if((head_x==body_x[i])&&(head_y==body_y[i]))
			{	
				flag2=0;
			    break;
			}
		}
		if(head_x==98||head_x==0||head_y==4||head_y==30)     //判断是否撞墙死亡
		{       
				flag2=0;
		}

		MOVE();                    //开始移动
	    JUDGE();
		
		if(flag2==0||num==200)              // 死亡或长度过长的话，退出循环
		{
			flag2=1;
			break;
		}
	}
}

void END()                         //结束函数
{
	
	if(score>=max) max=score;    // 看是否破纪录

	for(i=100;i<=500;i+=100)    //结束音乐     
	{
		Beep(i,200);
	}

	system("cls");       //清屏，画结束界面 
	IF();
	gotoxy(30,15);
	fontcolor(12);
	printf("You dead!   Do you want to continue?");
	gotoxy(40,18);fontcolor(156);
	printf("☆          Yes");
	gotoxy(40,19);fontcolor(2);
	printf("             No");

	while(1)                      //用户选择是否继续游戏
	{
		key3=getch();
		if(key3=='w')
		{
			Beep(800,150);
			gotoxy(40,18);fontcolor(156);printf("☆          Yes");
			gotoxy(40,19);fontcolor(2);printf("             No");
			flag4=1;
		}
		if(key3=='s')
		{
			Beep(800,150);
			gotoxy(40,18);fontcolor(2);printf("            Yes");
			gotoxy(40,19);fontcolor(156);printf("☆           No");
			flag4=0;
		}
		if(key3=='\r') 
		{
			Beep(800,150);
			if(flag4==0)
			{
				gotoxy(35,25);
				fontcolor(13);
				break;
			}
			else                       //继续的话，初始化数据，从来即可
			{
				fresh();
				IF();
				food_f();	
				Snake();                 
				END();                    
			}
		}
	}
}
