#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

struct student {
	int no;
	char name[20];
	int score;
	struct student* next;
};

int main() {

	FILE* file = fopen("d:\\student.txt", "r");
	if (file == NULL) {
		printf("文件打开失败\n");
		return 0;
	}

	int n,inum;
	inum = fscanf(file, "%d", &n);
	if (inum == 0) {
		printf("文件读取有误\n");
		return 0;
	}

	struct student* head = NULL, * tail = NULL;

	int i;
	for (i = 1;i <= n;i++) {
		struct student* p = NULL;
		p = (struct student*)malloc(sizeof(struct student));
		if (p == NULL) {
			printf("动态内存申请失败\n");
			return 0;
		}

		inum = fscanf(file, "%d%s%d", &(p->no), p->name, &(p->score));

		if (inum < 3) {
			printf("文件读取有误\n");
			return 0;
		}

		p->next = NULL;
		if (head == NULL)
			head = p, tail = p;
		else
			tail->next = p, tail = p;
	}

	fclose(file);//记得！关文件！！！

	struct student* p = head, * q;
	const int width = 10;
	while (p != NULL) {
		printf("学号:%-10d 姓名:%-10s 成绩:%-10d\n", p->no, p->name, p->score);
		q = p;
		p = p->next;
		free(q);
	}

	return 0;

}