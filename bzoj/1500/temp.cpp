#include<cstdio>
#include<iostream>
#define N 1000005
#define inf 1000000000
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,sz,rt;
int fa[N],c[N][2],id[N];
int a[N],lmx[N],rmx[N],mx[N],size[N],rec[N],v[N],sum[N];
bool tag[N],rev[N];
void pushup(int k)
{
	int l=c[k][0],r=c[k][1];
	size[k]=size[l]+size[r]+1;
	sum[k]=sum[l]+sum[r]+v[k];
	mx[k]=max(mx[l],mx[r]);
	mx[k]=max(mx[k],rmx[l]+v[k]+lmx[r]);
	lmx[k]=max(lmx[l],sum[l]+v[k]+lmx[r]);
	rmx[k]=max(rmx[r],sum[r]+v[k]+rmx[l]);
}
void pushdown(int k)
{
	int l=c[k][0],r=c[k][1];
	if(tag[k])
	{
		tag[k]=rev[k]=0;
		if(l){tag[l]=1;v[l]=v[k];sum[l]=v[k]*size[l];}
		if(r){tag[r]=1;v[r]=v[k];sum[r]=v[k]*size[r];}
		if(v[k]>=0)
		{
			if(l)lmx[l]=rmx[l]=mx[l]=sum[l];
			if(r)lmx[r]=rmx[r]=mx[r]=sum[r];
		}
		else 
		{
			if(l)lmx[l]=rmx[l]=0,mx[l]=v[k];
			if(r)lmx[r]=rmx[r]=0,mx[r]=v[k];
		}
	}
	if(rev[k])
	{
		rev[k]^=1;rev[l]^=1;rev[r]^=1;
		swap(lmx[l],rmx[l]);swap(lmx[r],rmx[r]);
		swap(c[l][0],c[l][1]);swap(c[r][0],c[r][1]);
		pushup(k);
	}
}
void rotate(int x,int &k)
{
	int y=fa[x],z=fa[y],l,r;
	if(c[y][0]==x)l=0;else l=1;r=l^1;
	if(y==k)k=x;
	else {if(c[z][0]==y)c[z][0]=x;else c[z][1]=x;}
	fa[c[x][r]]=y;fa[y]=x;fa[x]=z;
	c[y][l]=c[x][r];c[x][r]=y;
	pushup(y);pushup(x);
}
void splay(int x,int &k)
{
	while(x!=k)
	{
		int y=fa[x],z=fa[y];
		if(y!=k)
		{
			if(c[y][0]==x^c[z][0]==y)rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
}
void build(int l,int r,int f)
{
	if(l>r)return;
	int now=id[l],last=id[f];
	if(l==r)
	{
		v[now]=mx[now]=sum[now]=a[l];
		fa[now]=last;size[now]=1;
		if(a[l]>=0)lmx[now]=rmx[now]=a[l];
		else lmx[now]=rmx[now]=0;
		if(l<f)c[last][0]=now;
		else c[last][1]=now;
		return;
	}
	int mid=(l+r)>>1;now=id[mid];
	build(l,mid-1,mid);build(mid+1,r,mid);
	v[now]=a[mid];fa[now]=last;pushup(now);
	if(mid<f)c[last][0]=now;
	else c[last][1]=now;
}
int find(int k,int rk)
{
	if(tag[k]||rev[k])pushdown(k);
	int l=c[k][0],r=c[k][1];
	if(size[l]+1==rk)return k;
	else if(size[l]>=rk)return find(l,rk);
	else return find(r,rk-size[l]-1);
}
void reclaim(int k)
{
	if(!k)return;
	int l=c[k][0],r=c[k][1];
	reclaim(l);reclaim(r);
	fa[k]=c[k][0]=c[k][1]=0;
	tag[k]=rev[k]=0;
	rec[++rec[0]]=k;
}
void ins(int k,int tot)
{
	int x,y,z;
	for(int i=1;i<=tot;i++)
	{
		a[i]=read();
		if(rec[0])id[i]=rec[rec[0]--];
		else id[i]=++sz;
	}
	build(1,tot,0);
	z=id[(tot+1)>>1];
	x=find(rt,k+1);y=find(rt,k+2);
	splay(x,rt);splay(y,c[x][1]);
	c[y][0]=z;fa[z]=y;
	pushup(y);pushup(x);
}
void dele(int k,int tot)
{
	int x,y,z;
	x=find(rt,k);y=find(rt,k+tot+1);
	splay(x,rt);splay(y,c[x][1]);
	z=c[y][0];reclaim(z);c[y][0]=0;
	pushup(y);pushup(x);
}
void solve_change(int k,int val)
{
	v[k]=val;tag[k]=1;
	sum[k]=v[k]*size[k];
	if(val>=0)lmx[k]=rmx[k]=mx[k]=sum[k];
	else lmx[k]=rmx[k]=0,mx[k]=v[k];
}
void solve_rever(int k)
{
	if(tag[k])return;
	rev[k]^=1;
	swap(c[k][0],c[k][1]);
	swap(lmx[k],rmx[k]);
}
void change(int k,int tot,int val)
{
	int x,y,z;
	x=find(rt,k);y=find(rt,k+tot+1);
	splay(x,rt);splay(y,c[x][1]);
	z=c[y][0];
	solve_change(z,val);
	pushup(y);pushup(x);
}
void rever(int k,int tot)
{
	int x,y,z;
	x=find(rt,k);y=find(rt,k+tot+1);
	splay(x,rt);splay(y,c[x][1]);
	z=c[y][0];
	solve_rever(z);
	pushup(y);pushup(x);
}
void query(int k,int tot)
{
	int x,y,z;
	x=find(rt,k);y=find(rt,k+tot+1);
	splay(x,rt);splay(y,c[x][1]);
	z=c[y][0];
	printf("%d\n",sum[z]);
}
int main()
{
	freopen("1500.in", "r", stdin);
	n=read();m=read();
	mx[0]=-inf;
	a[1]=a[n+2]=-inf;
	for(int i=1;i<=n;i++)
	    a[i+1]=read();
	for(int i=1;i<=n+2;i++)
		id[i]=i;
	build(1,n+2,0);
	rt=(n+3)>>1;sz=n+2;
	char s[10];
	int k,tot,val;
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s);
		switch(s[0])
		{
		case 'I':k=read();tot=read();ins(k,tot);break;
		case 'D':k=read();tot=read();dele(k,tot);break;
		case 'M':
			if(s[2]=='K')
			{k=read();tot=read();val=read();change(k,tot,val);}
			else printf("%d\n",mx[rt]);
			break;
		case 'R':k=read();tot=read();rever(k,tot);break;
		case 'G':k=read();tot=read();query(k,tot);break;
		}
	}
	return 0;
}