/*
ID:shijiey1
PROG:milk
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Node{
	int all;
	int unit;
	bool operator < (const Node &n) const {
		return unit < n.unit;
	}
};

int tot, n;
int money = 0;
Node arr[5050];
int main() {
	freopen("milk.in", "r", stdin);
	freopen("milk.out", "w", stdout);
	scanf("%d %d", &tot, &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &arr[i].unit, &arr[i].all);
	}
	sort(arr, arr + n);
	for (int i = 0; i < n; i++) {
		if (tot - arr[i].all >= 0) {
			money += arr[i].all * arr[i].unit;
			tot -= arr[i].all;
		} else {
			money += tot * arr[i].unit;
			break;
		}
	}
	printf("%d\n", money);
	return 0;
}
