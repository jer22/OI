#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int n, m;
int arr[100005];
int brr[100005];
bool vis[100005];
int stack[50], top;
int len;

int fuck() {
	len = 0;
	int t = n;
	while (t) {
		len++;
		t >>= 1;
	}
}

int get(int t) {
	int k = 0;
	int f = 0;
	while (t) {
		f |= ((t & 1) ^ 1) << k;
		t >>= 1;
		k++;
	}
	vis[f] = vis[t] = 1;
	return f;
}

int main() {
	freopen("h.in", "r", stdin);
	while (~scanf("%d", &n)) {
		long long ans = 0;
		fuck();
		for (int i = 0; i <= n; i++)
			scanf("%d", &arr[i]);
		memset(vis, 0, sizeof(vis));
		for (int i = n; i >= 0; i--) {
			if (vis[i]) continue;
			int k = 0;
			int f = 0;
			int t = i;
			while (t) {
				f |= ((t & 1) ^ 1) << k;
				t >>= 1;
				k++;
			}
			vis[f] = 1;
			brr[i] = f;
			brr[f] = i;
			ans += (i ^ f) * 2;
		}
		cout << ans << endl;
		for (int i = 0; i <= n; i++) {
			if (i) printf(" ");
			printf("%d", brr[arr[i]]);
		}
		printf("\n");
	}


	return 0;
}
