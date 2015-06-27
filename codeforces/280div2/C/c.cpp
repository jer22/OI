#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct sub{
	long long a, b;
	bool operator < (const sub &s) const {
		return b < s.b;
	}
};

long long n, r, avg;
long long sum = 0;
sub arr[100005];
int main() {
	cin >> n >> r >> avg;
	avg *= n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i].a >> arr[i].b;
		sum += arr[i].a;
	}
	if (sum >= avg) {
		printf("0\n");
		return 0;
	}
	sum = avg - sum;
	sort(arr + 1, arr + 1 + n);
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		int t = r - arr[i].a;
		if (t > sum) {
			ans += arr[i].b * sum;
			break;
		} else {
			sum -= t;
			ans += arr[i].b * t;
		}

	}
	cout << ans << endl;

	return 0;
}
