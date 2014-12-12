#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1

using namespace std;

const int MAXN = 65537 << 1;

int cover[MAXN << 2];
int Xor[MAXN << 2];
int hash[MAXN];
void fxor(int rt) {
	if (cover[rt] != -1) cover[rt] ^= 1;
	else Xor[rt] ^= 1;
}

void pushDown(int rt) {
	if (cover[rt] != -1) {
		cover[rt << 1] = cover[rt << 1 | 1] = cover[rt];
		Xor[rt << 1] = Xor[rt << 1 | 1] = 0;
		cover[rt] = -1;
	}
	if (Xor[rt]) {
		fxor(rt << 1);
		fxor(rt << 1 | 1);
		Xor[rt] = 0;
	}
}

void update(char op, int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		if (op == 'U') {
			cover[rt] = 1;
			Xor[rt] = 0;
		} else if (op == 'D') {
			cover[rt] = 0;
			Xor[rt] = 0;
		} else if (op == 'C' || op == 'S') {
			fxor(rt);
		}
		return;
	}
	pushDown(rt);
	int m = (l + r) >> 1;
	if (L <= m) update(op, L, R, lch);
	else if (op == 'I' || op == 'C') cover[rt << 1] = Xor[rt << 1] = 0;
	if (R > m) update(op, L, R, rch);
	else if (op == 'I' || op == 'C') cover[rt << 1 | 1] = Xor[rt << 1 | 1] = 0;
}

void query(int l, int r, int rt) {
	if (cover[rt] == 1) {
		for (int i = l; i <= r; i++) hash[i] = 1;
	} else if (!cover[rt]) return;
	if (l == r) return;
	pushDown(rt);
	int m = (l + r) >> 1;
	query(lch);
	query(rch);
}

int main() {
	freopen("3225.in", "r", stdin);
	char op, lc, rc;
	int a, b;
	while (~scanf("%c %c%d,%d%c\n", &op, &lc, &a, &b, &rc)) {
		a <<= 1;
		b <<= 1;
		if (lc == '(') a++;
		if (rc == ')') b--;
		if (a > b) {
			if (op == 'I' || op == 'C')
				cover[1] = Xor[1] = 0;
		} else update(op, a, b, 0, MAXN, 1);
	}
	query(0, MAXN, 1);
	bool flag = false;
	int s = -1, e;
	for (int i = 0; i <= MAXN; i++) {
		if (hash[i]) {
			if (s == -1) s = i;
			e = i;
		} else {
			if (s == -1) continue;
			if (flag) printf(" ");
			flag = true;
			printf("%c%d,%d%c",s&1?'(':'[' , s>>1 , (e+1)>>1 , e&1?')':']');
			s = -1;
		}
	}
	if (!flag) printf("empty set");
	printf("\n");
	return 0;
}
