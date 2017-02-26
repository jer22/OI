#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, q;
vector<int> arr[MAXN];
int rr[MAXN];

int main() {
	freopen("c.in", "r", stdin);
	int a, b;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		arr[i].push_back(0);
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a);
			arr[i].push_back(a);

		}
	}
	for (int i = 1; i <= m; i++) {
		int l = 1;
		for (int j = 1; j <= n; j++) {
			if (j == 1 || arr[j][i] >= arr[j - 1][i]);
			else {
				rr[l] = max(rr[l], j - 1);
				l = j;
				// cout << i << endl;
			}
		}
		rr[l] = max(rr[l], n);
	}

	for (int i = 1; i <= n; i++) {
		// cout << rr[i] << endl;
		rr[i] = max(rr[i], rr[i - 1]);
	}
	scanf("%d", &q);

	while (q--) {
		scanf("%d %d", &a, &b);
		if (rr[a] >= b) cout << "Yes" << endl;
		else cout << "No" << endl;
	}


	return 0;
}
