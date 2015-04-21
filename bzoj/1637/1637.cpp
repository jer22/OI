#include <bits/stdc++.h>

using namespace std;

struct Node{
	int id, pos;
	Node() {}
	Node(int a, int b) : id(a), pos(b) {}
	bool operator < (const Node &n) const {
		return pos < n.pos;
	}
};

int n;
int id[2] = {-1, 1};
Node arr[50005];
map<int, int> vis;
int main() {
	freopen("1637.in", "r", stdin);
	cin >> n;
	int a, b;
	for (int i = 1; i <= n; i++) {
		cin >> a >> b;
		arr[i] = Node(id[a], b);
	}
	sort(arr + 1, arr + n + 1);
	int ans = 0, t = 0;;
	for (int i = 1; i <= n; i++) {
		t += arr[i].id;
		if (!vis[t]) vis[t] = arr[i + 1].pos;
		else ans = max(ans, arr[i].pos - vis[t]);
	}
	cout << ans << endl;

	return 0;
}
