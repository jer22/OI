#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 1000005;

int n;
long long a[MAXN];
int main() {
	// freopen("1003.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++)
			scanf("%lld", &a[i]);
		int ans = 0;
		long long sum = 0;
		for (int i = n; i >= 1; i--) {
			if (sum + a[i] >= 0) {
				sum = 0;
				ans++;
			} else sum += a[i];
		}
		cout << ans << endl;
	}


	return 0;
}
