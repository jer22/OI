#include <cstdio>
#include <cstring>
#include <algorithm>

#define INF 0x3f3f3f3f
#define MAXN 100010

using namespace std;

int n;
int arr[MAXN];
int size = 0;
int main() {
	freopen("1970.in", "r", stdin);
	scanf("%d", &n);
	int t;
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		if (!i || (i && t != arr[size - 1])) {
			arr[size++] = t;
		}
	}
	int ans = 2;
	for (int i = 1; i < size - 1; i++) {
		if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]
			|| arr[i] < arr[i - 1] && arr[i] < arr[i + 1]) {
			ans++;
		}
	}
	printf("%d\n", ans);

	return 0;
}
