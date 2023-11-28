#define _CRT_SECURE_NO_WARNINGS
#include"classes.h"
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<fstream>

using namespace std;

int menu(); //主页面
int menu1(); //进入【开始游戏】后选择游戏模式
void menu2(); //进入【历史记录】后的显示
int button_judge(int x, int y, int r[3][4]);

int button_judge(int x, int y, int r[3][4])
{
	if (x > r[0][0] && x<r[0][2] && y>r[0][1] && y < r[0][3]) return 1;
	if (x > r[1][0] && x<r[1][2] && y>r[1][1] && y < r[1][3]) return 2;
	if (x > r[2][0] && x<r[2][2] && y>r[2][1] && y < r[2][3]) return 3;
	return 0;
}

int menu() {
	initgraph(1200, 800);
	for (int i = 0;i < 256;i += 5)
	{
		setbkcolor(RGB(i, i, i));//设置背景色，原来默认黑色
		cleardevice();//清屏（取决于背景色）
		Sleep(15);//延时15ms
	}
	IMAGE title;
	loadimage(&title, _T("./image./1.jpg"), 700, 300);
	putimage(600 - 350, 0, &title);

	IMAGE pic;
	loadimage(&pic, _T("./image./dtt.jpg"), 140*1.2, 40*1.2);
	putimage(1000, 745, &pic);

	int butt[3][4] = { {380,280,820,430},{380,440,820,590},{380,600,820,750} };
	int r[3][4];
	for (int i = 0;i < 3;i++) {
		r[i][0] = butt[i][0] + 45;
		r[i][1] = butt[i][1] + 20;
		r[i][2] = butt[i][2] - 45;
		r[i][3] = butt[i][3] - 20;
	}
	RECT R1 = { butt[0][0],butt[0][1],butt[0][2],butt[0][3] }; //矩形指针 
	RECT R2 = { butt[1][0],butt[1][1],butt[1][2],butt[1][3] };
	RECT R3 = { butt[2][0],butt[2][1],butt[2][2],butt[2][3] };
	LOGFONT f; //字体样式指针
	gettextstyle(&f); //获取字体样式 （？没太懂
	_tcscpy(f.lfFaceName, _T("楷体")); //设置字体为宋体
	//_tcscpy(f.lfFaceName, _T("bold"));
	f.lfHeight = 40, f.lfWeight = 133; //设置字体大小
	f.lfQuality = ANTIALIASED_QUALITY; //设置输出效果为抗锯齿
	settextstyle(&f); //设置字体样式
	settextcolor(BLACK);
	drawtext(_T("开始游戏"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("继续游戏"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R2内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("历史记录"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R3内输入文字，水平居中，垂直居中，单行显示
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	MOUSEMSG m; //鼠标指针
	int event = 0, jud = 0;
	while (1) {
		m = GetMouseMsg(); //获取一条鼠标消息
		switch (m.uMsg) {
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//亮青色
			setlinestyle(PS_SOLID, 3);
			setfillcolor(WHITE);
			jud = button_judge(m.x, m.y, r);
			if (jud != 0) {
				if (event != jud) {
					event = jud;
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);
				}
			}
			else if (event != 0) {//上次触发的按钮未被修正为原来的颜色
				fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//两次同或为原来颜色
				event = 0;
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (int i = 0;i <= 10;i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(30);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}
			jud = button_judge(m.x, m.y, r);
			if (jud == 1) {
				cleardevice();
				return menu1();
			}
			else if (jud == 2) return 4;
			else if (jud == 3) {
				cleardevice();
				menu2(); 
				return 0;
			}
			break;
			FlushMouseMsgBuffer();//清空鼠标消息缓存区
		}
	}
	setrop2(R2_COPYPEN);
}
int menu1() {
	int butt[3][4] = { {0,0,400,250},{0,250,400,500},{0,500,400,750} };
	int r[3][4];
	for (int i = 0;i < 3;i++) {
		r[i][0] = butt[i][0] + 65;
		r[i][1] = butt[i][1] + 60;
		r[i][2] = butt[i][2] - 65;
		r[i][3] = butt[i][3] - 60;
	}
	RECT R1 = { butt[0][0],butt[0][1],butt[0][2],butt[0][3] }; //矩形指针 
	RECT R2 = { butt[1][0],butt[1][1],butt[1][2],butt[1][3] };
	RECT R3 = { butt[2][0],butt[2][1],butt[2][2],butt[2][3] };
	LOGFONT f; //字体样式指针
	gettextstyle(&f); //获取字体样式 （？没太懂
	//wcscpy_s(f.lfFaceName, _T("楷体"));
	_tcscpy(f.lfFaceName, _T("楷体")); //设置字体为楷体
	//_tcscpy(f.lfFaceName, _T("bold"));
	f.lfHeight = 40, f.lfWeight = 133; //设置字体大小
	f.lfQuality = ANTIALIASED_QUALITY; //设置输出效果为抗锯齿
	settextstyle(&f); //设置字体样式
	settextcolor(BLACK);
	drawtext(_T("入门版"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("进阶版"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R2内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("高级版"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R3内输入文字，水平居中，垂直居中，单行显示
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	IMAGE pic, pic1;
	loadimage(&pic, _T("./image./2.jpg"), 800, 250);
	putimage(400 - 32, 0, &pic);

	loadimage(&pic, _T("./image./3.jpg"), 800, 250);
	putimage(400 - 32, 245, &pic);

	loadimage(&pic, _T("./image./4.jpg"), 800, 250);
	putimage(400 - 32, 495, &pic);

	//loadimage(&pic1, _T("./image./Esc.jpg"), 700*0.4, 200*0.4);
	//putimage(900, 750, &pic1);



	MOUSEMSG m; //鼠标指针
	int event = 0, jud = 0;
	while (1) {
		m = GetMouseMsg(); //获取一条鼠标消息
		switch (m.uMsg) {
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//亮青色
			setlinestyle(PS_SOLID, 3);
			setfillcolor(WHITE);
			jud = button_judge(m.x, m.y, r);
			if (jud != 0) {
				if (event != jud) {
					event = jud;
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);
				}
			}
			else if (event != 0) {//上次触发的按钮未被修正为原来的颜色
				fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//两次同或为原来颜色
				event = 0;
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (int i = 0;i <= 10;i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(30);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}
			jud = button_judge(m.x, m.y, r);
			if (jud != 0) return jud;
			break;
			FlushMouseMsgBuffer();//清空鼠标消息缓存区
		}
	}
}
void menu2() {
	IMAGE pic1;
	loadimage(&pic1, _T("./image./Esc.jpg"), 700*0.4, 200*0.4);
	putimage(900, 750, &pic1);

	ifstream fl("./file./game_record.txt", ios::app);
	int ry[2] = { 0,50 }, rx[2] = { 0,100 };
	while (!fl.eof()) {
		int type, score;
		if (!(fl >> type >> score))break;
		LOGFONT f; //字体样式指针
		gettextstyle(&f); //获取字体样式 （？没太懂
		_tcscpy(f.lfFaceName, _T("楷体")); //设置字体为宋体
		//_tcscpy(f.lfFaceName, _T("bold"));
		//f.lfHeight = 40, f.lfWeight = 133; //设置字体大小
		//f.lfQuality = ANTIALIASED_QUALITY; //设置输出效果为抗锯齿
		settextstyle(&f); //设置字体样式
		settextcolor(BLACK);
		char str[15] = "", number[15] = { '0','1','2','3','4','5','6','7','8','9','\0' };

		int cur = 9, tmp = score;
		while (cur != 0 && (int)(score / pow(10, cur)) == 0)cur--;
		for (int i = cur;i >= 0;i--) {
			strncat(str, number + (int)(tmp / (int)pow(10, i)), 1);
			tmp %= (int)pow(10, i);
		}

		int num = MultiByteToWideChar(0, 0, str, -1, NULL, 0);
		wchar_t* wide = new wchar_t[num];
		MultiByteToWideChar(0, 0, str, -1, wide, num);
		/*num 获得长字节所需的空间
		MultiByteToWideChar()表示将s中的字符传递到ps指向的内存中。-1表示传输至s中的'\0'处，num表示传递的字节个数。*/

		RECT R1 = { rx[0], ry[0], rx[1], ry[1] };
		RECT R2 = { rx[0] + 100, ry[0], rx[1] + 200, ry[1] };
		RECT R3 = { rx[0] + 300, ry[0], rx[1] + 300, ry[1] };
		RECT R4 = { rx[0] + 400, ry[0], rx[1] + 400, ry[1] };
		drawtext(_T("版本："), &R1, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		if (type == 1)drawtext(_T("入门版"), &R2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		if (type == 2)drawtext(_T("进阶版"), &R2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		if (type == 3)drawtext(_T("高级版"), &R2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("得分："), &R3, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		drawtext((LPCTSTR)wide, &R4, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		ry[0] += 52  , ry[1] += 52;
	}

	while (Keyboard_monitor(0, 0) != 27); //按Esc退出页面
}
