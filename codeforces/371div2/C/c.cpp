#include <bits/stdc++.h>

using namespace std;

int q;
int tot = 0;
int nex[7000005][2], cnt[7000005], ed[7000005];
int bit[20];
void insert(long long x) {
	int pos = 0;
	for (int i = 0; i <= 18; i++) {
		int t = x & 1ll;
		// cout << t << ' ';
		if (!nex[pos][t]) nex[pos][t] = ++tot;
		pos = nex[pos][t];
		cnt[pos]++;

		x /= 10;
	}
	ed[pos]++;
	// cout << endl;
}

void del(long long x) {
	int pos = 0;
	for (int i = 0; i <= 18; i++) {
		int t = x & 1ll;
		pos = nex[pos][t];
		cnt[pos]--;

		x /= 10;
	}
	ed[pos]--;
}

int query(long long x) {
	int ans = 0;

	int pos = 0;
	for (int i = 0; i <= 18; i++) {
		int t = x & 1;
		
		if (!cnt[nex[pos][t]]) return 0;
		pos = nex[pos][t];

		x /= 10;
	}
	ans += ed[pos];
	return ans;
}

int main() {
	freopen("c.in", "r", stdin);
	cin >> q;
	char op[5];
	long long x;
	while (q--) {
		scanf("%s", op);
		cin >> x;
		if (op[0] == '+') {
			insert(x);
		} else if (op[0] == '-') {
			del(x);
		} else {
			int ans = query(x);
			cout << ans << endl;
		}
	}


	return 0;
}
