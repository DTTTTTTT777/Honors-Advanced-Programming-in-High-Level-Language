#include <iostream>
#include <cmath>

using namespace std;

/**********************************************
*
*    TO-DO:
*        请补全该区域的代码，并只提交在这个区域的代码。
*
***********************************************/
const double Pi = 3.141592;

class Shape {
public:
    virtual double area() = 0;
};

class Circle :public Shape {
private:
    double r;
public:
    Circle(double x) {
        r = x;
    }
    virtual double area() {
        return Pi * r * r;
    }
};

class Square :public Shape {
private:
    double l;
public:
    Square(double x) {
        l = x;
    }
    virtual double area() {
        return l * l;
    }
};

class Rectangle :public Shape {
private:
    double a, b;
public:
    Rectangle(double x, double y) {
        a = x, b = y;
    }
    virtual double area() {
        return a * b;
    }
};

class Trapezoid:public Shape {
private:
    double l1, l2, h;
public:
    Trapezoid(double x, double y, double z) {
        l1 = x, l2 = y, h = z;
    }
    virtual double area() {
        return (l1 + l2) * h / 2.0;
    }
};

class Triangle :public Shape {
private:
    double a, b, c;
public:
    Triangle(double x, double y, double z) {
        a = x, b = y, c = z;
    }
    virtual double area() {
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};


/**********************************************
*
*    TO-DO END
*
***********************************************/

int main() {
    Circle    c1(2);
    Square    s1(3);
    Rectangle r1(4, 5);
    Trapezoid t1(6, 7, 8);
    Triangle  t2(3, 4, 5);

    Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

    for (int i = 0; i < 5; i++) {
        cout << s[i]->area() << endl;
    }
    return 0;
}