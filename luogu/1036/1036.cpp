#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

#define MAXN 22

using namespace std;

int n, k;
int arr[MAXN];
int cnt = 0;

void isPrime(int a) {
	if (!a || a == 1)return;
	int t = sqrt(a);
	for (int i = 2; i <= t; i++) {
		if (!(a%i))return; 
	}
	cnt++;
}

void dfs(int idx, int step, int sum) {
	if (step == k) {
		isPrime(sum);
		return;
	}
	if (idx == n) {
		return;
	}
	for (int i = idx; i < n; i++) {
		dfs(i + 1, step + 1, sum + arr[i]);
	}
}

int main() {
	freopen("1036.in", "r", stdin);
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	dfs(0, 0, 0);
	printf("%d\n", cnt);
	return 0;
}
