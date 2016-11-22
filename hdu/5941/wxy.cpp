#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define sc second

typedef pair <double,double> pdd;

const int MAXN=2005;

int a[MAXN];
pdd p[MAXN];
vector <pdd> v[MAXN];

void solve()
{
	int n;
	scanf("%d",&n);
	if (n==1)
	{
		puts("0.00000");
		return;
	}
	for (int i=2;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
	{
		double b=1,c=0,d=1;
		int cnt=0;
		for (int j=i-1;j>=1;j--)
		{
			d=a[j+1]/d;
			if (i-j&1) c+=d;
			else b+=d;
			double t=sqrt(c/b);
			double t2=a[j]/((i-j&1)?d/t:d*t);
			vector <pdd> :: iterator it=lower_bound(v[j-1].begin(),v[j-1].end(),mp(t2,0.));
			if (it!=v[j-1].end())
				p[cnt++]=mp(t,b*t+c/t+it->sc);
		}
		sort(p,p+cnt);
		v[i].clear();
		for (int j=0;j<cnt;j++)
		{
			while (!v[i].empty()&&v[i].back().sc>=p[j].sc)
				v[i].pop_back();
			v[i].pb(p[j]);
		} 
	}
	// cout << v[4][0].fi << endl;
	printf("%.5f\n",v[n][0].sc);
}

int main()
{
	freopen("5941.in", "r", stdin);
	v[0].pb(mp(0.,0.));
	int T;
	scanf("%d",&T);
	for (int i=1;i<=T;i++)
	{
		printf("Case #%d: ",i);
		solve();
	}
	return 0;
}