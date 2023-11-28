#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>

using namespace std;

void get_outfile(char* infile, char* outfile) {
    int in_len = strlen(infile);
    int st = 0, ed = in_len;
    for (int i = in_len - 1;i >= 0;i--)
        if (infile[i] == '.') {
            ed = i;
            break;
        }
    for (int i = ed;i >= 0;i--)
        if (infile[i] == '/') {
            st = i + 1;
            break;
        }

    int out_len = ed - st + 4;
    strncat(outfile, infile + st, ed - st);
    strcat(outfile, "_red");
    strncat(outfile, infile + ed, in_len - ed);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "请确保输入参数正确" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if (!in) {
        cerr << "无法打开输入文件" << endl;
        return -1;
    }

    char outfile[100]=""; //necessary
    get_outfile(argv[1], outfile);

    ofstream out(outfile);
    if (!out) {
        cerr << "无法打开输出文件" << endl;
        return -1;
    }

    int check = 0;
    char ch = in.get();
    while (!in.eof()) {
        if (check == 0) out << ch;
        check = (check + 1) % 3;
        ch = in.get();
    }

    in.close();
    out.close();
    return 0;
}

/* 读取文件并进行降噪 */
/* 根据规则自动补充文件名并进行输出，规则如下:输出文件的名称是输入的文件名加上_red*/