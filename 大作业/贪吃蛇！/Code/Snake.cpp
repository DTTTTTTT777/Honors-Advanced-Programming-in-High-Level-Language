#include"classes.h"
#include<iostream>
#include<fstream>

using namespace std;

int tx[4] = { 1,-1,0,0 }, ty[4] = { 0,0,1,-1 };
Snake::Snake(Game& G) {
	head = NULL, tail = NULL;
	destructed = 0;
	removed_x = -1, removed_y = -1;
	int x, y;
	while (1) {
		x = rand() % 40, y = rand() % 40, dir = rand() % 4;
		if (G.query(x, y) != 0) continue;
		if (G.query(x + tx[dir], y + ty[dir]) != 0) continue;
		if (G.query(x + tx[dir] * 2, y + ty[dir] * 2) != 0) continue;
		append(x, y, G);
		append(x + tx[dir], y + ty[dir], G);
		append(x + tx[dir] * 2, y + ty[dir] * 2, G);
		break;
	}
	if (dir == 0)dir = 1;
	else if (dir == 1)dir = 0;
	else if (dir == 2)dir = 3;
	else if (dir == 3)dir = 2;
}
void Snake::append(int x, int y, Game& G) {
	coor* p = new coor;
	p->x = x, p->y = y;
	if (head == NULL)
		head = p, tail = p;
	else
		tail->next = p, p->last=tail, tail = p;
	tail->next = NULL;
	G.upd_map(x, y, 3);
}
coor* Snake::snake_head() {
	return head;
}
void Snake::move(int t, Game& G) {
	if (t == -1) t = dir;
	else dir = t;

	removed_x = tail->x, removed_y = tail->y;
	G.upd_map(tail->x, tail->y, 0);
	coor* tmp = tail;
	tail = tail->last;
	tail->next = NULL;
	delete tmp;  //	去掉尾部，下面开始增加头部

	int hx = head->x, hy = head->y;
	int dx = hx + tx[t], dy = hy + ty[t];
	coor* cur = new coor;
	cur->x = dx, cur->y = dy;
	cur->next = head, head->last = cur;
	head = cur;
}
void Snake::recover(Game& G) {
	append(removed_x, removed_y, G);
}
bool Snake::reset(Game& G, Food& F,Wall& W,int type) {
	coor* p = head, * q;
	while (p != NULL) {
		q = p->next;
		if (p != head) {
			G.upd_map(p->x, p->y, 0); //进行一些擦白
			if (type == 1) W.append(p->x, p->y, G);
			else if (type == 2) F.append(p->x, p->y, G);
		}
		delete p;
		p = q;
	}
	//先判断剩余空间能不能生成新的小蛇！
	bool ade = 0; //是否有足够的空间
	for (int i = 0;i < 40;i++) {
		for (int j = 0;j < 40 - 2;j++) {
			if (G.query(i, j) == 0 && G.query(i, j + 1) == 0 && G.query(i, j + 2) == 0) {
				ade = 1;
				break;
			}
		}
		if (ade == 1) break;
	}
	if (!ade) {
		for (int j = 0;j < 40;j++) {
			for (int i = 0;i < 40 - 2;i++) {
				if (G.query(i, j) == 0 && G.query(i + 1, j) == 0 && G.query(i + 2, j) == 0) {
					ade = 1;
					break;
				}
			}
			if (ade == 1)break;
		}
	}
	if (!ade)return 0;
	//-----------进行一些构造函数的复制粘贴来生成新的小蛇------------
	head = NULL, tail = NULL;
	int x, y;
	while (1) {
		x = rand() % 40, y = rand() % 40, dir = rand() % 4;
		if (G.query(x, y) != 0) continue;
		if (G.query(x + tx[dir], y + ty[dir]) != 0) continue;
		if (G.query(x + tx[dir] * 2, y + ty[dir] * 2) != 0) continue;
		append(x, y, G);
		append(x + tx[dir], y + ty[dir], G);
		append(x + tx[dir] * 2, y + ty[dir] * 2, G);
		break;
	}
	if (dir == 0)dir = 1;
	else if (dir == 1)dir = 0;
	else if (dir == 2)dir = 3;
	else if (dir == 3)dir = 2;
	return 1;
}
int Snake::get_dir() {
	return dir;
}
Snake::~Snake() {
	if (!destructed) {
		ofstream fl("./file./record.txt", ios::app);
		if (!fl.is_open()) {
			cout << "文件打开失败" << endl;
			exit(1);
		}
		fl << dir << " " << removed_x << " " << removed_y << endl;
		coor* p = head, * q;
		while (p != NULL) {
			fl << p->x << " " << p->y << " ";
			q = p;
			p = p->next;
			delete q;
		}
		fl << "-1" << endl;
		fl.close();
		cout << "Snake over" << endl;
	}
	destructed = 1;
}
Snake::Snake(istream& in, Game& G) {
	head = NULL, tail = NULL;
	destructed = 0;
	in >> dir >> removed_x >> removed_y;
	int x, y;
	while (1) {
		in >> x;
		if (x == -1) break;
		in >> y;
		append(x, y, G);
	}
}