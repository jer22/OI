#include <stdio.h>
#include <string.h>

void add(char * a, char * b) {
    int la = strlen(a), lb = strlen(b);
    int l = la > lb ? la : lb;
    int a1[1024];
    int b1[1024];
    memset(a1, 0, sizeof(a1));
    memset(b1, 0, sizeof(b1));
    int i;

    for (i = la - 1; i >= 0; i--)
        a1[la - i - 1] = a[i] - '0';
    for (i = lb - 1; i >= 0; i--)
        b1[lb - i - 1] = b[i] - '0';
    for (i = 0; i < l; i++) {
        a1[i] += b1[i];
        a1[i + 1] += a1[i] / 10;
        a1[i] = a1[i] % 10;
    }
    if (a1[l]) l++;
    memset(a, 0, sizeof(a));
    for (i = 0; i < l; i++) {
        a[l - i - 1] = a1[i] + '0';
    }
    a[i] = '\0';
    free(a1);
    free(b1);
}

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

	a[i] = '\0';
	free(a1);
    free(c);
}

int main( void ) {
	int n;
	scanf("%d", &n);
	int i, j;
    char re[10000];
    char temp[10000];
    strcpy(temp, "1");
    strcpy(re, "0");
	for (i = 1; i <= n; i++) {
        for (j = 1; j <= i; j++) {
            times(temp, j);
        }
        add(re, temp);
        strcpy(temp, "1");
    }
    printf("%s", re);
	return 0;
}
