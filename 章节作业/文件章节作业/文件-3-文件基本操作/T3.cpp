#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>

using namespace std;

int dat[20];

void readFromStdin() {
	for (int i = 0;i < 10;i++)
		cin >> dat[i];
}

void readFromFile() {
	FILE* infile = fopen("D:\\1.txt", "r");
	if (infile == NULL) {
		cout << "can't open file 1.txt\n";
		exit(1);
	}
	for (int i = 10;i < 20;i++) {
		if (fscanf(infile, "%d", &dat[i]) < 0) {
			cout << "can't read file 1.txt\n";
			exit(1);
		}
	}
	fclose(infile);
}

void outToFile() {
	FILE* outfile = fopen("1.out", "w");
	if (outfile == NULL) {
		cout << "can't open file 1.out\n";
		exit(1);
	}
	for (int i = 0;i < 20;i++) {
		if (fprintf(outfile, "%d ", dat[i]) < 0) {
			cout << "can't write file 1.out\n";
			exit(1);
		}
	}
	fclose(outfile);

	cout << "已将数据从小到大排序后输出到文件1.out\n";
}

void sort() {
	for (int k = 0;k < 20;k++) {
		for (int i = 0;i + 1 < 20 - k;i++)
			if (dat[i] > dat[i + 1])
				swap(dat[i], dat[i + 1]);
	}
}

int main() {
	readFromStdin();
	readFromFile();

	sort();

	outToFile();

	return 0;
}