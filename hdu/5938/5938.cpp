#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int T, len;
char str[22];
long long arr[22];
long long pre[22];
long long aft[22];

int main() {
	freopen("5938.in", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%s", str + 1);
		len = strlen(str + 1);
		for (int i = 1; i <= len; i++)
			arr[i] = (long long)(str[i] - '0');
		long long a = arr[1], b = arr[2];
		pre[2] = a + b;
		for (int i = 3; i <= len - 3; i++) {
			(a *= 10ll) += arr[i - 1];
			(b *= 10ll) += arr[i];
			pre[i] = max(a + arr[i], b + arr[1]);
		}
		aft[len - 3] = arr[len - 2] * arr[len - 1] / arr[len];
		a = arr[len], b = 10;
		for (int i = len - 4; i >= 2; i--) {
			a = arr[i + 3] * b + a;
			b *= 10;
			aft[i] = arr[i + 1] * arr[i + 2] / a;
		}
		long long ans = -1000000000000000000ll;
		for (int i = 2; i <= len - 3; i++)
			ans = max(ans, pre[i] - aft[i]);
		printf("Case #%d: %lld\n", cas, ans);
	}
	return 0;
}
