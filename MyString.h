#include <iostream> 
#include <string> 
using namespace std;

class MyString {
private:
	char* Mem; // строка к-ю вводит польз-ль
	int size; // размер к-й мы выделяем под эту строку
	int count; // сколько реально в Mem данных (знаков в строке)
public:
	// конструкторы созд-я разных обьектов класса
	// 1) обьект вида MyString("A")
	MyString(int _size = 256) {
		size = _size;
		Mem = new char[size]; // создаем массив размера 256
		count = 0;
		for (int i = 0; i < size; i++) { Mem[i] = ' '; }
	} // не в параметрах тк будет меняться в процессе работы проги а size нет 
// 2) обьект вида MyString B = "..."
	MyString(const MyString& tmp) {
		size = tmp.size; count = tmp.count;
		Mem = new char[size];
		for (int i = 0; i < size; i++) { Mem[i] = tmp.Mem[i]; }
	}
	// для этого нужна перегрузка оператора присваивания
	MyString& operator=(MyString tmp) {
		if (size != tmp.size) {
			if (size != 0) { delete Mem; }
			size = tmp.size;
			Mem = new char[size];
		}
		count = tmp.count;
		for (int i = 0; i < size; i++) { Mem[i] = tmp.Mem[i]; }
		return *this;
	}
	// 3) обьект вида MyString C()
	MyString(string str) {
		size = 256;
		if (str.length() > 256) { size = str.length() + 10; }
		Mem = new char[size];
		count = str.length();
		for (int i = 0; i < count; i++) { Mem[i] = str[i]; }
	}

	~MyString() { delete[] Mem; } // деструктор

	int length() { return count; }

	// перегрузка сложения
	MyString operator+(MyString tmp) {
		int newsize = 256;
		for (int i = 0; count + tmp.count > (i + 1) * 256; i++) { newsize += 256; }
		MyString res(newsize);
		for (int i = 0; i < count; i++) { res.Mem[i] = Mem[i]; }
		res.count = count;
		for (int i = 0; i < tmp.count; i++) { res.Mem[count + i] = tmp.Mem[i]; }
		res.count += tmp.count;
		return res;
	}


	// опр поз-ю вхож-я строки (что ищем) 
	int find(MyString tmp) {
		int res = -1; bool tf = false;
		for (int i = 0; i < count; i++) {
			if (Mem[i] == tmp.Mem[0]) {
				tf = true;
				for (int j = i; j < i + tmp.count; j++) {
					if (Mem[j] != tmp.Mem[j - i]) { tf = false; } // если нашли всё искомое слово в строке
				} if (tf) { res = i; break; }
			}
		} return res;
	}

	int find(char h) {
		int res = -1;
		for (int i = count - 1; i >= 0; i--) {
			if (Mem[i] == h) res = i;
		} return res;
	}

	int find(string str) {
		bool tf = false; int res = -1;
		for (int i = 0; i < count; i++) {
			if (Mem[i] == str[0]) {
				tf = true;
				for (int j = i; j < i + str.size(); j++) {
					if (Mem[j] != str[j - i]) tf = false;
				} if (tf) { res = i; break; }
			}
		} return res;
	}

	// копир-е части строки (откуда и ск)
	MyString copy(int n, int kolvo) {
		MyString res;
		if (kolvo > size) { res = MyString(kolvo); }
		if (n < count) {
			for (int i = 0; (i < kolvo) & (n + i < count); i++) {
				res.Mem[i] = Mem[i + n];
				res.count += 1;
			}
		}
		return res;
	}

	// перегрузка вывода
	friend ostream& operator<<(ostream& out, MyString tmp) {
		for (int i = 0; i < tmp.count; i++) { out << tmp.Mem[i]; }
		return out;
	}
	// перегрузка ввода
	friend istream& operator>>(istream& in, MyString& tmp) {
		char p = '1';
		tmp.count = 0;
		while (p != '\n') {
			p = getchar();
			tmp.Mem[tmp.count++] = p;
		} tmp.count--;
		for(int i = tmp.count; i < tmp.size; i++) {
			tmp.Mem[i] = ' ';
		}
		return in;
	}

	char& operator[] (int k) { // вывод перем-й по индексу
		char res = '/0';
		if (k >= 0 && k < count) { res = Mem[k]; }
		return res;
	}

	MyString IntToString(int inpt) { // нельзя сделать конструктором тк уже есть конструктор с целочисл парам-м
		MyString res;
		int db=inpt; // деление
		int cur, i = 0; // ост от дел
		res.count = log10(db) + 1;
		while (db != 0) {
			cur = db % 10;
			db /= 10; char tmp = '\0';
			res.Mem[res.count - i - 1] = char(cur + 48); i++;
		}return res;
	}

	void del(int beg, int how_much) {
		int k = 0;
		if (beg < count) {
			for (int i = beg; ((i < count) && (i + how_much < size)); i++) {
				Mem[i] = Mem[i + how_much];
				k++;
			}
			count -= how_much;
			for (int i = beg + k; i < size; i++) { Mem[i] = ' '; }
		}
	}

	int StrToInt() {
		int res = 0; int L = -1;
		for (int i = 0; i < count && L == -1; i++) {
			if (Mem[i] >= '0' && Mem[i] <= '9') { res = res * 10 + Mem[i] - '0'; } // вычитание «0» из ascii символа приводит к числу, которое представляет этот символ
			else { return L; }
		} return res;
	}

	int operator>(MyString tmp) {
		int res = 1;
		if (tmp.count > count) res = 0;
		for (int i = 0; (i < count) & (i < tmp.count); i++) {
			if (tmp.Mem[i] >= Mem[i]) { res = 0; }
		} return res;
	}

	int operator<(MyString tmp) {
		int res = 1;
		if (tmp.count < count) res = 0;
		for (int i = 0; (i < count) & (i < tmp.count); i++) {
			if (tmp.Mem[i] <= Mem[i]) { res = 0; }
		} return res;
	}
};








