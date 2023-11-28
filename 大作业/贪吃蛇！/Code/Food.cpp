#include"classes.h"
#include<iostream>
#include<fstream>

using namespace std;

Food::Food(Game& G) {
	head = NULL, tail = NULL;
	destructed = 0;
	int num = rand() % 5 + 1;
	while (num--) {
		int x = rand() % 38 + 1, y = rand() % 38 + 1;
		while (G.query(x, y) != 0)
			x = rand() % 38 + 1, y = rand() % 38 + 1;
		append(x, y, G);
	}
}
void Food::append(int x, int y, Game& G) {
	coor* p = new coor;
	p->x = x, p->y = y;
	if (head == NULL)
		head = p, tail = p;
	else
		tail->next = p, p->last = tail, tail = p;
	tail->next = NULL;
	G.upd_map(x, y, 2);
}
coor* Food::food_head() {
	return head;
}
void Food::remove(int x, int y, Game& G) {
	coor* p = head;
	while (!(p->x == x && p->y == y)) p=p->next;
	G.upd_map(x, y, 0); //将食物的部分擦白
	if (p == head && p == tail) {
		head = NULL, tail = NULL;
		delete p;
		//cout << "吃完食物啦" << endl;
		new_food(G);
	}
	else if (p == head) {
		head = p->next;
		p->next->last = NULL;
		delete p;
	}
	else if (p == tail) {
		tail = p->last;
		p->last->next = NULL;
		delete p;
	}
	else {
		p->last->next = p->next;
		p->next->last = p->last;
		delete p;
	}
}
void Food::new_food(Game& G) {
	int num = rand() % 5 + 1;
	while (num--) {
		int x = rand() % 40, y = rand() % 40;
		while (G.query(x, y) != 0)
			x = rand() % 40, y = rand() % 40;
		append(x, y, G);
	}
}
Food::~Food() {
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
		cout << "Food over" << endl;
	}
	destructed = 1;
}
Food::Food(istream& in, Game& G) {
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