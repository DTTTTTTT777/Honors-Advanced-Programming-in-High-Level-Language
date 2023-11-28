#include<iostream>
#include<conio.h>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

const int N = 300;
int len1, wid1, len2, wid2;
int m1[N][N], m2[N][N], m3[N][N];

void wait_for_enter(){
	cout << endl << "按回车键继续";
	while (_getch() != '\r');
	cout << endl << endl;
	return;
}

void menu() {

	const int width = 15;

	for (int i = 1;i <= width*4-4;i++)cout << '*';
	cout << endl;

	cout << " *";
	for (int i = 1;i <= width - 7;i++)cout << ' ';
	cout << std::left << setw(width) << "1 矩阵加法";
	cout << std::left << setw(width) << "2 矩阵数乘";
	cout << std::left << setw(width) << "3 矩阵转置";
	cout << '*' << endl;

	cout << " *";
	for (int i = 1;i <= width - 7;i++)cout << ' ';
	cout << std::left << setw(width) << "4 矩阵乘法";
	cout << std::left << setw(width) << "5 Hadamard乘积";
	cout << std::left << setw(width) << "6 矩阵卷积";
	cout << '*' << endl;

	cout << " *";
	for (int i = 1;i <= width - 7;i++)cout << ' ';
	cout << std::left << setw(width) << "7 卷积应用";
	cout << std::left << setw(width) << "8 OTSU算法";
	cout << std::left << setw(width) << "0 退出系统";
	cout << '*' << endl;

	for (int i = 1;i <= width*4-4;i++)cout << '*';
	cout << endl << "选择菜单项<0~8>:" << endl;
}

void matri_input() {
	cout << "请输入矩阵的行数和与列数" << endl;
	cin >> len1 >> wid1;
	cout << "请输入矩阵" << endl;
	for (int i = 1;i <= len1;i++)
		for (int j = 1;j <= wid1;j++)
			cin >> m1[i][j];
}
void matri1_input() {
	cout << "请输入第一个矩阵的行数和与列数" << endl;
	cin >> len1 >> wid1;
	cout << "请输入第一个矩阵" << endl;
	for (int i = 1;i <= len1;i++)
		for (int j = 1;j <= wid1;j++)
			cin >> m1[i][j];
}
void matri2_input() {
	cout << "请输入第二个矩阵的行数与列数" << endl;
	cin >> len2 >> wid2;
	cout << "请输入第二个矩阵" << endl;
	for (int i = 1;i <= len2;i++)
		for (int j = 1;j <= wid2;j++)
			cin >> m2[i][j];
}

void matri_output(int start, int len, int wid) { //输出答案矩阵

	int Width = 1; //获取矩阵输出时 合适的 每一个数字所占宽度
	for (int i = start;i <= len;i++)
		for (int j = start;j <= wid;j++)
			while ((m3[i][j] / (int)pow(10, Width)) != 0)Width++;
	Width += 2;

	cout << endl << "运算结果为：" << endl << endl;

	for (int i = start;i <= len;i++) {
		for (int j = start;j <= wid;j++) 
			cout << setw(Width) << m3[i][j];
		cout << endl;
	}

	wait_for_enter();

	return;
}

void matriplus() { //1：矩阵加法

	matri1_input(); //输入两个矩阵
	matri2_input();

	if (len1 != len2 || wid1 != wid2) { //若输入不合法
		cout << endl << "输入错误，只有同型矩阵的加法运算有意义" << endl;
		cout << "请重新选择菜单项" << endl;
		wait_for_enter();
		return;
	}

	for (int i = 1;i <= len1;i++) 
		for (int j = 1;j <= wid1;j++) 
			m3[i][j] = m1[i][j] + m2[i][j];

	matri_output(1, len1, wid1);

	return;
}

void nummulti() { //2：矩阵数乘

	matri_input(); //输入矩阵

	int num; //输入数字
	cout << "请输入矩阵需乘上的数字" << endl;
	cin >> num;

	for (int i = 1;i <= len1;i++) 
		for (int j = 1;j <= wid1;j++) 
			m3[i][j] = m1[i][j] * num;

	matri_output(1, len1, wid1);

	return;
}

