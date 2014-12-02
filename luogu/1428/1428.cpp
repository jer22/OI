#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[50000];
int re[50000];
int main() {
	freopen("1428.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	re[0] = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (arr[j] < arr[i]) {
				re[i]++;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", re[i]);
	}
	return 0;
}
