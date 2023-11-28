#include<iostream>

using namespace std;

class Student
{
public:
    void get_value()
    {
        cin >> num >> name >> sex;
    }

    void display()
    {
        cout << " name: " << name << endl;
        cout << " num: " << num << endl;
        cout << " sex: " << sex << endl;
    }

    Student() {
        name = new char[20];
        get_value();
    }

    ~Student() {
        delete name;
    }

private:
    int num;
    char* name;
    char sex;
};

class Student1 : public Student
{
public:

    void get_value_1()
    {
        cin >> age >> addr;
    }
    void display_1()
    {
        display();
        cout << " age: " << age << endl;
        cout << " address: " << addr << endl;
    }

    Student1() {
        addr = new char[20];
        get_value_1();
    }

    ~Student1() {
        delete addr;
    }

private:
    int age;
    char* addr;
};

int main()
{
    Student1 stud;
    stud.display_1();
    return 0;
}