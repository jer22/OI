/*
ID:shijiey1
PROG:palsquare
LANG:C++
*/

/*
数据范围300很小，从1到300扫一遍，如果是回文数就输出。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>

using namespace std;

int bin;
int num[20];
int ori[20];
int getNum(int n) {
	stack<int> s;
	while (n) {
		s.push(n % bin);
		n /= bin;
	}
	int i = 0;
	memset(num, 0, sizeof(num));
	while (!s.empty()) {
		num[i++] = s.top();
		s.pop();
	}
	return i;
}

int getOri(int n) {
	stack<int> s;
	while (n) {
		s.push(n % bin);
		n /= bin;
	}
	int i = 0;
	memset(ori, 0, sizeof(ori));
	while (!s.empty()) {
		ori[i++] = s.top();
		s.pop();
	}
	return i;
}

int main() {
	freopen("palsquare.in", "r", stdin);
	freopen("palsquare.out", "w", stdout);
	scanf("%d", &bin);
	for (int i = 1; i <= 300; i++) {
		int cur = i * i;
		int len = getNum(cur);
		bool flag = false;
		for (int j = 0; j <= len >> 1; j++) {
			if (num[j] != num[len - j - 1]) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			int l = getOri(i);
			for (int j = 0; j < l; j++) {
				if (ori[j] >= 10) {
					printf("%c", 'A' + ori[j] - 10);
				} else printf("%d", ori[j]);
			}
			printf(" ");
			for (int j = 0; j < len; j++) {
				if (num[j] >= 10) {
					printf("%c", 'A' + num[j] - 10);
				} else printf("%d", num[j]);
			}
			printf("\n");
		}
	}

	return 0;
}
