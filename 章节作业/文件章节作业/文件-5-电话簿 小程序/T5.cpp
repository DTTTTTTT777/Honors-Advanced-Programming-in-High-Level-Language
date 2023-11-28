#include<iostream>
#include<streambuf>
#include<cstring>
#include<iterator>
#include<fstream>
#include<sstream>
#include<time.h>

using namespace std;

bool valid(string str) {
    if (str.length() != 11)
        return 0;
    if (str[0] != '1' || str[1] < '3' || str[1] >'9')
        return 0;
    for (int i = 2;i < str.length();i++)
        if (str[i] < '0' || str[i]>'9')
            return 0;
    return 1;
}
int main(int argc, char* argv[]) {
    time_t start, end;
    start = clock();

    if (argc != 3) {
        cerr << "请给出文件名和前三位号码" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if (!in) {
        cerr << "无法打开输入文件" << endl;
        return -1;
    }
    string ans;
    while (!in.eof()) {
        string cur;
        getline(in, cur);
        if (!valid(cur))
            continue;
        if (argv[2] != cur.substr(0, 3))
            continue;
        if (ans < cur)
            ans = cur;
    }
    in.close();
    cout << ans << endl;

    end = clock();
    //cout << "程序运行时间：" << (end - start) * 1.0 / CLOCKS_PER_SEC << "s\n";


    //在哪里用字符流串??????






    /* 通过argv[2]查找所有合法信息，并输出所匹配的最大值 */
    /* 需要注意argv均为字符串类型，你可能需要对该参数进行转换 */
    return 0;
}
/*
    请你编写程序，从电话簿中按行读入信息，封装函数 valid() 进行检测读取到的信息是否为电话号码
    必须使用字符串流对象
    需要考虑错误输入，但是你不需要输出错误提示，仅需过滤掉不合法信息即可
    本题合法的数据仅为 11位(10进制长度)整型，前两位字符合法范围是 13-19 (即合法数据是 13000000000~19999999999)。
    使用longlong
*/
/* istreambuf_iterator<char> beg(fin),
      end; // 设置两个文件指针，指向开始和结束，以 char(一字节) 为步长
  string content(beg, end); // 将文件全部读入 string 字符串
  fin.close(); // 操作完文件后关闭文件句柄是一个好习惯*/