#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define MAXN 210

using namespace std;

struct Floor{
	int value;
	int step;
};

int n;
int a, b;
Floor arr[MAXN];
int done[MAXN];
queue<int> q;

int bfs(int start) {
	
	q.push(start);
	while (!q.empty()) {
		int now = q.front();
		
		if (now == b) {
			return arr[now].step;
		}
		if (now - arr[now].value > 0 && !done[now - arr[now].value]) {
			arr[now - arr[now].value].step = arr[now].step + 1;
			q.push(now - arr[now].value);
			done[now - arr[now].value] = 1;
		}
		if (now + arr[now].value <= n && !done[now + arr[now].value]) {
			arr[now + arr[now].value].step = arr[now].step + 1;
			q.push(now + arr[now].value);
			done[now + arr[now].value] = 1;
		}
		q.pop();
	}
	return -1;
}

int main() {
	freopen("1135.in", "r", stdin);
	scanf("%d %d %d", &n, &a, &b);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i].value);
	}
	arr[a].step = 0;
	done[a] = 1;
	printf("%d\n", bfs(a));;

	return 0;
}
