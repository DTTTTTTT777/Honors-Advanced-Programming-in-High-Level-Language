#include<iostream>
#include<fstream>
#include<cstring>
#include<queue>
#include<time.h>
#include<bitset>
#include<unordered_map>

using namespace std;

int node_num; //Huffman tree的结点总数

struct Huffman_node { //定义Huffman结点
	char c = '\0';
	int freq = 0, num = 0;
	Huffman_node* left_child = NULL, * right_child = NULL;
	/*friend bool operator <(Huffman_node x, Huffman_node y) {    //定义该结构体的大小比较
		return x.freq < y.freq;	  //不过由于此题中需要比较的是指向该结构体的指针，所以不采用这种方式
	}*/
}*root;

struct cmp { 
	bool operator() (const Huffman_node* x, const Huffman_node* y) {
		return x->freq > y->freq; 
	}
};

unordered_map<char, int>cnt; //cnt[c]: 字符c在待压缩文件中出现的次数
unordered_map<char, string>ans; //ans[c]: 字符c对应的01串
priority_queue<Huffman_node*, vector<Huffman_node*>, cmp>que; //构建Huffman时所需的对结点排序的优先队列

long getFileSize(const char* strFileName) //得到文件大小
{
	std::ifstream in(strFileName, ios::binary);
	if (!in.is_open()) return 0;

	in.seekg(0, std::ios_base::end);
	std::streampos sp = in.tellg();
	return sp;
}

bool is_leaf(Huffman_node* t) {
	return (t->left_child == NULL) && (t->right_child == NULL);
}

void output_tree(Huffman_node* t, char* fn) { //输出Huffman tree到fn文件中
	ofstream fl;
	if (t == root) {
		fl.open(fn,ios::binary); //二进制打开文件
		if (!fl) { //检查文件是否成功打开
			cout << "Error opening file" << endl;
			exit(1);
		}

		fl.write((char*)&node_num, sizeof(int));
		fl.close();
	}

	if (t->left_child != NULL)
		output_tree(t->left_child, fn);
	if (t->right_child != NULL)
		output_tree(t->right_child, fn);

	//先遍历，再输出，保证输出一个结点时，它的左右子结点都已输出，便于解压缩时重构Huffman tree
	fl.open(fn, ios::binary | ios::app);
	if (!fl) {
		cout << "Error opening file" << endl;
		exit(1);
	}

	if (is_leaf(t)) { //叶结点：首先输出一个代表叶结点的 1 , 接着输出编号与叶结点对应字符
		bool leaf = 1;
		fl.write((char*)&leaf, sizeof(bool));
		fl.write((char*)&t->num, sizeof(int));
		fl.write((char*)&t->c, sizeof(char));
	}
	else { //非叶结点：首先输出一个表示非叶节点的 0, 接着输出编号与其左右子结点编号（无子结点即用0表示）
		bool leaf = 0; 
		int child = 0;

		fl.write((char*)&leaf, sizeof(bool));
		fl.write((char*)&t->num, sizeof(int));
		if (t->left_child == NULL)
			fl.write((char*)&child, sizeof(int));
		else
			fl.write((char*)&t->left_child->num, sizeof(int));
		if (t->right_child == NULL)
			fl.write((char*)&child, sizeof(int));
		else
			fl.write((char*)&t->right_child->num, sizeof(int));
	}

	fl.close(); //及时关闭文件！
}

void traverse_tree(Huffman_node* t) { //遍历Huffman tree来找到每个字符（叶结点）对应的01串并存进 map ans中
	static string str;
	int len = str.length();
	if (t->left_child != NULL) {
		str = str + "0";
		traverse_tree(t->left_child);
		str.erase(len);
	}
	if (t->right_child != NULL) {
		str = str + "1";
		traverse_tree(t->right_child);
		str.erase(len);
	}
	if (is_leaf(t)) ans[t->c] = str;
}

void delete_tree(Huffman_node * t) {
	if (t->left_child != NULL)
		delete_tree(t->left_child);
	if (t->right_child != NULL)
		delete_tree(t->right_child);
	delete t;
}

