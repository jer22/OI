#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define MAXN 100005
#define INF 0x3f3f3f3f
#define lc tr[rt][0]
#define rc tr[rt][1]

using namespace std;

struct Node{
	int v, pos;
}arr[MAXN];

bool cmp1(Node a, Node b) {
	if (a.v != b.v) return a.v < b.v;
	return a.pos < b.pos;
}
bool cmp2(Node a, Node b) {
	return a.pos < b.pos;
}

int n, sz, root;
int siz[MAXN], fa[MAXN], tr[MAXN][2];
int v[MAXN], mi[MAXN], pos[MAXN];
bool rev[MAXN];
int s[MAXN], top;

void pushup(int x)
{
	int l=tr[x][0],r=tr[x][1];
	mi[x]=v[x];pos[x]=x;
	if(mi[l]<mi[x]){mi[x]=mi[l];pos[x]=pos[l];}
	if(mi[r]<mi[x]){mi[x]=mi[r];pos[x]=pos[r];}
	siz[x]=siz[l]+siz[r]+1;
}
void pushdown(int x)
{
    int l=tr[x][0],r=tr[x][1];
	rev[x]^=1;rev[l]^=1;rev[r]^=1;
	swap(tr[x][0],tr[x][1]);
}
void rotate(int x,int &k)
{
    int y=fa[x],z=fa[y],l,r;
    if(tr[y][0]==x)l=0;else l=1;r=l^1;
    if(y==k)k=x;
    else {if(tr[z][0]==y)tr[z][0]=x;else tr[z][1]=x;}
    fa[x]=z;fa[y]=x;fa[tr[x][r]]=y;
    tr[y][l]=tr[x][r];tr[x][r]=y;
    pushup(y);pushup(x);
}
void splay(int x,int &k)
{
	top=0;s[++top]=x;
    for(int i=x;fa[i];i=fa[i])
        s[++top]=fa[i];
    for(int i=top;i;i--)
        if(rev[s[i]])pushdown(s[i]);
    while(x!=k)
    {
        int y=fa[x],z=fa[y];
        if(y!=k)
        {    
            if(tr[y][0]==x^tr[z][0]==y)
                rotate(x,k);
            else rotate(y,k);
        }
        rotate(x,k);
    }
}
int find(int x,int rk)
{
	if(rev[x])pushdown(x);
	int l=tr[x][0],r=tr[x][1];
	if(siz[l]+1==rk)return x;
	else if(siz[l]>=rk)return find(l,rk);
	else return find(r,rk-siz[l]-1);
}
int query(int L,int R)
{
	int x=find(root,L),y=find(root,R+2);
	splay(x,root);splay(y,tr[x][1]);
	int z=tr[y][0];
	return pos[z];
}
void reverse(int L,int R)
{
	int x=find(root,L),y=find(root,R+2);
	splay(x,root);splay(y,tr[x][1]);
	int z=tr[y][0];
	rev[z]^=1;
}
void build(int l,int r,int f)
{
	if(l>r)return;
	if(l==r)
	{
		fa[l]=f;siz[l]=1;
		mi[l]=v[l]=arr[l].v;pos[l]=l;
		if(l<f)tr[f][0]=l;
		else tr[f][1]=l;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid-1,mid);build(mid+1,r,mid);
	fa[mid]=f;v[mid]=arr[mid].v;pushup(mid);
	if(mid<f)tr[f][0]=mid;
	else tr[f][1]=mid;
}
int main() {
	freopen("1552.in", "r", stdin);
	scanf("%d", &n);
	arr[1].v = arr[n + 2].v = mi[0] = INF;
	for (int i = 2; i <= n + 1; i++) {
		scanf("%d", &arr[i].v);
		arr[i].pos = i;
	}
	sort(arr + 2, arr + n + 2, cmp1);
	for (int i = 2; i <= n + 1; i++) arr[i].v = i - 1;
	sort(arr + 2, arr + n + 2, cmp2);
	build(1, n + 2, 0);
	root = n + 3 >> 1;
	for (int i = 1; i <= n; i++) {
		int x = query(i, n);
		splay(x, root);
		int ans = siz[tr[x][0]];
		cout << ans << " \n"[i == n];
		reverse(i, ans);
	}


	return 0;
}
