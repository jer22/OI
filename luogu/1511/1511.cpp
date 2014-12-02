#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>

using namespace std;

char p[210];
int next[210];
char s[250000];
int idx = 0;

void getNext() {
	int lenp = strlen(p);
	int i = 0, j = -1;
	next[0] = -1;
	while (i < lenp) {
		if (p[i] == p[j] || j == -1) {
			next[++i] = ++j;
		} else {
			j = next[j];
		}
	}
}

int kmp() {
	int lens = strlen(s), lenp = strlen(p);
	int i = 0, j = 0;
	while (i != lens && j != lenp) {
		if (s[i] == p[j] || j == -1) {
			i++;
			j++;
		} else {
			j = next[j];
		}
		if (j == lenp) {
			return i - lenp + 1;
		}
	}
	return 0;
}

void insert(int i) {
	char temp[7];
	memset(temp, 0, sizeof(temp));
	while (i) {
		temp[strlen(temp)] = ('0' + i % 10);
		i /= 10;
	}
	int l = strlen(temp);
	for (int j = 0; j < l; j++) {
		s[idx++] = temp[l - j - 1];
	}
}

int main() {
	freopen("1511.in", "r", stdin);
	scanf("%s", p);
	memset(s, 0, sizeof(s));
	for (int i = 1; i <= 50000; i++) {
		insert(i);
	}
	getNext();
	int ans = kmp();
	printf("%d\n", ans);
	return 0;
}
