#include<iostream>
#include<fstream>
#include<iomanip>
#include<utility>
using namespace std;

struct student {
    int no;
    char name[20];
    int score;
    struct student* next;
}*head = NULL, * tail = NULL;

int n;

void menu() {
    int i;
    std::cout << std::endl;
    for (i = 0; i < 57; i++)
        std::cout << '*';
    std::cout << std::endl;
    std::cout << "*\t1 显示记录\t2 统计记录\t3 排序记录\t*\n";
    std::cout << "*\t4 查找记录\t5 删除记录\t6 修改记录\t*\n";
    std::cout << "*\t7 添加记录\t0 退出系统\t\t\t*\n";
    for (i = 0; i < 57; i++)
    {
        std::cout << '*';
    }
    std::cout << std::endl;
}

void read() {
    ifstream file("d:\\student.txt");
    file >> n;

    for (int i = 1;i <= n;i++) {
        student* p = new(nothrow) student;
        if (p == NULL) {
            cout << "动态申请内存失败" << endl;
            exit(0);
        }
        file >> (p->no) >> (p->name) >> (p->score);
        p->next = NULL;
        if (head == NULL)
            head = p, tail = p;
        else
            tail->next = p, tail = p;
    }

    file.close();
}

void quit() {
    student* p = head, * q;
    while (p != NULL) {
        q = p;
        p = p->next;
        delete q;
    }
}

void disp() {
    student* p = head;
    const int width = 10;
    while (p != NULL) {
        cout << "学号：" << std::left << setw(width) << (p->no);
        cout << "姓名：" << std::left << setw(width) << (p->name);
        cout << "成绩：" << std::left << setw(width) << (p->score) << endl;
        p = p->next;
    }
}

void count() {
    int ans[6];
    for (int i = 1;i <= 5;i++)
        ans[i] = 0;

    student* p = head;
    while (p != NULL) {
        int score = p->score;
        if (score >= 90)
            ans[1]++;
        else if (score >= 80)
            ans[2]++;
        else if (score >= 70)
            ans[3]++;
        else if (score >= 60)
            ans[4]++;
        else
            ans[5]++;

        p = p->next;
    }

    const int width = 10;
    cout << std::left << setw(width) << "优：" << setw(width) << ans[1] << endl;
    cout << std::left << setw(width) << "良：" << setw(width) << ans[2] << endl;
    cout << std::left << setw(width) << "中：" << setw(width) << ans[3] << endl;
    cout << std::left << setw(width) << "及格：" << setw(width) << ans[4] << endl;
    cout << std::left << setw(width) << "不及格：" << setw(width) << ans[5] << endl;

}

void update_tail() {
    student* p = head;
    while (p != NULL) {
        tail = p;
        p = p->next;
    }
}

void stu_swap(student* p1, student* p2, student* p3) {
    if (p2 == head)
        head = p3;
    else p1->next = p3;
    p2->next = p3->next;
    p3->next = p2;
}

void sort1(student* last, student* cur, int num, int done) {
    if (num >= n - done)
        return;
    student* next = cur->next;
    if ((cur->score < next->score) || (cur->score == next->score && cur->no > next->no)) {
        stu_swap(last, cur, next);
        swap(cur, next); //这两个交换都必不可少！！
    }
    sort1(cur, next, num + 1, done);
}

void sort() {
    int done = 0;
    while (done < n) {
        sort1(NULL, head, 1, done);
        done++;
    }
    update_tail();
    //排序后要记得更新tail！因为后续还可能加入结点
}

bool iscontinue() {
    char c;
    cout << "是否继续查询？y or n" << endl;
    cin >> c;
    if (c == 'y' || c == 'Y')
        return 1;
    else return 0;
}

pair<student*, student*> searchbyID1(int num) {
    student* p = head, * last = NULL;
    while (p != NULL) {
        if (p->no == num)
            return { last,p };
        else
            last = p, p = p->next;
    }
    return { NULL,NULL };
}

void searchbyID() {
    int num;
    while (1) {
        cin >> num;
        student* p = searchbyID1(num).second;
        if (p == NULL)
            cout << "Not Exist" << endl;
        else {
            const int width = 10;
            cout << "学号：" << std::left << setw(width) << (p->no);
            cout << "姓名：" << std::left << setw(width) << (p->name);
            cout << "成绩：" << std::left << setw(width) << (p->score) << endl;
        }
        if (!iscontinue())
            return;
    }
}

void deleteptr(student* last, student* p) {
    if (p == head)
        head = p->next;
    else
        last->next = p->next;
    delete p;
}

void delbyID() {
    int num;
    while (1) {
        cin >> num;
        pair<student*, student*> ot = searchbyID1(num);

        if (ot.second == NULL)
            cout << "Not Exist" << endl;
        else deleteptr(ot.first, ot.second);

        if (!iscontinue())
            return;
    }

}

void modibyID() {
    int num;
    while (1) {
        cin >> num;
        student* p = searchbyID1(num).second;

        if (p == NULL)
            cout << "Not Exist" << endl;
        else {
            int newscore;
            cin >> newscore;
            p->score = newscore;
        }

        if (!iscontinue())
            return;
    }
}

void addnode(int num) {
    student* p = new(nothrow) student;
    if (p == NULL) {
        cout << "动态申请内存失败" << endl;
        exit(0);
    }
    p->no = num;
    cin >> (p->name) >> (p->score);
    p->next = NULL;
    if (head == NULL)
        head = p, tail = p;
    else
        tail->next = p, tail = p;
    n++;
}

void addbyID() {
    int num;
    while (1) {
        cin >> num;
        student* p = searchbyID1(num).second;
        if (p != NULL)
            cout << "Existed" << endl;
        else
            addnode(num);
        if (!iscontinue())
            return;
    }
}

int main() {
    read();
    menu();

    while (true) {
        //system("CLS");
        // /* 清屏函数，为防止沙箱判断失误，请提交时保留此项为注释 */
        int choice;
        char ch;

        std::cout << "选择菜单项(0~7):" << endl;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "\n 确定退出吗?(y/n)" << std::endl;
            std::cin >> ch;
            if (ch == 'y' || ch == 'Y') {
                quit();
                break;
            }
            else
                continue;
        }
        switch (choice) {
        case 1:
            disp(); //显示记录
            break;
        case 2:
            count(); // 统计记录
            break;
        case 3:
            sort(); // 排序记录
            break;
        case 4:
            searchbyID(); // 查找记录
            break;
        case 5:
            delbyID(); // 删除记录
            break;
        case 6:
            modibyID(); // 修改记录
            break;
        case 7:
            addbyID(); // 添加记录
            break;
        default:
            std::cout << "\n输入错误，请从新输入" << std::endl;
        }
    }
    return 0;
}