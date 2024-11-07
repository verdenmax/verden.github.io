#include <algorithm>
#include <cstdio>

const int N = 1e5 + 100;
using ll = long long;

int n;
int a[N];

int main() {
  scanf("%d", &n);

  ll ans = 0;
  int mx = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);

    if (a[i] >= a[i - 1]) {
      ans += (mx - a[i - 1]);
      mx = a[i];
    } else
      mx = std::max(a[i], mx);
  }

  ans += mx;

  printf("%lld\n", ans);
  return 0;
}
