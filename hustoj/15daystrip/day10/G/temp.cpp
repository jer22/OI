    #include<map>  
    #include<set>  
    #include<cmath>  
    #include<queue>  
    #include<bitset>  
    #include<math.h>  
    #include<vector>  
    #include<string>  
    #include<stdio.h>  
    #include<cstring>  
    #include<iostream>  
    #include<algorithm>  
    #pragma comment(linker, "/STACK:102400000,102400000")  
    using namespace std;  
    const int N=100010;  
    const int mod=100000000;  
    const int MOD1=1000000007;  
    const int MOD2=1000000009;  
    const double EPS=0.00000001;  
    typedef long long ll;  
    const ll MOD=1000000007;  
    const int MAX=1000000010;  
    const ll INF=1ll<<50;  
    const double pi=acos(-1.0);  
    typedef double db;  
    typedef unsigned long long ull;  
    struct node {  
        int x,y;  
    }p[N];  
    int A,B,d[N];  
    ll ans,mi,tmp;  
    bool cmpx(node a,node b) {  
        return a.x<b.x;  
    }  
    bool cmpy(int a,int b) {  
        return p[a].y<p[b].y;  
    }  
    ll dis(node a,node b) {  
        return 1ll*(a.x-b.x)*(a.x-b.x)+1ll*(a.y-b.y)*(a.y-b.y);  
    }  
    void updata(int a,int b) {  
        if ((tmp=dis(p[a],p[b]))<mi) { mi=tmp;A=a;B=b; }  
    }  
    ll closest(int l,int r) {  
        if (l+1==r) { updata(l,r);return dis(p[l],p[r]); }  
        if (l+2==r) {  
            updata(l,r);updata(l,l+1);updata(l+1,r);  
            return min(dis(p[l],p[l+1]),min(dis(p[l],p[l+2]),dis(p[l+1],p[l+2])));  
        }  
        int mid=(l+r)>>1;  
        ll ret=min(closest(l,mid),closest(mid+1,r));  
        int i,j,k=0;  
        for (i=l;i<=r;i++)  
        if (1ll*(p[mid].x-p[i].x)*(p[mid].x-p[i].x)<ret) d[++k]=i;  
        sort(d+1,d+k+1,cmpy);  
        for (i=1;i<=k;i++)  
            for (j=i+1;j<=k;j++) {  
                if (1ll*(p[d[i]].y-p[d[j]].y)*(p[d[i]].y-p[d[j]].y)>=ret) break ;  
                updata(d[i],d[j]);ret=min(ret,dis(p[d[i]],p[d[j]]));  
            }  
        return ret;  
    }  
    int main()  
    {  
        freopen("g.in", "r", stdin);
        int a,b,i,n,t;  
        scanf("%d", &t);  
        while (t--) {  
            scanf("%d", &n);  
            for (i=1;i<=n;i++) scanf("%d%d", &p[i].x, &p[i].y);  
            sort(p+1,p+n+1,cmpx);  
            ans=0;mi=INF;  
            closest(1,n);  
            a=A;b=B;ans=mi*1ll*(n-2);  
            for (i=a;i<n;i++) swap(p[i],p[i+1]);  
            mi=INF;ans+=closest(1,n-1);  
            for (i=n-1;i>=a;i--) swap(p[i],p[i+1]);  
            for (i=b;i<n;i++) swap(p[i],p[i+1]);  
            mi=INF;ans+=closest(1,n-1);  
            printf("%lld\n", ans);  
        }  
        return 0;  
    }  