#include <iostream>

using namespace std;

class Student
{
public:
    Student(int n, float s) :num(n), score(s) {}
    void change(int n, float s) { num = n; score = s; }
    void display() { cout << num << " " << score << endl; }
    void fun(Student&);
private:
    int num;
    float score;
};

void Student::fun(Student& stu) {
    display();
    change(stu.num, stu.score);
    display();
}

int main()
{
    Student stud(101, 78.5), stud_change(101, 80.5);
    stud.fun(stud_change);
    return 0;
}
/*
-*Result-*
output:
101 78.5
101 80.5
-*end*-
Analysis:
定义stud和stud_change对象时调用了构造函数：
Student(int n, float s) :num(n), score(s) {}
调用fun函数（change和display操作被移入fun函数中）：
先输出stud的学号与成绩
接着用stud_change的值改变stud的值
最后输出改变后的stud的学号与成绩
*/