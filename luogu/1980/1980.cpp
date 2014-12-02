#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, k;

int getNum(int i) {
	int cnt = 0;
	while (i) {
		if (i % 10 == k) {
			cnt++;
		}
		i /= 10;
	}
	return cnt;
}

int cnt = 0;
int main() {
	freopen("1980.in", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		cnt += getNum(i);
	}
	printf("%d\n", cnt);
	return 0;
}
