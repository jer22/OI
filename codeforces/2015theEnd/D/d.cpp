#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

int n;
char str[5005];
int ans[5005];
int pre[5005];

char dest[5005];
char cmp[5005];
void init() {
	int idx = n / 2;
	if (n & 1) idx++;
	for (int i = n; i > idx; i--) {
		strncpy(dest, str + i, n - i + 1);
		strncpy(cmp, str+ i - (n - i + 1), n - i + 1);
		if (strcmp(dest, cmp) > 0) pre[i] = i - (n - i + 1) - 1;
		else pre[i] = i - (n - i + 1);
	}
}

int main() {
	freopen("d.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s", str + 1);
	ans[0] = 1;
	init();
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) {
			int tmp = ans[j];
			
		}
	}


	return 0;
}
