#define _CRT_SECURE_NO_WARNINGS
#include"classes.h"
#include<iostream>
#include<graphics.h>
#include<fstream>

using namespace std;

Game::Game(int md) {
	mode = md;
	lives = 6;
	score = -5;
	destructed = 0;
	blank = 1600;
	for (int i = 0;i < 40;i++)
		for (int j = 0;j < 40;j++)
			map[i][j] = 0;

	ifstream ifl;
	if (mode == 1) ifl.open("./file./max1.txt");
	if (mode == 2) ifl.open("./file./max2.txt");
	if (mode == 3) ifl.open("./file./max3.txt");
	ifl >> maxs;
	ifl.close();
}
int Game::query(int x, int y) {
	return map[x][y];
}
void Game::upd_map(int x, int y, int type) {
	if (map[x][y] == 0 && type != 0) --blank;
	if (map[x][y] != 0 && type == 0) ++blank;
	map[x][y] = type;
	upd_view(x, y, type);
}
void Game::upd_view(int x, int y, int type) {
	setrop2(R2_COPYPEN);
	//if(type==0)cout << "x=" << x << "  y=" << y << " type=" << type << endl;
	IMAGE pic;
	switch(type) {
	case 0://空白
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		fillrectangle(x * 20, y * 20, x * 20 + 19, y * 20 + 19);
			break;
	case 1: //墙
		setlinecolor(RGB(123, 123, 123));
		setfillcolor(RGB(123, 123, 123));
		fillrectangle(x * 20, y * 20, x * 20 + 19, y * 20 + 19);
			break;
	case 2: //食物
		loadimage(&pic, _T("./image/bread.jpg"), 20, 20);
		putimage(x * 20, y * 20, &pic);
		break;
	case 3: //蛇
		setlinecolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(x * 20 + 9.5, y * 20 + 9.5, 9.5);
		break;


	}
}
void Game::show_UI() {
	if (mode == 1) {
		IMAGE pic1, pic2, pic3, pic4, pic5, pic6, pic7;
		loadimage(&pic1, _T("./image/UI1.jpg"), 250, 125);
		putimage(800 + 60, 0, &pic1);
		loadimage(&pic2, _T("./image/UI4.jpg"), 150, 75); //如果这里还用pic会有问题
		putimage(800 + 10, 200, &pic2);
		loadimage(&pic3, _T("./image/ctrl.jpg"), 150, 150);
		putimage(800 + 30, 600, &pic3);
		loadimage(&pic4, _T("./image/begin.jpg"), 196, 56);
		putimage(800 + 30, 737, &pic4);
		loadimage(&pic5, _T("./image/Esc.jpg"), 196*1.06, 56*1.06);
		putimage(800 + 40, 770, &pic5);
		loadimage(&pic6, _T("./image/speed.jpg"), 196 * 1.2, 56 * 1.2);
		putimage(800 + 195, 668, &pic6);
		//loadimage(&pic7, _T("./image/time.jpg"), 196 * 0.8, 56 * 0.8);
		//putimage(800 + 48, 265, &pic7);
		add_score();
	}
	else if (mode == 2) {
		IMAGE pic1, pic2, pic3, pic4, pic5, pic6, pic7;
		loadimage(&pic1, _T("./image/UI2.jpg"), 250, 125);
		putimage(800 + 60, 0, &pic1);
		loadimage(&pic2, _T("./image/UI4.jpg"), 150, 75); //如果这里还用pic会有问题
		putimage(800 + 10, 200, &pic2);
		loadimage(&pic3, _T("./image/ctrl.jpg"), 150, 150);
		putimage(800 + 30, 600, &pic3);
		loadimage(&pic4, _T("./image/begin.jpg"), 196, 56);
		putimage(800 + 30, 737, &pic4);
		loadimage(&pic5, _T("./image/Esc.jpg"), 196 * 1.06, 56 * 1.06);
		putimage(800 + 40, 770, &pic5);
		loadimage(&pic6, _T("./image/speed.jpg"), 196 * 1.2, 56 * 1.2);
		putimage(800 + 195, 668, &pic6);
		//loadimage(&pic7, _T("./image/time.jpg"), 196 * 0.8, 56 * 0.8);
		//putimage(800 + 48, 265, &pic7);
		add_score();
	}
	else if (mode = 3) { //加上生命值的显示喔！
		IMAGE pic1, pic2, pic3, pic4, pic5, pic6, pic7, pic8;
		loadimage(&pic1, _T("./image/UI3.jpg"), 250, 125);
		putimage(800 + 60, 0, &pic1);
		loadimage(&pic2, _T("./image/UI4.jpg"), 150, 75); //如果这里还用pic会有问题
		putimage(800 + 10, 200, &pic2);
		loadimage(&pic3, _T("./image/ctrl.jpg"), 150, 150);
		putimage(800 + 30, 600, &pic3);
		loadimage(&pic4, _T("./image/begin.jpg"), 196, 56);
		putimage(800 + 30, 737, &pic4);
		loadimage(&pic5, _T("./image/left.jpg"), 196 * 1.17, 56 * 1.17);
		putimage(800 + 40, 265, &pic5);
		loadimage(&pic6, _T("./image/Esc.jpg"), 196 * 1.06, 56 * 1.06);
		putimage(800 + 40, 770, &pic6);
		loadimage(&pic7, _T("./image/speed.jpg"), 196 * 1.2, 56 * 1.2);
		putimage(800 + 195, 668, &pic7);
		//loadimage(&pic8, _T("./image/time.jpg"), 196 * 0.8, 56 * 0.8);
		//putimage(800 + 48, 322, &pic8);
		add_score();
		die();
	}
}
void Game::add_score() {
	score += 5;
	LOGFONT f; //字体样式指针
	gettextstyle(&f); //获取字体样式 （？没太懂
	_tcscpy(f.lfFaceName, _T("Comic Sans MS")); //设置字体
	settextstyle(&f); //设置字体样式
	settextcolor(BLACK);
	f.lfHeight = 10, f.lfWeight = 10; //设置字体大小

	char str[15] = "", number[15] = { '0','1','2','3','4','5','6','7','8','9','\0' };
	int cur = 9, tmp=score;
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
	RECT R = { 938,200,1101,275 };
	drawtext((LPCTSTR)wide, &R, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	if (maxs < score) maxs = score;
	IMAGE pic;
	loadimage(&pic, _T("./image/max.jpg"), 196 * 1.25, 56 * 1.25);
	putimage(800 + 45, 380, &pic);

	strcpy(str, "");
	cur = 9, tmp = maxs;
	while (cur != 0 && (int)(tmp / pow(10, cur)) == 0)cur--;
	for (int i = cur;i >= 0;i--) {
		strncat(str, number + (int)(tmp / (int)pow(10, i)), 1);
		tmp %= (int)pow(10, i);
	}

	num = MultiByteToWideChar(0, 0, str, -1, NULL, 0);
	wide = new wchar_t[num];
	MultiByteToWideChar(0, 0, str, -1, wide, num);
	/*num 获得长字节所需的空间
	MultiByteToWideChar()表示将s中的字符传递到ps指向的内存中。-1表示传输至s中的'\0'处，num表示传递的字节个数。*/

	RECT R1 = { 835,450,1100,490 };
	drawtext((LPCTSTR)wide, &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}
int Game::get_score() {
	return score;
}
void Game::die() {
	lives--;
	char number[10] = { '0','1','2','3','4','5','\0' };
	char ch = number[lives];

	RECT R = { 1080,260.5,1080+19*1.17,260.5 + 56 * 1.17 };
	LOGFONT f; //字体样式指针
	gettextstyle(&f); //获取字体样式 （？没太懂
	_tcscpy(f.lfFaceName, _T("Comic Sans MS")); //设置字体
	settextstyle(&f); //设置字体样式
	settextcolor(BLACK);
	f.lfHeight = 10, f.lfWeight = 10; //设置字体大小

	drawtext(ch, &R, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

}
bool Game::over() {
	if (lives == 0 || blank < 5) return 1;
	return 0;
}
int Game::get_mode() {
	return mode;
}
void Game::set_mode(int x) {
	mode = x;
}
Game::~Game() {
	if (!destructed) {
		ofstream fl("./file./record.txt", ios::app);
		if (!fl.is_open()) {
			cout << "文件打开失败" << endl;
			exit(1);
		}
		fl << mode << " " << lives << " " << score << endl;
		fl.close();
		fl.open("./file./game_record.txt", ios::app);
		if (!fl.is_open()) {
			cout << "文件打开失败" << endl;
			exit(1);
		}
		fl << mode << " " << score << endl;
		fl.close();
		ifstream ifl;
		if (mode == 1) ifl.open("./file./max1.txt");
		if (mode == 2) ifl.open("./file./max2.txt");
		if (mode == 3) ifl.open("./file./max3.txt");
		if (!ifl.is_open()) {
			cout << "文件打开失败" << endl;
			exit(1);
		}
		int cur;
		ifl >> cur;
		ifl.close();
		if (cur < score){
			if (mode == 1) fl.open("./file./max1.txt");
			if (mode == 2) fl.open("./file./max2.txt");
			if (mode == 3) fl.open("./file./max3.txt");
			if (!fl.is_open()) {
				cout << "文件打开失败" << endl;
				exit(1);
			}
			fl << score;
		}
		fl.close();
		//cout << "maxs" << maxs << endl << "Game over" << endl;

	}
	destructed = 1;
}
Game::Game(istream& in) {
	in >> mode >> lives >> score;
	lives += 1, score -= 5;
	destructed = 0;
	blank = 1600;
	for (int i = 0;i < 40;i++)
		for (int j = 0;j < 40;j++)
			map[i][j] = 0;

	ifstream ifl;
	if (mode == 1) ifl.open("./file./max1.txt");
	if (mode == 2) ifl.open("./file./max2.txt");
	if (mode == 3) ifl.open("./file./max3.txt");
	ifl >> maxs;
	ifl.close();
}