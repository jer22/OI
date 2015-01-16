#include <cstdio>
#include <iostream>
#include<queue>
#include<set>
#include<ctime>
#include<algorithm>
#include<cmath>
#include<vector>
#include<map>
#include<cstring>
using namespace std;
const double eps=1e-10;
#define M 109
#define type double 
const type inf=(1)<<30;
struct point 
{
    double x,y;
}p[M];
double dis(point a,point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
struct Node{
    int u , v;
    type cost;
}E[M*M+5];
int pre[M],ID[M],vis[M];
type In[M];
int n,m; 
type Directed_MST(int root,int NV,int NE) {
    type ret = 0;
    while(true) {
        //1.找最小入边
        for(int i=0;i<NV;i++) In[i] = inf;
        for(int i=0;i<NE;i++){
            int u = E[i].u;
            int v = E[i].v;
            if(E[i].cost < In[v] && u != v) {
                pre[v] = u;
                In[v] = E[i].cost;
            }
        }
        for(int i=0;i<NV;i++) {
            if(i == root) continue;
            if(In[i] == inf)    return -1;//除了跟以外有点没有入边,则根无法到达它
        }
        //2.找环
        int cntnode = 0;
        //  CC(ID,-1);
        //  CC(vis,-1);
        memset(ID,-1,sizeof(ID));
        memset(vis,-1,sizeof(vis));
        In[root] = 0;
        for(int i=0;i<NV;i++) {//标记每个环
            ret += In[i];
            int v = i;
            while(vis[v] != i && ID[v] == -1 && v != root) {
                vis[v] = i;
                v = pre[v];
            }
            if(v != root && ID[v] == -1) {
                for(int u = pre[v] ; u != v ; u = pre[u]) {
                    ID[u] = cntnode;
                }
                ID[v] = cntnode ++;
            }
        }
        if(cntnode == 0)    break;//无环
        for(int i=0;i<NV;i++) if(ID[i] == -1) {
            ID[i] = cntnode ++;
        }
        //3.缩点,重新标记
        for(int i=0;i<NE;i++) {
            int v = E[i].v;
            E[i].u = ID[E[i].u];
            E[i].v = ID[E[i].v];
            if(E[i].u != E[i].v) {
                E[i].cost -= In[v];
            }
        }
        NV = cntnode;
        root = ID[root];
    }
    return ret;
}


int main()
{
    freopen("3164.in", "r", stdin);
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        // memset(pre,0,sizeof(pre));
        for(int i=0;i<n;i++)
            scanf("%lf%lf",&p[i].x,&p[i].y);
        for(int i=0;i<m;i++)  {
            scanf("%d%d",&E[i].u,&E[i].v);
            E[i].u--;
            E[i].v--;
            if(E[i].u!=E[i].v)
            E[i].cost=dis(p[E[i].u],p[E[i].v]);
            else E[i].cost=1<<30;
        }
        type ans=Directed_MST(0,n,m);
        if(ans==-1)
            printf("poor snoopy\n");
        else 
            printf("%.2f\n",ans);
    }
    return 0;
}