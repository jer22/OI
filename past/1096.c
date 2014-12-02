#include <stdio.h>
#include <string.h>

void times(char * a, int b) {
	int l = strlen(a);
	int a1[1024];
	int c[1024];
    memset(a1, 0, sizeof(a1));
    memset(c, 0, sizeof(c));
	int i, j;
	
	for (i = l - 1; i >= 0; i--) {
		a1[l - i - 1] = a[i] - '0'; 
    }
	for (i = 0; i < l; i++) {
		c[i] += (a1[i] * b);
	}
	for (i = 0; i <= l; i++) {
		if (c[i] > 9) {
			c[i + 1] += c[i] / 10;
			c[i] = c[i] % 10;
		}
	}
	for (i = l; i <= l; i++) {
        if (c[i] || c[i + 1]) l++;
    }
    memset(a, 0, sizeof(a));
	for (i = 0; i < l; i++) {
		a[i] = c[l - i - 1] + '0';
	}

	a[l] = '\0';
	free(a1);
    free(c);
}

int main( void ) {
	int n;
	int i;
	char re[100];
	strcpy(re, "1");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		times(re, 2);
	}
	re[strlen(re) - 1]--;
	times(re, 2);
	printf("%s\n", re);
	system("pause");
	return 0;
}
