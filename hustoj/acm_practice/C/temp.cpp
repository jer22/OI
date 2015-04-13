#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#define eps 1e-8

using namespace std;

int t;
int x,y;
struct nod{
	int vx,vy;
	int x,y;
}node[2];
nod cal(nod now,int tim)
{
	now.x+=tim*now.vx;
	now.y+=tim*now.vy;
	// if ((now.x==0 && now.y==0) || (now.x==0 && now.y==y)
	// 	|| (now.x==x && now.y==0) || (now.x==x && now.y==y))
	// {
	// 	now.vx*=-1;
	// 	now.vy*=-1;
	// 	return now;
	// }
	int f1=1,f2=1;
	if (now.x==0 || now.x==x)
	{
		if ((now.x==0 && now.vx<0) || (now.x==x && now.vx>0))
			f1=-1;
		//return now;
	}
	if (now.y==0 || now.y==y)
	{		
		if ((now.y==0 && now.vy<0) || (now.y==y && now.vy>0))
			f2=-1;
		//return now;
	}
	//cout<<now.x<<' '<<now.y<<' '<<now.vx<<' '<<now.vy<<endl;
	now.vx*=f1;
	now.vy*=f2;
	//cout<<now.x<<' '<<now.y<<' '<<now.vx<<' '<<now.vy<<endl;
	return now;
}
int main()
{
	freopen("c.in", "r", stdin);
	cin>>t;
	for (int cas=1;cas<=t;cas++)
	{
		int flag=0;
		cin>>x>>y;
		cin>>node[0].x>>node[0].y>>node[1].x>>node[1].y;
		cout<<"Case #"<<cas<<":"<<endl;
		node[0].vx=1; node[0].vy=1;
		node[1].vx=1; node[1].vy=1;
		int x1,x2,y1,y2,vx1,vx2,vy1,vy2;
		for (int i=1;i<=1000000;i++)
		{
			x1=node[0].x;
			x2=node[1].x;
			y1=node[0].y;
			y2=node[1].y;
			vx1=node[0].vx;
			vx2=node[1].vx;
			vy1=node[0].vy;
			vy2=node[1].vy;
			// if (i<=36)
   //          	cout<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<endl;
			// {
			// }
            // getchar();
			int tim=100005;
			for (int j=0;j<=1;j++)
			{
				if (node[j].vx<0) tim=min(tim,node[j].x);
				else tim=min(tim,x-node[j].x);
				if (node[j].vy<0) tim=min(tim,node[j].y);
				else tim=min(tim,y-node[j].y);
			}
			//x y vx vy x2 y2 
			double k1,k2;
			k1=(node[0].vy+0.0)/node[0].vx;
			k2=(node[1].vy+0.0)/node[1].vx;
			if (fabs(k1-k2)<eps) //速度平行，还是有可能相遇的，那么肯定是要在同一个点出发的
			{
				double crx,cry;
				crx=(x1+x2)/2.0;
				cry=(y1+y2)/2.0;
				double tt1,tt2,tt3,tt4;
				tt1=(crx-x1)/vx1;
				tt2=(crx-x2)/vx2;
				tt3=(cry-y1)/vy1;
				tt4=(cry-y2)/vy2;
				// cout<<crx<<' '<<cry<<endl;
				// cout<<tt1<<' '<<tt2<<endl;
				if (tt1>=0 && tt2>=0 && crx>=0 && cry>=0 && fabs(tt1-tt2)<eps  && fabs(tt2-tt3)<eps  && fabs(tt3-tt4)<eps)
				if (crx<=x && cry<=y)
				{
					flag=1;
					printf("%.1lf %.1lf\n",crx,cry);
					break;
				}
				//cout<<x1<<' '<<y1<<' '<<vx1<<' '<<vy1<<endl;
				//cout<<x2<<' '<<y2<<' '<<vx2<<' '<<vy2<<endl;
				node[0]=cal(node[0],tim);
				node[1]=cal(node[1],tim);
				continue;
			}
			double b1,b2;
			b1=y1-k1*x1;
			b2=y2-k2*x2;

			double cha=b2-b1;
			double kk=k1-k2;
			double crx,cry;
			crx=cha/kk;
			double tt1,tt2;
			tt1=(crx-x1)/vx1;
			tt2=(crx-x2)/vx2;
			cry=y1+tt1*vy1;
			if (tt1>=0 && tt2>=0 && crx>=0 && cry>=0 && fabs(tt1-tt2)<eps)
			if (crx<=x && cry<=y)
			{	
				printf("%.1lf %.1lf\n",crx,cry);
				flag=1;
				break;
			}
			node[0]=cal(node[0],tim);
			node[1]=cal(node[1],tim);
		}
		if (flag==0)
		{
			printf("Collision will not happen.\n");
		}
	}
}