#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

struct Num{
	int ope, x;
	int calcu(int y) {
		if (!ope) return x & y;
		if (ope == 1) return x | y;
		return x ^ y;
	}
};

int n, m;
Num arr[100010];

int calculate(int x) {
	for (int i = 0; i < n; i++) 
		x = arr[i].calcu(x);
	return x;
}

int main() {
	freopen("3668.in", "r", stdin);
	scanf("%d %d", &n, &m);
	string s;
	int t;
	for (int i = 0; i < n; i++) {
		cin >> s >> arr[i].x;
		if (s[0] == 'A') arr[i].ope = 0;
		else if (s[0] == 'O') arr[i].ope = 1;
		else if (s[0] == 'X') arr[i].ope = 2;
	}
	int ans = 0;
	int now = 1;
	while (now <= m) now <<= 1;
	for (now >>= 1; now; now >>= 1) {
		if (calculate(0) & now) {
			continue;
		}
		if (ans + now <= m && calculate(now) & now)
			ans += now;
		
	}
	printf("%d\n", calculate(ans));
	return 0;
}
