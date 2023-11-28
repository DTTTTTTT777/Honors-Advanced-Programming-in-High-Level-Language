#include <iostream>  
#include <iomanip>     
#include <graphics.h>  
#include <math.h>  
#include <conio.h>  
#include <time.h>  
using namespace std;
const double Pi = 3.1415926;
struct tm t;
time_t now;
struct coordinate {
	int x, y;
};
void drawtxt(char* str, RECT r) {
	drawtext(*str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void init() {
	//设置画布颜色：
	initgraph(640, 480);
	setbkcolor(RGB(253, 245, 230));
	cleardevice();

	//画表盘：
	setfillcolor(RGB(255, 235, 205));
	fillcircle(320, 240, 150);

	//画时钟指针中间小圆：
	setfillcolor(RGB(235, 141, 76));
	fillcircle(320, 240, 5);

	//写表盘上的数字：
	settextcolor(RGB(235, 112, 76));
	drawtxt((char*)"1", { 310,95,320,105 });
	drawtxt((char*)"2", { 320,95,330,105 });
	drawtxt((char*)"6", { 310,385,330,375 });
	drawtxt((char*)"9", { 175,230,185,250 });
	drawtxt((char*)"3", { 465,230,455,250 });

	//画刻度：
	setfillcolor(RGB(235, 112, 76));
	for (int i = 1;i <= 12;i++) {
		if (i % 3 == 0)continue;
		double x = 320 + 140 * sin(i / 6.0 * Pi);
		double y = 240 - 140 * cos(i / 6.0 * Pi);
		fillcircle((int)x, (int)y, 3);
	}
	for (int i = 1;i <= 60;i++) {
		if (i % 5 == 0)continue;
		double x = 320 + 141 * sin(i / 30.0 * Pi);
		double y = 240 - 141 * cos(i / 30.0 * Pi);
		fillcircle((int)x, (int)y, 2.2);
	}
}
int squdis(coordinate n1, coordinate n2) {
	return (n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y);
}

COLORREF mixcolor(COLORREF col1, COLORREF col2, double alpha) { //混合颜色!
	int R, G, B;
	R = GetRValue(col1) * (1 - alpha) + GetRValue(col2) * alpha;
	G = GetGValue(col1) * (1 - alpha) + GetGValue(col2) * alpha;
	B = GetBValue(col1) * (1 - alpha) + GetBValue(col2) * alpha;
	return RGB(R, G, B);
}

//SDF抗锯齿
void SDF_line(coordinate n1, coordinate n2, double width, COLORREF line_col, COLORREF back_col)
{
	const int range = 10;
	int minx = min(n1.x, n2.x), maxx = max(n1.x, n2.x);
	int miny = min(n1.y, n2.y), maxy = max(n1.y, n2.y);
	for (int i = minx - range;i <= maxx + range;i++)
		for (int j = miny - range;j <= maxy + range;j++) {
			coordinate n0 = { i,j };
			double h = 1.0 * ((n1.x - i) * (n1.x - n2.x) + (n1.y - j) * (n1.y - n2.y)) / (squdis(n1, n2));
			if (h < 0 || h>1) {
				double d1 = sqrt(squdis(n0, n1)), d2 = sqrt(squdis(n0, n2));
				h = min(d1, d2);
			}
			double d = sqrt(squdis(n0, n1) - h * h * (squdis(n1, n2))) - width;
			if (h < 0 || h>1)d += width;
			double alpha = 0.5 - d;
			back_col = getpixel(i, j);
			if (d < 0) putpixel(i, j, line_col);
			else if (alpha >= 0 && alpha <= 1)
				putpixel(i, j, mixcolor(back_col, line_col, alpha));
		}
}
void draw() {

	static int lastsec = -1, lastmin = -1;
	if (t.tm_sec == lastsec)return; //防止不必要的更新指针导致闪烁
	lastsec = t.tm_sec;

	//定义一些静态变量来存上一次时钟指针的位置
	static struct coordinate sec = { 320,240 }, min = { 320,240 }, hour = { 320,240 };

	//画秒针
	setcolor(RGB(255, 235, 205));
	setlinestyle(PS_SOLID, 2);
	line(320, 240, sec.x, sec.y);//擦除上一条秒针
	sec.x = 320 + 120 * sin(t.tm_sec / 60.0 * 2 * Pi);
	sec.y = 240 - 120 * cos(t.tm_sec / 60.0 * 2 * Pi);

	setlinestyle(PS_SOLID, 2);
	setcolor(RGB(235, 112, 76));
	//SDF_line({ 320,240 }, sec, 0.8, RGB(235, 112, 76), RGB(255, 235, 205));
	line(320, 240, sec.x, sec.y);//画新秒针

	setfillcolor(RGB(235, 141, 76));//补上因为擦去旧秒针造成的中间圆缺失
	fillcircle(320, 240, 5);

	if (t.tm_min == lastmin) {//如果分针不用更新，则再画一次上一个分针与时针【是为了防止因擦去旧秒针而造成其他指针部分缺失】
		setcolor(RGB(235, 112, 76));
		setlinestyle(PS_SOLID, 3);
		line(320, 240, min.x, min.y);

		setlinestyle(PS_SOLID, 4);
		setcolor(RGB(235, 112, 76));
		line(320, 240, hour.x, hour.y);
		return;
	}
	lastmin = t.tm_min;

	//画新分针：
	setcolor(RGB(255, 235, 205));
	setlinestyle(PS_SOLID, 3);
	line(320, 240, min.x, min.y);//擦去旧分针

	min.x = 320 + 100 * sin(1.0 * t.tm_min / 60.0 * 2 * Pi);
	min.y = 240 - 100 * cos(1.0 * t.tm_min / 60.0 * 2 * Pi);

	setlinestyle(PS_SOLID, 3);
	setcolor(RGB(235, 112, 76));
	line(320, 240, min.x, min.y);//画新分针

	//画时针（无论新旧），此处已经保证一分钟更新一次，不会有闪烁现象
	setcolor(RGB(255, 235, 205));
	setlinestyle(PS_SOLID, 4);
	line(320, 240, hour.x, hour.y);//擦去旧时针

	hour.x = 320 + 70 * sin(t.tm_hour % 12 / 12.0 * 2 * Pi + t.tm_min / 360.0 * Pi);
	hour.y = 240 - 70 * cos(t.tm_hour % 12 / 12.0 * 2 * Pi + t.tm_min / 360.0 * Pi);

	setlinestyle(PS_SOLID, 4);
	setcolor(RGB(235, 112, 76));
	line(320, 240, hour.x, hour.y);//画新时针

}
int main()
{
	//初始化表盘
	init();

	while (!_kbhit()) {
		//获取当前时间
		time(&now);
		localtime_s(&t, &now);
		//根据当前时间画出指针
		draw();
	}
	closegraph();
	return 0;
}