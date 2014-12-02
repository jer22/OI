#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int year[2];
int month[2];
int day[2];
int hour[2];
int minute[2];
int n;
int arr[5010];
int mon[15] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
long long ans = 0;

bool plusYear(long long x) {
	if (!(x % 100)) {
		if (!(x % 400)) return true;
	} else if (!(x % 4)) return true;
	return false;
}

long long getMonth(int x) {
	long long ans = 0;
	for (int i = 1; i < month[x]; i++) {
		ans += mon[i];
	}

	ans += day[x] - 1;
	if (mon[month[x]] > 2 && plusYear(year[x])) {
		ans++;
	}
	return ans;
}

int main() {
	memset(arr, 0, sizeof(arr));
	freopen("words.in", "r", stdin);
	freopen("words.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	sort(arr, arr + n);
	getchar();
	scanf("%d-%d-%d-%d:%d\n", &year[0], &month[0], &day[0], &hour[0], &minute[0]);
	scanf("%d-%d-%d-%d:%d", &year[1], &month[1], &day[1], &hour[1], &minute[1]);
	ans -= hour[0] * 60 + minute[0];
	ans -= getMonth(0) * 1440;
	ans += hour[1] * 60 + minute[1];
	ans += getMonth(1) * 1440;
	for (int i = year[0]; i < year[1]; i++) {
		if (plusYear(i)) {
			ans += 366 * 1440;
		} else {
			ans += 365 * 1440;
		}
	}

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (ans - arr[i] >= 0) {
			cnt++;
			ans -= arr[i];
		}
	}
	printf("%d\n", cnt);
	
	return 0;
}
