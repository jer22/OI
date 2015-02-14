#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>

#define N 500005

using namespace std;

long long can[N],qz[N],c[N],s,sum,ans;
int n;

inline void go()
{
    while (~scanf("%d",&n)) {
    	memset(qz, 0, sizeof(qz));
    	sum = 0;
    	ans = 0;
    	s = 0;
    	memset(c, 0, sizeof(c));
	    for(int i=1;i<=n;i++)
	    {
	        scanf("%lld",&can[i]);
	        sum+=can[i];
	    }
	    s=sum/n;
	    for(int i=2;i<=n;i++) c[i]=can[i-1]-s;
	    c[1]=0;
	    for(int i=2;i<=n;i++) c[i]+=c[i-1]; 
	    sort(c+1,c+1+n);
	    s=c[(n+1)>>1];
	    for(int i=1;i<=n;i++) ans+=abs(c[i]-s);
	    printf("%lld\n",ans);
	}
}

int main()
{
	freopen("e.in", "r", stdin);
    go();
    return 0;
}


