#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[5010];
int theme[5010];
int main() {
	freopen("theme.in", "r", stdin);
	// freopen("theme.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	for (int i = 0; i < n - 1; i++) {
		theme[i] = arr[i + 1] - arr[i];
	}

	return 0;
}
