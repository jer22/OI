/*
题意：求三元组(x, y, z)的个数满足x, y, z两两互质或两两不互质
(x, y, z)共4种关系：0,1,2,3对互质。因此问题就是：三元组的总数-（至少有一对互质且至少有一对不互质）
考虑一个数Ai，包含Ai的上述三元组的个数即为（与Ai互质的数的个数）*（与Ai不互质的数的个数）
然后用莫比乌斯函数容斥。
*/
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 100005;

bool notp[MAXN];
long long mob[MAXN];
int primes[10005], tot = 0;
vector<int> fac[MAXN];
void init() {
	for (int i = 2; i < MAXN; i++) {
		if (notp[i]) continue;
		primes[++tot] = i;
		for (int j = i + i; j < MAXN; j += i) notp[j] = 1;
	}
	for (int i = 1; i <= 100000; i++) {
		int target = (i == 1 ? 1 : 0);
		int delta = target - mob[i];
		mob[i] = delta;
		for (int j = i + i; j <= 100000; j += i)
			mob[j] += delta;
		if (!mob[i]) continue;
		for (int j = i; j <= 100000; j += i)
			fac[j].push_back(i);
	}
}

int arr[MAXN], cnt[MAXN];
int main() {
	freopen("c.in", "r", stdin);
	init();
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			for (int j = 0; j < fac[arr[i]].size(); j++)
				cnt[fac[arr[i]][j]]++;
		}
		long long ans = 0;
		for (int i = 1; i <= n; i++) {
			long long tmp = 0;
			for (int j = 0; j < fac[arr[i]].size(); j++) {
				int d = fac[arr[i]][j];
				tmp += (cnt[d] - 1) * mob[d];
			}
			ans += tmp * (n - 1 - tmp);
		}
		printf("%lld\n", (long long)n * (n - 1) * (n - 2) / 6 - (ans >> 1));
	}
	return 0;
}
