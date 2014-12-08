/*
ID:shijiey1
PROG:barn1
LANG:C++
*/

/*
总长度最小即总间隙最大。
选取最大的m-1段间隙，其余部分用木板盖住。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int m, s, c;
int arr[210];
int spacing[210];

bool cmp(int a, int b) {
	return a > b;
}

int main() {
	freopen("barn1.in", "r", stdin);
	freopen("barn1.out", "w", stdout);
	scanf("%d %d %d", &m, &s, &c);
	for (int i = 0; i < c; i++) {
		scanf("%d", &arr[i]);
	}
	sort(arr, arr + c);
	for (int i = 1; i < c; i++) {
		spacing[i - 1] = arr[i] - arr[i - 1];
	}
	int len = arr[c - 1] - arr[0] + 1;
	sort(spacing, spacing + c - 1, cmp);
	int blank = 0;
	for (int i = 0; i < m - 1; i++) {
		blank += spacing[i];
	}
	blank -= m - 1;
	if (c <= m) {
		printf("%d\n", c);
	} else printf("%d\n", len - blank);

	return 0;
}