void matritrans() { //3：矩阵转置

	matri_input();

	for (int i = 1;i <= wid1;i++) 
		for (int j = 1;j <= len1;j++) 
			m3[i][j] = m1[j][i];

	matri_output(1, wid1, len1);

	return;
}
void matrimulti() { //4：矩阵乘法

	matri1_input();
	matri2_input();

	if (len2 != wid1) {
		cout << endl << "输入错误，第一个矩阵的列数与第二个矩阵的行数相等运算才有意义" << endl;
		cout << "请重新选择菜单项" << endl;
		wait_for_enter();
		return;
	}

	for (int i = 1;i <= len1;i++) 
		for (int j = 1;j <= wid2;j++) 
			for (int k = 1;k <= len2;k++)
				m3[i][j] += m1[i][k] * m2[k][j];

	matri_output(1, len1, wid2);

	return;
}

void hadamulti() { //5：Hadamard乘积

	matri1_input();
	matri2_input();

	if (len1 != len2 || wid1 != wid2) {
		cout << endl << "输入错误，只有同型矩阵的Hadamard乘积才有意义" << endl;
		cout << "请重新选择菜单项" << endl;
		wait_for_enter();
		return;
	}

	for (int i = 1;i <= len1;i++) 
		for (int j = 1;j <= wid1;j++) 
			m3[i][j] = m1[i][j] * m2[i][j];

	matri_output(1, len1, wid1);

	return;
}

void conv() { //6：矩阵卷积

	matri1_input();
	matri2_input();

	len1++, wid1++; //由于padding(填补)=1;

	if (len2 != 3 || wid2 != 3) {
		cout << endl << "输入错误，请输入3*3的kernel矩阵" << endl;
		cout << "请重新选择菜单项" << endl;
		wait_for_enter();
		return;
	}

	for (int i = 0;i <= len1 - 2;i++)//枚举卷积结果矩阵的坐标
		for (int j = 0;j <= wid1 - 2;j++) {
			for (int lk = 0;lk < 3;lk++)//计算该坐标的值
				for (int rk = 0;rk < 3;rk++)
					m3[i][j] += m1[i + lk][j + rk] * m2[lk + 1][rk + 1];
		}

	matri_output(0, len1 - 2, wid1 - 2);

	return;
}

Mat demo_conv(Mat m, int B[3][3]) {

	cvtColor(m, m, CV_BGR2GRAY); //将待处理图形转为灰度图
	len1 = m.rows, wid1 = m.cols;//得到待处理图形的行数和列数

	for (int i = 0;i < len1;i++) //将Mat转化成二维数组以进行运算
		for (int j = 0;j < wid1;j++) {
			m1[i][j] = m.at<uchar>(i, j);
		}

	int sum=0; //计算卷积核的总和sum
	for (int i = 0;i < 3;i++)
		for (int j = 0;j < 3;j++)
			sum += B[i][j];

	memset(m3, 0, sizeof(m3)); //由于多次调用此函数，需要初始化m3即答案矩阵

	//开始卷（积）啦
	for (int i = 0;i < len1 - 2;i++) { //枚举卷积答案矩阵的坐标
		for (int j = 0;j < wid1 - 2;j++) {

			for (int lk = 0;lk < 3;lk++) //计算该坐标的值
				for (int rk = 0;rk < 3;rk++)
					m3[i][j] += m1[i + lk][j + rk] * B[lk][rk];

			if (sum)m3[i][j] /= sum;

			if (m3[i][j] < 0)m3[i][j] = 0; //注意到灰度值的取值范围是0~255！！！
			if (m3[i][j] > 255)m3[i][j] = 255;
		
		}
	}

	for (int i = 0;i < len1;i++) //将卷积结果复制给Mat类型的m并返回
		for (int j = 0;j < wid1;j++) {
			m.at<uchar>(i,j) = m3[i][j];
		}

	return m;
}

