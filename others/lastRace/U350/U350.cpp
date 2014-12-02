#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[300000];
int sum[300000];
int main() {
	freopen("U350.in", "r", stdin);
	scanf("%d\n", &n);
	int t;
	char c;
	for (int i = 0; i < n; i++) {
		scanf("%d %c\n", &t, &c);
		if (c == 'W') arr[t + 100000] = 1;
		else arr[t + 100000] = -1;
	}
	sum[0] = arr[0];
	for (int i = 1; i < 200000; i++) {
		sum[i] = sum[i - 1] + arr[i];
	}
	for (int i = 0; i < 200000; i++) {
		if (arr[i]) {
			int l = i, r = 200000;

		}
	}

	return 0;
}
