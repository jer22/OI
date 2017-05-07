#include <bits/stdc++.h>

using namespace std;

const int MAXN = 106;

int n, f;
int arr[MAXN];
int vis[MAXN];
int ss[MAXN];

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &f);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		ss[arr[i]] = 1;
	}
	int cnt = 0;
	int idx = 1;
	while (idx <= n) {
		if (vis[arr[idx]]) {
			++idx;
			continue;
		}
		int sp = 1;
		if (arr[idx] < f) sp = -1;
		for (; f != arr[idx]; f += sp) {
			if (vis[f]) continue;
			vis[f] = 1;
			if (ss[f]) {
				cnt++;
				cout << f << " \n"[cnt == n];
			}
		}
		cnt++;
		cout << f << " \n"[cnt == n];
		vis[f] = 1;
		idx++;
	}

	return 0;
}
