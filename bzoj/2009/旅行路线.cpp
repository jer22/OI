#include<cstdio>
#include<cstdlib>
#include<map>
#include<bitset>
#include<algorithm>

using namespace std;

const int MAXN=3, MAXM=50, MAXNUM=MAXN*MAXM+1;
const int MOD=11192869;

void inc(int &a, int b)
{
    if((a+=b)>=MOD)
        a-=MOD;
}

int N,M;
struct status
{
    bitset<MAXNUM+1> use;
    int a[MAXN], w;
    int pre_suc(int t)
    {
        if(t<0)
            return 3;
        return (t==1 || use[t-1])<<1 | (t==N*M || use[t+1]);
    }
    int pre_suc_a(int t)
    {
        return pre_suc(a[t]);
    }
    void add(int j);

    bool adj(int j,int k)
    {
        return a[j]==k || (j && a[j-1]==k);
    }
    void work(int j, int k)
    {
        if(!use[k] && use[k-1]==adj(j, k-1) && use[k+1]==adj(j, k+1))
        {
            int t=a[j];
            use[k]=1;
            a[j]=k;
            add(j+1);
            a[j]=t;
            use[k]=0;
        }
    }
};

map<int,status> f[MAXN+1];
void status::add(int j)
{
    int i, t=0;
    for(i=0;i<N;++i)
        t=(t*MAXNUM+max(a[i],0))*4+pre_suc_a(i);
    if(f[j].count(t))
        inc(f[j][t].w, w);
    else f[j][t]=*this;
}

int T[MAXN][MAXM], L[MAXNUM];
int main()
{

    int i,j,k;
    scanf("%d%d",&N,&M);
    for(i=0;i<N;++i)
        for(j=0;j<M;++j)
            scanf("%d",T[i]+j);
    for(i=1;i<=N*M;++i)
        scanf("%d",L+i);

    map<int,status>::iterator it, tmp;
    status init;
    init.a[0]=init.a[1]=init.a[2]=-1, init.w=1;
    init.add(N);
    for(i=0;i<M;++i)
    {
        f[0].swap(f[N]);
        for(j=1;j<=N;++j)
            f[j].clear();
        for(it=f[0].begin(); it!=f[0].end(); )
            if(it->second.pre_suc_a(N-1)==0)
            {
                tmp=it++;
                f[0].erase(tmp);
            }
            else ++it;

        for(j=0;j<N;++j)
        {
            bool side= i==0 || i==M-1 || j==0 || j==N-1;
            for(it=f[j].begin(); it!=f[j].end(); ++it)
            {
                status &now=it->second;
                int up=now.pre_suc_a(j);
                int left= j ? now.pre_suc_a(j-1) : 3;
                if(up==3 && left)
                {
                    if(i || j)
                    {
                        k= now.a[i?j:j-1]&1 ? 2 : 1;
                        if(k<1+!side)
                            k+=2;
                        for(; k<=N*M; k+=2)
                            if(L[k]==T[j][i])
                                now.work(j,k);
                    }
                    else for(k=1; k<=N*M; ++k)
                        if(L[k]==T[j][i])
                            now.work(j,k);
                }
                else if(up==3 || left)
                {
                    int mid=now.a[left ? j : j-1];
                    for(k=mid-1; k<=N*M && k<=mid+1; k+=2)
                        if(k>0 && (side || k>1)
                        && L[k]==T[j][i])
                            now.work(j,k);
                }
                else if(abs(now.a[j-1]-now.a[j])==2)
                {
                    k=(now.a[j-1]+now.a[j])>>1;
                    if(L[k]==T[j][i])
                        now.work(j,k);
                }
            }
        }
    }

    int ans=0;
    for(it=f[N].begin(); it!=f[N].end(); ++it)
        inc(ans, it->second.w);
    printf("%d\n",ans);
    return 0;
}
