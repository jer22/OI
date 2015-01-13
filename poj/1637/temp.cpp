#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int SS = 202, TT = 203;
const int INF = 0x3fffffff;
int N, M, flow;
int in[205], out[205];
int mp[205][205]; // 用来记录无向边

struct Edge {
    int v, c, next;    
};
Edge e[10000];
int idx, head[205];
int lv[205], que[205];
int front, tail;

void insert(int a, int b, int c) {
    e[idx].v = b, e[idx].c = c;
    e[idx].next = head[a];
    head[a] = idx++;
}

bool Euler() {
    flow = 0;
    for (int i = 1; i <= N; ++i) {
        if (in[i] > out[i]) flow += (in[i]-out[i]) >> 1; // 定义入度大于出度的点流出流量 
        if (abs(in[i]-out[i]) & 1) { // 如果入度和出度之差为奇数
            return false;
        }
    }
    return true;
}

bool bfs() {
    front = tail = 0;
    memset(lv, 0xff, sizeof (lv));
    lv[SS] = 0;
    que[tail++] = SS;
    while (front < tail) {
        int u = que[front++];
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (!(~lv[v]) && e[i].c) {
                lv[v] = lv[u] + 1;
                if (v == TT) return true;
                que[tail++] = v;
            }
        }
    }
    return false;
}

int dfs(int u, int sup) {
    if (u == TT) return sup;
    int tf = 0, f;
    for (int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (lv[u]+1 == lv[v] && e[i].c && (f=dfs(v, min(e[i].c, sup-tf)))) {
            tf += f;
            e[i].c -= f, e[i^1].c += f;
            if (tf == sup) return sup;
        }
    }
    if (!tf) lv[u] = -1;
    return tf;
}

int dinic() {
    int ret = 0;
    while (bfs()) {
        ret += dfs(SS, INF);    
        cout << ret << endl;
    }
    return ret;
}

void solve() {
    idx = 0;
    memset(head, 0xff, sizeof (head));
    for (int i = 1; i <= N; ++i) {
        if (in[i] > out[i]) {
            insert(SS, i, (in[i]-out[i])>>1);
            insert(i, SS, 0);
        } else if (out[i] > in[i]) {
            insert(i, TT, (out[i]-in[i])>>1);
            insert(TT, i, 0);
        }
        for (int j = 1; j <= N; ++j) {
            if (mp[i][j]) {// 这是假定的双向边的方向    
                insert(j, i, mp[i][j]);
                insert(i, j, 0);
            }
        }
    }
    int a = dinic();
    if (a == flow) {
        puts("possible");
    } else {
        puts("impossible");
    }
}

int main() {
    freopen("1637.in", "r", stdin);
    int T, a, b, c;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &N, &M); // N个点，M条边
        memset(in, 0, sizeof (in));
        memset(out, 0, sizeof (out));
        memset(mp, 0, sizeof (mp));
        for (int i = 0; i < M; ++i) {
            scanf("%d %d %d", &a, &b, &c);
            ++in[b], ++out[a];
            if (!c) {// 说明该边是双向的
                ++mp[a][b]; // 默认把a作为弧尾，b作为弧头 
            }
        }
        if (!Euler()) {
            puts("impossible");
            continue;
        }
        solve();
    }
    return 0;
}