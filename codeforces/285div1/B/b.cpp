#include <bits/stdc++.h>

using namespace std;

int n;
int a[200005];
int b[200005];
int c[200005];
int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &b[i]);
	for (int i = 0; i < n; i++) {
		if (a[i] == b[i]) continue;
		else if (a[i] > b[i]) {
			swap(a, b);
			break;
		} else break;
	}
	for (int i = 0; i < n; i++) {
		a[i] = n - 1 - a[i];
		b[i] = n - 1 - b[i];
		b[i] -= i;
		c[i] = a[i] - b[i];
	}
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("%d", c[i]);
	}
	printf("\n");
	return 0;
}
