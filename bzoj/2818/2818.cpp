#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXN = 10000005;
 
int phi[MAXN];
char vis[MAXN];
int prime[MAXN / 10], tot = 0;
long long sum[MAXN];
void init() {
    phi[1] = 1;
    for (int i = 2; i < MAXN - 4; i++) {
        if (!vis[i]) {
            prime[++tot] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= tot; j++) {
            if(i * prime[j] > MAXN) break;
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    phi[1] = 0;
    for (int i = 1; i <= MAXN - 4; i++)
        sum[i] = sum[i - 1] + phi[i];
}
int main() {
    init();
    int n;
    scanf("%d", &n);
    long long ans = 0;
    for (int i = 1; i <= tot; i++) {
        if (prime[i] > n) break;
        int t = n / prime[i];
        ans += sum[t] * 2 + 1;
    }
    printf("%lld\n", ans);
    return 0;
}