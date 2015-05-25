#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int T;
int n, k;
char str[100005];

void solve() {
	n = strlen(str);
	int cnt = 0;
	int a = n / k;
	int b = n % k;
	if (b) {
		int s = n - a * k;
		a++;
		int t;
		for (int i = 0; i < a - 1; i++) {
			t = i;
			printf("%c", str[i]);
			for (int j = 1; j <= b; j++) {
				t += a;
				printf("%c", str[t]);
			}
			t += a - 1;
			for (int j = b + 1; j < k; j++) {
				printf("%c", str[t]);
				t += a - 1;
			}
		}
		printf("%c", str[a - 1]);
		s--;
		t = a - 1;
		for (int j = 1; j <= min(s, b); j++) {
			t += a;
			printf("%c", str[t]);
		}
		t += a - 1;
		for (int j = b + 1; j <= min(s, k - 1); j++) {
			printf("%c", str[t]);
			t += a - 1;
		}
	} else {
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < k; j++)
				printf("%c", str[i + j * a]);
		}
	}
}

int main() {
	freopen("1002.in", "r", stdin);
	scanf("%d\n", &T);
	int cas = 1;
	while (T--) {
		char c;
		int top = 0;
		while ((c = getchar()) != '\n') {
			str[top++] = c;
		}
		str[top] = '\0';
		scanf("%d\n", &k);
		printf("Case #%d:\n", cas++);
		solve();
		printf("\n");
	}


	return 0;
}
