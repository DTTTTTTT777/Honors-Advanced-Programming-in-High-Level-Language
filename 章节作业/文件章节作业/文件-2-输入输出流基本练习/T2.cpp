#include<iostream>
using namespace std;
istream& f(istream& in) {
    auto in_state = in.rdstate(); // 保存流入函数的状态
    /* 复读整数，并拒绝错误输入 */
    while (!in.eof()) {
        int x;
        if (in >> x) {
            if (x == -1 || in.eof())
                break;
            else {
                cout << "你说了:" << x << " ";
            }
        }
        else {
            if (in.eof())
                break;
            if (!in.fail()) {
                cout << "I cannot go on\n";
                exit(1);
            }
            cout << "输入非法！请重新输入 ";
            in.clear();
            while (!isspace(in.get()))
                continue;
        }
    }
    in.setstate(in_state);        // 复位流
    return in;
}
int main() {
    cout << "请输入一些整数，以-1或Ctrl+Z结束。" << endl;
    f(cin);
    cout << "------程序结束------";
    return 0;
}

/*
    我认为第1种复位方式更好，
    “复位”的意思应该是使流恢复到do something之前的状态，
    而do something之前的状态不一定是 failbit=eofbit=badbit=0
*/