#include <bits/stdc++.h>

using namespace std;

char str[15005];
int k;
int ans;
int next[15005];

void kmp(char *s) {
	int i, j = 0;
	for (i = 2; s[i]; i++) {
		while (j && s[j + 1] != s[i])
			j = next[j];
		if (s[j + 1] == s[i])
			j++;
		next[i] = j;
	}
	j = 0;
	for (i = 1; s[i]; i++) {
		while (j && s[j + 1] != s[i])
			j = next[j];
		if (s[j + 1] == s[i])
			j++;
		while (j << 1 >= i)
			j = next[j];
		if (j >= k) ans++;
	}
}

int main() {
	freopen("3620.in", "r", stdin);
	scanf("%s", str + 1);
	scanf("%d", &k);
	for (int i = 0; str[i + 1]; i++)
		kmp(str + i);
	printf("%d\n", ans);
	return 0;
}
