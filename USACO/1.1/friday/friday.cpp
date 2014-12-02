/*
ID:shijiey1
PROG:friday
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int cnt[8];
int mon[15] = {0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void getFib(int year) {
	bool flag = false;
	if (year % 100) {
		if (!(year % 4)) flag = true;
	} else {
		if (!(year % 400)) flag = true;
	}
	if (flag) mon[2] = 29;
	else mon[2] = 28;
}

int main() {
	freopen("friday.in", "r", stdin);
	freopen("friday.out", "w", stdout);
	scanf("%d", &n);
	int date = 6;
	for (int i = 0; i < n; i++) {
		int year = i + 1900;
		getFib(year);
		for (int month = 1; month <= 12; month++) {
			cnt[date]++;
			date = (date + mon[month]) % 7;
		}
	}
	for (int i = 6; i < 13; i++) {
		if (i != 6) printf(" ");
		printf("%d", cnt[i % 7]);
	}
	printf("\n");
	return 0;
}
