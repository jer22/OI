#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int n, m;
vector<int> edges[MAXN];
int dfn[MAXN], low[MAXN];
int father[MAXN];
int tim = 0;
void Tarjan(int i,int Father) {
    father[i]=Father;/*记录每一个点的父亲*/
    dfn[i]=low[i]=tim++;
    for(int j=0;j<edges[i].size();++j)
    {
        int k=edges[i][j];
        if(dfn[k]==-1)
        {
            Tarjan(k,i);
            low[i]=min(low[i],low[k]);
        }
        else if(Father!=k)/*假如k是i的父亲的话，那么这就是无向边中的重边，有重边那么一定不是桥*/
            low[i]=min(low[i],dfn[k]);//dfn[k]可能！=low[k]，所以不能用low[k]代替dfn[k],否则会上翻过头了。
    }
}
int deg[MAXN], cnt[MAXN], col[MAXN];
bool vis[MAXN];

vector<int> bri[MAXN];
void count()
{
    int rootson=0;
    Tarjan(1,0);
    // for(int i=2;i<=n;++i)
    // {
    //     int v=father[i];
    //     if(v==1)
    //     rootson++;/*统计根节点子树的个数，根节点的子树个数>=2,就是割点*/
    //     else{
    //         if(low[i]>=dfn[v])/*割点的条件*/
    //         is_cut[v]=true;
    //     }
    // }
    // if(rootson>1)
    // is_cut[1]=true;
    // for(int i=1;i<=n;++i)
    // if(is_cut[i])
    // printf("%d\n",i);
    for(int i=1;i<=n;++i)
    {
        int v=father[i];
        
        if(v>0&&low[i]>dfn[v]) {/*桥的条件*/
        	// printf("%d,%d\n",v,i);
        	// deg[v]--;
        	// deg[i]--;
        	cnt[v]++;
        	cnt[i]++;
        	bri[v].push_back(i);
        	bri[i].push_back(v);
    	}
    }
    
}

void dfs(int x) {
	vis[x] = 1;
	for (auto nex : edges[x]) if (!vis[nex]) dfs(nex);
}

int rd[MAXN];
int main() {
	freopen("b.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b;
	long long lp = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &a, &b);
		if (a != b) {
			deg[a]++;
			edges[a].push_back(b);
			edges[b].push_back(a);
			deg[b]++;
		} else {
			rd[a]++;
			lp++;
		}
	}
	int tt = 0;
	for (int i = 1; i <= n; i++) {
		if (!deg[i] && !rd[i]) continue;
		if (!vis[i]) {
			dfs(i);
			tt++;
		}
	}
	if (tt > 1) {
		printf("0\n");
		return 0;
	}

	int coln = 0;
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += (long long)deg[i] * (deg[i] - 1) / 2;
	}
	ans += lp * (m - 1) - lp * (lp - 1) / 2;

	cout << ans << endl;


	return 0;
}
