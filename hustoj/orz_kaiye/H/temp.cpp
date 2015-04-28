#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
using namespace std;
int n,a[10005],b[10005],t1,t2,k,ans;
int main(void)
{
freopen("h.in", "r", stdin);
while(~scanf("%d",&n))
{
memset(b,0,sizeof(b));
ans=0;
for(int i=n;i>=0;i--)
{
if(b[i])continue;
t1=0,t2=i,k=0;
while(t2)
{
if(!(t2 & 1))
t1|=(1<<k);
t2>>=1;
k++;
}
b[t1]=1;
a[i]=t1;
a[t1]=i;
ans+=2*(i^t1);
}
printf("%d\n",ans);
for(int i=0;i<=n;i++)
{
scanf("%d",&k);
printf("%d",a[k]);
if(i!=n)printf(" ");
else printf("\n");
}
}
return 0;
}