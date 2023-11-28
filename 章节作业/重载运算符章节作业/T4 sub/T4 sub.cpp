int y_sum[2] = { 365,366 };
int m_sum[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

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
    friend Date operator +(Date&, int);
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
bool operator<(Date& d1, Date& d2) {
    return int(d1) < int(d2);
}
bool operator>=(Date& d1, Date& d2) {
    return int(d1) >= int(d2);
}
bool operator<=(Date& d1, Date& d2) {
    return int(d1) <= int(d2);
}
bool operator==(Date& d1, Date& d2) {
    return int(d1) == int(d2);
}
bool operator!=(Date& d1, Date& d2) {
    return int(d1) != int(d2);
}