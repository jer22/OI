#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

struct Num{
	int len;
	int arr[100];
	void print() {
		for (int i = len - 1; i >= 0; i--) {
			printf("%d", arr[i]);
		}
		printf("\n");
	}
	void init(string s) {
		len = s.size();
		memset(arr, 0, sizeof(arr));
		for (int i = 0; i < len; i++) {
			arr[i] = s[len - i - 1] - '0';
		}
	}
	bool operator < (const Num &n) const {
		if (len != n.len) return len < n.len;
		for (int i = len - 1; i >= 0; i--) {
			if (arr[i] != n.arr[i]) {
				return arr[i] < n.arr[i];
			}
		}
		return 0;
	}
};

Num operator - (Num a, Num b) {
	if (a < b) {
		printf("-");
		swap(a, b);
	}
	Num c;
	c.len = max(a.len, b.len);
	memset(c.arr, 0, sizeof(c.arr));
	for (int i = 0; i < c.len; i++) {
		c.arr[i] += a.arr[i] - b.arr[i];
		
		if (c.arr[i] < 0) {
			c.arr[i + 1] -= 1;
			c.arr[i] += 10;
		}
	}
	while (!c.arr[c.len - 1]) c.len--;
	return c;
}

int n;
int main() {
	freopen("temp.in", "r", stdin);
	string s1;
	string s2;
	cin >> s1 >> s2;
	Num a, b;
	a.init(s1);
	b.init(s2);
	a.print();
	b.print();
	Num c = a - b;
	c.print();

	return 0;
}
