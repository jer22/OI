#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_DIM 5000

vector<pair<int, int> > fin[MAX_DIM][MAX_DIM];
int vals[MAX_DIM][MAX_DIM];

int last_one(int x) { return x&(x^(x-1)); }

void add(int x, int y, int c, int time) {
  for (int i = x; i < MAX_DIM; i+=last_one(i)) {
    for (int j = y; j < MAX_DIM; j+=last_one(j)) {
      if (fin[i][j].size()==0)
        fin[i][j].push_back(make_pair(time, c));
      else
        fin[i][j].push_back(make_pair(time, fin[i][j].back().second+c));
    }
  }
}

int get(int x, int y, int time) {
  int ret = 0;
  for (int i = x; i > 0; i-=last_one(i)) {
    for (int j = y; j > 0; j-=last_one(j)) {
      vector<pair<int, int> >::iterator it = lower_bound(fin[i][j].begin(), fin[i][j].end(), make_pair(time+1,(int)0));
      if (it != fin[i][j].begin()) {
        it--;
        ret += it->second;
      }
    }
  }
  return ret;
}

// Add count
int tt = 0;

class Op {
 public:
  virtual int Do(int C)=0;
  virtual void Load()=0;
};

int XM(int x, int C) {
  return (x^C) % 4096;
}

class Add : public Op {
 public:
  virtual int Do(int C) {
    int X = XM(x,C)+3;
    int Y = XM(y,C)+3;
    add(X,Y,a,++tt);
    vals[X][Y]+=a;
    return vals[X][Y];
  }

  virtual void Load() {
    scanf("%d %d %d", &x, &y, &a);
  }

  int x, y, a;
};

class GetSum : public Op {
 public:
  virtual int Do(int C) {
    int X1 = XM(x1,C)+3;
    int X2 = XM(x2,C)+3;
    int Y1 = XM(y1,C)+3;
    int Y2 = XM(y2,C)+3;
    int L = min(X1, X2), R = max(X1, X2);
    int D = min(Y1, Y2), U = max(Y1, Y2);
    int T;
    if (t == 0) T = tt;
    if (t > 0)  T = t;
    if (t < 0) { T = tt+t; if (T < 0) T = 0; }
    int res = get(R,U,T)+get(L-1,D-1,T)-get(L-1,U,T)-get(R,D-1,T);
    printf("%d\n", res);
    return res;
  }

  virtual void Load() {
    scanf("%d %d %d %d %d", &x1, &x2, &y1, &y2, &t);
  }

  int x1, x2, y1, y2, t;
};

int main() {
    freopen("g.in", "r", stdin);
  freopen("t.out", "w", stdout);
  int r, q;
  scanf("%d\n", &r);
  scanf("%d\n", &q);
  vector<Op*> ops;
  for (int i = 0; i < q; i++) {
    int a; scanf("%d", &a);
    if (a==1) {
      Op *o = new Add;
      o->Load();
      ops.push_back(o);
    }
    if (a==2) {
      Op *o = new GetSum;
      o->Load();
      ops.push_back(o);
    }
  }
  int C = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < q; j++) {
      C = ops[j]->Do(C);
    }
  }
}
