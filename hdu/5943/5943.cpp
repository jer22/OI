#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int MAXN = 100005;

int T, n, s;

bool vis[MAXN];
int prime[MAXN], tot = 0;
void init() {
	for (int i = 2; i < MAXN - 1; i++) {
		if (!vis[i]) prime[++tot] = i;
		for (int j = 1; j <= tot; j++) {
			if(i * prime[j] > MAXN) break;
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

bool isprime(int x) {
	if (x == 1) return true;
	for (int i = 1; i <= tot; i++) {
		if (prime[i] >= x) break;
		if (!(x % prime[i])) return false;
	}
	return true;
}

const int MAXV = 1005;
int V;
vector<int> edges[MAXV];
int mat[MAXV];
bool done[MAXV];
bool dfs(int k) {
	for (int i = 0; i < edges[k].size(); i++) {
		int j = edges[k][i];
		if (!done[j]) {
			done[j] = 1;
			if (!mat[j] || dfs(mat[j])) {
				mat[j] = k;
				return true;
			}
		}
	}
	return false;
}

int match() {
	int ans = 0;
	for (int i = 1; i <= V; i++) {
		memset(done, 0, sizeof(done));
		if (dfs(i)) ans++;
	}
	return ans;
}
int main() {
	// freopen("5943.in", "r", stdin);
	init();
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d %d", &n, &s);
		int cnt = 0;
		if (!s) {
			printf("Case #%d: Yes\n", cas);
			continue;
		}
		// cout << min(s + n, s + 1000) << endl;

		for (int i = max(s + 1, n + 1); i <= min(s + n, max(s + 1, n + 1) + 1000); i++) {
			// cout << i << endl;
			if (isprime(i)) cnt++;
			if (cnt == 2) break;
		}
		if (cnt >= 2) printf("Case #%d: No\n", cas);
		else {
			memset(mat, 0, sizeof(mat));
			V = min(s, n);
			for (int i = 1; i <= min(s, n); i++) {
				edges[i].clear();
				for (int j = max(s + 1, n + 1); j <= s + n; j++) {
					if (!(j % i)) edges[i].push_back(j - max(s + 1, n + 1) + 1);
				}
			}
			if (match() == min(s, n)) printf("Case #%d: Yes\n", cas);
			else printf("Case #%d: No\n", cas);
		}
	}
	return 0;
}
