#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std;

int y_sum[2] = { 365,366 };
int m_sum[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

inline void wait_for_press()
{
	cout << endl << "按任意键继续..." << endl;
	_getch();
}

bool is_leap(int x) {
    if (x % 100 == 0)
        return x % 400 == 0;
    return x % 4 == 0;
}

class Date {
private:
	int year, month, day;
public:
	Date();
	Date(int, int, int);
	Date(int);
    void set(int, int, int);
	void set(int, int);
	void set(int);
	operator int();
	friend istream& operator >>(istream&, Date&);
	friend ostream& operator <<(ostream&, Date&);
	friend Date operator +(Date&,int);
    friend Date operator +(int, Date&);
    friend Date operator -(Date&, int);
    friend int operator -(Date&, Date&);
    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);
    friend bool operator>(Date&, Date&);
    friend bool operator<(Date&, Date&);
    friend bool operator>=(Date&, Date&);
    friend bool operator<=(Date&, Date&);
    friend bool operator==(Date&, Date&);
    friend bool operator!=(Date&, Date&);
};

Date::Date() {
    tm t;
    time_t cur;
    time(&cur);
    localtime_s(&t, &cur);
    year = t.tm_year + 1900;
    month = t.tm_mon + 1;
    day = t.tm_mday;
}
Date::Date(int x, int y, int z) :year(x), month(y), day(z) {};
Date::Date(int x) { //考虑负数？
    year = 1900, month = 1, day = 1;
    bool leap = is_leap(year);
    while (x > y_sum[leap]) {
        x -= y_sum[leap];
        ++year;
        leap = is_leap(year);
    }
    while ((month != 2 && x > m_sum[month - 1]) || (x > m_sum[month - 1] + leap)) {
        if (month != 2) x -= m_sum[month - 1];
        else x -= (m_sum[month - 1] + leap);
        ++month;
    }
    day = x;
}
void Date::set(int x, int y, int z) {
    if (x != 0)year = x;
    if (y != 0) month = y;
    if (z != 0)day = z;
}
void Date::set(int x, int y) {
    year = x;
    month = y;
    day = 1;
}
void Date::set(int x) {
    year = x;
    month = 1;
    day = 1;
}
Date::operator int() {
    int ret = 0;
    ret += day;
    for (int i = 0;i < month - 1;++i)
        ret += i == 1 ? (m_sum[i] + is_leap(year)) : m_sum[i];
    for (int i = 1900;i < year;++i)
        ret += y_sum[is_leap(i)];
    return ret;
}
istream& operator>>(istream& is, Date& d) {
    is >> d.year >> d.month >> d.day;
    return is;
}
ostream& operator <<(ostream& os, Date& d) {
    os << d.year << "年" << d.month << "月" << d.day << "日";
    return os;
}
/*
* 其实甚至不必重载+-也能得出答案
* 因为已经实现了Date和int的相互转换
* 以1900.1.1为中转来计算
*/
Date operator +(Date& d, int x) {
    int tmp = int(d) + x;
    return Date(tmp);
}
Date operator +(int x, Date& d) {
    int tmp = int(d) + x;
    return Date(tmp);
}
Date operator -(Date& d, int x) {
    int tmp = int(d) - x;
    return Date(tmp);
}
int operator -(Date& d1, Date& d2) {
    int tmp = int(d1) - int(d2);
    return tmp;
}
Date& Date::operator++() {
    ++day;
    if (day > (month == 2 ? (m_sum[month - 1] + is_leap(year)) : m_sum[month - 1]))
        ++month, day = 1;
    if (month > 12)
        ++year, month = 1;
    return *this;
}
Date Date::operator++(int) {
    Date ret(year, month, day);
    ++day;
    if (day > (month == 2 ? (m_sum[month - 1] + is_leap(year)) : m_sum[month - 1]))
        ++month, day = 1;
    if (month > 12)
        ++year, month = 1;
    return ret;
}
Date& Date::operator--() {
    --day;
    if (day == 0) {
        if (month == 1)
            --year, month = 12, day = 31;
        else
            --month, day = (month == 2 ? (m_sum[month - 1] + is_leap(year)) : m_sum[month - 1]);
    }
    return *this;
}
Date Date::operator--(int) {
    Date ret(year, month, day);
    --day;
    if (day == 0) {
        if (month == 1)
            --year, month = 12, day = 31;
        else
            --month, day = (month == 2 ? (m_sum[month - 1] + is_leap(year)) : m_sum[month - 1]);
    }
    return ret;
}
bool operator>(Date& d1, Date& d2) {
    return int(d1) > int(d2);
}
bool operator<(Date& d1, Date& d2){
    return int(d1) < int(d2);
}
bool operator>=(Date& d1, Date& d2) {
    return int(d1) >= int(d2);
}
bool operator<=(Date& d1, Date& d2){
    return int(d1) <= int(d2);
}
bool operator==(Date& d1, Date& d2) {
    return int(d1) == int(d2);
}
bool operator!=(Date& d1, Date& d2) {
    return int(d1) != int(d2);
}
int main()
{
     {
        Date d1;
        Date d2(1907, 5, 20);

        cout << "测试初始化和cout重载" << endl;

        cout << "d1应该是今天， 实际为：" << d1 << endl;
        cout << "d2应该是1907年5月20日，实际为：" << d2 << endl;

        wait_for_press();
    }

    {
        Date d1, d2, d3, d4;

        cout << "测试set和cin重载" << endl;
        d1.set(1907, 5, 20);
        d2.set(1907, 5);
        d3.set(1907);

        cout << "d1应该是1907年5月20日，实际为：" << d1 << endl;
        cout << "d2应该是1907年5月1日， 实际为：" << d2 << endl;
        cout << "d3应该是1907年1月1日， 实际为：" << d3 << endl;

        cout << "请输入某日期" << endl;
        cin >> d4;
        d4.set(0, 0, 0);
        cout << "d4应该是您刚输入的日期，实际为：" << d4 << endl;

        wait_for_press();
    }
     {
        Date d1(10);
        Date d2(250);
        Date d3(1314);
        Date d4(13145);

        cout << "测试转换构造函数" << endl;

        cout << "d1应该是1900年1月10日，  实际为：" << d1 << endl;
        cout << "d2应该是1900年9月7日，实际为：" << d2 << endl;
        cout << "d3应该是1903年8月7日，  实际为：" << d3 << endl;
        cout << "d4应该是1935年12月28日，实际为：" << d4 << endl;

        Date d5, d6;
        d5 = 30041;
        cout << "d5应该是1982年4月1日， 实际为：" << d5 << endl;

        d6 = 42301;
        cout << "d6应该是2015年10月25日， 实际为：" << d6 << endl;

        wait_for_press();
    }
    
    {
        Date d1(1900, 1, 1);
        Date d2(1907, 5, 20);
        Date d3(1982, 4, 1);
        Date d4(2015, 10, 25);

        cout << "测试类型转换函数" << endl;

        cout << "d1应该是1，     实际为：" << int(d1) << endl;
        cout << "d2应该是2696， 实际为：" << int(d2) << endl;
        cout << "d3应该是30041， 实际为：" << int(d3) << endl;
        cout << "d4应该是42301， 实际为：" << int(d4) << endl;

        wait_for_press();
    }
    
    {
        Date d1(1907, 5, 20);
        Date d2;

        cout << "测试重载+/-" << endl;

        d2 = d1 + 520;
        cout << "d2应该是1908年10月21日，    实际为：" << d2 << endl;

        d2 = 520 + d1;
        cout << "d2应该是1908年10月21日，    实际为：" << d2 << endl;

        d2 = d1 - 3;
        cout << "d2应该是1907年5月17日，   实际为：" << d2 << endl;

        d1.set(2016, 5, 20);
        d2.set(2015, 5, 20);
        cout << "d1-d2应该是366，实际为：" << d1 - d2 << endl;

        d1.set(2018, 5, 20);
        d2.set(2017, 5, 20);
        cout << "d1-d2应该是365，实际为：" << d1 - d2 << endl;

        wait_for_press();
    }
    
    {
        Date d1, d2;

        cout << "测试重载++/--" << endl;

        d1.set(1907, 5, 20);
        d2 = d1++;
        cout << "d1应该是1907年5月21日，  实际为：" << d1 << endl;
        cout << "d2应该是1907年5月20日，  实际为：" << d2 << endl;

        d1.set(1907, 5, 20);
        d2 = ++d1;
        cout << "d1应该是1907年5月21日，  实际为：" << d1 << endl;
        cout << "d2应该是1907年5月21日，  实际为：" << d2 << endl;

        d1.set(1907, 1, 1);
        d2 = d1--;
        cout << "d1应该是1906年12月31日， 实际为：" << d1 << endl;
        cout << "d2应该是1907年1月1日，  实际为：" << d2 << endl;

        d1.set(1907, 1, 1);
        d2 = --d1;
        cout << "d1应该是1906年12月31日， 实际为：" << d1 << endl;
        cout << "d2应该是1906年12月31日， 实际为：" << d2 << endl;

        d1.set(2016, 2, 28);
        d2 = d1++;
        cout << "d1应该是2016年2月29日， 实际为：" << d1 << endl;
        cout << "d2应该是2016年2月28日， 实际为：" << d2 << endl;

        d1.set(2018, 3, 1);
        d2 = d1--;
        cout << "d1应该是2018年2月28日， 实际为：" << d1 << endl;
        cout << "d2应该是2018年3月1日，  实际为：" << d2 << endl;

        wait_for_press();
    }
    
    
    {
        Date d1(1907, 5, 20);
        Date d2(1907, 5, 20);
        Date d3(1907, 1, 1);

        cout << "测试比较运算符" << endl;

        cout << "比较结果应为1，实际为：" << (d1 > d3) << endl;
        cout << "比较结果应为1，实际为：" << (d2 >= d3) << endl;
        cout << "比较结果应为0，实际为：" << (d1 < d3) << endl;
        cout << "比较结果应为0，实际为：" << (d2 <= d3) << endl;
        cout << "比较结果应为1，实际为：" << (d1 == d2) << endl;
        cout << "比较结果应为0，实际为：" << (d1 != d1) << endl;

        wait_for_press();
    }
    
    return 0;
}
