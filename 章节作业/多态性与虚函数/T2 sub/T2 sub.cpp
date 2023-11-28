
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