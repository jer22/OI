#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const long long MOD = 1000000007;

char str[705];
int stack[705], top = 0;
int mat[705];
long long dp[705][705][4][4];

bool check(int i, int j) {
	return ((!i) || (!j) || (i != j));
}

long long dfs(int l, int r, int cl, int cr) {
	long long &ans = dp[l][r][cl][cr];
	if (ans != -1) return ans;
	ans = 0;
	if (mat[l] == r) {
		if ((!cl) ^ (!cr)) {
			if (l + 1 == r) return ans = 1;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					if (check(cl, i) && check(j, cr))
						ans = (ans + dfs(l + 1, r - 1, i, j)) % MOD;
		}
	} else {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (check(i, j))
					ans = (ans + dfs(l, mat[l], cl, i) * dfs(mat[l] + 1, r, j, cr)) % MOD;
	}
	return ans;
}

int main() {
	// freopen("d.in", "r", stdin);
	scanf("%s", str + 1);
	int len = strlen(str + 1);
	for (int i = len; i >= 1; i--) {
		if (str[i] == ')') stack[top++] = i;
		else mat[i] = stack[--top];
	}
	memset(dp, -1, sizeof(dp));
	long long ans = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ans = (ans + dfs(1, len, i, j)) % MOD;
		}
	}
	printf("%I64d\n", ans);
	return 0;
}
