#include <iostream>
#include<cstring>

using namespace std;

class TString
{
private:
    char* content;        //指向字符串的指针
    int   len;            //字符串的长度，不含尾零
public:
    TString(char* s = NULL);
    TString(const TString&);
    ~TString();
    char* get_content();
    void set(char* s = NULL);
    void set(const TString&);
    int length();
};

TString::TString(char* s) {
    content = s;
    if (content != NULL)
        len = strlen(s);
    else
        len = 0;
}
TString::TString(const TString& tmp) { 
    content = tmp.content;
    len = tmp.len;
}
TString::~TString() {}
char* TString::get_content() {
    return content;
}
void TString::set(char* s) {
    content = s;
    if (content != NULL)
        len = strlen(s);
    else
        len = 0;
}
void TString::set(const TString& tmp) {
    content = tmp.content;
    len = tmp.len;
}
int TString::length() {
    if (content == NULL)
        return 0;
    return len;
}