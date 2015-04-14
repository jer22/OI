#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node{
	int t, d;
	bool operator < (const Node &n) const {
		return d < n.d;
	}
};

int n;
Node arr[1005];
int main() {
	freopen("1620.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &arr[i].t, &arr[i].d);
	arr[0].d = 0x3f3f3f3f;
	sort(arr + 1, arr + n + 1);
	for (int i = n - 1; i >= 0; i--) {
		arr[i].d = min(arr[i].d, arr[i + 1].d - arr[i + 1].t);
	}
	if (arr[0].d < 0) cout << -1 << endl;
	else cout << arr[0].d << endl;
	return 0;
}
