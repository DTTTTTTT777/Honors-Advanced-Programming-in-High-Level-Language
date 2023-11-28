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
			cout << "ÉêÇëÄÚ´æÊ§°Ü";
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
		cout << "Ñ§ºÅ£º" << std::left << setw(width) << (p->no);
		cout << " ÐÕÃû£º" << std::left << setw(width) << (p->name);
		cout << " ³É¼¨£º" << std::left << setw(width) << (p->score) << endl;

		q = p;
		p = p->next;
		delete q;
	}
}

bool iscontinue() {
	char c;
	cout << "ÊÇ·ñ¼ÌÐøÐÞ¸Ä£¿y or n" << endl;
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

void sol() {
	int num;
	while (1) {
		cin >> num;
		student* p = searchbyID(num);

		if (p == NULL)
			cout << "Not Exist" << endl;
		else {
			int newscore;
			cin >> newscore;
			p->score = newscore;
		}

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