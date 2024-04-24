
#include <iostream> 
#include "MyString.h" 

int main() {
	setlocale(LC_ALL, "RUS");

	MyString s1;
	cout << "введи строку s1" << endl;
	cin >> s1;

	MyString s;
	cout << "введи строку s2" << endl;
	cin >> s;
	MyString s2(s);

	MyString s3(200);
	cout << "введи строку s3" << endl;
	cin >> s3;

	cout << "s1 = " << s1 << endl; cout << "s2 = " << s2 << endl; cout << "s3 = " << s3 << endl;

	cout << "длина 2 строки " << s2.length() << endl;

	cout << "s2[2] = " << s2[2] << endl;

	if (s1 > s2) {
		cout << "Первая строка больше второй" << endl;
	}
	else { cout << "Вторая строка больше 1й" << endl; }

	if (s2 < s3) {
		cout << "Вторая строка меньше третьей" << endl;
	}
	else { cout << "Вторая строка больше третьей" << endl; }

	MyString s4 = s1 + s2 + s3;
	cout << "s1 + s2 + s3 = " << s4 << endl;

	cout << "позиция s2 в s1 = " << s1.find(s2) << endl;

	s1.del(1, 2);
	cout << "s1 после удал-я 2х симв-в нач-я со 2го = " << s1 << endl;

	cout << "s2 = " << s2 << endl; cout << "s3 = " << s3 << endl;
	s3 = s2; cout << "теперь s3 = " << s3 << endl;

	s3 = s2.copy(0, 2); cout << "s3 после копир-я = " << s3 << endl;

	MyString D(s2); cout << "MyString D(s2) = " << D << endl;

	MyString st;
	cout << "введи строку для дел-я на слова" << endl; cin >> st;
	MyString t = st; t = t + MyString(" ");
	int l = -1;
	MyString* W = new MyString[st.length()];
	int k = 0;
	while (t.length() > 0) {
		l = t.find(' ');
		if (l > 0) { W[k] = t.copy(0, l); k++; }
		t.del(0, l + 1); }
	cout << "слова строки " << endl;
	for (int i = 0; i < k; i++) { cout << W[i] << endl; }

	MyString c; cout << "press c: "; cin >> c;
	int res = c.MyStringToInt(c); cout << res << endl; cout << res + res << endl;

	cout << "press chislo "; cin >> res;
	c = c.IntToString(res); cout << c << endl; cout << c + c << endl;
}
