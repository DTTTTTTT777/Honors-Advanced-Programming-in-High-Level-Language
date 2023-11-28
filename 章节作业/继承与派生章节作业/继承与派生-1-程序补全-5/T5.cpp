#include<iostream>

using namespace std;

class Teacher {
protected:
	char* name;
	int age;
	char sex;
	char* address;
	long long tele;
	char* title;
public:
	Teacher();
	~Teacher();
	void display();
};

class Cadre {
protected:
	char* name;
	int age;
	char sex;
	char* address;
	long long tele;
	char* post;
public:
	Cadre();
	Cadre(int);
	~Cadre();
	void display();
};

class Teacher_Cadre : protected Teacher, protected Cadre {
private:
	int wages;
public:
	Teacher_Cadre();
	void show();
};

Teacher::Teacher() {
	name = new char[20];
	address = new char[20];
	title = new char[20];
	cin >> name >> age >> sex >> address >> tele >> title;
}
Teacher::~Teacher() {
	delete name;
	delete address;
	delete title;
}
void Teacher::display() {
	cout << "姓名:" << name << endl;
	cout << "年龄:" << age << endl;
	cout << "性别:" << sex << endl;
	cout << "地址:" << address << endl;
	cout << "电话:" << tele << endl;
	cout << "职称:" << title << endl;
}
Cadre::Cadre() {
	name = new char[20];
	address = new char[20];
	post = new char[20];
	cin >> name >> age >> sex >> address >> tele >> post;
}
Cadre::Cadre(int) {
	name = new char[20];
	address = new char[20];
	post = new char[20];
	cin >> post;
	//address = (char*)"";name = (char*)"";
	age = 0, sex = 0, tele = 0;
}
Cadre::~Cadre() {
	delete name;
	delete address;
	delete post;
}
void Cadre::display() {
	cout << "姓名:" << name << endl;
	cout << "年龄:" << age << endl;
	cout << "性别:" << sex << endl;
	cout << "地址:" << address << endl;
	cout << "电话:" << tele << endl;
	cout << "职务:" << post << endl;
}
Teacher_Cadre::Teacher_Cadre():Teacher(),Cadre(0) {
	cin >> wages;
}
void Teacher_Cadre::show() {
	Teacher::display();
	cout << "职务:" << post << endl;
	cout << "薪水:" << wages << endl;
}
int main() {
	int type;
	cin >> type;
	switch(type) {
	case 0: {
		Teacher tea;
		cout << "教师信息如下" << endl;
		tea.display();
		break;
	}
	case 1: {
		Cadre cad;
		cout << "干部信息如下" << endl;
		cad.display();
		break;
	}
	case 2: {
		Teacher_Cadre tc;
		cout << "教师兼干部信息如下" << endl;
		tc.show();
		break;
	}
	}
	return 0;
}