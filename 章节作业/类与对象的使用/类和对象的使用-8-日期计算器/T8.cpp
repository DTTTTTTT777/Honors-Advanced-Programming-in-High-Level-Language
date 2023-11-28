#include<iostream>
#include<stdlib.h>

using namespace std;

bool sig[12] = { 1,0,1,0,1,0,1,1,0,1,0,1 };
int sum[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

class dateToDay
{
public:
    dateToDay(int, int, int);    // 通过传参构建
    // dateToDay();              // 构建时从键盘读入 实现方式二选一
    void setDate(int, int, int); // 设置日期
    //void setDate();           // 从键盘读入设置日期 实现方式二选一
    // 合法性检查应该在构建/设置时完成
    void display();              // 将计算结果输出(即本年内第几天)
private:
    bool checkLeap();            // 该函数用于检查闰年
    bool checkValid();           // 该函数用于检查合法
    int computeDay();            // 该函数用于计算日期
    int year;
    int month;
    int day;
};

dateToDay::dateToDay(int y, int m, int d) :year(y), month(m), day(d) {
    if (!checkValid()) {
        cout << "输入有误！程序退出" << endl;
        exit(0);
    }
};
void dateToDay::setDate(int y, int m, int d) {
    year = y, month = m, day = d;
    if (!checkValid()) {
        cout << "输入有误！程序退出" << endl;
        exit(1);
    }
}
bool dateToDay::checkLeap() {
    if (year % 100 == 0 && year % 400 != 0) return 0;
    if (year % 4 == 0) return 1;
    return 0;
}
bool dateToDay::checkValid() {
    if (year < 1 || year>9999) return 0;
    if (month < 1 || month>12) return 0;
    if (day < 1) return 0;
    if (month == 2) {
        if (checkLeap() && day > 29) return 0;
        else if (day > 28) return 0;
    }
    else {
        if (sig[month - 1] && day > 31) return 0;
        else if (day > 30) return 0;
    }
    return 1;
}
int dateToDay::computeDay() {
    int ret = 0;
    for (int i = 0;i < month - 1;i++) {
        ret += sum[i];
        if (i == 1)ret += checkLeap();
    }
    ret += day;
    return ret;
}
void dateToDay::display() {
    cout << year << '-' << month << '-' << day << "是第" << year << "年的第" << computeDay() << "天" << endl;
}

bool read(int& x) {
    return bool(cin >> x);
}
int main() {
    int day[3];
    cout << "请输入一个日期" << endl;
    for (int i = 0;i < 3;i++) {
        if (!read(day[i])) {
            cout << "illegal" << endl;
            return -1;
        }
    }
    dateToDay t(day[0], day[1], day[2]);
    t.display();
    cout << "请输入一个日期" << endl;
    for (int i = 0;i < 3;i++) {
        if (!read(day[i])) {
            cout << "illegal" << endl;
            return -1;
        }
    }
    t.setDate(day[0], day[1], day[2]);
    t.display();
    return 0;
}