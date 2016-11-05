#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

struct Node{
	int val, d, id;
	Node() {}
	Node(int a, int b, int c) : val(a), d(b), id(c) {}
	bool operator < (const Node &n) const {
		if (val != n.val) return val > n.val;
		return id < n.id;
	}
};

int n;
Node arr[MAXN];
bool vis[MAXN];
int main() {
	freopen("e.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i].val >> arr[i].d;
		arr[i].id = i;
	}
	sort(arr + 1, arr + n + 1);
	int ans = 0;
	for (int i = n; i >= 1; i--) {
		if (vis[arr[i].id]) continue;
		if (arr[i].d < 0) continue;

		vis[arr[i].id] = 1;
		arr[i].val += arr[i].d;
		for (int j = i - 1; j >= 1; j--) {
			if (arr[j + 1] < arr[j]) {
				ans++;
				swap(arr[j], arr[j + 1]);
			} else break;
		}
		i++;
	}
	for (int i = 1; i <= n; i++) {
		if (vis[arr[i].id]) continue;
		vis[arr[i].id] = 1;
		arr[i].val += arr[i].d;
		for (int j = i + 1; j <= n; j++) {
			if (arr[j] < arr[j - 1]) {
				ans++;
				swap(arr[j], arr[j - 1]);
			} else break;
		}
		i--;
	}
	cout << ans << endl;
	return 0;
}
