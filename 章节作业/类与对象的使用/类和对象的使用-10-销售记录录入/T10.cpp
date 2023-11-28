#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<cmath>
#include<iomanip>

using namespace std;

class Book_Sale
{
private:
    char* isbn; // 指向书籍编号的指针
                 // 存放书籍编号的空间需动态申请
                 // 书籍编号由 5 段 13 位数字组成，如 978-7-121-15535-2
    int    sales_volume;   // 销售量
    double original_price; // 原始价格
    double real_price;     // 实售价格
    double discount;       // 折扣
    double gross_sales;    // 销售总额

public:
    /* 可以接受 istream & 并从中读取书籍销售信息的构造函数Book_Sale (istream &)，析构函数以及其他必要的成员函数 */
    Book_Sale(istream &);
    ~Book_Sale();
    void Set(istream&);
    void calculate_isbn(int);
    void display();
};

Book_Sale::Book_Sale(istream &in) {
    int isbn;
    in >> isbn;
    if (isbn == -1)
        exit(0);
    in >> sales_volume >> original_price >> discount;

    calculate_isbn(isbn);
    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}
Book_Sale::~Book_Sale() {
    delete(isbn);//动态申请的要delete嗷！
}
void Book_Sale::Set(istream& in) {
    int isbn;
    in >> isbn;
    if (isbn == -1)
        exit(0);
    in >> sales_volume >> original_price >> discount;

    calculate_isbn(isbn);
    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}

void Book_Sale::calculate_isbn(int x) {
    isbn = new char[20];
    strcpy(isbn, "978-7-121-");

    int ind = 9;
    for (int i = 4;i >= 0;i--) {
        //cout << (pow(10, i)) << endl;
        //cout << (int)(x / (pow(10, i))) << endl;
        char ch = '0' + (int)(x / (pow(10, i)));
        x %= (int)(pow(10, i));
        isbn[++ind] = ch;
    }
    isbn[++ind]= '-';

    int outcome = 0, multi[2] = { 1,3 }, num = 0;
    for (int i = 0;i < 17;i++) {
        int t = isbn[i] - '0';
        if (t < 0 || t>9) continue;
        outcome = (outcome + t * multi[num]) % 10;
        num = (num + 1) % 2;
    }
    outcome = (10 - outcome) % 10;
    char ch = '0' + outcome;
    isbn[++ind] = ch;
    isbn[++ind] = '\0';
}
void Book_Sale::display() {
    cout << "该书的ISBN号为" << isbn << endl;
    cout << "销量为" << fixed << setprecision(5) << sales_volume << "本" << endl;
    cout << "原价为" << fixed << setprecision(5) << original_price << "元" << endl;
    cout << "折扣为" << fixed << setprecision(5) << discount << endl;
    cout << "现价为" << fixed << setprecision(5) << real_price << "元" << endl;
    cout << "总销售额为" << fixed << setprecision(5) << gross_sales <<  "元" << endl;
    cout << endl;
}
int main() {
    Book_Sale moon(cin);
    moon.display();
    while (1) {
        moon.Set(cin);
        moon.display();
    }
    return 0;
}