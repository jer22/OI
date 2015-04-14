#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

char str[10000005];
char nex[10000005];
int n;
int main() {
	freopen("number.in", "r", stdin);
	scanf("%s", str);
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int len = strlen(str);
		int cnt = 0;
		char c = str[0];
		int idx = 0;
		memset(nex, 0, sizeof(nex));
		int tot = 0;
		while (idx < len) {
			if (str[idx] == c) {
				cnt++;
			}
			else {
				nex[tot++] = cnt + '0';
				nex[tot++] = c;
				c = str[idx];
				cnt = 1;
			}
			idx++;
		}
		nex[tot++] = cnt + '0';
		nex[tot++] = c;
		nex[tot] = '\0';
		memcpy(str, nex, sizeof(nex));
	}
	printf("%s\n", nex);
	// cout << strlen(nex);

	return 0;
}