void ZIP(char** argv) {
	ifstream infile(argv[1], ios::binary);
	if (!infile) { //检查文件是否成功打开
		cerr << "Error opening file" << endl;
		exit(1);
	}

	while (!infile.eof()) { //统计所有字符出现的次数
		char c;
		//infile >> c;  注意到此种读入会忽略空格与换行！
		c = infile.get();
		if (infile.eof())break; //此句的必要性与eof()的特性有关 
		if (cnt.find(c) == cnt.end()) cnt[c] = 1;
		else cnt[c]++;
	}

	infile.close();

	unordered_map<char, int>::iterator it; //定义一个unordered map<char,int>类型的迭代器用来遍历 cnt
	for (it = cnt.begin();it != cnt.end();it++) { //创建所有字符的Huffman结点并且加入优先队列
		char c = it->first;
		int freq = it->second;
		Huffman_node* nd = new Huffman_node;
		nd->c = c;
		nd->freq = freq;
		nd->num = ++node_num;
		que.push(nd);
	}

	while (que.size() > 1) {
		Huffman_node* n1, * n2; //取出优先队列队首的两个元素
		n1 = que.top();
		que.pop();
		n2 = que.top();
		que.pop();

		Huffman_node* nd = new Huffman_node; //创建新结点：n1 n2的父结点
		nd->freq = n1->freq + n2->freq;
		nd->left_child = n1;
		nd->right_child = n2;
		nd->num = ++node_num;

		que.push(nd);
	}

	root = que.top(); //最后剩下的结点是根结点

	output_tree(root, argv[2]); //输出Huffman tree
	traverse_tree(root); ////遍历Huffman tree来找到每个字符（叶结点）对应的01串并存进 map ans中

	long long tot_ansc = 0, left_num=0; //left_ansc: 输出unsigned char 类型的总数-1 ; left_num:原文件对应的01串除以8得到的余数
	infile.open(argv[1], ios::binary);
	ofstream outfile(argv[2], ios::binary | ios::app);

	while (!infile.eof()) {
		char c;
		//infile >> c;  注意到此种读入会忽略空格与换行！
		c = infile.get();
		left_num += ans[c].length();
		tot_ansc += left_num / 8;
		left_num %= 8;
	}
	outfile.write((char*)&tot_ansc, sizeof(long long));
	outfile.write((char*)&left_num, sizeof(long long));
	infile.close();

	infile.open(argv[1], ios::binary);
	if (!infile) {
		cerr << "Can not open the input file!" << endl; // 输出错误信息并退出
		return;
	}
	string ans_str;
	while (!infile.eof()) {
		char c;
		c = infile.get();
		ans_str += ans[c];
		while (ans_str.length() >= 8) {
			unsigned char ansc = 0;
			for (int i = 0;i < 8;i++)
				ansc = ansc << 1 | (ans_str[i] - '0');
			outfile.write((char*)&ansc, sizeof(unsigned char));
			ans_str.erase(0, 8);
		}
	}
	if (ans_str.length()) {
		unsigned char ansc = 0;
		for (int i = 0;i < ans_str.length();i++)
			ansc = ansc << 1 | (ans_str[i] - '0');
		outfile.write((char*)&ansc, sizeof(unsigned char));
	}

	infile.close();
	outfile.close();
	delete_tree(root); //清理动态申请的内存！

	cerr << "文件压缩率：" << 1.0 * getFileSize(argv[2]) / getFileSize(argv[1]) * 100 << "%" << endl;
}

unordered_map<int, Huffman_node*>mp2; // mp2[num]: num对应的Huffman结点

void UNZIP(char** argv) {
	ifstream infile(argv[1], ios::binary); // 以二进制方式打开文件
	ofstream outfile(argv[2], ios::binary);
	if ((!infile) || (!outfile)) {
		cerr << "Can not open the input file!" << endl; // 输出错误信息并退出
		return;
	}

	infile.read((char*)&node_num, sizeof(int));  //开始重构Huffman tree
	while (node_num--) {
		Huffman_node* nd = new Huffman_node;
		if (node_num == 0) { //最后一个是根结点！
			root = nd;
		}
		bool leaf;
		infile.read((char*)&leaf, sizeof(bool));
		infile.read((char*)&nd->num, sizeof(int));
		mp2[nd->num] = nd;
		if (leaf) {
			infile.read((char*)&nd->c, sizeof(char));
		}
		else {
			int n1 = 0, n2 = 0;
			infile.read((char*)&n1, sizeof(int));
			infile.read((char*)&n2, sizeof(int));
			if (n1 != 0)nd->left_child = mp2[n1];
			if (n2 != 0)nd->right_child = mp2[n2];
		}
	}

	long long tot_ansc, left_num; //开始读取原文本对应的压缩编码
	infile.read((char*)&tot_ansc, sizeof(long long));
	infile.read((char*)&left_num, sizeof(long long));

	Huffman_node* cur = root;
	while (tot_ansc--) {
		unsigned char c;
		infile.read((char*)&c, sizeof(unsigned char));
		bitset<8> bit(c);

		for (int i = 7;i >= 0;i--) {//倒序！
			if (bit[i] == 0) //注意是0而非'0'！
				cur = cur->left_child;
			else
				cur = cur->right_child;

			if (is_leaf(cur)) {
				outfile << cur->c;
				cur = root;
			}
		}

	}
	if (left_num != 0) { //最后一个单独处理
		unsigned char c;
		infile.read((char*)&c, sizeof(unsigned char));
		bitset<8> bit(c);
		for (int i = 7 - left_num;i >= 0;i--) {
			if (bit[i] == 0)
				cur = cur->left_child;
			else 
				cur = cur->right_child;
			if (is_leaf(cur)) {
				outfile << cur->c;
				cur = root;
			}
		}

	}

	infile.close();
	outfile.close();
	delete_tree(root);//清理动态申请的内存！
}

int main(int argc, char** argv) {
	clock_t starttime, endtime;
	starttime = clock();

	if (argc != 4) {
		cerr << "Please make sure the number of parameters is correct." << endl;
		return -1;
	}
	if (strcmp(argv[3], "zip") == 0) {
		ZIP(argv);
	}
	else if (strcmp(argv[3], "unzip") == 0) {
		UNZIP(argv);
	}
	else {
		cerr << "Unknown parameter!\nCommand list:\nzip/unzip" << endl;
		return -1;
	}

	endtime = clock();
	cerr << "程序运行时间：" << 1.00 * (endtime - starttime) / CLOCKS_PER_SEC << "秒" << endl;
	return 0;
}
/*
g++ 文件压缩.cpp -o 文件压缩
文件压缩.exe ser.log ser_compressed.log zip
文件压缩.exe ser_compressed.log ser_decompressed.log unzip
*/