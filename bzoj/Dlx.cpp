#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int a,b,i,j,k,temp;
int U[260001],D[260001],L[260001],R[260001],S[260001],C[260001],H[260001],J[260001],SHU[260001];
int OK[26001];
int vis[350];
int stack[10];
int ans[10][10];
//C是每个节点的列的序号，S是每列1的个数
int n,m,num,head;
void insert(int j,int num) //这个是把上下给链接起来 
{
   int temp;
   temp=j;
   while (D[temp]!=j) temp=D[temp];
   //temp 是该列最底下的那一个
   U[num]=temp; D[temp]=num;
   D[num]=j;    U[j]=num;
   return;
} 

void fuck(int lie,int num)
{
   stack[0]++;
   stack[stack[0]]=num;
   insert(lie,num);
   S[lie]++;
   C[num]=lie;
   if (stack[0]==1) //只有一个点的话
   {
         L[num]=num;
         R[num]=num;
   }
   else
   {
      L[num]=stack[stack[0]-1];
      R[num]=stack[1];
      L[stack[1]]=num;
      R[stack[stack[0]]-1]=num;
   }
}
int suan(int i,int j)
{
   if (i<=3)
   {
      if (j<=3) return 0;
      if (j<=6) return 1;
      if (j<=9) return 2;
   }
   if (i<=6)
   {
      if (j<=3) return 3;
      if (j<=6) return 4;
      if (j<=9) return 5;
   }
   if (i<=9)
   {
      if (j<=3) return 6;
      if (j<=6) return 7;
      if (j<=9) return 8;
   }
}

int initialize() //这个是造十字链表
{
   int a,i,j,k;
   head=0;
   n=9*9*9; //81个格子，每个格子有9种放法 
   m=324;  //(9+9+9)*9+81=324 9行9列9小块
   R[head]=1;
   L[head]=m;  
   for (a=1;a<=m;a++)
   {
      L[a]=a-1;
      R[a]=a+1;
      if (a==m) R[a]=0;
      U[a]=a;
      D[a]=a;
      C[a]=a;
      S[a]=0;
   }
   int hang,lie;
   num=m;
   for (i=1;i<=9;i++)
      for (j=1;j<=9;j++)
         for (k=1;k<=9;k++)
         {
            //第i行j列放了k 
            stack[0]=0;
            //首先是第i行不能有k了
            lie=(i-1)*9+k;
            num++;
            H[num]=i;
            J[num]=j;
            SHU[num]=k;
            fuck(lie,num);
            //然后是第j列不能有k了
            lie=81+(j-1)*9+k;
            num++;
            H[num]=i;
            J[num]=j;
            SHU[num]=k;
            fuck(lie,num);
            //然后是某个方格不能有k了
            lie=81+81+suan(i,j)*9+k;
            num++;
            H[num]=i;
            J[num]=j;
            SHU[num]=k;
            fuck(lie,num);
            //最后是某个方格不能填了
            lie=81+81+81+(i-1)*9+j;
            num++;
            H[num]=i;
            J[num]=j;
            SHU[num]=k;
            fuck(lie,num);
         }
}

void remove(int c) //删除某一列j 
{
   int i,j;
   //if (vis[c]==1) cout<<c<<endl;
   vis[c]=1;
   R[L[c]]=R[c];  //先删除那一列的最前一个 
   L[R[c]]=L[c];
   for (i=D[c];i!=c;i=D[i])
   {
      for (j=R[i];j!=i;j=R[j])
      {
         U[D[j]]=U[j];  //然后再把在那一列里面包含1的行全部都删掉 
         D[U[j]]=D[j];
         S[C[j]]--; //那一列上的1的个数减少1
      }
   }
   return;
} 

void resume(int c)
{
   int i,j;
   for (i=U[c];i!=c;i=U[i])
   {
      for (j=L[i];j!=i;j=L[j])
      {
         S[C[j]]++;
         D[U[j]]=j;
         U[D[j]]=j;
      }
   }
   R[L[c]]=c;
   L[R[c]]=c;
}

bool dfs(int k)
{
   if (head==R[head]) return true; //如果没有了就返回true
   int a,s=10000000,c;
   int i,j;
   for (a=R[head];a!=head;a=R[a])
   {
      if (s>S[a]) {s=S[a]; c=a;}
      if (s==1) break;
   }
   remove(c);
   for (i=D[c];i!=c;i=D[i])
   {
      OK[k]=i;
      ans[H[i]][J[i]]=SHU[i];
      for (j=R[i];j!=i;j=R[j]) remove(C[j]);
      if (dfs(k+1)==true) return true;
      for (j=L[i];j!=i;j=L[j]) resume(C[j]);
   }
   resume(c);
   return false;
}

int main()
{
   int lie;
   char sss;
   while (true)
   {
      memset(C,0,sizeof(C));
      memset(OK,0,sizeof(OK));
      memset(vis,0,sizeof(vis));
      initialize();
      for (int i=1;i<=9;i++)
         for (int j=1;j<=9;j++)
         {
            if (sss=='e') return 0;
            cin>>sss;
            if (sss=='.') continue;
            int k=sss-'0';
            ans[i][j]=k;
            
            lie=(i-1)*9+k;
            remove(lie);
            lie=81+(j-1)*9+k;
            remove(lie);
            lie=81+81+suan(i,j)*9+k;
            remove(lie);
            lie=81+81+81+(i-1)*9+j;
            remove(lie);
         }
         dfs(0);
         for (int i=1;i<=9;i++)
            for (int j=1;j<=9;j++)
            {
               cout<<ans[i][j];
            }
         cout<<endl;
   }}

