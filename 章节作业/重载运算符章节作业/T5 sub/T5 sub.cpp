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
bool operator>(Book_Sale& bk1, Book_Sale& bk2) {
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