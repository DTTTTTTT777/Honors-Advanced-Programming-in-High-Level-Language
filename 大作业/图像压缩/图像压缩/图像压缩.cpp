#include "PicReader.h"
#include <stdio.h>
#include <iostream>
#include<cmath>
#include<bitset>
#include<unordered_map>
#include<fstream>
#include<time.h>

using namespace std;

//一些需要用到的常量-------------------------------------------------------------
const double Pi = 3.14159;
const int Q[2][8][8] = { //量化表 Q[0]是L的 Q[1]是C的
	16, 11, 10, 16, 24, 40, 51, 61,
	12, 12, 14, 19, 26, 58, 60, 55,
	14, 13, 16, 24, 40, 57, 69, 56,
	14, 17, 22, 29, 51, 87, 80, 62,
	18, 22, 37, 56, 68, 109, 103, 77,
	24, 35, 55, 64, 81, 104, 113, 92,
	49, 64, 78, 87, 103, 121, 120, 101,
	72, 92, 95, 98, 112, 100, 103, 99,

	17, 18, 24, 47, 99, 99, 99, 99,
	18, 21, 26, 66, 99, 99, 99, 99,
	24, 26, 56, 99, 99, 99, 99, 99,
	47, 66, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
};
const char ZigZag[64] = {
	0, 1, 5, 6, 14, 15, 27, 28,
	2, 4, 7, 13, 16, 26, 29, 42,
	3, 8, 12, 17, 25, 30, 41, 43,
	9, 11, 18, 24, 31, 40, 44, 53,
	10, 19, 23, 32, 39, 45, 52, 54,
	20, 22, 33, 38, 46, 51, 55, 60,
	21, 34, 37, 47, 50, 56, 59, 61,
	35, 36, 48, 49, 57, 58, 62, 63
};
const char Standard_DC_Luminance_NRCodes[] = { 0, 0, 7, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
const unsigned char Standard_DC_Luminance_Values[] = { 4, 5, 3, 2, 6, 1, 0, 7, 8, 9, 10, 11 };
const char Standard_DC_Chrominance_NRCodes[] = { 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 };
const unsigned char Standard_DC_Chrominance_Values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
const char Standard_AC_Luminance_NRCodes[] = { 0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7d };
const unsigned char Standard_AC_Luminance_Values[] = {
	0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
	0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
	0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
	0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
	0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
	0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
	0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
	0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
	0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
	0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
	0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
	0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
	0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
	0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
	0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
	0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
	0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
	0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
	0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa
};
const char Standard_AC_Chrominance_NRCodes[] = { 0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77 };
const unsigned char Standard_AC_Chrominance_Values[] = {
	0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
	0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
	0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
	0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
	0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
	0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
	0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
	0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
	0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
	0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
	0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
	0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
	0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
	0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
	0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
	0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
	0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
	0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa
};

struct block {
	double Y[8][8], Cb[8][8], Cr[8][8];
	struct block* next;
}*head = NULL, * tail = NULL;

unordered_map<unsigned char, string>Huffcode[4];
string ans; //答案字符串

double alpha(int u) {
	if (u == 0)return 1.000 / sqrt(8);
	return 0.500;
}

void DCT(double mt[8][8]) {
	double f[8][8];
	for (int u = 0;u < 8;u++)
		for (int v = 0;v < 8;v++) {
			f[u][v] = 0;//init！
			for (int x = 0;x < 8;x++)
				for (int y = 0;y < 8;y++) {
					f[u][v] += mt[x][y] * cos(1.0 * (2 * x + 1) / 16.0 * u * Pi) * cos(1.0 * (2 * y + 1) / 16.0 * v * Pi);
				}
			f[u][v] *= alpha(u) * alpha(v);
		}
	for (int i = 0;i < 8;i++) {
		for (int j = 0;j < 8;j++) {
			mt[i][j] = f[i][j];
		}
	}
}

void quantify(double mt[8][8], bool fl, int* tmp) {
	for (int i = 0;i < 8;i++)
		for (int j = 0;j < 8;j++) {
			tmp[i * 8 + j] = round(mt[i][j] / Q[fl][i][j]);
		}
}

void zigzag(int* tmp) {
	int ret[64];
	for (int i = 0;i < 64;i++)
		ret[ZigZag[i]] = tmp[i];
	for (int i = 0;i < 64;i++)
		tmp[i] = ret[i];
}

int GetBinLen(int x) {
	if (x == 0) return 0;
	if (x < 0) x = -x;
	for (int i = 31;i >= 0;i--) {
		if (x & (1 << i)) return i + 1;
	}
}

string leftstr;
int lastone[3];

void Code(int* tmp, int type, int num) {

	int tmp0 = tmp[0]; //对第一个值（DC）进行特殊处理：减去前一个小块该值的原值
	tmp[0] -= lastone[num];
	lastone[num] = tmp0;

	int tail_zero = 0; //找到从后往前的最后一个0
	for (int i = 63;i > 0;i--) {
		if (tmp[i] == 0) tail_zero++;
		else break;
	}

	//开始编码
	int zero_num = 0;
	bool is_AC = 0;
	string str = leftstr;
	for (int i = 0;i < 64 - tail_zero;i++) {
		if (tmp[i] != 0 || zero_num == 15 || i == 0) { //三种情况缺一不可
			int flag = 0;
			if (tmp[i] < 0) flag = 1, tmp[i] *= -1;
			int bin_len = GetBinLen(tmp[i]);
			bitset<40>bit(tmp[i]);
			str = str + Huffcode[type + is_AC][(zero_num << 4) | bin_len];
			for (int i = bin_len - 1;i >= 0;i--)
				if (bit[i] ^ flag) { str = str + '1'; }
				else { str = str + '0'; }
			zero_num = 0;
		}
		else
			zero_num++;
		is_AC = 1;
	}

	if (tail_zero) str = str + Huffcode[type + 1][0];//eob！并不都是1010

	int cur = 0;
	while (str.length() > cur + 7) {
		bitset<8>bit(str.substr(cur, 8));
		cur += 8;
		unsigned char c = bit.to_ullong();
		ans.push_back(c);
		if (c == 0xff)  ans.push_back(0x00);
	}
	leftstr = str.substr(cur, str.length() - cur);
}

void Get_Huffman_Code(const char* Numbers, const unsigned char* Values, int ind) {
	const unsigned char* values = Values;
	int code = 0;
	for (int i = 0;i < 16;i++) {
		char num = Numbers[i];
		int n_bits = i + 1;
		for (int j = 0;j < num;j++) {
			unsigned char value = *values;
			string str;
			bitset<50>bit(code);
			for (int k = i;k >= 0;k--) {
				if (bit[k] == 0) str = str + '0';
				else str = str + '1';
			}
			Huffcode[ind][value] = str;
			code++;
			values++;
		}
		code <<= 1;
	}
}

void Init_Huffman_Code() {
	Get_Huffman_Code(Standard_DC_Luminance_NRCodes, Standard_DC_Luminance_Values, 0);
	Get_Huffman_Code(Standard_AC_Luminance_NRCodes, Standard_AC_Luminance_Values, 1);
	Get_Huffman_Code(Standard_DC_Chrominance_NRCodes, Standard_DC_Chrominance_Values, 2);
	Get_Huffman_Code(Standard_AC_Chrominance_NRCodes, Standard_AC_Chrominance_Values, 3);
}

void Get_ans(int im_height, int im_width) {

	//SOI Start of Image 图像开始----------------------------------------------------------
	ans.push_back(0xff);ans.push_back(0xd8);  //标记代码0xffd8

	//APP0 Application--------------------------------------------------------------------------
	ans.push_back(0xff);ans.push_back(0xe0); //标记代码0xffe0
	ans.push_back(0x00);ans.push_back(0x10); //16！数据长度
	ans.push_back(0x4a);ans.push_back(0x46);ans.push_back(0x49);ans.push_back(0x46);ans.push_back(0x00);//标识符 0x4A46494600
	ans.push_back(0x01);ans.push_back(0x02);//版本号 0x0102
	ans.push_back(0x00);//X和Y的密度单位
	ans.push_back(0x00);ans.push_back(0x01);//X方向像素密度
	ans.push_back(0x00);ans.push_back(0x01); //Y方向像素密度
	ans.push_back(0x00); //缩略图水平像素数目
	ans.push_back(0x00);//缩略图垂直像素数目

	//DQT Define Quantization Table 定义量化表------------------------------------------------------
	ans.push_back(0xff);ans.push_back(0xdb); //标记代码0xffdb
	ans.push_back(0x00);ans.push_back(0x84); //132！数据长度
	ans.push_back(0x00); //第0个量化表 是L的量化表！注意量化表的输出也要zigzag
	int tmp[64], tmp1[64];
	for (int i = 0;i < 8;i++)
		for (int j = 0;j < 8;j++)
			tmp[i * 8 + j] = Q[0][i][j];
	for (int i = 0;i < 64;i++)tmp1[ZigZag[i]] = tmp[i];
	for (int i = 0;i < 64;i++) ans.push_back(tmp1[i]);
	ans.push_back(0x01); //第1个量化表 是C的量化表！
	for (int i = 0;i < 8;i++)
		for (int j = 0;j < 8;j++)
			tmp[i * 8 + j] = Q[1][i][j];
	for (int i = 0;i < 64;i++)tmp1[ZigZag[i]] = tmp[i];
	for (int i = 0;i < 64;i++) ans.push_back(tmp1[i]);

	//SOF0 Start of Frame 帧图像开始--------------------------------------------------------------
	ans.push_back(0xff);ans.push_back(0xc0); //标记代码0xffc0
	ans.push_back(0x00);ans.push_back(0x11); //17！数据长度
	ans.push_back(0x08); //8位 精度
	ans.push_back(im_height >> 8);ans.push_back(im_height & 15); //图像高度
	ans.push_back(im_width >> 8);ans.push_back(im_width & 15);// 图像宽度
	ans.push_back(0x03); // 颜色分量数
	ans.push_back(0x01);ans.push_back(0x11);ans.push_back(0x00); //颜色分量ID (0 Y通道) 水平垂直采样因子 量化表ID
	ans.push_back(0x02);ans.push_back(0x11);ans.push_back(0x01); //颜色分量ID(1 Cr通道) 水平垂直采样因子 量化表ID
	ans.push_back(0x03);ans.push_back(0x11);ans.push_back(0x01); //颜色分量ID(1 Cb通道) 水平垂直采样因子 量化表ID

	//DHT Define Huffman Table 定义哈夫曼表------------------------------------------------------------
	ans.push_back(0xff);ans.push_back(0xc4); //标记代码0xffc4
	ans.push_back(0x01);ans.push_back(0xa2);//418！数据长度 
	ans.push_back(0x00); //DC 第0个哈夫曼表（L
	for (int i = 0;i < 16;i++)
		ans.push_back(Standard_DC_Luminance_NRCodes[i]);
	for (int i = 0;i < 12;i++)
		ans.push_back(Standard_DC_Luminance_Values[i]);
	ans.push_back(0x10); //AC 第0个哈夫曼表（L
	for (int i = 0;i < 16;i++)
		ans.push_back(Standard_AC_Luminance_NRCodes[i]);
	for (int i = 0;i < 162;i++)
		ans.push_back(Standard_AC_Luminance_Values[i]);
	ans.push_back(0x01); //DC 第1个哈夫曼表(C
	for (int i = 0;i < 16;i++)
		ans.push_back(Standard_DC_Chrominance_NRCodes[i]);
	for (int i = 0;i < 12;i++)
		ans.push_back(Standard_DC_Chrominance_Values[i]);
	ans.push_back(0x11); //AC 第1个哈夫曼表 (C
	for (int i = 0;i < 16;i++)
		ans.push_back(Standard_AC_Chrominance_NRCodes[i]);
	for (int i = 0;i < 162;i++)
		ans.push_back(Standard_AC_Chrominance_Values[i]);

	//SOS Start of Scan 扫描开始------------------------------------------------------------------
	ans.push_back(0xff);ans.push_back(0xda); //标记代码0xffda
	ans.push_back(0x00);ans.push_back(0x0c);//12! 数据长度
	ans.push_back(0x03); //颜色分量数
	ans.push_back(0x01);ans.push_back(0x00); //Y分量 直流0交流0
	ans.push_back(0x02);ans.push_back(0x11); //Cr分量 直流1交流1
	ans.push_back(0x03);ans.push_back(0x11); //Cb分量 直流1交流1
	ans.push_back(0x00);ans.push_back(0x3f);ans.push_back(0x00);

	//图像信息--------------------------------------------------------------------------------
	block* p = head;
	while (p->next != NULL) {
		p = p->next;
		DCT(p->Y);
		int tmp2[64];
		quantify(p->Y, 0, tmp2);
		zigzag(tmp2);
		Code(tmp2, 0, 0);

		DCT(p->Cb);
		quantify(p->Cb, 1, tmp2);
		zigzag(tmp2);
		Code(tmp2, 2, 1);

		DCT(p->Cr);
		quantify(p->Cr, 1, tmp2);
		zigzag(tmp2);
		Code(tmp2, 2, 2);
	}

	if (leftstr.length()) {
		int addzero = (8 - leftstr.length() % 8) % 8;
		for (int i = 0;i < addzero;i++)leftstr = leftstr + '0';
		bitset<8>bit(leftstr);
		unsigned char c = bit.to_ulong();
		ans.push_back(c);
		if (c == 0xff)  ans.push_back(0x00);
	}

	//EOI End of Image 扫描结束----------------------------------------------------------------------------
	ans.push_back(0xff);ans.push_back(0xd9);
}

void Delete() {
	block* p = head;
	while (p != NULL) {
		block* q = p->next;
		delete p;
		p = q;
	}
}

void Compress(const char* infile) {
	//预处理出所有的哈夫曼编码并存入unordered_map<unsigned char,string> Huffcode[4];中
	Init_Huffman_Code();

	PicReader imread;
	BYTE* data = nullptr;
	UINT x, y;
	imread.readPic(infile);
	imread.getData(data, x, y);

	head = new(nothrow) block;
	if (head == NULL) {
		cout << "内存申请失败" << endl;
		exit(0);
	}
	head->next = NULL;
	tail = head;

	for (int i = 0;i < x;i += 8)
		for (int j = 0;j < y;j += 8) {
			block* p = new(nothrow) block;
			if (p == NULL) {
				cout << "内存申请失败" << endl;
				exit(0);
			}
			tail->next = p, tail = p;

			for (int ki = i;ki < i + 8;ki++)
				for (int kj = j;kj < j + 8;kj++) {
					int cur = (ki * y + kj) * 4;
					p->Y[ki - i][kj - j] = 0.29871 * data[cur] + 0.58661 * data[cur + 1] + 0.11448 * data[cur + 2] - 128;
					p->Cb[ki - i][kj - j] = -0.16874 * data[cur] - 0.33126 * data[cur + 1] + 0.50000 * data[cur + 2];
					p->Cr[ki - i][kj - j] = 0.50000 * data[cur] - 0.41869 * data[cur + 1] - 0.08131 * data[cur + 2];
				}
			p->next = NULL;
		}

	delete[] data;
	data = nullptr;

	//打印文件头，压缩图像并输出至lena.jpg
	Get_ans(x, y);

	//输出
	const char* outfile = "lena.jpg";
	ofstream fl(outfile, ios::binary);
	if (!fl) {
		cout << "文件打开失败" << endl;
		exit(0);
	}
	fl << ans;
	fl.close();

	//释放动态申请的空间（链表）
	Delete();
}
void Show(const char* readfile) {
	printf("show lena, press enter to continue...");
	(void)getchar();

	PicReader imread;
	BYTE* data = nullptr;
	UINT x, y;
	imread.readPic(readfile);
	imread.getData(data, x, y);
	imread.showPic(data, x, y);

	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	(void)getchar();
}
int main(int argc, char** argv) {
	clock_t starttime, endtime;
	starttime = clock();

	if (argc != 3) {
		cerr << "Please make sure the number of parameters is correct." << endl;
		return -1;
	}

	if (strcmp(argv[1], "-compress") == 0) {
		Compress(argv[2]);
	}
	else if (strcmp(argv[1], "-read") == 0) {
		Show(argv[2]);
	}
	else {
		cerr << "Unknown parameter!\nCommand list:\nzip/unzip" << endl;
		return -1;
	}

	endtime = clock();
	cerr << "程序运行时间：" << 1.00 * (endtime - starttime) / CLOCKS_PER_SEC << "s" << endl;

	return 0;
}