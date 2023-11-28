#include"PicReader.h"
#include"FastPrinter.h"
using namespace std;

char asciiStrength[] = { 'M','N','H','Q','$','0','C','?','7','>','!',':','-',';','.' };
int tmp[200][200];

void func(const char* infile) {
	PicReader imread;
	imread.readPic(infile);
	UINT x, y;
	Array arr1 = imread.getData(y, x); //y是宽度（横），x是长度（竖）

	if (x != y) {
		if (x < y) y = x;
		else x = y;
	}

	Array arr2(x, y);
	for (int i = 0;i < x;i++) {
		for (int j = 0;j < y;j++) {
			arr2[i][j] = int((int)arr1[i][j][0] * 299 + (int)arr1[i][j][1] * 587 + (int)arr1[i][j][2] * 114 + 500) / 1000; //计算灰度
		}
	}
	
	const int div = min(x,y) / 120 + 1;
	for (int i = 0;i < x / div;i++) {
		for (int j = 0;j < y / div;j++) {
			tmp[i][j] = 0;
			for (int ki = div * i;ki < div * i + div;ki++) {
				for (int kj = div * j;kj < div * j + div;kj++) {
					tmp[i][j] += int(arr2[ki][kj]);
				}
			}
			tmp[i][j] = tmp[i][j] / (div * div);
		}
	}
	for (int i = 0;i < x / div;i++)
		for (int j = 0;j < y / div;j++) {
			arr2[i][j] = unsigned char(int(tmp[i][j]));
		}
	x /= div, y /= div;

	FastPrinter printer(y * 2, x, 3);
	printer.cleanSrceen();

	char* dataBuffer = new char[200 * 200];
	for (int i = 0;i < x;i++)
		for (int j = 0;j < y * 2;j += 2) {
			unsigned char asciiIndex = int(arr2[i][j / 2]) / 18;
			dataBuffer[i * y * 2 + j] = asciiStrength[asciiIndex];
			dataBuffer[i * y * 2 + j + 1] = asciiStrength[asciiIndex];
		}

	BYTE* frontColorBuffer = new BYTE[200 * 200 * 3];
	BYTE* backColorBuffer = new BYTE[200 * 200 * 3];

	for (int i = 0;i < x * y * 6;i++) {
		frontColorBuffer[i] = 0;
		backColorBuffer[i] = 255;
	}


	/*SMALL_RECT drawArea;
	drawArea.Left = 0;
	drawArea.Right = y*2-1;
	drawArea.Top = 0;
	drawArea.Bottom = x-1;*/

	printer.setData(dataBuffer, frontColorBuffer, backColorBuffer);
	//printer.setData(dataBuffer, frontColorBuffer, backColorBuffer, drawArea);
	printer.draw(true);

	getchar();

	delete[] dataBuffer;
	delete[] frontColorBuffer;
	delete[] backColorBuffer;
	arr1.releaseData();
	arr2.releaseData();
}

int main() {
	cout << "每输出一张字符画，回车跳转至下一张" << endl;
	cout << "提醒：第一张图片的等候时间稍长..." << endl;
	cout << "按回车键开始" << endl;
	getchar();


	//func("picture\\compa.png");
	//func("picture\\goldhill.jpg");
	//func("picture\\barbara.jpg");

	func("picture\\airplane.jpg");
	func("picture\\baboon.jpg");
	func("picture\\cameraman.jpg");
	func("picture\\lena.jpg");
	func("picture\\milkdrop.jpg");
	func("picture\\peppers.jpg");
	func("picture\\woman.jpg");
	return 0;
}

