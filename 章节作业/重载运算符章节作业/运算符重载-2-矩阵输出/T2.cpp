//用友元函数重载运算符+
#include<iostream>
#include<iomanip> //包含了setw
using namespace std;
class Array {
private:
	int matrix[2][3];
public:
	void readFromKeyboard();
	friend Array operator+(const Array&, const Array&);
	friend istream& operator>>(istream&, Array&);
	friend ostream& operator<<(ostream&, const Array&);
};
void Array::readFromKeyboard() {
	for (int i = 0;i < 2;++i)
		for (int j = 0;j < 3;++j)
			cin >> matrix[i][j];
}
Array operator + (const Array& a, const Array& b) { //operator！！是or！
	Array c;
	for (int i = 0;i < 2;++i)
		for (int j = 0;j < 3;++j)
			c.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
	return c;
}
istream& operator>>(istream& is, Array& a) {
	for (int i = 0;i < 2;i++)
		for (int j = 0;j < 3;j++)
			is >> a.matrix[i][j];
	return is;
}
ostream& operator<<(ostream& os, const Array& a) {
	for (int i = 0;i < 2;++i) {
		for (int j = 0;j < 3;++j)
			os << setw(7) << a.matrix[i][j];
		os << endl;
	}
		return os;
};

int main() {
	Array a, b, c;

	cin >> a >> b;
	c = a + b;
	cout << c;

	return 0;
}