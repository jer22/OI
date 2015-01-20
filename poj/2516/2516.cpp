#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INF 0x3f3f3f3f

using namespace std;

int n, m, k;
int shop[55][55];
int sup[55][55];
int cost[55][55][55];
int edges[200][200];
int cntA, cntB;
int belongA[200], belongB[200];
int A[200], B[200];
bool visA[200], visB[200];
int mat[200];
int d;

bool dfs(int k) {
	visA[k] = 1;
	for (int i = 1; i <= cntB; i++) {
		if (!visB[i] && edges[k][i]) {
			int t = edges[k][i] - A[k] - B[i];
			if (!t) {
				visB[i] = 1;
				if (!mat[i] || dfs(mat[i])) {
					mat[i] = k;
					return true;
				}
			} else d = min(d, t);
		}
	}
	return false;
}

int match() {
	memset(A, 0x3f, sizeof(A));
	memset(B, 0, sizeof(B));
	for (int i = 1; i <= cntA; i++)
		for (int j = 1; j <= cntB; j++)
			A[i] = min(A[i], edges[i][j]);
	memset(mat, 0, sizeof(mat));
	for (int i = 1; i <= cntA; i++) {
		while (true) {
			memset(visA, 0, sizeof(visA));
			memset(visB, 0, sizeof(visB));
			d = INF;
			if (dfs(i)) break;
			for (int j = 1; j <= cntA; j++)
				if (visA[j]) A[j] += d;
			for (int j = 1; j <= cntB; j++)
				if (visB[j]) B[j] -= d;
		}
	}
	int ans = 0;
	for (int i = 1; i <= cntB; i++)
		ans += edges[mat[i]][i];
	return ans;
}

int main() {
	freopen("2516.in", "r", stdin);
	while (~scanf("%d %d %d", &n, &m, &k)) {
		if (!n && !m && !k) break;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= k; j++)
				scanf("%d", &shop[i][j]);
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= k; j++)
				scanf("%d", &sup[i][j]);
		for (int t = 1; t <= k; t++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= m; j++)
					scanf("%d", &cost[t][i][j]);
		bool flag = true;
		for (int i = 1; i <= k; i++) {
			int need = 0, have = 0;
			for (int j = 1; j <= n; j++)
				need += shop[j][i];
			for (int j = 1; j <= m; j++)
				have += sup[j][i];
			if (need > have) {
				flag = false;
				printf("-1\n");
				break;
			}
		}
		if (!flag) continue;
		int ans = 0;
		for (int t = 1; t <= k; t++) {
			cntA = cntB = 0;
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= shop[i][t]; j++)
					belongA[++cntA] = i;
			for (int i = 1; i <= m; i++)
				for (int j = 1; j <= sup[i][t]; j++)
					belongB[++cntB] = i;
			for (int i = 1; i <= cntA; i++)
				for (int j = 1; j <= cntB; j++)
					edges[i][j] = cost[t][belongA[i]][belongB[j]];
			ans += match();
		}
		printf("%d\n", ans);
	}
	return 0;
}
