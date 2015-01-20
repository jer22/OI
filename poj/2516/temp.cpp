//最小权匹配(KM算法)
//构图是关键，又是拆点这个思想。因为商品数量很少，最多才3，所以将一个商品拆成3个点
//一开始我将K种商品全部拆出来，想一次KM解决，结果构出来的图最坏情况是50*50*3 和50*50*3 的二部图来匹配最优权值
//在经过O(n^3)的KM + 多组数据，结果毫无疑问的TLE了
//此题的关键是将K种商品独立出来求解，因为K种商品相互无影响
//将他们独立出来分别进行K次KM算法，大大降低了时间和空间
//50*3和50*3的二部图最小权匹配
//复杂度是O(K*(N^3))，效率就好很多了
//另外一点是，提前判断库存是否能满足需要，如果不能满足就直接输出-1，无需匹配了
#include<iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 1000000000;
const int MAX = 151;
int N,M,K,ans;
int need[51][51],have[51][51],cost[51][51][51],A[MAX],B[MAX];
bool vis_x[MAX],vis_y[MAX];
int lx[MAX],ly[MAX];//可行顶标
int xMatch[MAX],yMatch[MAX];//匹配记录
int W[MAX][MAX];//边权值
int X,Y,slack;//左部图X,右部图Y,slack松弛值
//O(N^3)的KM算法，带slack优化
bool findPath(int x)
{
	vis_x[x] = 1;
	for(int y = 1;y <= Y;++y)
	{
		if(vis_y[y])	continue;
		int temp = W[x][y] - lx[x] - ly[y];
		if(temp == 0)
		{
			vis_y[y] = 1;
			if(!yMatch[y] || findPath(yMatch[y]))
			{
				xMatch[x] = y;//记录匹配状态，xMatch可省略
				yMatch[y] = x;
				return true;
			}
		}
		else if(temp < slack)	slack = temp;//更新松弛值
	}
	return false;
}
//此模板为最小权匹配，传递正权值即可
//若要改为最大权匹配，需要修改的参数见注释
void KM()
{
	memset(ly,0,sizeof(ly));
	memset(yMatch,0,sizeof(yMatch));
	for(int x = 1;x <= X;++x)
	{
		lx[x] = INF;//lx[x] = -INF;
		for(int y = 1;y <= Y;++y)
			if(lx[x] > W[x][y])//lx[x] < W[x][y]
				lx[x] = W[x][y];
	}
	for(int x = 1;x <= X;++x)
	{
		while(1)
		{
			memset(vis_x,0,sizeof(vis_x));
			memset(vis_y,0,sizeof(vis_y));
			slack = INF;
			if(findPath(x))	break;
			for(int x = 1;x <= X;++x)
				if(vis_x[x])	lx[x] += slack;//lx[x] -= slack;
			for(int y = 1;y <= Y;++y)
				if(vis_y[y])	ly[y] -= slack;//ly[y] += slack;
		}
	}
}
int main()
{
	freopen("2516.in","r",stdin);
	while(scanf("%d%d%d",&N,&M,&K) && N)
	{
		for(int i = 1;i <= N;++i)
			for(int j = 1;j <= K;++j)
				scanf("%d",&need[i][j]);
		for(int i = 1;i <= M;++i)
			for(int j = 1;j <= K;++j)
				scanf("%d",&have[i][j]);
		for(int k = 1;k <= K;++k)
			for(int i = 1;i <= N;++i)
				for(int j = 1;j <= M;++j)
					scanf("%d",&cost[k][i][j]);
		bool ok = 1;
		for(int i = 1;i <= K;++i)
		{
			int allNeed = 0,allHave = 0;
			for(int j = 1;j <= N;++j)
				allNeed += need[j][i];
			for(int j = 1;j <= M;++j)
				allHave += have[j][i];
			if(allNeed > allHave)//如果库存小于需求，直接返回-1
			{
				ok = 0;
				printf("-1/n");
				break;
			}
		}
		if(!ok)	continue;
		ans = 0;
		for(int k = 1;k <= K;++k)//关在在于拆点，将每种货物做一次KM
		{
			X = 0,Y = 0;
			for(int i = 1;i <= N;++i)
				for(int j = 1;j <= need[i][k];++j)
					A[++X] = i;
			for(int i = 1;i <= M;++i)
				for(int j = 1;j <= have[i][k];++j)
					B[++Y] = i;
			for(int i = 1;i <= X;++i) {
				for(int j = 1;j <= Y;++j) {
					W[i][j] = cost[k][A[i]][B[j]];
					cout << W[i][j] << ' ';
				}
				cout << endl;
			}
			KM();
			for(int x = 1;x <= X;++x)
				ans += W[x][xMatch[x]];
		}
		printf("%d\n",ans);
	}
	return 0;
}