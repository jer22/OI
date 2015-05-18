/* I will wait for you*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <string>
#define m_p make_pair
#define p_b push_back
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int maxn = 100010;
const int maxm = 1010;
const int maxs = 26;
const int inf = 0x3f3f3f3f;
const int P = 1000000007;
const double error = 1e-9;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch <= 47 || ch >= 58)
        f = (ch == 45 ? -1 : 1), ch = getchar();
    while (ch >= 48 && ch <= 57)
        x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

struct edge
{
    int v, next;
} e[4 * maxn];

int n, cnt, tot, clo, c[maxn], next[maxn][maxs], q[4 * maxn], fa[maxn], 
    head[maxn], size[maxn], val[maxn], fail[maxn], dfn[maxn], ans[maxn];
char s[maxn];

vector<pii> query[maxn];

void init()
{
    int now = 0, len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == 'P')
            val[++cnt] = now;
        if (s[i] == 'B')
            now = fa[now];
        if (s[i] >= 'a' && s[i] <= 'z') {
            int pos = s[i] - 'a';
            if (!next[now][pos]) {
                next[now][pos] = ++tot;
                fa[tot] = now;
            }
            now = next[now][pos];
        }
    }

    int l = 0, r = 1;
    while (l != r) {
        int u = q[l++];
        for (int i = 0, pos; i < maxs; i++) {
            if (!(pos = next[u][i]))
                next[u][i] = next[fail[u]][i];
            else {
                fail[pos] = u ? next[fail[u]][i] : 0;
                q[r++] = pos;
            }
        }
    }
}

void insert(int u, int v)
{
    e[cnt] = (edge) {v, head[u]}, head[u] = cnt++;
}

void dfs(int u)
{
    dfn[u] = ++clo, size[u] = 1;
    for (int i = head[u]; i != -1; i = e[i].next)
        dfs(e[i].v), size[u] += size[e[i].v];
}

void change(int x, int y)
{
    for (; x < maxn; c[x] += y, x += x & -x);
}

int sum(int x)
{
    int tmp = 0;
    for (; x; tmp += c[x], x -= x & -x);
    return tmp;
}

void solve()
{
    cnt = 0, memset(head, -1, sizeof head);

    for (int i = 1; i <= tot; i ++)
        insert(fail[i], i);
    cnt = 0, dfs(0);

    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == 'B')
            change(dfn[cnt], -1), cnt = fa[cnt];
        if (s[i] == 'P') {  
            for (int i = 0; i < query[cnt].size(); i++) {
                pii tmp = query[cnt][i];
                int root = tmp.fi, r = dfn[root];
                ans[tmp.se] = sum(r + size[root] - 1) - sum(r - 1);
            }
        }
        if (s[i] >= 'a' && s[i] <= 'z') {
            cnt = next[cnt][s[i] - 'a'];
            change(dfn[cnt], 1);
        }
    }
}

int main()
{
    freopen("2434.in", "r", stdin);
    scanf("%s", s), n = read(), init();

    for (int i = 1; i <= n; i++) {
        int x = read(), y = read();
        query[val[y]].p_b(m_p(val[x], i));
    }

    solve();

    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);

    return 0;
}