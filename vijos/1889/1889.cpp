#include <bits/stdc++.h>

using namespace std;

long long mob[1000004];
void getMob() {
	for (int i = 1; i <= 1000000; i++) {
		int target = (i == 1 ? 1 : 0);
		int delta = target - mob[i];
		mob[i] = delta;
		for (int j = i + i; j <= 1000000; j += i)
			mob[j] += delta;
	}
}

long long cal(long long n) {
	long long t = sqrt(n);
	long long ans = 0;
	for (long long i = 2; i <= t; i++) {
		ans += (-1) * mob[i] * (n / (i * i));
	}
	return ans;
}

int main() {
	freopen("1889.in", "r", stdin);
	getMob();
	long long n;
	scanf("%lld", &n);
	long long l = 1, r = 1000000000000ll;
	while (l < r) {
		long long mid = l + r >> 1;
		if (cal(mid) >= n) r = mid;
		else l = mid + 1;
	}
	cout << l << endl;
	return 0;
}
