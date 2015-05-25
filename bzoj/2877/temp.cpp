#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N=555555;
int n,m,x,y,t,x1,x2,yyy,y2,opt;
LL d[N<<2],a[N<<2],s[2][N<<2],d1[N],d2[N],p[N<<4],c,ans;
LL gcd(LL a,LL b){
    if (a<0) a=-a; if (b<0) b=-b; LL temp;
    while (b) {temp=b; b=a%b; a=temp;}
    return a;
}
int pos(int x,int y){
    return (x-1)*m+y;
}
int get(int x,int y){
    return (x-1)*((m<<2)+100)+y;
}
void update(int k,int rt,int L,int R,int x,LL c){
    if (L==R) {s[k][rt]=c; return;}
        int m=(L+R)>>1;
    if (x<=m) update(k,rt<<1,L,m,x,c);
    else update(k,rt<<1|1,m+1,R,x,c);
    s[k][rt]=gcd(s[k][rt<<1],s[k][rt<<1|1]);
}
LL query(int k,int rt,int L,int R,int l,int r){
    if (l>r) return 0;
    if (l<=L&&r>=R) return s[k][rt];
    int m=(L+R)>>1; LL temp1=0,temp2=0;
    if (l<=m) temp1=query(k,rt<<1,L,m,l,r);
    if (r>m) temp2=query(k,rt<<1|1,m+1,R,l,r);
    return gcd(temp1,temp2);
}
LL quy(int rx,int ry,int L,int R,int l,int r){
    if (l<=L&&r>=R) return p[get(rx,ry)];
    int m=(L+R)>>1; LL temp1=0,temp2=0;
    if (l<=m) temp1=quy(rx,ry<<1,L,m,l,r);
    if (r>m) temp2=quy(rx,ry<<1|1,m+1,R,l,r);
    return gcd(temp1,temp2);
}
LL qux(int rx,int L,int R,int l1,int r1,int l2,int r2){
    if (l1>r1||l2>r2) return 0;
    if (l1<=L&&r1>=R) return quy(rx,1,1,m,l2,r2);
    int M=(L+R)>>1; LL temp1=0,temp2=0;
    if (l1<=M) temp1=qux(rx<<1,L,M,l1,r1,l2,r2);
    if (r1>M) temp2=qux(rx<<1|1,M+1,R,l1,r1,l2,r2);
    return gcd(temp1,temp2);
}
void upy(int rx,int f,int ry,int L,int R,int y,LL c){
    if (L==R){
        if (f) p[get(rx,ry)]=c;
        else p[get(rx,ry)]=gcd(p[get(rx<<1,ry)],p[get(rx<<1|1,ry)]);
        return;
    }
    int m=(L+R)>>1;
    if (y<=m) upy(rx,f,ry<<1,L,m,y,c);
    else upy(rx,f,ry<<1|1,m+1,R,y,c);
    p[get(rx,ry)]=gcd(p[get(rx,ry<<1)],p[get(rx,ry<<1|1)]);
}
void upx(int rx,int L,int R,int x,int y,LL c){
    if (L==R){upy(rx,1,1,1,m,y,c); return;}
    int M=(L+R)>>1;
    if (x<=M) upx(rx<<1,L,M,x,y,c);
    else upx(rx<<1|1,M+1,R,x,y,c);
    upy(rx,0,1,1,m,y,c);
}
int main(){
    freopen("2877.in", "r", stdin);
    scanf("%d%d%d%d%d",&n,&m,&x,&y,&t);
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
                scanf("%lld",&d[pos(i,j)]);
    for (int i=1; i<n; i++)
        for (int j=1; j<m; j++){
                a[pos(i,j)]=d[pos(i,j)]+d[pos(i+1,j+1)]-d[pos(i,j+1)]-d[pos(i+1,j)];
                upx(1,1,n,i,j,a[pos(i,j)]);
    }
    for (int i=1; i<n; i++){
        d1[i]=d[pos(i+1,y)]-d[pos(i,y)];
        update(1,1,1,n,i,d1[i]);
    }
    for (int i=1; i<m; i++){
        d2[i]=d[pos(x,i+1)]-d[pos(x,i)];
        update(0,1,1,m,i,d2[i]);
    }
    while (t--){
        scanf("%d%d%d%d%d",&opt,&x1,&yyy,&x2,&y2);
        if (!opt){
            ans=gcd(d[pos(x,y)],qux(1,1,n,x-x1,x+x2-1,y-yyy,y+y2-1));
            ans=gcd(ans,query(1,1,1,n,x-x1,x+x2-1));
            ans=gcd(ans,query(0,1,1,m,y-yyy,y+y2-1));
            printf("%lld\n",ans);
        }
        else{
            scanf("%lld",&c);
            if (x1!=1&&yyy!=1) upx(1,1,n,x1-1,yyy-1,a[pos(x1-1,yyy-1)]+=c);
            if (x1!=1&&y2!=m) upx(1,1,n,x1-1,y2,a[pos(x1-1,y2)]-=c);
                if (x2!=n&&yyy!=1) upx(1,1,n,x2,yyy-1,a[pos(x2,yyy-1)]-=c);
            if (x2!=n&&y2!=m) upx(1,1,n,x2,y2,a[pos(x2,y2)]+=c);
            if (yyy<=y&&y2>=y){
                if (x1!=1) update(1,1,1,n,x1-1,d1[x1-1]+=c);
                if (x2!=n) update(1,1,1,n,x2,d1[x2]-=c);
            }
            if (x1<=x&&x2>=x){
                if (yyy!=1) update(0,1,1,m,yyy-1,d2[yyy-1]+=c);
                if (y2!=m) update(0,1,1,m,y2,d2[y2]-=c);
            }
            if (x1<=x&&x2>=x&&yyy<=y&&y2>=y)
                d[pos(x,y)]+=c;
        }
    }
    return 0;
}      