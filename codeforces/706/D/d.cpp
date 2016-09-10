#include <bits/stdc++.h>

using namespace std;

int q;
map<int, int> vis;

int nex[6000005][2], cnt[6000005];
int tot = 0;
int bit[31];
void insert(int x) {
	for (int i = 29; i >= 0; i--) {
		bit[i] = x & 1;
		x >>= 1;
	}
	int pos = 0;
	for (int i = 0; i < 30; i++) {
		int t = bit[i];
		if (!nex[pos][t]) nex[pos][t] = ++tot;
		pos = nex[pos][t];
		cnt[pos]++;
	}
}

void del(int x) {
	for (int i = 29; i >= 0; i--) {
		bit[i] = x & 1;
		x >>= 1;
	}
	int pos = 0;
	for (int i = 0; i < 30; i++) {
		int t = bit[i];
		pos = nex[pos][t];
		cnt[pos]--;
	}
}

int ans[31];
void query(int x) {
	for (int i = 29; i >= 0; i--) {
		bit[i] = x & 1;
		x >>= 1;
	}
	int pos = 0;
	for (int i = 0; i < 30; i++) {
		int t = bit[i];
		if (cnt[nex[pos][t ^ 1]]) {
			ans[i] = 1;
		} else {
			ans[i] = 0;
		}
		pos = nex[pos][t ^ ans[i]];
	}
}

int get() {
	int ret = 0;
	int t = 1;
	for (int i = 29; i >= 0; i--) {
		ret += ans[i] * t;
		t <<= 1;
	}
	return ret;
}

int main() {
	freopen("d.in", "r", stdin);
	cin >> q;
	string s;
	int a;
	while (q--) {
		cin >> s;
		cin >> a;
		if (s[0] == '+') {
			if (!vis[a]) {
				insert(a);
			}
			vis[a]++;
		} else if (s[0] == '-') {
			if (vis[a] == 1) {
				del(a);
			}
			vis[a]--;
		} else {
			query(a);
			cout << max(a, get()) << endl;
		}
	}


	return 0;
}
