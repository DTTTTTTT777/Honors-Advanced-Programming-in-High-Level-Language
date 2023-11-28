#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>

using namespace std;

class Teacher
{
public:
    Teacher();
    ~Teacher();
    void set(int, const char*, char);
    void display();
private:
    int num;
    char* name;
    char sex;
};

class BirthDate
{
public:
    void set(int, int, int);
    void display();
private:
    int year;
    int month;
    int day;
};

class Professor : public Teacher
{
public:
    Professor();
    void change_birthdate();
    void display();
private:
    BirthDate birthday;
};

void fun1(Teacher& tea) {
    tea.set(10000, "张三", 'm');
}
void fun2(BirthDate& bir) {
    cout << "输入改变的日期:" << endl;
    int y, m, d;
    cin >> y >> m >> d;
    bir.set(y, m, d);
}

Teacher::Teacher() {
    name = new char[20];
    num = 0, sex = 0;
    strcpy(name, "");
}
Teacher::~Teacher() {
    delete name;
}
void Teacher::set(int in_num, const char* in_name, char in_sex) {
    num = in_num;
    sex = in_sex;
    strcpy(name, in_name);
}
void Teacher::display() {
    cout << "姓名: " << name << endl;
    cout << "教工号: " << num << endl;
    cout << "性别: " << sex << endl;
}
void BirthDate::set(int y, int m, int d) {
    year = y, month = m, day = d;
}
void BirthDate::display() {
    cout << "生日: " << year << "-" << month << "-" << day << endl;
}

Professor::Professor() {
    fun1(*this);
    birthday.set(1975, 1, 1);
}
void Professor::change_birthdate() {
    fun2(birthday);
}
void Professor::display() {
    Teacher::display();
    birthday.display();
}

int main() {
    Professor prof1;
    prof1.change_birthdate();
    prof1.display();
    return 0;
}