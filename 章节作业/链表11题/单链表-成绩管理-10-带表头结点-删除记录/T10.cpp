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
}*head, * tail;

int n;

void read() {
	head = new(nothrow) student; //建立表头结点
	if (head == NULL) {
		cout << "申请内存失败";
		exit(0);
	}
	head->next = NULL;
	tail = head;

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
		tail->next = p, tail = p;
	}

	file.close();
}

void print() {
	student* p = head->next, * q;
	const int width = 10;
	while (p != NULL) {
		cout << "学号：" << std::left << setw(width) << (p->no);
		cout << " 姓名：" << std::left << setw(width) << (p->name);
		cout << " 成绩：" << std::left << setw(width) << (p->score) << endl;

		q = p;
		p = p->next;
		delete q;
	}
	delete head;
}

bool iscontinue() {
	char c;
	cout << "是否继续删除？y or n" << endl;
	cin >> c;
	if (c == 'y' || c == 'Y')
		return 1;
	else return 0;
}

pair<student*, student*> searchbyID(int num) {
	student* p = head->next, * last = head;
	while (p != NULL) {
		if (p->no == num)
			return { last,p };
		else
			last = p, p = p->next;
	}
	return { NULL,NULL };
}

void deleteptr(student* last, student* p) {
	last->next = p->next;
	delete p;
}

void sol() {
	int num;
	while (1) {
		cin >> num;
		pair<student*, student*> ot = searchbyID(num);

		if (ot.second == NULL)
			cout << "Not Exist" << endl;
		else deleteptr(ot.first, ot.second);

		if (!iscontinue())
			return;
	}
}

int main() {
	read();
	sol();
	print();

	return 0;
}