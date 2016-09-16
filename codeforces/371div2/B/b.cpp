#include <bits/stdc++.h>

using namespace std;

int n;
int arr[100005];
int main() {
	freopen("b.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	sort(arr + 1, arr + n + 1);
	int m = unique(arr + 1, arr + n + 1) - arr - 1;
	if (m >= 4) {
		printf("NO\n");
	} else if (m == 3) {
		if (arr[3] + arr[1] == arr[2] * 2) {
			printf("YES\n");
		} else printf("NO\n");
	} else {
		printf("YES\n");
	}



	return 0;
}
