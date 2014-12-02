#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 200010

using namespace std;

int n, m;
int arr[MAXN];


// 能否把数列分成segments段，使每一段的和不超过maxmium
bool canDivide(int segments, int maxmium) {
	// 可以把数列分成cnt段，每一段的和不超过maxmium
	int cnt = 0;
	int total = 0;
	for (int i = 0; i < n; i++) {
		total += arr[i];
		if (total > maxmium) {
			total = arr[i];
			cnt++;
		}
	}
	if (total) cnt++;
	return cnt <= segments;
}

int main() {
	freopen("1182.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a = 0, b = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		b += arr[i];
		a = max(a, arr[i]);
	}
	while (a < b) {
		int c = (a + b) >> 1;
		if (canDivide(m, c)) {
			b = c;
		} else {
			a = c + 1; 
		}
	}

	printf("%d\n", a);
	return 0;
}
