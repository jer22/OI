#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <stack>
#include <cctype>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <climits>
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
#define fi first
#define se second
#define ping(x,y) ((x-y)*(x-y))
#define mst(x,y) memset(x,y,sizeof(x))
#define mcp(x,y) memcpy(x,y,sizeof(y))
using namespace std;
#define gamma 0.5772156649015328606065120
#define mod 1000000007
#define inf 0x3f3f3f3f
#define N 1005050
#define maxn 20005
typedef pair<int,int> PII;
typedef long long LL;

int n,m,k,x,y,v;
int S,T,L;
int head[N],hcnt;
struct Node{
    int to,nxt,v;
}node[maxn];
int d[N],vis[N],s[maxn];
vector<int>eg;  ///存重构边
queue<int>q;
int spfa(){   
    for(int i=0;i<n;++i) d[i]=(int)1e9+1; d[S]=0;
    mst(vis,0); q.push(S);
    while(!q.empty()){
        int x=q.front();q.pop(); vis[x]=0;
        for(int i=head[x];~i;i=node[i].nxt){
            int e=node[i].to;
            if(d[e]>d[x]+node[i].v){
                d[e]=d[x]+node[i].v;
                if(!vis[e]){vis[e]=1;q.push(e);}
            }
        }
    }
    return d[T];
}
int check(LL sum){  ///判断是否合法
    for(int i = 0; i < eg.size(); i++){
    	int u = eg[i];
        node[u].v=node[u|1].v=1+min(sum, 1000000000ll); 
                    ///给每个重构边分配权值
        sum-=node[u].v-1;
    }
    return spfa();
}
inline void add(int x,int y,int v){
    node[hcnt].to=y;node[hcnt].nxt=head[x];node[hcnt].v=v;head[x]=hcnt++;
}
int main(){
	freopen("d.in", "r", stdin);
    int i,j,group;
    mst(head,-1);
    scanf("%d%d%d%d%d",&n,&m,&L,&S,&T);
    for(i=1;i<=m;++i){
        scanf("%d%d%d",&x,&y,&v);
        if(!v)eg.push_back(hcnt);
        s[hcnt]=x;
        add(x,y,v);
        add(y,x,v);
    }
    LL l=0,r=eg.size()*LL(1e9);
    if(check(0)>L||check(r)<L)return 0*printf("NO\n");
    LL ans;
    while(l<=r){
        LL mid=l+r>>1,temp=check(mid);
        if(temp>L)ans=mid,r=mid-1;
        else if(temp<L)l=mid+1;
        else break;
    }
    printf("YES\n");
    for(i=0;i<m*2;i+=2)printf("%d %d %d\n",s[i],node[i].to,node[i].v);
    return 0;
}