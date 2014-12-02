#include <stdio.h>
#include <string.h>

char re[16383];
int a1[16383];
int c[16383];

void times(int b) {
	int l = strlen(re);
	memset(a1, 0, sizeof(a1));
	memset(c, 0, sizeof(c));
	int i, j;
	
	for (i = l - 1; i >= 0; i--) {
		a1[l - i - 1] = re[i] - '0'; 
    }
	for (i = 0; i < l; i++) {
		c[i] += (a1[i] * b);
	}
	for (i = 0; i <= l; i++) {
		if (c[i] > 9) {
			c[i + 1] += c[i] / 10;
			c[i] = c[i] % 10;
		}
		if (c[l]) {
			l++;
		}
	}
    memset(re, 0, sizeof(re));
	for (i = 0; i < l; i++) {
		re[i] = c[l - i - 1] + '0';
	}
	re[i] = '\0';
}

int main( void ) {
	FILE* fin = fopen("cway.in", "r");
	FILE* fout = fopen("cway.out", "w");
	int n;
	fscanf(fin, "%d", &n);
	int i;
	re[0] = '1';
	re[1] = '\0';
	for (i = 1; i <= n - 2; i++) {
		times(i);
		re[strlen(re) - 1]++;

	}
	fprintf(fout, "%s", re);
	
	fclose(fin);
	fclose(fout);
	return 0;
}
