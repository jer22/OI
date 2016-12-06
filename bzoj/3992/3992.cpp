#include <bits/stdc++.h>

using namespace std;

const long long P = 1004535809; // 479 * 2 ^ 21 + 1, g = 3
const int G = 3;
const int MAXM = 17000;

int n, m, x, s, len;
long long power(long long a, long long b, long long p) {
	long long res = 1;
	for (; b; (a *= a) %= p, b >>= 1)
		if (b & 1) (res *= a) %= p;
	return res;
}

int getpr(int p) {
	static int st[MAXM], top;
	int tmp = p - 1;
	for (int i = 2; i <= tmp; i++) {
		if (tmp % i) continue;
		st[++top] = i;
		while (!(tmp % i)) tmp /= i;
	}
	for (int i = 2;; i++) {
		int j;
		for (j = 1; j <= top; j++) {
			if (power(i, (m - 1) / st[j], m) == 1)
				break;
		}
		if (j == top + 1) return i;
	}
}
long long mul(long long x, long long y) {
	return (x * y - (long long)(x / (long double)P * y + 1e-3) * P + P) % P;
}
long long wn[25];
void getwn() {
	for (int i = 1; i <= 18; i++) {
		int t = 1 << i;
		wn[i] = power(G, (P - 1) / t, P);
	}
}
void NTT(int y[], int op) {
	for (int i = 1, j = len >> 1, k; i < len - 1; i++){
		if (i < j) swap(y[i], y[j]);
		k = len >> 1;
		while (j >= k){
			j -= k;
			k >>= 1;
		}
		if (j < k) j += k;
	}
	int id = 0;
	for (int h = 2; h <= len; h <<= 1) {
		id++;
		for (int i = 0; i < len; i += h) {
			long long w = 1;
			for (int j = i; j < i + (h >> 1); ++j){
				long long u = y[j], t = mul(y[j + h / 2], w);
				y[j] = u + t;
				if (y[j] >= P) y[j] -= P;
				y[j + h / 2] = u - t + P;
				if (y[j + h / 2] >= P) y[j + h / 2] -= P;
				w = mul(w, wn[id]);
			}
		}
	}
	if (op == -1) {
		for (int i = 1; i < len / 2; i++) swap(y[i], y[len - i]);
		long long inv = power(len, P - 2, P);
		for (int i = 0; i < len; i++) y[i] = mul(y[i], inv);
	}
}
struct Node{
	int a[MAXM];
	Node() {
		memset(a, 0, sizeof(a));
	}
	int &operator [] (int x) {
		return a[x];
	}
	Node &operator *= (const Node &f) {
		static int b[MAXM];
		memcpy(b, f.a, sizeof(b));
		NTT(a, 1);
		NTT(b, 1);
		for (int i = 0; i < len; i++)
			a[i] = mul(a[i], b[i]);
		NTT(a, -1);
		for (int i = m - 1; i <= m - 2 << 1; i++)
			(a[i - m + 1] += a[i]) %= P, a[i] = 0;
		return *this;
	}
};
Node po(Node a, int b) {
	Node res = Node();
	res[0] = 1;
	for (; b; a *= a, b >>= 1)
		if (b & 1) res *= a;
	return res;
}
int gind[MAXM];
int main() {
	freopen("3992.in", "r", stdin);
	scanf("%d %d %d %d", &n, &m, &x, &s);
	int g = getpr(m);
	getwn();
	for (int i = 0, t = 1; i < m - 1; i++, (t *= g) %= m)
		gind[t] = i;
	int a;
	Node ori = Node();
	for (len = 1; len <= m + m; len <<= 1);
	for (int i = 1; i <= s; i++) {
		scanf("%d", &a);
		if (!a) continue;
		ori[gind[a]] = 1;
	}
	ori = po(ori, n);
	printf("%d\n", ori[gind[x]]);
	return 0;
}
