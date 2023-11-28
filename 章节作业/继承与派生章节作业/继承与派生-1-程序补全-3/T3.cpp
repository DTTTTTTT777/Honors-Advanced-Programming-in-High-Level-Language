#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
    Student();
    ~Student();

protected:
    int num;
    char* name;
    char sex;
};

Student::Student() {
    name = new char[20];
    num = 0, sex = 'm';
}
Student:: ~Student() {
    delete name;
}

class Student1 : protected Student
{
public:
    void get_value1();
    void display1();
    Student1();
    ~Student1();

private:
    int age;
    char* addr;
};

Student1::Student1() {
    addr = new char[20];
    get_value1();
}
Student1::~Student1() {
    delete addr;
}
void Student1::get_value1()
{
    cin >> num >> name >> sex;
    cin >> age >> addr;
}
void Student1::display1()
{
    cout << " name: " << name << endl;
    cout << " num: " << num << endl;
    cout << " sex: " << sex << endl;
    cout << " age: " << age << endl;
    cout << " address: " << addr << endl;
}

int main()
{
    Student1 stud1;
    stud1.display1();
    return 0;
}