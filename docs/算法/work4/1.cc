
#include <algorithm>
#include <cstdio>

int add(int a, int &n, int val) {
  int d = std::min(a, n);

  n -= d;
  return d * val;
}

int main() {
  int a, b, c;
  int n;

  scanf("%d%d%d%d", &a, &b, &c, &n);

  long long ans = 0;

  ans += add(a, n, 1);
  ans += add(b, n, 0);
  ans += add(c, n, -1);

  printf("%lld\n", ans);

  return 0;
}
