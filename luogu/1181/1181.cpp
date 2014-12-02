#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 100010

using namespace std;

int n, m;
int arr[MAXN];
int main() {
	freopen("1181.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	int total = 0;
	int cnt = 1;
	for (int i = 0; i < n; i++) {
		total += arr[i];
		if (total > m) {
			cnt++;
			total = arr[i];
		}
		printf("%d %d\n", total, cnt);
	}
	printf("%d\n", cnt);

	return 0;
}
