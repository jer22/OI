#include <bits/stdc++.h>

#define p(i, j) (((i) - 1) * m + (j - 1))

using namespace std;

const int MOD = 11192869;

struct Node{
	bitset<155> stat;
	Node() {}
	Node(bitset<155> a) : stat(a) {}
	bool operator < (const Node &n) const {
		return stat.to_string() < n.stat.to_string();
	}
};

int n, m;
char arr[5][55];
char str[155];
map<Node, int> dp[155][5][55];

int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

bool check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}

int main() {
	freopen("2009.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", arr[i] + 1);
	scanf("%s", str + 1);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if ((i == 1 || j == 1 || i == n || j == m)
				&& arr[i][j] == str[1]) {
				bitset<155> t(1 << p(i, j));
				dp[1][i][j][Node(t)] = 1;
			}
		}
	}
	for (int now = 2; now <= n * m; now++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (arr[i][j] != str[now]) continue;
				for (int pos = 0; pos < 4; pos++) {
					int px = i + dir[pos][0];
					int py = j + dir[pos][1];
					if (!check(px, py)) continue;
					map<Node, int> pre = dp[now - 1][px][py];
					for (map<Node, int>::iterator it = pre.begin(); it != pre.end(); it++) {
						Node c = it -> first;
						int sum = it -> second;
						bitset<155> f(1 << p(i, j));
						if ((c.stat & f).any()) continue;
						dp[now][i][j][c.stat ^ f] += sum;
						dp[now][i][j][c.stat ^ f] %= MOD;
					}
				}
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			map<Node, int> pre = dp[n * m][i][j];
			for (map<Node, int>::iterator it = pre.begin(); it != pre.end(); it++) {
				ans += it -> second;
				ans %= MOD;
			}
		}
	}
	printf("%d\n", ans);

	return 0;
}
