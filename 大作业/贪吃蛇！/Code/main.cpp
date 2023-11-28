#define _CRT_SECURE_NO_WARNINGS
#include"classes.h"
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<windows.h>

using namespace std;

int Keyboard_monitor(int time_limit, bool flag) {
    time_t beg = clock(), cur;
    char black[] = "                ";     // 为输出填加的尾部空白，用于覆盖输出
    INPUT_RECORD inRec = { 0 };                    // 输入信息结构体，记录输入信息
    DWORD res;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);       // 获取控制台标准输入句柄
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);     // 获取控制台标准输出句柄

    // 开启控制台窗口鼠标输入
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    while (1) {
        cur = clock();
        //cout << (cur - beg) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
        if (flag && (cur - beg) * 1.0 / CLOCKS_PER_SEC * 1000 >= time_limit) break;

        // 获取当前输入信息，采用WaitForSingleObject来防止函数阻塞（异步监听）
        if (WaitForSingleObject(hInput, 0) == WAIT_OBJECT_0)
            ReadConsoleInputA(hInput, &inRec, 1, &res);

        // 将光标移动到左上角，覆盖输出
        COORD zeroPos = { 0,0 };
        SetConsoleCursorPosition(hOutput, zeroPos);

        if (flag && inRec.EventType == KEY_EVENT) {
            int num = inRec.Event.KeyEvent.uChar.UnicodeChar;
            if (num == 97 || num == 100 || num == 115 || num == 119 || num==27) return num;
        }
        if (flag) continue;
        // 监听事件状态
        switch (inRec.EventType) {
        case KEY_EVENT:
            // 键盘事件
            // dwControlKeyState 会记录键盘控制键状态，例如大小写是否开启等
            // wVirtualKeyCode wVirtualScanCode 是最终键盘按键的可以使用的组合变量
            return inRec.Event.KeyEvent.uChar.UnicodeChar;
            break;
        }
    }
    return -1;
}
int play(Game& G, Wall& W, Food& F, Snake& S, int mode) {

    int keyy = Keyboard_monitor(0, 0);
    while (keyy != 32) keyy = Keyboard_monitor(0, 0); //按空格开始游戏

    int is_over = 0;
    if (mode == 1) {
        while (is_over == 0) {
            int keyb = Keyboard_monitor(150, 1);
            int dir = S.get_dir();
            if (dir == 0 && keyb == 97)continue;
            if (dir == 1 && keyb == 100)continue;
            if (dir == 2 && keyb == 119)continue;
            if (dir == 3 && keyb == 115)continue;
            switch (keyb) {
            case -1:
                S.move(-1, G);
                break;
            case 97:
                S.move(1, G);
                break;
            case 100:
                S.move(0, G);
                break;
            case 115:
                S.move(2, G);
                break;
            case 119:
                S.move(3, G);
                break;
            case 27:
                return is_over;
                break;
            }
            coor* sh = S.snake_head();
            int type = G.query(sh->x, sh->y);

            if (type == 0) { //走到空白处，无事发生
                G.upd_map(sh->x, sh->y, 3);
            }
            else if (type == 1) { //撞到墙，游戏结束
                is_over = 1;
                //break;
            }
            else if (type == 2) { //吃到食物，长度加1，分数加5
                //cout << "bread！" << endl;
                F.remove(sh->x, sh->y, G); //在remove里擦白
                S.recover(G);
                G.upd_map(sh->x, sh->y, 3);
                G.add_score();
            }
            else if (type == 3) { //撞到自己，游戏结束
                is_over = 2;
            }
            Sleep(50);
        }
        if (is_over == 1) {
            IMAGE pic;
            loadimage(&pic, _T("./image/over1.jpg"), 300, 150);
            putimage(800 + 50, 350, &pic);
            return 1;
        }
        else if (is_over == 2) {
            IMAGE pic;
            loadimage(&pic, _T("./image/over2.jpg"), 300, 150);
            putimage(800 + 50, 350, &pic);
            return 2;
        }
    }
    else if (mode == 2) {
        bool ade = 1;
        while (!G.over() && ade) {
            int keyb = Keyboard_monitor(150, 1);
            int dir = S.get_dir();
            if (dir == 0 && keyb == 97)continue;
            if (dir == 1 && keyb == 100)continue;
            if (dir == 2 && keyb == 119)continue;
            if (dir == 3 && keyb == 115)continue;
            switch (keyb) {
            case -1:
                S.move(-1, G);
                break;
            case 97:
                S.move(1, G);
                break;
            case 100:
                S.move(0, G);
                break;
            case 115:
                S.move(2, G);
                break;
            case 119:
                S.move(3, G);
                break;
            case 27:
                return is_over;
                break;
            }
            coor* sh = S.snake_head();
            int type = G.query(sh->x, sh->y);

            if (type == 0) { //走到空白处，无事发生
                G.upd_map(sh->x, sh->y, 3);
            }
            else if (type == 1) { //撞到墙，游戏结束
                ade = S.reset(G, F, W, 1);//将原来的蛇变成新的墙壁，再产生新的蛇
                //is_over = 1;
                //break;
            }
            else if (type == 2) { //吃到食物，长度加1，分数加5
                //cout << "bread！" << endl;
                F.remove(sh->x, sh->y, G); //在remove里擦白
                S.recover(G);
                G.upd_map(sh->x, sh->y, 3);
                G.add_score();
            }
            else if (type == 3) { //撞到自己，游戏结束
                ade = S.reset(G, F, W, 1);
                //is_over = 2;
            }
            Sleep(50);
        }
        if (is_over == 1) {
            IMAGE pic;
            loadimage(&pic, _T("./image/over1.jpg"), 300, 150);
            putimage(800 + 50, 350, &pic);
            //return 1;
        }
        else if (is_over == 2) {
            IMAGE pic;
            loadimage(&pic, _T("./image/over2.jpg"), 300, 150);
            putimage(800 + 50, 350, &pic);
           // return 2;
        }
    }
    else if (mode == 3) {
        bool ade = 1;
        while (!G.over() && ade) {
            int keyb = Keyboard_monitor(150, 1);
            int dir = S.get_dir();
            if (dir == 0 && keyb == 97)continue;
            if (dir == 1 && keyb == 100)continue;
            if (dir == 2 && keyb == 119)continue;
            if (dir == 3 && keyb == 115)continue;
            switch (keyb) {
            case -1:
                S.move(-1, G);
                break;
            case 97:
                S.move(1, G);
                break;
            case 100:
                S.move(0, G);
                break;
            case 115:
                S.move(2, G);
                break;
            case 119:
                S.move(3, G);
                break;
            case 27:
                return is_over;
                break;
            }
            coor* sh = S.snake_head();
            int type = G.query(sh->x, sh->y);

            if (type == 0) { //走到空白处，无事发生
                G.upd_map(sh->x, sh->y, 3);
            }
            else if (type == 1) { //撞到墙，生命j--
                ade = S.reset(G, F, W, 2);//将原来的蛇变成新的食物，再产生新的蛇
                G.die();
                //is_over = 1;
                //break;
            }
            else if (type == 2) { //吃到食物，长度加1，分数加5
                //cout << "bread！" << endl;
                F.remove(sh->x, sh->y, G); //在remove里擦白
                S.recover(G);
                G.upd_map(sh->x, sh->y, 3);
                G.add_score();
            }
            else if (type == 3) { //撞到自己，生命--
                ade = S.reset(G, F, W, 2);
                G.die();
                //is_over = 2;
            }
            Sleep(50);
        }
        is_over = 3;
    }
    return is_over;
}
int main() {
    while (1) {
        srand(time(0));
        int mode = menu();
        while (mode == 0) {
            mode = menu();
        }
        cleardevice();
        if (mode == 4) {

            ifstream fl("./file./record.txt");
            if (!fl.is_open()) {
                cout << "文件打开失败" << endl;
                exit(1);
            }
            int is_over;
            fl >> is_over;
            if (is_over) {
                fl.close();
                cleardevice();
                IMAGE pic1, pic2, pic3;
                loadimage(&pic1, _T("./image/error.jpg"), 700, 200);
                putimage(250, 120, &pic1);
                loadimage(&pic2, _T("./image/nomore.jpg"), 700, 200);
                putimage(250, 375, &pic2);
                loadimage(&pic3, _T("./image/Esc.jpg"), 700 * 0.86, 200 * 0.86);
                putimage(300, 580, &pic3);
                while (Keyboard_monitor(0, 0) != 27); //按Esc退出

            }
            else {
                Game G(fl);
                Food F(fl, G);
                Wall W(fl, G);
                Snake S(fl, G);
                G.show_UI();
                int is_ov = play(G, W, F, S, G.get_mode());
                ofstream fl("./file./record.txt");
                if (!fl.is_open()) {
                    cout << "文件打开失败" << endl;
                    exit(1);
                }
                fl << is_ov << endl;
                fl.close();
                G.~Game();
                F.~Food();
                W.~Wall();
                S.~Snake();
                while (Keyboard_monitor(0, 0) != 27);
            }
        }
        else {
            Game G(mode);
            Food F(G);
            Wall W(G);
            Snake S(G);
            G.show_UI();
            int is_ov = play(G, W, F, S, mode);
            ofstream fl("./file./record.txt");
            if (!fl.is_open()) {
                cout << "文件打开失败" << endl;
                exit(1);
            }
            fl << is_ov << endl;
            fl.close();
            G.~Game();
            F.~Food();
            W.~Wall();
            //IMAGE pic1;
            //loadimage(&pic1, _T("./image/error.jpg"), 700, 200);
            //putimage(250, 120, &pic1);
            S.~Snake();
            //Sleep(2000);
            while (Keyboard_monitor(0, 0) != 27);
        }
    }
    return 0;
}
