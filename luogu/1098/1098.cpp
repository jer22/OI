#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int p1, p2, p3;
char str[110];
int main() {
	freopen("1098.in", "r", stdin);
	scanf("%d %d %d", &p1, &p2, &p3);
	scanf("%s", str);
	char c;
	for (int i = 0; i < strlen(str); i++) {
		c = str[i];
		if (c != '-' || !i) {
			printf("%c", c);
			continue;
		}
		char s = str[i - 1];
		char t = str[i + 1];
		if (s == '-' || t == '-') {
			printf("%c", c);
			continue;
		}
		if (s >= '0' && s <= '9' && t >= 'a' && t <= 'z'
			|| s >= 'a' && s <= 'z' && t >= '0' && t <= '9') {
			printf("-");
			continue;
		}
		if (t <= s) {
			printf("-");
			continue;
		}
		if (t - s == 1) {
			continue;
		}

		if (p3 == 1) {
			for (char j = s + 1; j <= t - 1; j++) {
				if (p1 != 3) {
					if (j >= 'a' && j <= 'z') {
						for (int k = 0; k < p2; k++) {
							printf("%c", j + (p1 - 1) * ('A' - 'a'));
						}
					} else {
						for (int k = 0; k < p2; k++) {
							printf("%c", j);
						}
					}
				} else {
					for (int k = 0; k < p2; k++) {
						printf("*");
					}
				}
				
			}
		} else {
			for (char j = t - 1; j >= s + 1; j--) {
				if (p1 != 3) {
					if (j >= 'a' && j <= 'z') {
						for (int k = 0; k < p2; k++) {
							printf("%c", j + (p1 - 1) * ('A' - 'a'));
						}
					} else {
						for (int k = 0; k < p2; k++) {
							printf("%c", j);
						}
					}
				} else {
					for (int k = 0; k < p2; k++) {
						printf("*");
					}
				}
			}
		}
	}
	return 0;
}
