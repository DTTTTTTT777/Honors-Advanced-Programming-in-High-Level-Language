#include<iostream>

using namespace std;

class student {
private:
	int num;
	int score;
public:
	void set(int, int);
	void reveal(int);
};
void student::set(int x, int y) {
	num = x, score = y;
}
void student::reveal(int x) {
	cout << "第" << x << "个学生的学号是" << num << "，成绩为" << score << endl;
}

int main() {
	student stu[5];
	student* p = &stu[0];
	for (int i = 0;i < 5;i++, p++) {
		cout << "请输入第" << i + 1 << "个学生的成绩：" << endl;
		int num, score;
		cin >> num >> score;
		p->set(num, score);
	}
	p = &stu[0];
	for (int i = 0;i < 5;i++, p++) {
		if (i % 2 == 1) continue;
		p->reveal(i + 1);
	}
	//delete p;不是动态申请的！不能delete！ 
	cout << "-*程序结束*-" << endl;
	return 0;
}