#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;

struct Num {
    int a[2048], len;
    void print() {
        for (int i = len - 1; i >= 0; i--) {
            printf("%d", a[i]);
        }
        printf("\n");
    }
}a[102], b[102];

Num operator - (Num a, Num b) {
    int i;
    for (i = 0; i < b.len; i++) {
        a.a[i] -= b.a[i];
    }
    for (i = 0; i < a.len; i++) {
        if (a.a[i] < 0) {
            a.a[i] += 10;
            a.a[i + 1]--;
        }
    }
    while (!a.a[a.len - 1]) a.len--;
    return a;
}

Num operator * (Num a, Num b) {
    Num c;
    c.len = a.len + b.len;
    memset(c.a, 0, sizeof(c.a));
    for (int i = 0; i < a.len; i++) {
        for (int j = 0; j < b.len; j++) {
            c.a[i + j] += a.a[i] * b.a[j];
        }
    }
    for (int i = 0; i < c.len; i++) {
        c.a[i + 1] += c.a[i] / 10;
        c.a[i] %= 10;
    }
    while (!c.a[c.len - 1]) c.len--;
    return c;
}

Num operator ^ (Num a, int b) {
    int i;
    for (i = 0; i < a.len; i++) {
        a.a[i] *= b;
    }
    for (i = 0; i < a.len; i++) {
        a.a[i + 1] += a.a[i] / 10;
        a.a[i] %= 10;
    }
    while (a.a[a.len]) {
        a.a[a.len + 1] += a.a[a.len] / 10;
        a.a[a.len] %= 10;
        a.len++;
    }
    return a;
}

void cpy(Num &a, Num b) {
    a.len = b.len;
    for (int i = 0; i < a.len; i++) {
        a.a[i] = b.a[i];
    }
}

int main( void ){
    scanf("%d", &n);
    a[1].a[0] = 1;
    a[2].a[0] = 4;
    b[1].a[0] = 1;
    b[2].a[0] = 3;
    a[1].len = a[2].len = b[1].len = b[2].len = 1;
    for (int i = 3; i <= n; i++) {
        cpy(a[i], (a[i - 1] ^ 3) - a[i - 2]);
        cpy(b[i], (b[i - 1] ^ 3) - b[i - 2]);
    }
    Num ans;
    if (n % 2) cpy(ans, a[n + 1 >> 1] * a[n + 1 >> 1]);
    else cpy(ans, b[n >> 1] * b[n >> 1] ^ 5);
    ans.print();
    return 0;
}
