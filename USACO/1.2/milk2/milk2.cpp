/*
ID:shijiey1
PROG:milk2
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

struct Node {
	int tim;
	int stat;
	bool operator < (const Node &n) const {
		if (tim != n.tim) return tim < n.tim;
		return stat > n.stat;
	}
};

int n;
Node arr[12000];
int main() {
	freopen("milk2.in", "r", stdin);
	freopen("milk2.out", "w", stdout);
	scanf("%d", &n);
	Node temp;
	int a, b;
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &a, &b);
		temp.tim = a;
		temp.stat = 1;
		arr[i << 1] = temp;
		temp.tim = b;
		temp.stat = -1;
		arr[(i << 1) + 1] = temp;
	}
	int len = n << 1;
	sort(arr, arr + len);
	bool on = false;
	int busyStart = arr[0].tim;
	int freeStart = arr[0].tim;
	int busyTime = 0;
	int freeTime = 0;
	int cur = 0;
	bool flag = false;
	for (int i = 0; i < len; i++) {
		cur += arr[i].stat;
		if (!flag) {
			freeTime = max(freeTime, arr[i].tim - freeStart);
			busyStart = arr[i].tim;
			flag = true;
		}
		if (!cur) {
			freeStart = arr[i].tim;
			busyTime = max(busyTime, arr[i].tim - busyStart);
			flag = false;
		}
		
	}
	printf("%d %d\n", busyTime, freeTime);
	return 0;
}
