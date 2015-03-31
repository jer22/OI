#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[30005];
int increase[30005];
int decrease[30005];
int maxleninc = 0;
int maxlendec = 0;

int find_inc(int num) {
	int l = 0, r = maxleninc;
	while (l < r) {
		int mid = (l + r >> 1) + 1;
		if (num < increase[mid])
			r = mid - 1;
		else l = mid;
	}
	if (!increase[l + 1]) maxleninc++;
	return l + 1;
}

int find_dec(int num) {
	int l = 0, r = maxlendec;
	while (l < r) {
		int mid = (l + r >> 1) + 1;
		if (num > decrease[mid])
			r = mid - 1;
		else l = mid;
	}
	if (!decrease[l + 1]) maxlendec++;
	return l + 1;
}

int main() {
	freopen("1609.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	decrease[0] = 0x3f3f3f3f;
	for (int i = 1; i <= n; i++) {
		increase[find_inc(arr[i])] = arr[i];
		decrease[find_dec(arr[i])] = arr[i];
	}
	printf("%d\n", min(n - maxlendec, n - maxleninc));
	return 0;
}
