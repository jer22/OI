#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>
#include <fstream>

#define INF 0x3f3f3f3f

using namespace std;

struct Node{
	int cnt[6];
	int cost;
};

int n, m;
int num = 0;
bool vis[1005];
int hash[1005];
int tot = 0;
Node arr[120];
int cnt[6];
int dp[6][6][6][6][6];

int dfs(int a, int b, int c, int d, int e) {
	if (!a && !b && !c && !d && !e) return 0;
	if (dp[a][b][c][d][e] != INF) return dp[a][b][c][d][e];
	int na, nb, nc, nd, ne;
	for (int i = 1; i <= tot; i++) {
		na = a - arr[i].cnt[1];
		nb = b - arr[i].cnt[2];
		nc = c - arr[i].cnt[3];
		nd = d - arr[i].cnt[4];
		ne = e - arr[i].cnt[5];
		if (na < 0 || nb < 0 || nc < 0 || nd < 0 || ne < 0)
			continue;
		dp[a][b][c][d][e] = min(dp[a][b][c][d][e], dfs(na, nb, nc, nd, ne) + arr[i].cost);
	}
	return dp[a][b][c][d][e];
}

int main() {
	ifstream fin1("discount.in");
	ifstream fin2("offer.in");
	fin1 >> n;
	int id, cn, price;
	memset(arr, 0, sizeof(arr));
	for (int i = 1; i <= n; i++) {
		fin1 >> id >> cn >> price;
		if (!vis[id]) {
			vis[i] = 1;
			hash[id] = ++num;
			id = num;
		}
		cnt[id] = cn;
		arr[++tot].cnt[id] = 1;
		arr[tot].cost = price;
	}
	fin2 >> m;
	int t;
	for (int i = 1; i <= m; i++) {
		fin2 >> t;
		tot++;
		for (int j = 1; j <= t; j++) {
			fin2 >> id >> cn;
			id = hash[id];
			arr[tot].cnt[id] = cn;
		}
		fin2 >> arr[tot].cost;
	}
	memset(dp, 0x3f, sizeof(dp));
	cout << dfs(cnt[1], cnt[2], cnt[3], cnt[4], cnt[5]);

	return 0;
}
