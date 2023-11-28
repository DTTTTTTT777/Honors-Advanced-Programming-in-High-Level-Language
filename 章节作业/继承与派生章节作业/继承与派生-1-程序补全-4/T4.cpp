#include <iostream>

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

class Student1 : public Student
{
public:
    Student1();
    ~Student1();
    void get_value1();
    void display1();
private:
    int age;
    char* addr;
};

Student1::Student1() {
    addr = new char[20];
    //get_value1();
    age = 0;
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
    stud1.get_value1();
    stud1.display1();
    return 0;
}
/*
* Analysis:
* 定义一个Student1类型的stud1时
    在Student1的构造函数中先自动激活基类（Student）的构造函数
    然后执行Student1的构造函数中的语句

    在stud1出作用域时，自动调用派生类（Student1）的析构函数
    执行完毕后自动调用基类（Student）的析构函数

    总之，构造函数先基类再派生类，析构函数先派生类再基类。
*/
/*
* public和protected两种继承方式的比较分析：
* 采用公用继承方式时：
* 基类成员访问控制为public和protected的成员在派生类中访问控制相同，privated的不可访问
* 采用保护继承方式时：
* 基类成员访问控制为public和protected的成员在派生类中均为protected,private的不可访问
* 
* 二者的不同之处在于，基类成员为public时，派生类中访问控制分别为public和protected。
* 
* 何种情况下二者不能互相代替？
* 对于public的基类成员，若要求必须能够域外访问，则只能公用继承而不能保护继承；
    若要求必须不能够在域外访问，则公用继承不能代替保护继承。
*/