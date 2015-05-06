#include<cstdio>  
#include<cstring>  
#include<cstdlib>  
#include<algorithm>  
#include<functional>  
#include<iostream>  
#include<cmath>  
#include<cctype>  
#include<ctime>  
using namespace std;  
#define For(i,n) for(int i=1;i<=n;i++)  
#define Fork(i,k,n) for(int i=k;i<=n;i++)  
#define Rep(i,n) for(int i=0;i<n;i++)  
#define ForD(i,n) for(int i=n;i;i--)  
#define RepD(i,n) for(int i=n;i>=0;i--)  
#define Forp(x) for(int p=pre[x];p;p=next[p])  
#define Lson (x<<1)  
#define Rson ((x<<1)+1)  
#define MEM(a) memset(a,0,sizeof(a));  
#define MEMI(a) memset(a,127,sizeof(a));  
#define MEMi(a) memset(a,128,sizeof(a));  
#define INF (2139062143)  
#define F (1000000007)  
#define MAXN (1000000+10)  
long long mul(long long a,long long b){return (a*b)%F;}  
long long add(long long a,long long b){return (a+b)%F;}  
long long sub(long long a,long long b){return (a-b+(a-b)/F*F+F)%F;}  
typedef long long ll;  
ll a,b,c,d,n,m,phiF;  
ll getint(char s[]) //_dec_1  
{  
    char c;  
    ll x=0;  
    for(int i=0,c=s[i];s[i];c=s[++i])  
    {  
        x=(x*10+c-48)%phiF;  
    }  
    x=(x-1+phiF)%phiF;  
    return x;  
}  
struct M  
{  
    int n,m;  
    ll a[3][3];  
    M(){n=m=2;MEM(a);}  
    M(ll a1,ll a2,ll b1,ll b2){n=m=2;MEM(a) a[1][1]=a1,a[1][2]=a2,a[2][1]=b1,a[2][2]=b2;    }  
    friend M operator*(M a,M b)  
    {  
        M c;  
        For(k,2)  
            For(i,2)  
                For(j,2)  
                    c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j])%F;  
    /* 
    For(i,2) 
    { 
        For(j,2) cout<<c.a[i][j]<<' ';cout<<endl; 
    }*/  
        return c;     
    }  
    void make_I()  
    {  
        n=m=2;MEM(a)  
        For(i,n) a[i][i]=1;  
    }  
}A,B,C,D,I;  
void print(M a)  
{  
    For(i,2)  
    {  
        For(j,2) cout<<a.a[i][j]<<' ';cout<<endl;  
    }  
}  
M pow2(M a,ll b)  
{  
    M c=I;  
    static bool a2[MAXN];  
    int n=0;while (b) a2[++n]=b&1,b>>=1;  
    For(i,n)  
    {  
        if (a2[i]) c=c*a;  
        a=a*a;  
    }  
    return c;  
}  
char s1[MAXN],s2[MAXN];  
int main()  
{  
    freopen("3240.in", "r", stdin);
    scanf("%s%s",s1,s2);  
    scanf("%lld%lld%lld%lld",&a,&b,&c,&d);  
    if (a==1) phiF=F;else phiF=F-1;  
    n=getint(s1);
	if (c==1) phiF=F;else phiF=F-1;  
    m=getint(s2);  
    A=M(a,b,0,1);B=M(c,d,0,1);I=M(1,0,0,1);  
    C=pow2(A,m);//print(C);  
    D=B*C;//print(D);  
    D=pow2(D,n);  
    D=C*D;//print(D);  
    cout<<(D.a[1][2]+D.a[1][1])%F<<endl;  
      
    return 0;  
}