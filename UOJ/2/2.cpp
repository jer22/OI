#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Gate{
	char op[6];
	int num;
	int calc(const int &n) {
		if (op[0] == 'A') return (n & num);
		if (op[0] == 'O') return (n | num);
		if (op[0] == 'X') return (n ^ num);
	}
};

int n, m;
Gate gate[200005];
int arr[33];
int tot = 0;
int ans[33];
void init() {
	while (m) {
		if (m & 1) arr[tot++] = 1;
		else arr[tot++] = 0;
		m >>= 1;
	}
}

int calc(int numm, int pos) {
	int num = (numm << pos);
	for (int i = 0; i < n; i++)
		num = gate[i].calc(num);
	return (num);
}

int get() {
	int st = 0;
	for (int i = tot-1; i >= 0; i--) {
		st <<= 1;
		st |= ans[i];
	}
	return st;
}

int main() {
	freopen("2.in", "r", stdin);
	scanf("%d %d", &n, &m);
	init();
	for (int i = 0; i < n; i++)
	{
		scanf("%s%d", gate[i].op, &gate[i].num);
	}
	bool flag = false;
	for (int i = tot - 1; i >= 0; i--) {
		if (!flag) {
			if (arr[i]) {
				if (calc(1, i) > calc(0, i)) ans[i] = 1;
				else {ans[i] = 0; flag = true;}
			} else {
				ans[i] = 0;
			}
		} else {
			if (calc(1, i) > calc(0, i)) ans[i] = 1;
			else ans[i] = 0;
		}
	}
	int st = get();

	for (int i = 0; i < n; i++)
		st = gate[i].calc(st);
	cout << st << endl;
	return 0;
}
