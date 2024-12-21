#include <cmath>
#include <cstring>
#include <map>
#include <stdio.h>

using namespace std;

const int N = 2e5 + 100;

int n;
int h[N], e[N], ne[N], idx;
int d[N]; // 统计度
int dep[N];

void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }

int calc(int u, int fa, int depth) {
  if (d[u] == 1) {
    dep[u] = 0;
    return 1;
  }

  dep[u] = N;
  int totans = 0;
  for (int i = h[u]; ~i; i = ne[i]) {

    int j = e[i];

    if (j == fa)
      continue;

    totans += calc(j, u, depth + 1);
    dep[u] = min(dep[u], dep[j] + 1);
  }

  if (dep[u] <= depth)
    return 1;
  return totans;
}

int main() {
  memset(h, -1, sizeof h);

  // scanf("%d", &n);
  n = 70000;

  for (int i = 1; i <= n - 1; i++) {
    int a, b;
    // scanf("%d%d", &a, &b);
    a = i, b = i + 1;

    d[a]++, d[b]++;
    add(a, b), add(b, a);
  }

  // 对于每一个点做一次
  for (int i = 1; i <= n; i++) {
    calc(i, -1, 0);
    // printf("%d\n", calc(i, -1, 0));
  }
  return 0;
}
