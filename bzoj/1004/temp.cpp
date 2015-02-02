#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 100
#define M 25
using namespace std;
 
int n, m, a[N];
int sb, sr, sg;
int yu;
int f[M][M][M];
 
int mi(int a, int b)
{
    int ans = 1, zan = a;
    while (b)
    {
        if (b & 1)
        {
            ans *= zan;
            if (ans > yu) ans %= yu;
        }
        b >>= 1;
        zan *= zan;
        if (zan > yu) zan %= yu;
    }
    return ans;
}
 
int cal()
{
    memset(f, 0, sizeof(f));
    int cir[N] = {0}, cirnum = 0;
    bool vis[N] = {0};
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
        {
            cirnum ++; cir[cirnum] = 1;
            vis[i] = 1; int x = a[i];
            while (!vis[x])
            {
                vis[x] = 1;
                cir[cirnum] ++;
                x = a[x];
            }
        }
    f[0][0][0] = 1;
    for (int w = 1; w <= cirnum; ++w)
    for (int i = sr; i >= 0; --i)
    for (int j = sb; j >= 0; --j)
    for (int k = sg; k >= 0; --k)
    {
        if (i - cir[w] >= 0) f[i][j][k] += f[i-cir[w]][j][k];
        if (f[i][j][k] > yu) f[i][j][k] %= yu;
        if (j - cir[w] >= 0) f[i][j][k] += f[i][j-cir[w]][k];
        if (f[i][j][k] > yu) f[i][j][k] %= yu;
        if (k - cir[w] >= 0) f[i][j][k] += f[i][j][k-cir[w]];
        if (f[i][j][k] > yu) f[i][j][k] %= yu;
    }
    return f[sr][sb][sg];
}
 
int main()
{
    freopen("1004.in", "r", stdin);
    scanf("%d%d%d%d%d", &sr, &sb, &sg, &m, &yu);
    n = sr+sb+sg;
    int ans = 0;
    for (int i = 1; i <= n; ++i) a[i] = i;
    ans += cal(); if (ans > yu) ans %= yu;
    for (int i = 1; i <= m; ++i)
    {
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        ans += cal(); if (ans > yu) ans %= yu;
    }
    ans *= mi(m+1, yu-2)%yu;
    printf("%d\n", ans % yu);
}