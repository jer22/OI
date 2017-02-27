#include <stdio.h>  
#include <vector>  
#include <string>  
#include <algorithm>  
#include <queue>  
#include <cstring>  
#include <map>  
#include <set>  
#include <iostream>  
#include <cmath>  
using namespace std;  
#ifdef __GNUC__  
#define opt64(a) printf("%lld",a);  
#else  
typedef __int64 LL;  
#define opt64(a) printf("%I64d",a);  
#endif // __GNUC__  
//acm.hdu.edu.cn/showproblem.php?pid=5076  
const int MAXN = 1<<10;  
const int inf = 0x3f3f3f3f;  
const double eps = 1e-8;  
const double PI = acos(-1.0);  
int n, m;  
int thrd[MAXN], u[MAXN];  
int LE[MAXN], LEid[MAXN], Ss[MAXN], Sid[MAXN];   

struct Edge{
	int to;
	int cap;
	Edge() {}
	Edge(int a, int b) : to(a), cap(b) {}
};

vector<Edge> edges;
vector<int> G[MAXN];
int dis[MAXN];
int cur[MAXN];

void add(int from, int to, int cap) {
	edges.push_back(Edge(to, cap));
	edges.push_back(Edge(from, 0));
	G[from].push_back(edges.size() - 2);
	G[to].push_back(edges.size() - 1);
}
int S, T;
bool build() {
	memset(dis, -1, sizeof(dis));
	queue<int> q;
	q.push(S);
	dis[S] = 0;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++) {
			Edge& e = edges[G[x][i]];
			if (dis[e.to] == -1 && e.cap > 0) {
				dis[e.to] = dis[x] + 1;
				q.push(e.to);
			}
		}
	}
	return dis[T] != -1;
}

int find(int x, int a) {
	if (x == T || a == 0) return a;
	int flow = 0, f;
	for (int& i = cur[x]; i < G[x].size(); i++) {
		Edge& e = edges[G[x][i]];
		if (dis[x] + 1 == dis[e.to]
			&& (f = find(e.to, min(a, e.cap))) != 0) {
			e.cap -= f;
			edges[G[x][i] ^ 1].cap += f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}
  
int main()  
{  
    freopen("g.in", "r", stdin);  
    int cc;  
    scanf("%d", &cc);  
    while (cc--)  
    {  
    	edges.clear();
    	for (int i = 0; i < MAXN; i++)
    		G[i].clear();
        scanf("%d%d", &n, &m);  
        n = 1<<n; m = 1<<m;  
        for (int i = 0; i< n; ++i) scanf("%d", thrd+i);  
        for (int i = 0; i< n; ++i) scanf("%d", u+i);  
        for (int i = 0; i< n; ++i)  
        {  
            LE[i] = -1, Ss[i] = -1;  
            for (int j = 0; j< m; ++j)  
            {  
                int w;  
                scanf("%d", &w);  
                w += 2333;  
                if (j >= thrd[i])  
                {  
                    if (LE[i] < w) LE[i]=w, LEid[i]=j;  
                }  
                else  
                {  
                    if (Ss[i] < w) Ss[i] = w, Sid[i] = j;  
                }  
            }  
        }  
        S = 2*n, T = S+1;  
        for (int i = 0; i< n; ++i)  
        {  
            int k = __builtin_popcount(i);  
            if (k & 1)  
                add(S, i, Ss[i]), add(i+n, T, LE[i]);  
            else  
                add(S, i, LE[i]), add(i+n, T, Ss[i]);  
            add(i, i+n, inf);  
            for (int j = i+1; j< n; ++j)  
            {  
                if (__builtin_popcount(i^j) == 1)  
                {  
                    if (k & 1)  
                        add(i, j+n, u[i]^u[j]);  
                    else  
                        add(j, i+n, u[i]^u[j]);  
                }  
            }  
        }  
        while (build())  {
        	memset(cur, 0, sizeof(cur));
            find(S, inf);  
        }
        for (int i = 0; i < n; i++)  
        {  
            if (i)  
                printf(" ");  
            int aa = __builtin_popcount(i);  
            if (aa & 1) {  
                if (dis[i] != -1)  
                    printf("%d", Sid[i]);  
                else  
                    printf("%d", LEid[i]);  
            } else {  
                if (dis[i] != -1)  
                    printf("%d", LEid[i]);  
                else  
                    printf("%d", Sid[i]);  
            }  
        }  
        printf("\n");  
    }  
    return 0;  
}  