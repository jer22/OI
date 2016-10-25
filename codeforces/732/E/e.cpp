#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

struct Node{
	int val, pos;
	Node() {}
	Node(int a, int b) : val(a), pos(b) {}

	bool operator < (const Node &s) const {
		if (val != s.val) return val > s.val;
		return pos < s.pos;
	}
};

int n, m;
set<Node> arr;
Node socs[MAXN];
int ma = 0, us = 0;
int ans[MAXN], cnt[MAXN];

bool check(int x, int val) {
	set<Node>::iterator it = arr.lower_bound(Node(val, 0));
	if (it == arr.end()) return false;
	// if (val == 103023) {
	// 	for (set<Node>::iterator yyy = arr.begin(); yyy != arr.end(); yyy++) {
	// 		cout << yyy -> val << ' ' << yyy -> pos << endl;
	// 	}
	// 	cout << it -> val << endl;
	// }

	if (it -> val == val) {
		ma++;
		ans[it -> pos] = socs[x].pos;
		arr.erase(it);
		return true;
	} else return false;
}

int main() {
	freopen("e.in", "r", stdin);
	cin >> n >> m;
	int val;
	for (int i = 1; i <= n; i++) {
		cin >> val;
		arr.insert(Node(val, i));
	}
	for (int i = 1; i <= m; i++) {
		cin >> socs[i].val;
		socs[i].pos = i;
	}
	sort(socs + 1, socs + m + 1);

	for (int i = m; i >= 1; i--) {
		int val = socs[i].val, t = 0;

		while (val && !check(i, val)) {

			if (val == 1) val = 0;
			else val = val + 1 >> 1;
			t++;
		}

		if (val) {
			cnt[socs[i].pos] = t;
			us += t;
		}
	}
	cout << ma << ' ' << us << endl;
	for (int i = 1; i <= m; i++)
		cout << cnt[i] << " \n"[i == m];
	for (int i = 1; i <= n; i++)
		cout << ans[i] << " \n"[i == n];

	return 0;
}
