#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

struct student {
	int no;
	char name[20];
	int score;
	struct student* next;
};

int main() {

	ifstream file("d:\\student.txt");
	int n;
	file >> n;

	student* head = NULL, * tail = NULL;

	for (int i = 1;i <= n;i++) {
		student* p=new(nothrow) student;
		if (p == NULL) {
			cout << "申请内存失败";
			return 0;
		}
		file >> (p->no) >> (p->name) >> (p->score);
		p->next = NULL;
		if (head == NULL)
			head = p, tail = p;
		else
			tail->next = p, tail = p;
	}

	file.close();//记得关文件！

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

	return 0;

}