#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int len;
char str[1000005];
int next[1000005];
bool vis[1000005];

void getnext() {
	int i = 0, j = -1;
	next[0] = -1;
	while (i < len) {
		if (j == -1 || str[i] == str[j])
			next[++i] = ++j;
		else j = next[j];
	}
	for (int i = 0; i < len; i++)
		vis[next[i]] = 1;
}

int main() {
	// freopen("b.in", "r", stdin);
	scanf("%s", str);
	len = strlen(str);
	getnext();
	while (next[len]) {
		if (vis[next[len]]) {
			for (int i = 0; i < next[len]; i++)
				printf("%c", str[i]);
			printf("\n");
			return 0;
		}
		len = next[len];
	}
	printf("Just a legend\n");

	return 0;
}
