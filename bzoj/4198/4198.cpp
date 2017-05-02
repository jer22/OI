#include <bits/stdc++.h>

using namespace std;

struct Node{
	long long val;
	int tim;
	Node() {}
	Node(long long a, int b) : val(a), tim(b) {}
	bool operator < (const Node &n) const {
		if (val != n.val) return val > n.val;
		return tim > n.tim;
	}
};

int n, k;
int main() {
	freopen("4198.in", "r", stdin);
	priority_queue<Node> q;
	long long a;
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a);
		q.push(Node(a, 1));
	}
	long long ans = 0;
	int cnt = n;  
    if((n - 1)%(k - 1))  
        cnt += k - 1 - (n - 1)%(k - 1);
    for(int i = n+1; i <= cnt; ++i)
        q.push(Node(0, 1));
	while (cnt > 1) {
		long long sum = 0;
		int mx = 0;
		for (int i = 0; i < k; i++) {
			Node cur = q.top();
			q.pop();
			sum += cur.val;
			mx = max(mx, cur.tim);
		}
		ans += sum;
		q.push(Node(sum, mx + 1));
		cnt -= k - 1;
	}
	printf("%lld\n%d\n", ans, q.top().tim - 1);

	return 0;
}
