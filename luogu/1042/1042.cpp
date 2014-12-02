#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char score[50000];
int n = 0;
int l = 0;
int w = 0;
int main() {
	freopen("1042.in", "r", stdin);
	char c;
	scanf("%c", &c);
	while (c != 'E') {
		if (c != '\n') {
			score[n++] = c;
		}
		scanf("%c", &c);
	}
	for (int i = 0; i < n; i++) {
		if (score[i] == 'W')
			w++;
		if (score[i] == 'L')
			l++;
		if ((w >= 11 || l >= 11) && abs(l - w) > 1) {
			printf("%d:%d\n", w, l);
			w = 0;
			l = 0;
		}
	}
	printf("%d:%d\n\n", w, l);
	
	w = 0;
	l = 0;
	for (int i = 0; i < n; i++) {
		if (score[i] == 'W')
			w++;
		if (score[i] == 'L')
			l++;
		if ((w >= 21 || l >= 21) && abs(l - w) > 1) {
			printf("%d:%d\n", w, l);
			w = 0;
			l = 0;
		}
	}
	printf("%d:%d\n", w, l);
	return 0;
}
