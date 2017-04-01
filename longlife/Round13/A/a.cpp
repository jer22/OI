#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

int n;
unsigned long long arr[MAXN], brr[MAXN];
int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &arr[i]);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &brr[i]);
	sort(arr + 1, arr + n + 1);
	sort(brr + 1, brr + n + 1);
	unsigned long long ans = 0;
	for (int i = 1; i <= n; i++)
		ans += arr[i] * brr[i];
	cout << ans << endl;


	return 0;
}
