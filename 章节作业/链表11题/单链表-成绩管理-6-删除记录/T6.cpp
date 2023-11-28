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
	cout << "ÊÇ·ñ¼ÌÐøÉ¾³ý£¿y or n" << endl;
	cin >> c;
	if (c == 'y' || c == 'Y')
		return 1;
	else return 0;
}

pair<student*, student*> searchbyID(int num) {
	student* p = head, * last = NULL;
	while (p != NULL) {
		if (p->no == num) 
			return { last,p };
		else 
			last=p, p = p->next;
	}
	return { NULL,NULL };
}

void deleteptr(student* last, student* p) {
	if (p == head) 
		head = p->next;
	else 
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