//
//int main()
//{
//    {
//    // 1，至少能初始化三个维度的数组，即该类至少需要支持三维索引（可通过重载[]或使用成员函数实现）。
//
//        cout << "##1-------------初始化数组" << endl;
//    // example
//        Array a(3, 3); // the shape with 3x3
//        //{a[2][2] = 10;}
//        //cout << int(a[2][2]) << "$" << endl;
//        //return 0;
//        for (int i = 0; i < 3; i++)
//        {
//            for (int j = 0; j < 3; j++)
//            {
//                a[i][j] = i * j;
//                //cout << i << "*" << j << "=" << i * j << endl;
//                //cout << "a[" << i << "][" << j << "]=" << int(a[i][j]) << endl;
//                // or
//                //a.at(i, j).set(i * j);
//            }
//        }
//        for (int i = 0;i < 3;i++) {
//            for (int j = 0;j < 3;j++) {
//                cout << int(a[i][j]) << "| ";
//            }
//            cout << endl;
//        }
//
//        /*for (int i = 0;i < 3;i++) {
//            for (int j = 0;j < 3;j++)
//                cout << "a[" << i << "][" << j << "]=" << int(a[i][j]) << endl;
//        }*/
//
//    }
//
//    //return 0;
//
//    {
//        // 2，具备基本的矩阵操作功能，至少拥有：矩阵加减法，矩阵点乘点除的操作（具体算法可参看上学期之大作业1）。
//
//        // example
//        Array a(2, 2), b(2, 2), c(2, 2), d(2, 2);
//        int cnt = 1;
//        for (int i = 0; i < 2; i++)
//            for (int j = 0; j < 2; j++)
//            {
//                a[i][j] = cnt;
//                b[i][j] = cnt;
//                cnt++;
//                //cout << "a[" << i << "][" << j << "]=" << int(a[i][j]) << endl;
//            }
//        /*
//        a: [1, 2     b: [1, 2
//            3, 4]        3, 4]
//        */
//
//        cout << "a：" << endl;
//        for (int i = 0;i < 2;i++) {
//            for (int j = 0;j < 2;j++)
//                cout << a[i][j] << " ";
//            cout << endl;
//        }
//
//        cout << "b：" << endl;
//        for (int i = 0;i < 2;i++) {
//            for (int j = 0;j < 2;j++)
//                cout << b[i][j] << " ";
//            cout << endl;
//        }
//
//        c = a + b;
//        d = a + 2;
//
//        cout << "c：" << endl;
//        for (int i = 0;i < 2;i++) {
//            for (int j = 0;j < 2;j++)
//                cout << c[i][j] << " ";
//            cout << endl;
//        }
//
//        cout << "d：" << endl;
//        for (int i = 0;i < 2;i++) {
//            for (int j = 0;j < 2;j++)
//                cout << d[i][j] << " ";
//            cout << endl;
//        }
//
//        /*
//        逐元素相加
//        c: [2, 4
//            6, 8]
//        d: [3, 4
//            5, 6]
//        */
//        c = a - b;
//        d = a - 2;
//        cout << "c：" << endl;
//        for (int i = 0;i < 2;i++) {
//            for (int j = 0;j < 2;j++)
//                cout << c[i][j] << " ";
//            cout << endl;
//        }
//
//        cout << "d：" << endl;
//        for (int i = 0;i < 2;i++) {
//            for (int j = 0;j < 2;j++)
//                cout << d[i][j] << " ";
//            cout << endl;
//        }
//        /*
//        逐元素相减
//        c: [0, 0
//            0, 0]
//        d: [-1, 0
//            1, 2]
//        */
//        c = a * b;
//        d = a * 2;
//        cout << "c：" << endl;
//        for (int i = 0;i < 2;i++) {
//            for (int j = 0;j < 2;j++)
//                cout << c[i][j] << " ";
//            cout << endl;
//        }
//
//        cout << "d：" << endl;
//        for (int i = 0;i < 2;i++) {
//            for (int j = 0;j < 2;j++)
//                cout << d[i][j] << " ";
//            cout << endl;
//        }
//
//        /*
//        逐元素相乘
//        c: [1, 4
//            9, 16]
//        d: [2, 4
//            6, 8]
//        */
//        c = a / b;
//        d = a / 2;
//        cout << "c：" << endl;
//        for (int i = 0;i < 2;i++) {
//            for (int j = 0;j < 2;j++)
//                cout << c[i][j] << " ";
//            cout << endl;
//        }
//
//        cout << "d：" << endl;
//        for (int i = 0;i < 2;i++) {
//            for (int j = 0;j < 2;j++)
//                cout << d[i][j] << " ";
//            cout << endl;
//        }
//        /*
//        逐元素相除
//        c: [1, 1
//            1, 1]
//        d: [0.5, 1
//            1.5, 2]    关于这里的小数qwq
//        注意：这个仅供参考，具体结果可能和你内部成员实现关联。
//        */
//    }
//
//    {
//        // 3，支持reshape操作，即从一个一维矩阵reshape成二维或三维矩阵。
//
//        // example
//      Array a(16);
//      for (int i = 0; i < 16; i++){
//         a[i] = i;
//      }
//      cout << "a：" << endl;
//      for (int i = 0;i < 16;i++)
//          cout << a[i] << " ";
//      cout << endl;
//      // a: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
//      a.reshape(4, 4);
//
//      cout << "a：" << endl;
//      for (int i = 0;i < 4;i++) {
//          for (int j = 0;j < 4;j++)
//              cout << a[i][j] << " ";
//          cout << endl;
//      }
//      cout << endl;
//        /*
//        a: [0,  1,  2,  3
//            4,  5,  6,  7
//            8,  9, 10, 11
//           12, 13, 14, 15]
//        */
//    }
//
//    {
//        // 4，支持获取c风格元数据操作，即从Array中获取一个指针，指针内的数据为你矩阵的元数据。
//
//        // example
//        Array a(4);
//        for (int i = 0; i < 4; i++)
//        {
//            a[i] = i;
//        }
//        // a: [0, 1, 2, 3]
//
//        int* b = a.get_content(); // 数据类型取决于你的实现
//        for (int i = 0; i < 4; i++)
//        {
//            cout << b[i] << ' ';
//        }
//        // output: 0 1 2 3
//    }
//  }
//  

	/*
	Sleep(2000);
	cout << x << " " << y << endl;
	return 0;*/
	/*COORD textXY;
	for (int i = 0;i < y;i+=1) {
		for (int j = 0;j < x*2;j+=2) {
			//printer.cleanSrceen();
			// 255 / 18 = 14，故不会导致越界且能划分出强度等级
			unsigned char asciiIndex = int(arr2[i][j/2]) / 18;
			//cout << asciiStrength[asciiIndex];
			textXY.X = j, textXY.Y = i;
			char* outchar = new char;
			*outchar = asciiStrength[asciiIndex];
			//cout << *outchar<<*outchar;
			//cout << i<<" "<<j/2<<" "<<arr2[i][j / 2] << " " << (int)asciiIndex << " " << *outchar << endl;
			printer.setText(textXY, outchar, 0, 0, 0, 255, 255, 255);
			printer.draw(true);
			textXY.X += 1;
			printer.setText(textXY, outchar, 0, 0, 0, 255, 255, 255);
			printer.draw(true);
			//Sleep(1000);
		}
		//cout << endl;
	}*/