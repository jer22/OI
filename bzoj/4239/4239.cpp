#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>


#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

namespace Hash_Set{
    struct List{
        int x,y,val;
        List *next;
        List(int _,int __,List *___):
            x(_),y(__),val(0),next(___) {}
    }*head[3001][3001];
    inline int& Hash(int x,int y)
    {
        int pos1=x%3001;
        int pos2=y%3001;
        List *temp;
        for(temp=head[pos1][pos2];temp;temp=temp->next)
            if(temp->x==x&&temp->y==y)
                return temp->val;
        return (head[pos1][pos2]=new List(x,y,head[pos1][pos2]))->val;
    }
}

const int MAXN = 100005;
const int MAXM = 300005;

int n, m;
// map<pii, int> hash;
int tot = 0;
vector<int> tim[MAXN];
vector<int> edges[MAXM << 1];
pii ref[MAXM << 1];

inline int Hash(int x,int y)
{
    int &val=Hash_Set::Hash(x,y);
    if( !val )
        ref[val=++tot]=make_pair(x,y);
    return val;
}

inline void addEdge(pii a, pii b) {
	// if (hash.find(a) == hash.end()) {
	// 	hash[a] = ++tot;
	// 	ref[tot] = a;
	// }
	// if (hash.find(b) == hash.end()) {
	// 	hash[b] = ++tot;
	// 	ref[tot] = b;
	// }
	edges[Hash(a.first, a.second)].push_back(Hash(b.first, b.second));
}

int lat = -1;
bool vis[MAXM << 1];

queue<int> q;
inline void bfs(int x) {
	q.push(x);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			int nex = edges[cur][i];
			if (vis[nex]) continue;
			vis[nex] = 1;
			q.push(nex);
		}
		if (ref[cur].first == 1) {
			lat = max(lat, ref[cur].second);
		}
	}
}

pii ans[MAXM << 1];
int top = 0;
int main() {
	freopen("4239.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b, c, d;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		tim[a].push_back(c);
		tim[b].push_back(d);
		addEdge(mp(b, d), mp(a, c));
	}
	for (int i = 1; i <= n; i++) {
		sort(tim[i].begin(), tim[i].end());
		for (int j = 1; j < tim[i].size(); j++)
			if (tim[i][j] != tim[i][j - 1])
				addEdge(mp(i, tim[i][j]), mp(i, tim[i][j - 1]));
	}
	for (int i = 0; i < tim[n].size(); i++) {
		int t = Hash(n, tim[n][i]);
		if (vis[t]) continue;
		vis[t] = 1;
		bfs(t);
		ans[++top] = mp(tim[n][i], lat);
	}
	int q;
	scanf("%d", &q);
	ans[0].second = -1;
	while (q--) {
		scanf("%d", &a);
		printf("%d\n",(lower_bound(ans+1,ans+top+1,pair<int,int>(a,0x3f3f3f3f) )-1)->second);
	}


	return 0;
}
