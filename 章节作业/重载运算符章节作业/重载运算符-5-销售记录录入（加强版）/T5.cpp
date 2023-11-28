#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<cmath>
#include<iomanip>
#include <conio.h>

using namespace std;
inline void wait_for_press()
{
    cout << endl << "按任意键继续..." << endl;
    _getch();
}

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
    Book_Sale(int, int, double, double);
    Book_Sale(Book_Sale&);
    Book_Sale();
    Book_Sale(istream&);
    ~Book_Sale();
    void set(int, int, double, double);
    void set(int, int, double);
    void Set(istream&);
    void calculate_isbn(int);
    void display();
    friend istream& operator>>(istream&, Book_Sale&);
    void operator+=(int);
    void operator-=(int);
    friend bool operator>(Book_Sale&, Book_Sale&);
    friend bool operator>=(Book_Sale&, Book_Sale&);
    friend bool operator<(Book_Sale&, Book_Sale&);
    friend bool operator<=(Book_Sale&, Book_Sale&);
    friend bool operator==(Book_Sale&, Book_Sale&);
    friend bool operator!=(Book_Sale&, Book_Sale&);

};
Book_Sale::Book_Sale(int x, int y, double z, double dis) {
    isbn = new char[20];
    calculate_isbn(x);
    sales_volume = y;
    original_price = z;
    discount = dis;

    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}
Book_Sale::Book_Sale(Book_Sale& bk) {
    isbn = new char[20];
    strcpy(isbn, bk.isbn);
    sales_volume = bk.sales_volume;
    original_price = bk.original_price;
    real_price = bk.real_price;
    discount = bk.discount;
    gross_sales = bk.gross_sales;
}
Book_Sale::Book_Sale() {
    isbn = new char[20];
    strcpy(isbn, "");
    sales_volume = 0;
    original_price = 0;
    real_price = 0;
    discount = 0;
    gross_sales = 0;
}
Book_Sale::Book_Sale(istream& in) {
    int ib;
    in >> ib;
    if (ib == -1)
        exit(0);
    in >> sales_volume >> original_price >> discount;

    isbn = new char[20];
    calculate_isbn(ib);
    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}
Book_Sale::~Book_Sale() {
   // delete(isbn);//动态申请的要delete嗷！
}
void Book_Sale::set(int x, int y, double z, double dis) {
    if (x != -1) calculate_isbn(x);
    if (y != -1) sales_volume = y;
    if (z != -1) original_price = z;
    if (dis != -1) discount = dis;

    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}
void Book_Sale::set(int x, int y, double z) {
    if (x != -1) calculate_isbn(x);
    if (y != -1) sales_volume = y;
    if (z != -1) original_price = z;
    discount = 1;

    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}
void Book_Sale::Set(istream& in) {
    int ib;
    in >> ib;
    if (ib == -1)
        exit(0);
    in >> sales_volume >> original_price >> discount;

    calculate_isbn(ib);
    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}

void Book_Sale::calculate_isbn(int x) {
    strcpy(isbn, "978-7-121-");

    int ind = 9;
    for (int i = 4;i >= 0;i--) {
        char ch = '0' + (int)(x / (pow(10, i)));
        x %= (int)(pow(10, i));
        isbn[++ind] = ch;
    }
    isbn[++ind] = '-';

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
    cout << "该书的ISBN号为:" << isbn;
    cout << "，销量为:" << sales_volume << "本";
    cout << "，原价为:" << original_price << "元";
    cout << "，折扣为:" << discount;
    cout << "，现价为:" << real_price << "元";
    cout << "，总销售额为:" << gross_sales << "元";
    cout << endl;
}
void Book_Sale::operator+=(int x) {
    sales_volume += x;
    gross_sales = real_price * sales_volume;
}
void Book_Sale::operator-=(int x) {
    sales_volume -= x;
    gross_sales = real_price * sales_volume;
}
bool operator>(Book_Sale& bk1, Book_Sale& bk2){
    return bk1.gross_sales > bk2.gross_sales;
}
bool operator>=(Book_Sale& bk1, Book_Sale& bk2) {
    return bk1.gross_sales >= bk2.gross_sales;
}
bool operator<(Book_Sale& bk1, Book_Sale& bk2) {
    return bk1.gross_sales <= bk2.gross_sales;
}
bool operator<=(Book_Sale& bk1, Book_Sale& bk2) {
    return bk1.gross_sales <= bk2.gross_sales;
}
bool operator==(Book_Sale& bk1, Book_Sale& bk2) {
    return bk1.gross_sales == bk2.gross_sales;
}
bool operator!=(Book_Sale& bk1, Book_Sale& bk2) {
    return bk1.gross_sales != bk2.gross_sales;
}
istream& operator>>(istream& in, Book_Sale& bk) {
    int ib;
    in >> ib;
    if (ib == -1)
        exit(0);
    in >> bk.sales_volume >> bk.original_price >> bk.discount;

    bk.calculate_isbn(ib);
    bk.real_price = bk.original_price * bk.discount;
    bk.gross_sales = bk.real_price * bk.sales_volume;
}
int main()
{
     {
        Book_Sale b1(95995, 3418, 100, 0.9);
        Book_Sale b2 = b1;
        Book_Sale b3;
        b3 = b1;

        cout << "测试初始化，display和cin重载" << endl;

        cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:307620元\n实际为：";
        b1.display();
        cout << "b2应该是同上，实际为：";
        b2.display();
        cout << "b3应该是同上，实际为：";
        b3.display();

        Book_Sale b4;
        cout << "请输入某书籍销售信息：" << endl; //95995 3418 100 0.9
        cin >> b4;
        cout << "b4应该是您刚输入的信息，实际为：";
        b4.display();

        wait_for_press(); 
    }

     {
        Book_Sale b1, b2, b3(95995, 3418, 100, 1);

        cout << "测试set" << endl;

        b1.set(95995, 3418, 100, 0.9);
        b2.set(95995, 3418, 100);
        b3.set(-1, 3500, -1, 0.8);

        cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:307620元\n实际为：";
        b1.display();
        cout << "b2应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:1，现价为:100元，总销售额为:341800元\n实际为：";
        b2.display();
        cout << "b3应该是该书的ISBN号为:978-7-121-95995-0，销量为:3500本，原价为:100元，折扣为:0.8，现价为:80元，总销售额为:280000元\n实际为：";
        b3.display();

        wait_for_press();
    }
     
    {
        Book_Sale b1(95995, 3418, 100, 0.9);

        cout << "测试重载+=/-=" << endl;

        b1 += 10;
        cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3428本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:308520元\n实际为：";
        b1.display();

        b1 -= 10;
        cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:307620元\n实际为：";
        b1.display();


        wait_for_press();
    }
    
    {
        Book_Sale b1(95994, 3000, 100, 0.8);
        Book_Sale b2(95996, 4800, 100, 0.5);
        Book_Sale b3(95998, 2000, 100, 0.9);

        cout << "测试比较运算符" << endl;

        cout << "比较结果应为1，实际为：" << (b1 > b3) << endl;
        cout << "比较结果应为1，实际为：" << (b2 >= b3) << endl;
        cout << "比较结果应为0，实际为：" << (b1 < b3) << endl;
        cout << "比较结果应为0，实际为：" << (b2 <= b3) << endl;
        cout << "比较结果应为1，实际为：" << (b1 == b2) << endl;
        cout << "比较结果应为0，实际为：" << (b1 != b1) << endl;

        wait_for_press();
    }

    return 0;
}
