#include<iostream>
#include<fstream>
#include<iomanip>
#include<utility>
using namespace std;

struct student {
	int no;
	char name[20];
	int score;
	struct student* next;
}*head = NULL, * tail = NULL;

int n;

void read() {
	ifstream file("d:\\student.txt");
	file >> n;

	for (int i = 1;i <= n;i++) {
		student* p = new(nothrow) student;
		if (p == NULL) {
			cout << "申请内存失败";
			exit(0);
		}
		file >> (p->no) >> (p->name) >> (p->score);
		p->next = NULL;
		if (head == NULL)
			head = p, tail = p;
		else
			tail->next = p, tail = p;
	}

	file.close();
}

void print() {
	student* p = head, * q;
	const int width = 10;
	while (p != NULL) {
		cout << "学号：" << std::left << setw(width) << (p->no);
		cout << " 姓名：" << std::left << setw(width) << (p->name);
		cout << " 成绩：" << std::left << setw(width) << (p->score) << endl;

		q = p;
		p = p->next;
		delete q;
	}
}

void stu_swap(student* p1, student* p2, student* p3) {
	if (p2 == head)
		head = p3;
	else p1->next = p3;
	p2->next = p3->next;
	p3->next = p2;
}

void sort1(student* last, student* cur, int num, int done) {
	if (num >= n - done)
		return;
	student* next = cur->next;
	if ((cur->score < next->score) || (cur->score == next->score && cur->no > next->no)) {
		stu_swap(last, cur, next);
		swap(cur, next); //这两个交换都必不可少！！
	}
	sort1(cur, next, num + 1, done);
}

void sort() {
	int done = 0;
	while (done < n) {
		sort1(NULL, head, 1, done);
		done++;
	}
}

bool iscontinue() {
	char c;
	cout << "是否继续添加？y or n" << endl;
	cin >> c;
	if (c == 'y' || c == 'Y')
		return 1;
	else return 0;
}

student* searchbyID(int num) {
	student* p = head;
	while (p != NULL) {
		if (p->no == num)
			return p;
		else
			p = p->next;
	}
	return NULL;
}

void addnode(int num) {
	student* p = new(nothrow) student;
	if (p == NULL) {
		cout << "申请内存失败";
		exit(0);
	}
	p->no = num;
	cin >> (p->name) >> (p->score);
	p->next = NULL;
	if (head == NULL)
		head = p, tail = p;
	else
		tail->next = p, tail = p;
	n++;
}

void sol() {
	int num;
	while (1) {
		cin >> num;
		student* p = searchbyID(num);
		if (p != NULL)
			cout << "Existed" << endl;
		else
			addnode(num);
		if (!iscontinue())
			return;
	}
}

int main() {
	read();
	sol();
	sort();
	print();

	return 0;
}