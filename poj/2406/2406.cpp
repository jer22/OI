#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char p[1000010];
int next[1000010];
int lenp;

void getNext() {
	int i = 0, j = -1;
	next[0] = -1;
	while (i < lenp) {
		if (j == -1 || p[i] == p[j]) {
			i++;
			j++;
			if (p[i] != p[j]) {
				next[i] = j;
			} else {
				next[i] = next[j];
			}
		} else {
			j = next[j];
		}
	}	
}

int main() {
	freopen("2406.in", "r", stdin);
	while (scanf("%s", p) != EOF) {
		if (p[0] == '.') break;
		lenp = strlen(p);
		getNext();
		if (!(lenp % (lenp - next[lenp]))) {
			printf("%d\n", lenp / (lenp - next[lenp]));
		} else {
			printf("1\n");
		}
	}

	return 0;
}
