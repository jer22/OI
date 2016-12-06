#include <bits/stdc++.h>

using namespace std;

const int MAXN = 270005;
const long long G = 3;
const long long P = 4179340454199820289LL; // 29 * (2 ^ 57), 4e18, g = 3
// const long long P = 50000000001507329LL; //190734863287 * 2 ^ 18 + 1, g = 3
//const long long P = 1945555039024054273LL; // 27 * (2 ^ 56), 1e18, g = 5
// const long long P = 1004535809; // 479 * 2 ^ 21 + 1, g = 3
//const long long P = 998244353; // 119 * 2 ^ 23 + 1, g = 3

int T, n;
long long arr[MAXN];
long long brr[MAXN];

long long mul(long long x, long long y) {
	return (x * y - (long long)(x / (long double)P * y + 1e-3) * P + P) % P;
}
long long qpow(long long x, long long k, long long p){
	long long ret = 1;
	while (k) {
		if (k & 1) ret = mul(ret, x);
		k >>= 1;
		x = mul(x, x);
	}
	return ret;
}

long long wn[25];
void getwn(){
	for (int i = 1; i <= 18; i++) {
		int t = 1 << i;
		wn[i] = qpow(G, (P - 1) / t, P);
	}
}

int len;
void NTT(long long y[], int op){
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
		long long inv = qpow(len, P - 2, P);
		for (int i = 0; i < len; i++) y[i] = mul(y[i], inv);
	}
}
void Convolution(long long A[], long long B[], int n){
	for(len = 1; len < (n << 1); len <<= 1);
	for(int i = n; i < len; i++)
		A[i] = B[i] = 0;
	
	NTT(A, 1); NTT(B, 1);
	for(int i = 0; i < len; i++){
		A[i] = mul(A[i], B[i]);
	}
	NTT(A, -1);
}

int main() {
	freopen("1388.in", "r", stdin);
	scanf("%d", &T);
	getwn();
	while (T--) {
		scanf("%d", &n);
		long long tot = 0;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &arr[i]);
			tot += arr[i] * arr[i];
		}
		for (int i = 0; i < n; i++) {
			scanf("%lld", &brr[i]);
			tot += brr[i] * brr[i];
		}
		for (int i = 0; i < n / 2; i++)
			swap(brr[i], brr[n - i - 1]);
		Convolution(arr, brr, n);
		long long ans = 1ll << 62;
		for (int i = 0; i < n; i++) {
			long long t = tot - mul(arr[i] + arr[i + n], 2);
			while (t < 0) t += P;
			t %= P;
			ans = min(ans, t);
		}
		cout << ans << endl;
		

	}


	return 0;
}
