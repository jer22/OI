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
    for (i = 0; i < l; i++)
        a[l - i - 1] = a1[i] + '0';
    a[i] = '\0';
    free(a1);
    free(b1);
}

void times(char * a) {
	int l = strlen(a);
	int a1[1024];
	int c[1024];
	memset(a1, 0, sizeof(a1));
	memset(c, 0, sizeof(c));
	int i, j;
	for (i = l - 1; i >= 0; i--)
		a1[l - i - 1] = a[i] - '0'; 
	for (i = 0; i < l; i++)
		c[i] += (a1[i] << 1);
	for (i = 0; i <= l; i++) {
		if (c[i] > 9) {
			c[i + 1] += c[i] / 10;
			c[i] = c[i] % 10;
		}
	}
	if (c[l]) l++;
	memset(a, 0, sizeof(a));
	for (i = 0; i < l; i++)
		a[i] = c[l - i - 1] + '0';
	a[i] = '\0';
	free(a1);
	free(c);
}

int mod(char *a,int m) {
	int i, j;
	int a1[10000];
	int l = strlen(a);
	memset(a1, 0, sizeof(a1));
	for(i = 0; i < l; i++)
		a1[i] = a[i] - '0';
	for(i = 0; i < l; i++) {
		a1[i + 1] += a1[i] % m * 10;
	}
	return a1[l] / 10;
}

char a[200004];
int b;
char a1[20000];
int b1 = 0;
char temp[20000];
int temp1 = 1;
int main( void ) {
	FILE * in = fopen("binary.in", "r");
	FILE * out = fopen("binary.out", "w");
	fscanf(in, "%s%d", a, &b);
	int i;
	int la = strlen(a);
	int lb = strlen(b);
	strcpy(a1, "0");
	strcpy(temp, "1");
	int re = mod(a, b);
	char re2[100];
	int n;
	for (n = 0; temp1 < re; n++) {
		temp1 <<= 1;
	}
	temp1 = 0;
	int t;
	for (i = 0; i < n; i++) {
		t = 1 << (n - i - 1);
		if ((temp1 + t) <= re) {
			re2[i] = '1';
			temp1 += t;
		} else {
			re2[i] = '0';
		}
	}
	re2[i] = '\0';
	fprintf(out, "%s", re2);
	fclose(in);
	fclose(out);
	return 0;
}
