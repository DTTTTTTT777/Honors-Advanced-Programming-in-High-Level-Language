#include <iostream>
using namespace std;
class Date
{
public:
	Date(int = 1, int = 1, int = 2005);
	//Date(int, int);
	//Date(int);
	//Date();
	/*【错误原因】： 
	*由于Date(int =1,int =1,int 2005)构造函数为所有的参数都提供了默认实参，
	* 相当于定义了默认构造函数（不提供实参也能调用该构造函数）
	* 如果再定义Date(int, int)构造函数，则提供两个实参时产生二义性，报错
	* Date(int)与Date()同理
	*【修改方法】：
	* 将后面三个构造函数删去即可
	*/
	void display();
private:
	int month;
	int day;
	int year;
};
Date::Date(int m, int d, int y) : month(m), day(d), year(y) {}
/*Date::Date(int m, int d) : month(m), day(d)
{
	year = 2005;
}
Date::Date(int m) : month(m)
{
	day = 1;
	year = 2005;
}
Date::Date()
{
	month = 1;
	day = 1;
	year = 2005;
}*/
void Date::display()
{
	cout << month << "/" << day << "/" << year << endl;
}
int main()
{
	Date d1(10, 13, 2005);
	Date d2(12, 30);
	Date d3(10);
	Date d4;
	d1.display();
	d2.display();
	d3.display();
	d4.display();
	return 0;
}