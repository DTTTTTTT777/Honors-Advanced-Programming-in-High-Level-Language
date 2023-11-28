
#include <iostream>
#include <cmath>

using namespace std;

/**********************************************
*
*    TO-DO:
*        请补全该区域的代码，并只提交在这个区域的代码。
*
***********************************************/

class integral {
protected:
    double a, b;
public:
    integral() {
        a = 0, b = 0;
    }
    virtual double value() = 0;
    friend istream& operator>>(istream& is, integral& x) {
        is >> x.a >> x.b;
        return is;
    }
};

class integral_sin :public integral {
public:
    double value() {
        double ret = 0, dat = (b - a) / 10000.0;
        for (int i = 0;i <= 10000;++i) {
            ret += sin(a + dat * i) * dat;
        }
        return ret;
    }
};

class integral_cos :public integral {
public:
    double value() {
        double ret = 0, dat = (b - a) / 10000.0;
        for (int i = 0;i <= 10000;++i) {
            ret += cos(a + dat * i) * dat;
        }
        return ret;
    }
};

class integral_exp :public integral {
public:
    double value() {
        double ret = 0, dat = (b - a) / 10000.0;
        for (int i = 0;i <= 10000;++i) {
            ret += exp(a + dat * i) * dat;
        }
        return ret;
    }
};
/**********************************************
*
*    TO-DO END
*
***********************************************/

int main()
{
    integral_sin s1;
    integral_cos s2;
    integral_exp s3;
    integral* p;

    cout << "请输入上下限：";
    cin >> s1;
    p = &s1;
    cout << "∫sinxdx的计算结果为：" << (p->value()) << endl;

    cout << "请输入上下限：";
    cin >> s2;
    p = &s2;
    cout << "∫cosxdx的计算结果为：" << (p->value()) << endl;

    cout << "请输入上下限：";
    cin >> s3;
    p = &s3;
    cout << "∫expxdx的计算结果为：" << (p->value()) << endl;

    return 0;
}