#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int T;
int n, m;
char name[105][25];

struct Node{
	int id;
	double r1, r2;
	double s1, s2;
	Node() {}
	Node(int a, double b, double c) : id(a), r1(b), r2(c) {}
	bool operator < (const Node &n) const {
		return s1 * 0.3 + s2 * 0.7 > n.s1 * 0.3 + n.s2 * 0.7;
	}
};

vector<Node> arr, brr;

int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		printf("The member list of Shandong team is as follows:\n");
		memset(name, 0, sizeof(name));
		arr.clear();
		brr.clear();
		scanf("%d %d", &n, &m);
		char sex[10];
		bool flag = false;
		double a, b;
		double maxa = 0, maxb = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%s", name[i]);
			scanf("%s", sex);
			scanf("%lf %lf", &a, &b);
			if (sex[0] == 'f') {
				flag = true;
				brr.push_back(Node(i, a, b));
			} else arr.push_back(Node(i, a, b));
			maxa = max(maxa, a);
			maxb = max(maxb, b);
		}
		for (int i = 0; i < arr.size(); i++) {
			arr[i].s1 = arr[i].r1 * (300 / maxa);
			arr[i].s2 = arr[i].r2 * (300 / maxb);
		}
		for (int i = 0; i < brr.size(); i++) {
			brr[i].s1 = brr[i].r1 * (300 / maxa);
			brr[i].s2 = brr[i].r2 * (300 / maxb);
		}
		sort(brr.begin(), brr.end());
		Node temp = brr[0];
		for (int i = 0; i < brr.size(); i++) {
			if (brr[i].id != temp.id) arr.push_back(brr[i]);
		}
		sort(arr.begin(), arr.end());
		if (flag) {
			m--;
			for (int i = 0; i < m; i++) {
				if (temp < arr[i] && flag) {
					printf("%s\n", name[temp.id]);
					flag = false;
				}
				printf("%s\n", name[arr[i].id]);
			}
			if (flag && m > -1) printf("%s\n", name[temp.id]);
		} else {
			for (int i = 0; i < m; i++) {
				printf("%s\n", name[arr[i].id]);
			}
		}

		
	}

	return 0;
}
