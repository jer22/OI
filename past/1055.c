#include <stdio.h>
#include <string.h>
int idx(char c) {
    return c - '0';
}
int main( void ) {
    int nn, b, j = 1, i, sum = 0;
    int a[20];
    char s[26];
    memset(a, 0, sizeof(a));
    scanf("%s", s);
    nn = strlen(s);
    for(i = 0; i < nn; i++)
       if((s[i] != '-') && (s[i] != 'X')) a[j++] = idx(s[i]);
    if(s[12] == 'X') a[10] = 10;
    for(i = 1;i < 10; i++)
       sum += a[i]*i;
    b = sum % 11;
    if(b == a[10]) printf("Right");
    else {
        printf("%d-%d%d%d-%d%d%d%d%d-", a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);
        if(b < 10) printf("%d", b);
        else printf("X");
    }
    return 0;

}
