class Teacher;
class Student;

class Teacher {
private:
    int id, age, gender;
    char name[100];
public:
    Teacher();
    explicit Teacher(Student&);
    void show_info();
};

class Student {
private:
    int id, age, gender;
    char name[100];
public:
    friend class Teacher;
    Student(int, int, int, char*);
    void show_info();
};

Teacher::Teacher() :id(0), age(0), gender(0) {
    strcpy(name, "");
}
Teacher::Teacher(Student& stu) {
    id = stu.id;
    age = stu.age;
    gender = stu.gender;
    strcpy(name, stu.name);
}
void Teacher::show_info() {
    cout << "教师号:" << id << " ";
    cout << "教师年龄:" << age << "岁 ";
    if (gender == 0)
        cout << "教师性别:女 ";
    else
        cout << "教师性别:男 ";
    cout << "教师姓名:" << name << endl;
}
Student::Student(int x, int y, int z, char* s) :id(x), age(y), gender(z) {
    strcpy(name, s);
}
void Student::show_info() {
    cout << "学生学号:" << id << " ";
    cout << "学生年龄:" << age << "岁 ";
    if (gender == 0)
        cout << "学生性别:女 ";
    else
        cout << "学生性别:男 ";
    cout << "学生姓名:" << name << endl;
}
