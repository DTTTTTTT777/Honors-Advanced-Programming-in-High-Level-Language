#include <iostream>

using namespace std;

class Student
{
public:
    Student(int n, float s) :num(n), score(s) {}
    void change(int n, float s) { num = n; score = s; }
    void display() { cout << num << " " << score << endl; }
private:
    int num;
    float score;
};

int main()
{
    Student stud(101, 78.5);
    stud.display();
    stud.change(101, 80.5);
    stud.display();
    return 0;
}
/*
-*Result-*
output:
101 78.5
101 80.5
-*end*-
Analysis:
定义stud对象时调用了构造函数：
Student(int n, float s) :num(n), score(s) {}
调用display函数时输出：101 78.5
调用change函数时将学号与成绩修改为：101 80.5
再次调用display函数输出：101 80.5
*/