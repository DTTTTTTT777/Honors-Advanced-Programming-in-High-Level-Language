#include"classes.h"
#include<iostream>
#include<fstream>

using namespace std;

Wall::Wall(Game& G) {
	head = NULL, tail = NULL;
	destructed = 0;
	for (int i = 0;i < 40;i++) {
		append(0, i, G);
		append(39, i, G);
		append(i, 0, G);
		append(i, 39, G);
	}
}
void Wall::append(int x, int y, Game& G) {
	coor* p = new coor;
	p->x = x, p->y = y;
	if (head == NULL)
		head = p, tail = p;
	else
		tail->next = p, p->last=tail, tail = p;
	tail->next = NULL;
	G.upd_map(x, y, 1);
}
coor* Wall::wall_head() {
	return head;
}
Wall::~Wall() {
	if (!destructed) {
		ofstream fl("./file./record.txt", ios::app);
		if (!fl.is_open()) {
			cout << "文件打开失败" << endl;
			exit(1);
		}
		coor* p = head, * q;
		while (p != NULL) {
			fl << p->x << " " << p->y << " ";
			q = p;
			p = p->next;
			delete q;
		}
		fl << "-1" << endl;
		fl.close();
		cout << "Wall over" << endl;
	}
	destructed = 1;
}
Wall::Wall(istream& in, Game& G) {
	head = NULL, tail = NULL;
	destructed = 0;
	int x, y;
	while (1) {
		in >> x;
		if (x == -1) break;
		in >> y;
		append(x, y, G);
	}
}