void demo() { //7：卷积应用

	Mat image = imread("demolena.jpg"); //获取lena原图 
	
	int B1[3][3] = { {1,1,1},{1,1,1},{1,1,1} }; //定义卷积核们
	int B2[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
	int B3[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
	int B4[3][3] = { {-1,-1,-1},{-1,9,-1},{-1,-1,-1} };
	int B5[3][3] = { {-1,-1,0},{-1,0,1},{0,1,1} };
	int B6[3][3] = { {1,2,1},{2,4,2},{1,2,1} };

	Mat image1=demo_conv(image, B1); //调用函数得到不同卷积处理后的lena
	Mat image2 = demo_conv(image, B2);
	Mat image3 = demo_conv(image, B3);
	Mat image4 = demo_conv(image, B4);
	Mat image5 = demo_conv(image, B5);
	Mat image6 = demo_conv(image, B6);

	imshow("original_Image", image);//显示所有的lena！
	imshow("B1卷积Image", image1); 
	imshow("B2卷积Image", image2);
	imshow("B3卷积Image", image3);
	imshow("B4卷积Image", image4);
	imshow("B5卷积Image", image5);
	imshow("B6卷积Image", image6);
	waitKey(0);
	
	wait_for_enter();

	return;
}

void otsu() { //8:OTSU算法
	Mat origin_image = imread("demolena.jpg"); //获取lena原图 
	Mat result_image = origin_image;

	cvtColor(origin_image, origin_image, CV_BGR2GRAY); //将待处理图形转为灰度图
	cvtColor(result_image, result_image, CV_BGR2GRAY); 

	len1 = origin_image.rows, wid1 = origin_image.cols;//得到待处理图形的行数和列数

	int maxG = 0, ansT;

	for (int T = 0;T <= 255;T++) { //用otsu算法找到阈值！

		int N0 = 0, N1 = 0;
		double w0=0, w1=0, u0=0, u1=0;

		for (int i = 0;i < len1;i++)
			for (int j = 0;j < wid1;j++) {
				int val = origin_image.at<uchar>(i, j);
				if (val < T)
					N0++, u0 += (double)val;
				else 
					N1++, u1 += (double)val;
			}

		w0 = 1.0 * N0 / (N0 + N1), w1 = 1.0 * N1 / (N0 + N1);
		u0 /= N0, u1 /= N1;

		int G = w0 * w1 * pow(u0 - u1, 2);
		if (G > maxG)maxG = G, ansT = T;
	}

	for (int i = 0;i < len1;i++)
		for (int j = 0;j < wid1;j++){
			int val = origin_image.at<uchar>(i, j);
			if(val>ansT) result_image.at<uchar>(i, j)=255;
			else result_image.at<uchar>(i, j)=0;
		}

	imshow("Origin", origin_image);
	imshow("Result", result_image);
	waitKey(0);

	wait_for_enter();

	return;
}

int main() {

	wait_for_enter();

	while (1) {

		system("cls");//清屏并显示菜单
		menu();

		char choice = _getch();//输入选择的菜单项

		if (choice == '0') {//退出系统
			cout << endl << "确定退出吗？退出请输入y，继续请输入n" << endl;
			char ch;
			cin >> ch;
			if (ch == 'y')break;
			else continue;
		}

		memset(m1, 0, sizeof(m1));//初始化矩阵数组！
		memset(m2, 0, sizeof(m2));
		memset(m3, 0, sizeof(m3));

		switch (choice) {
		case'1':
			matriplus(); //1：矩阵加法
			break;
		case'2':
			nummulti(); //2：矩阵数乘
			break;
		case'3':
			matritrans(); //3：矩阵转置
			break;
		case'4':
			matrimulti(); //4：矩阵乘法
			break;
		case'5':
			hadamulti(); //5：Hadamard乘积
			break;
		case'6':
			conv(); //6：矩阵卷积
			break;
		case'7':
			demo(); //7：卷积应用
			break;
		case'8':
			otsu();
			break;
		default:
			cout << endl << "输入错误，请重新输入" << endl;
			wait_for_enter();
		}
	}

	return 0;
}