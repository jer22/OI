#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 200010

using namespace std;

int n;
int arr[MAXN];
int sum[MAXN];
int re;
int main() {
	freopen("1115.in","r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		sum[i] = sum[i - 1] + arr[i];
	}
	re = arr[1];
	int minnum = 0;
	for (int i = 1; i <= n; i++) {
		minnum = min(minnum, sum[i - 1]);
		re = max(re, sum[i] - minnum);
	}
	printf("%d\n", re);
	return 0;
}
