#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

struct student {
	int no;
	char name[20];
	int score;
	struct student* next;
}*head = NULL, * tail = 0;

int n, ans[6];

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

void calc() {
	student* p = head, * q;
	while (p != NULL) {
		int score = p->score;
		if (score >= 90)
			ans[1]++;
		else if (score >= 80)
			ans[2]++;
		else if (score >= 70)
			ans[3]++;
		else if (score >= 60)
			ans[4]++;
		else
			ans[5]++;

		q = p;
		p = p->next;
		delete q;
	}
}

void print() {
	const int width = 10;
	cout << std::left << setw(width) << "优：" << setw(width) << ans[1] << endl;
	cout << std::left << setw(width) << "良：" << setw(width) << ans[2] << endl;
	cout << std::left << setw(width) << "中：" << setw(width) << ans[3] << endl;
	cout << std::left << setw(width) << "及格：" << setw(width) << ans[4] << endl;
	cout << std::left << setw(width) << "不及格：" << setw(width) << ans[5] << endl;
}

int main() {
	read();
	calc();
	print();

	return 0;
}