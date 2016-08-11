

    #include <iostream>  
    #include <string>  
    #include <vector>  
    #include <cstring>  
    #include <cstdio>  
    #include <map>  
    #include <queue>  
    #include <algorithm>  
    #include <stack>  
    #include <cstring>  
    #include <cmath>  
    #include <set>  
    #include <vector>  
    using namespace std;  
    template <class T>  
    inline bool rd(T &ret) {  
        char c; int sgn;  
        if (c = getchar(), c == EOF) return 0;  
        while (c != '-' && (c<'0' || c>'9')) c = getchar();  
        sgn = (c == '-') ? -1 : 1;  
        ret = (c == '-') ? 0 : (c - '0');  
        while (c = getchar(), c >= '0'&&c <= '9') ret = ret * 10 + (c - '0');  
        ret *= sgn;  
        return 1;  
    }  
    template <class T>  
    inline void pt(T x) {  
        if (x < 0) {  
            putchar('-');  
            x = -x;  
        }  
        if (x > 9) pt(x / 10);  
        putchar(x % 10 + '0');  
    }  
    typedef long long ll;  
    typedef pair<int, int> pii;  
    const int inf = 1e9;  
    const int N = 1e5+10;  
    int n;  
    int num[N], dp[N], siz, root;  
    bool vis[N];  
    vector<int>G[N];  
    char s[N];  
    void getroot(int u, int fa) {  
        dp[u] = 0; num[u] = 1;  
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];  
            if (vis[v] || v == fa)continue;  
            getroot(v, u);  
            num[u] += num[v];  
            dp[u] = max(num[v], dp[u]);  
        }  
        dp[u] = max(dp[u], siz - num[u]);  
        if (dp[u] < dp[root])root = u;  
    }  
    void work(int u, int fa, int dep) {  
        root = 0; siz = num[u];  
        getroot(u, fa);  
        s[root] = dep + 'A';  
        vis[root] = true;  
        for (int i = 0; i < G[root].size(); i++) {  
            int v = G[root][i];
            if (vis[v])continue;  
            work(v, u, dep + 1);  
        }  
    }  
    void init() {  
        dp[0] = num[1] = n;  
        memset(vis, 0, sizeof vis);  
    }  
    int main() {  
        freopen("c.in", "r", stdin);
        rd(n);  
        for (int i = 1, u, v; i < n; i++) {  
            rd(u); rd(v); G[u].push_back(v); G[v].push_back(u);  
        }  
        init();  
        work(1, 1, 0);  
        for (int i = 1; i <= n; i++)putchar(s[i]), putchar(' ');  
        return 0;  
    }  