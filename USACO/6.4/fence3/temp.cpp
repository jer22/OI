#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <cmath>
#include <iomanip>
#define V 150
#define sqr(q) ((q)*(q))
#define ex(a,b) ({long c;c=(a);(a)=(b);(b)=c;})
#define ou(x,y,x1,y1) (sqrt(sqr((x)-(x1))+sqr((y)-(y1))))
using namespace std;
struct re{
	long x1,y1,x2,y2;
}l[V];
long n=0;
double dis(double x,double y,long k){
	if(l[k].x1==l[k].x2){
		if(y<l[k].y1)return ou(x,y,l[k].x1,l[k].y1);
		if(y>l[k].y2)return ou(x,y,l[k].x2,l[k].y2);
		return fabs(x-l[k].x1);
	}else{
		if(x<l[k].x1)return ou(x,y,l[k].x1,l[k].y1);
		if(x>l[k].x2)return ou(x,y,l[k].x2,l[k].y2);
		return fabs(y-l[k].y1);
	}
}
int main(int argc,char** argv){
	freopen("fence3.in", "r", stdin);
	srand(size_t(time(NULL)));
	cin >>n;
	double x=rand()%100,y=rand()%100;double t=100;double best=0;
	for(long i=1;i<=n;i++){
		cin >>l[i].x1>>l[i].y1>>l[i].x2>>l[i].y2;
		if(l[i].x1>l[i].x2)ex(l[i].x1,l[i].x2);
		if(l[i].y1>l[i].y2)ex(l[i].y1,l[i].y2);
		best+=dis(x,y,i);
	}
	long d=31;double temp1,temp2;
	while(t>10e-3){
		for(long i=1;i<=500;i++){
			double x1,y1;
				x1=t*(double(rand())/double(RAND_MAX))*(2*(rand()%2)-1);
				y1=sqrt(sqr(t)-sqr(x1))*(2*(rand()%2)-1)+y;
			x1+=x;
			double temp=0;
			for(long k=1;k<=n;k++)temp+=dis(x1,y1,k);
			double p=temp-best,yy=0;
			if(p<0){
				yy=1;
				temp1=x1;temp2=y1;best=temp;
			}else
				yy=exp(-p/t);
			double q=double(rand())/double(RAND_MAX);
			if(q<yy)
				{x=x1;
					y=y1;}
			}
		d++;
		t=t/(log10(d)/log10(20));
		}

	cout<<temp1<<' '<<temp2<<' '<<best<<endl;
	return 0;
}