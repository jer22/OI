#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

struct Node{
	int pos, height;
	Node() {}
	Node(int a, int b) : pos(a), height(b) {}
};

int n;
int arr[MAXN], refl[MAXN];
int temp[MAXN];
map<int, int> hha;
int l[MAXN], r[MAXN];
int maxlen[MAXN];
int ans[MAXN];
int main() {
	// freopen("b.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		temp[i] = arr[i];
	}
	sort(temp + 1, temp + n + 1);
	int tot = 0;
	for (int i = 1; i <= n; i++) {
		if (!hha[temp[i]]) hha[temp[i]] = ++tot;
	}
	for (int i = 1; i <= n; i++) {
		refl[hha[arr[i]]] = arr[i];
		arr[i] = hha[arr[i]];
	}
	stack<Node> s;
	for (int i = 1; i <= n; i++) {
		Node cur = Node(i, arr[i]);
		while (!s.empty() && s.top().height > arr[i]) {
			Node t = s.top();
			s.pop();
			r[t.pos] = i - 1;
		}
		s.push(cur);
	}
	while (!s.empty()) {
		r[s.top().pos] = n;
		s.pop();
	}
	for (int i = n; i >= 1; i--) {
		Node cur = Node(i, arr[i]);
		while (!s.empty() && s.top().height > arr[i]) {
			Node t = s.top();
			s.pop();
			l[t.pos] = i + 1;
		}
		s.push(cur);
	}
	while (!s.empty()) {
		l[s.top().pos] = 1;
		s.pop();
	}
	for (int i = 1; i <= n; i++) {
		// cout << arr[i] << endl;
		maxlen[arr[i]] = max(maxlen[arr[i]], r[i] - l[i] + 1);
	}
	int t = tot;
	for (int i = 1; i <= n; i++) {
		// while (!hha[t]) t--;
		if (maxlen[t] >= i) ans[i] = t;
		while (maxlen[t] < i) {
			t--;
		}
		ans[i] = t;
	}
	for (int i = 1; i <= n; i++)
		cout << refl[ans[i]] << " \n"[i == n];

	return 0;
}
