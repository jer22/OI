#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

struct Num {
	int num[105];
	int len;
	void init() { len = 0; memset(num, 0, sizeof(num)); }
	Num() { init(); }
	Num(int a) {
		init();
		while (a) {
			num[len++] = a % 10;
			a /= 10;
		}
	}
	Num(string s) {
		init();
		len = s.size();
		for (int i = len - 1; i >= 0; i--)
			num[len - i - 1] = s[i] - '0';
	}
	void print() {
		for (int i = len - 1; i >= 0; i--)
			cout << num[i];
		cout << endl;
	}
	Num operator + (Num b) {
		Num c;
		c.len = max(len, b.len);
		for (int i = 0; i < c.len; i++) {
			c.num[i] += num[i] + b.num[i];
			c.num[i + 1] += c.num[i] / 10;
			c.num[i] %= 10;
		}
		if (c.num[c.len]) c.len++;
		return c;
	}
	Num split(int st, int ed) {
		Num c;
		c.len = ed - st + 1;
		for (int i = st; i <= ed; i++)
			c.num[i - st] = num[i];
		return c;
	}
	Num reverse() {
		Num c;
		c.len = len;
		for (int i = 0; i < len; i++)
			c.num[len - i - 1] = num[i];
		return c;
	}
	bool fuck() {
		for (int i = 1; i < len; i++)
			if (num[i]) return false;
		return num[0] == 1;
	}
	bool cnm() {
		for (int i = 0; i < len; i++)
			if (num[i]) return false;
		return true;
	}
};

Num t[105];
void init() {
	Num num1 = Num(1);
	t[1] = Num(10);
	Num temp;
	Num tt = Num(9);
	for (int i = 2; i <= 100; i++) {
		int len = i / 2;
		if (len > temp.len) temp.num[temp.len++] = 9;

		t[i] = t[i - 1] + temp + temp + num1;
		if (i & 1) {
			tt.num[tt.len - 1] = 0;
			tt.num[tt.len++] = 9;
			t[i] = t[i] + tt;
		}
	}
}

int main() {
	freopen("number.in", "r", stdin);
	init();
	string str;
	cin >> str;
	if (str.size() == 1) {
		cout << str << endl;
		return 0;
	}
	Num n = Num(str);
	Num ans = t[n.len - 1];
	int len = (n.len + 1) / 2;
	Num tt = n.split(0, len - 1);
	Num gg = n.split(len, n.len - 1).reverse();
	if (gg.fuck()) gg = Num(0);
	if (tt.cnm()) tt = n.split(0, len), gg = n.split(len + 1, n.len - 1).reverse();
	ans = ans + tt + gg;
	ans.print();
	return 0;
}
