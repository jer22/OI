#include<iostream>
#include<cstdio>
#include <cstring>
#include<cmath>
#include<vector>
#include<algorithm>
#include<complex>
const long double pi=3.14159265358979323;
using namespace std;
typedef vector<complex<long double> > pl;
pl a,b,ans;
int n;
long long c[140005];
int ttttt;
long long ret;
void ini()
{
	scanf("%d",&n);
	long long tt;
	ret = 0;
	a.clear();
	b.clear();
	ans.clear();
	memset(c, 0, sizeof(c));
	for(int i=0;i<n;i++) {
		scanf("%lld", &tt);
        a.push_back(tt);
        ret += tt * tt;
	}
	ttttt = n;
	for(int i=0;i<n;i++) {
		scanf("%lld", &tt);
        b.push_back(tt);
        ret += tt * tt;
	}
	reverse(b.begin(), b.end());
	n<<=1;
	int t=0;
	while((1<<t)<n)t++;
	n=(1<<t);
	a.resize(n);b.resize(n);
}
pl getpoint(pl x)
{
	int n=x.size();
	if(n>1)
	{
		pl l,r;
		for(int i=0;i<n;i+=2)
		{
			l.push_back(x[i]);
			r.push_back(x[i+1]);
		}
		complex<long double> wn(cos(2*pi/n),sin(2*pi/n)),w(1,0);
		pl lp(getpoint(l)),rp(getpoint(r));
		for(int i=0;i<n/2;i++)
		{
			x[i]=lp[i]+w*rp[i];
			x[i+n/2]=lp[i]-w*rp[i];
			w*=wn;
		}
	}
	return x;
}
pl getvec(pl x)
{
	int n=x.size();
	if(n>1)
	{
		pl l,r;
		for(int i=0;i<n;i+=2)
		{
			l.push_back(x[i]);
			r.push_back(x[i+1]);
		}
		complex<long double> wn(cos(2*pi*(n-1)/n),sin(2*pi*(n-1)/n)),w(1,0);
		pl lp(getvec(l)),rp(getvec(r));
		for(int i=0;i<n/2;i++)
		{
			x[i]=lp[i]+w*rp[i];
			x[i+n/2]=lp[i]-w*rp[i];
			w*=wn;
		}
	}
	return x;
}
void FFT()
{
	pl pa(getpoint(a)),pb(getpoint(b)),p(n);
	for(int i=0;i!=pa.size();i++)
	    p[i]=pa[i]*pb[i];
    pl ans(getvec(p));
    for(int i=0;i<=n-2;i++)
        c[i]=ans[i].real()/n+0.4;
    long long rrrr = -100000000000000000;
    for(int i=0;i<ttttt;i++)
    	rrrr = max(rrrr, c[i] + c[i + ttttt]);
    cout << ret - rrrr * 2 << endl;
}
int main()
{
	freopen("f.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--) {
		ini();
		FFT();
	}
	return 0;
}