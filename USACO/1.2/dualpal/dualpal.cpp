/*
ID:shijiey1
PROG:dualpal
LANG:C++
*/

/*
从s+1向上枚举，再枚举每一个进制。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>

using namespace std;

int n, s;
int number[40];

int getNum(int num, int bin) {
	stack<int> ss;
	int i = 0;
	while (num) {
		ss.push(num % bin);
		num /= bin;
	}
	while (!ss.empty()) {
		number[i++] = ss.top();
		ss.pop();
	}
	return i;
}

int main() {
	freopen("dualpal.in", "r", stdin);
	freopen("dualpal.out", "w", stdout);
	scanf("%d %d", &n, &s);
	for (int i = s + 1; n > 0; i++) {
		int cnt = 0;
		for (int bin = 2; bin <= 10; bin++) {
			memset(number, 0, sizeof(number));
			int l = getNum(i, bin);
			bool flag = false;
			for (int j = 0; j <= l >> 1; j++) {
				if (number[j] != number[l - j - 1]) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				cnt++;
			}
			if (cnt >= 2) {
				n--;
				printf("%d\n", i);
				break;
			}
		}
	}


	return 0;
}
