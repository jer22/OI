#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int k, n;
int arr[10010];
int base[50];
int len = 0;
int deep = 11;

void initBase() {
	int num = 1;
	base[0] = 1;
	for (int i = 1; i <= deep; i++) {
		num *= k;
		base[i] = num;
	}
}

void dfs(int step, int num) {

	if (step == deep) {
		arr[len++] = num;
		return;
	}
	dfs(step + 1, num);
	dfs(step + 1, num + base[step - 1]);

}

int main() {
	freopen("1062.in", "r", stdin);
	scanf("%d %d", &k, &n);
	if (k > 5) {
		deep = 10;
	}
	if (k > 11) {
		deep = 9;
	}
	memset(base, 0, sizeof(base));
	initBase();
	dfs(1, 0);
	sort(arr, arr + len);
	// for (int i = 0; i < len; i++) {
	// 	printf("%d ", arr[i]);
	// }
	printf("%d\n", arr[n]);
	return 0;
}
