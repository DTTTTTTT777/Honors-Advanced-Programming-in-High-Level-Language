#include<iostream>
#include<fstream>

using namespace std;

int main() {
	//打开文件foo.bar
	ifstream  infile("foo.bar", ios::binary); //用二进制方式打开！
	if (!infile.is_open()) {
		cout << "can't open file foo.bar\n";
		return -1;
	}

	//计算行数
	int rows=0;
	while (!infile.eof()) {
		while (infile.get() != '\n' && !infile.eof())
			continue;
		rows++;
	}

	//找到结束位置
	infile.clear(); //一定要先clear再seekg
	infile.seekg(0, ios_base::end);
	streampos endpos = infile.tellg();
	//cout << "endpos=" << endpos << endl;

	//输出行数
	ofstream outfile("foo.bar", ios::binary|ios::app);
	if (!outfile.is_open()) {
		cout << "can't open file foo.bar\n";
		return -1;
	}
	outfile << endl << rows;

	//再次遍历并且输出每一行的偏移量
	infile.clear(); //一定要先clear再seekg
	infile.seekg(0, ios_base::beg);
	while (rows != 0) {
		outfile << ' ' << infile.tellg();
		while (infile.get() != '\n' && infile.tellg() < endpos)
			continue;
		rows--;
	}
	outfile << ' ' << endpos + 1ll;

	//关闭文件
	infile.close();
	outfile.close();

	return 0;
}
