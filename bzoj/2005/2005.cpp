#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int MAXN = 100005;

int n, m;

bool notprime[MAXN];
int primes[MAXN], tot;
void initPrime() {
	for (int i = 2; i <= 100000; i++) {
		if (notprime[i]) continue;
		for (int j = i + i; j <= 100000; j += i)
			notprime[j] = 1;
	}
	for (int i = 2; i <= 100000; i++)
		if (!notprime[i]) primes[tot++] = i;
}

vector<int> divide(int num) {
	vector<int> division;
	int i = 0;
	while (num != 1) {
		int base = primes[i];
		if (!(num % base)) {
			while (!(num % base)) num /= base;
			division.push_back(base);
		}
		i++;
	}
	return division;
}

vector<int> getFact(int num) {
	vector<int> facts;
	int k = sqrt(num);
	if (k * k == num) {
		facts.push_back(k);
		k--;
	}
	for (int i = 1; i <= k; i++) {
		if (!(num % i)) {
			facts.push_back(i);
			facts.push_back(num / i);
		}
	}
	return facts;
}

long long getsum(vector<int> divis, int t) {
	int siz = divis.size();
	long long sum = m / t;
	for (int i = 0; i < siz; i++) {
		int a = t * divis[i];
		sum -= m / a;
		for (int j = i + 1; j < siz; j++) {
			int b = a * divis[j];
			sum += m / b;
			for (int k = j + 1; k < siz; k++) {
				int c = b * divis[k];
				sum -= m / c;
				for (int l = k + 1; l < siz; l++) {
					int d = c * divis[l];
					sum += m / d;
					for (int p = l + 1; p < siz; p++) {
						int e = d * divis[p];
						sum -= m / e;
						for (int q = p + 1; q < siz; q++) {
							int f = e * divis[q];
							sum += m / f;
						}
					}
				}
			}
		}
	}
	return sum;
}

int main() {
	freopen("2005.in", "r", stdin);
	initPrime();
	scanf("%d %d", &n, &m);
	if (n > m) swap(n, m);
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		vector<int> facts = getFact(i);
		for (vector<int>::iterator it = facts.begin(); it != facts.end(); it++) {
			vector<int> divis = divide(i / (*it));
			long long sum = getsum(divis, *it);
			ans += (((*it) - 1) * 2 + 1) * sum;
		}
	}
	cout << ans << endl;
	return 0;
}
