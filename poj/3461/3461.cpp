#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int T;
char s[1000100], p[100010];
int next[100010];
int lens;
int lenp;

void getNext() {
	int i = 0, j = -1;  
	next[0] = -1;  
	while(i < lenp) {  
		if (p[i] == p[j] || j == -1) {
			i++;
			j++;
		} else {
			j = next[j];
		}
	}
}

int KMP() {
	int i = 0, j = 0;
	int cnt = 0;
	while (i != lens && j != lenp) {
		if (j == -1 || s[i] == p[j]) {
			i++;
			j++;
		} else {
			j = next[j];
		}
		if (j == lenp) {
			cnt++;
			j = next[j];
		}
	}
	return cnt;
}

int main() {
	freopen("3461.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%s%s", p, s);
		lens = strlen(s);
		lenp = strlen(p);
		getNext();
		int ans = KMP();
		printf("%d\n", ans);
	}

	return 0;
}
