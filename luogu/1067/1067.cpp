#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int n;
int main() {
	freopen("1067.in", "r", stdin);
	scanf("%d", &n);
	int power = n;
	int t;
	for (int i = 0; i <= n; i++) {
		scanf("%d", &t);
		if (!t) {
			power--;
			continue;
		}
		
		if (t > 0 && i) {
			printf("+");
		} else if (t < 0) {
			printf("-");
		}
		
		if (power == 1) {
			if (t == 1 || t == -1) {
				printf("x");
			} else {
				printf("%dx", abs(t));
			}
		} else if (!power) {
			printf("%d", abs(t));
		} else {
			if (t == 1 || t == -1) {
				printf("x^%d", power);
			} else {
				printf("%dx^%d", abs(t), power);
			}
			
		}
		power--;
	}

	return 0;
}
