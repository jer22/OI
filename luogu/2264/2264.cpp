#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
char p[110][60];
char str[1100];
int next[110][60];
void toUpper(char *str) {
	for (int j = 0; j < strlen(str); j++) {
		if (str[j] >= 'a' && str[j] <= 'z') {
			str[j] = str[j] + 'A' - 'a';
		}
	}
}

void getNext() {
	memset(next, 0, sizeof(next));
	for (int t = 0; t < n; t++) {
		int i = 0, j = -1;  
		next[t][0] = -1;  
		while(i < strlen(p[t])) {  
			if (p[t][i] == p[t][j] || j == -1) {
				next[t][++i] = ++j;
			} else {
				j = next[t][j];
			}
		}
	}
}

int ans = 0;

int kmp(char *s) {
	int cnt = 0;
	int lens = strlen(s);
	for (int t = 0; t < n; t++) {
		int lenp = strlen(p[t]);
		int i = 0, j = 0;
		while (i != lens && j != lenp) {
			if (j == -1 || s[i] == p[t][j]) {
				i++;
				j++;
			} else {
				j = next[t][j];
			}
			if (j == lenp) {
				cnt++;
				break;
			}
		}
	}
	return cnt;
}

int main() {
	freopen("2264.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", &p[i]);
		toUpper(p[i]);
	}
	getNext();
	char c = getchar();
	int l = 0;
	while ((c = getchar()) != EOF) {
		if (c == '.') {
			toUpper(str);
			ans += kmp(str);
			memset(str, 0, sizeof(str));
			l = 0;
			continue;
		}
		str[l++] = c;
	}
	toUpper(str);
	ans += kmp(str);
	printf("%d\n", ans);
	return 0;
}
