#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
char p[2][105];
int next[2][105];
char s[400002];
void getNext() {
	int lenp = strlen(p[0]);
	int i = 0, j = -1;
	next[0][0] = -1;
	while (i != lenp) {
		if (p[0][i] == p[0][j] || j == -1) {
			i++;
			j++;
		} else {
			j = next[0][j];
		}
	}
	lenp = strlen(p[1]);
	i = 0, j = -1;
	next[1][0] = -1;
	while (i != lenp) {
		if (p[1][i] == p[1][j] || j == -1) {
			i++;
			j++;
		} else {
			j = next[1][j];
		}
	}
}

int lens = 400000;
int kmp(int x) {
	int lenp = strlen(p[x]);
	int i = 0, j = 0;
	int cnt = 0;
	while (i != lens && j != lenp) {
		if (j == -1 || s[i] == p[x][j]) {
			i++;
			j++;
		} else {
			j = next[x][j];
		}
		if (j == lenp) {
			return i - j;
		}
	}
	return 0;
}

int main() {
	freopen("1004.in", "r", stdin);
	srand(time(0));
	scanf("%d", &T);
	int bi;
	for (int i = 0; i < 400000; i++) {
		bi = rand() % 2;
		if (bi) s[i] = '0';
		else s[i] = '1';
	}
	while (T--) {
		scanf("%s %s", p[0], p[1]);
		getNext();
		int ans1 = kmp(0);
		int ans2 = kmp(1);
		if (abs(ans1 - ans2) < strlen(p[0]) * 2) printf("Fair\n");
		else if (ans1 < ans2) printf("A\n");
		else printf("B\n");
	}
	return 0;
}
