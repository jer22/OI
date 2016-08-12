#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define MAXV 22

using namespace std;

const unsigned long long MOD = (1ull << 32);

int V;
int color[MAXV];
int vis[MAXV];
int arr[22][22];
int ans;
void dfs(int x, int cols, int stat) {
	if (cols > ans) return;
	if (x > V) {
		if (ans > cols) ans = cols;
		return;
	}
	if (!((1 << (x - 1)) & stat)) dfs(x + 1, cols, stat);
	int i, j;  
    for (i = 1; i <= cols; i++){ // 枚举当前存在的频道  
        for (j = 1; j <= x; j++){ // 检查是否可以在i频道内  
        	if (!((1 << (j - 1)) & stat)) continue;
            if ((vis[j] == i) && arr[x][j])  
                break;  
        }  
        if (j > x){ // 如果可以加入i频道  
            vis[x] = i;  
            dfs(x+1, cols, stat);  
            vis[x] = 0;  
        }  
    }  
    // 将 x 放入一个新的频道  
    vis[x] = cols+1;  
    dfs(x+1, cols+1, stat);  
    vis[x] = 0;  

}

int MCS(int stat) {
	memset(vis, 0, sizeof(vis));
	ans = 999999;
	int idx;
	for (int i = 1; i <= V; i++) {
		if (!((1 << (i - 1)) & stat)) continue;
		idx = i;
		break;
	}
	vis[idx] = 1;
	dfs(idx, 1, stat);
	// if (!((1 << (j - 1)) & stat)) continue;
	return ans;
}

unsigned long long power(unsigned long long a, int b) {
	unsigned long long ans = 1ull;
	unsigned long long base = a;
	while (b) {
		if (b & 1) ans = (ans * base) % MOD;
		base = (base * base) % MOD;
		b >>= 1;
	}
	return ans % MOD;
}

int T;

int main() {
	freopen("1003.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &V);
		char str[22];
		for (int i = 1; i <= V; i++) {
			scanf("%s", str);
			for (int j = 1; j <= V; j++) {
				arr[i][j] = (str[j - 1] == '1');
			}
		}
		unsigned long long ans = 0ull;
		for (int stat = 1; stat < (1 << V); stat++) {


			int t = MCS(stat);
			// cout << stat << ' ' << t << endl;
			unsigned long long x = power(233ull, stat);
			ans += ((unsigned long long)t * x) % MOD;
			ans %= MOD;
		}
		printf("%llu\n", ans % MOD);
	}
	
	return 0;
}
