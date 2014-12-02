#include <stdio.h>
#include <string.h>

char arr[10000];
int j = 0;

void power(int a) {
	int i;
	while (a > 0) {
		if (a == 2) {
			arr[j++] = '2';
			return;
		}
		if (a == 1) {
			arr[j++] = '2';
			arr[j++] = '(';
			arr[j++] = '0';
			arr[j++] = ')';
			return;
		}
		for (i = 0; i < a; i++) {
			if ((1 << i) > a) {
				if (i == 2) {
					arr[j++] = '2';
					break;
				}
				arr[j++] = '2';
				arr[j++] = '(';
				power(i - 1);
				arr[j++] = ')';
				break;
			}
		}
		a -= (1 << (i - 1));
	}
}

int main( void ) {
	int n;
	int i;
	scanf("%d", &n);
	power(n);
	for (i = 0; i < j; i++) {
		printf("%c", arr[i]);
		if (arr[i + 1] == '2' && (arr[i] == ')' || arr[i] == '2'))
			printf("+");
	}
	return 0;
}
