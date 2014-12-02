#include <stdio.h>
#include <string.h>

#define TRUE 1

char arr[1002];
int length[1002] = {1, 1};
int end[1002] = {0, 1};

int str(int n) {
	int i, j;
	int r = 0;
	for (i = 1; i < n; i++) {
		for (j = i; j <= (n - i >> 1) + i; j++) {
			if (arr[j] != arr[n - j + i]) {
				break;
			}
		}
		if (j == (n - i >> 1) + i + 1) {
			r = n - i + 1;
			return r;
		}
	}
	return r;
}

int main( void ) {
	FILE* in = fopen("str.in", "r");
	FILE* out = fopen("str.out", "w");
	int n = 1;
	char temp;
	while (TRUE) {
		temp = fgetc(in);
		if (temp == EOF) {
			break;
		}
		if (temp != '\n') {
			arr[n++] = temp;
		}
	}
	n -= 1;
	int i, t;
	for (i = 2; i <= n; i++) {
		if (i - 1 == end[i - 1]) {
			if (length[i - 1] == 1) {
				if (arr[i] == arr[i - 1]) {
					length[i] = 2;
				} else {
					length[i] = 1;
				}
				end[i] = i;
			} else {
				if (arr[i] == arr[i - length[i - 1] - 1]) {
					length[i] = length[i - 1] + 2;
					end[i] = i;
				} else {
					length[i] = length[i - 1];
					end[i] = end[i - 1];
				}
			}
		} else {
			t = str(i);
			if (t > length[i - 1]) {
				length[i] = t;
				end[i] = i;
			} else {
				length[i] = length[i - 1];
				end[i] = end[i - 1];
			}
		}
	}
	/*for (i = 1; i <= n; i++) {
		printf("%c %d %d\n", arr[i], length[i], end[i]);
	}*/

	fprintf(out, "%d", length[n]);
	fclose(in);
	fclose(out);
	return 0;
}
