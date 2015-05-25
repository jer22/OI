#include <bits/stdc++.h>
using namespace std;
double w[200005]={0},up[100005]={0},down[100005]={0},fa[100005]={0},son[100005]={0},len[25][25]={0};//fa[i],son[i]:i的父/子结点数 
int u[200005]={0},v[200005]={0},first[100005]={0},next[200005]={0};
int hash[100005]={0},cir[25]={0},cirE[25]={0},La[25]={0},Ne[25]={0},vis[25]={0};//cir[i]:环上的点号, cirE[i]:环上的边号, La/NE:前驱/后继
int e=0,flag=0,p=0,pE=0;
void tj(int x,int y,double z)
{
	u[++e]=x;
	v[e]=y;
	w[e]=z;
	next[e]=first[x];
	first[x]=e;
}
void get_cir(int x,int f)
{
	int i;
	hash[x]=1;
	for(i=first[x];i!=0;i=next[i])
		if(v[i]!=f)
		{
			if(hash[v[i]]==1)
			{
				cirE[++pE]=i;
				flag=v[i];
				return;	
			}
			get_cir(v[i],x);
			if(flag>0)
			{
				cirE[++pE]=i;
				if(flag==x) flag=-1;
				return;
			}
			if(flag==-1) break;
		}
	hash[x]=0;
}
void get_L_N(int x,int f)//得到环上结点的前驱后继 
{
	int i;
	if(x==1&&vis[x]==1) return;
	for(i=first[cir[x]];i!=0;i=next[i])
		if(hash[v[i]]!=f&&hash[v[i]]>0&&vis[hash[v[i]]]==0)
		{
			vis[hash[v[i]]]=1;
			Ne[x]=hash[v[i]];
			La[hash[v[i]]]=x;
			get_L_N(hash[v[i]],x);
		}
}
void get_down(int x,int f)
{
	int i;
	for(i=first[x];i!=0;i=next[i])
		if(v[i]!=f&&hash[v[i]]==0)
		{
			fa[v[i]]=1;
			get_down(v[i],x);
			son[x]++;
			down[x]+=down[v[i]]+w[i];
		}
	if(son[x]>0) down[x]/=son[x];
}
void get_up(int x,int f,int fE)
{
	int i;
	up[x]=w[fE];
	if(fa[f]+son[f]>1) up[x]+=(fa[f]*up[f]+son[f]*down[f]-w[fE]-down[x])/(fa[f]+son[f]-1);
	for(i=first[x];i!=0;i=next[i])
		if(v[i]!=f) get_up(v[i],x,i);
}
int main()
{
	freopen("2878.in", "r", stdin);
	double z,P,ans=0;
	int n,m,i,j,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%lf",&x,&y,&z);
		tj(x,y,z);
		tj(y,x,z);
	}
	get_cir(1,0);
	if(m<n)//无环 
	{
		get_down(1,0);
		for(i=first[1];i!=0;i=next[i])
			get_up(v[i],1,i);
	}
	else//有环 
	{
		for(i=1;i<=n;i++)
			if(hash[i]>0)
			{
				cir[++p]=i;//注意：环上相邻的点编号不一定相邻，在环上的序号也不一定相邻 
				hash[i]=p;//结点i在环上的序号 
				fa[i]=2;
			}
		for(i=1;i<=pE;i++)
			len[hash[ u[cirE[i]] ]][hash[ v[cirE[i]] ]]=len[hash[ v[cirE[i]] ]][hash[ u[cirE[i]] ]]=w[cirE[i]];
		get_L_N(1,0);
		for(i=1;i<=p;i++)
			get_down(cir[i],0);
		for(i=1;i<=p;i++)
		{
			for(P=1,j=Ne[i];j!=i;j=Ne[j])//往后找 
			{
				if(Ne[j]!=i) up[cir[i]]+=P*(len[La[j]][j]+down[cir[j]]*son[cir[j]]/(son[cir[j]]+1));
				else up[cir[i]]+=P*(len[La[j]][j]+down[cir[j]]);
				P/=(son[cir[j]]+1);
			}
			for(P=1,j=La[i];j!=i;j=La[j])//往前找 
			{
				z=up[cir[i]];
				if(La[j]!=i) up[cir[i]]+=P*(len[Ne[j]][j]+down[cir[j]]*son[cir[j]]/(son[cir[j]]+1));
				else up[cir[i]]+=P*(len[Ne[j]][j]+down[cir[j]]);
				P/=(son[cir[j]]+1);
			}
			up[cir[i]]/=2;
		}
		for(i=1;i<=p;i++)
			for(j=first[cir[i]];j!=0;j=next[j])
				if(hash[v[j]]==0) get_up(v[j],cir[i],j);
	}
	for(i=1;i<=n;i++) {
		cout << up[i] << ' ' << down[i] << endl;
		ans+=(up[i]*fa[i]+down[i]*son[i])/(fa[i]+son[i]);
	}
	printf("%.5lf",ans/(double)n);
	return 0;
}