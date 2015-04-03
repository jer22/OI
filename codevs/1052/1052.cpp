#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	int t, sc;
	Node() {}
	Node(int a, int b) : t(a), sc(b) {}
	bool operator < (const Node &n) const {
		return t > n.t;
	}
};

int n;
Node arr[105];
int main() {
	freopen("1052.in", "r", stdin);
	cin >> n;
	int st = 0;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i].t;
		st = max(st, arr[i].t);
	}
	for (int i = 1; i <= n; i++) cin >> arr[i].sc;
	sort(arr + 1, arr + n + 1);
	priority_queue<int> q;
	int pos = 1;

	// for (int i = 1; i <= n; i++) cout << arr[i].t << " \n"[i == n];
	// for (int i = 1; i <= n; i++) cout << arr[i].sc << " \n"[i == n];

	int ans = 0;
	while (st) {
		while (pos <= n) {
			if (arr[pos].t != st) break;
			// cout << st << endl;
			q.push(arr[pos].sc);
			pos++;
		}
		// cout << st << ' ' << q.size() << endl;
		if (!q.empty()) {
			int t = q.top();
			q.pop();
			ans += t;
		}

		st--;
	}
	cout << ans << endl;

	return 0;
}
