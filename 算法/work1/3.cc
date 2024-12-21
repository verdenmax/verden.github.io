#include <cmath>
#include <cstring>
#include <map>
#include <stdio.h>

using namespace std;

using ll = long long;

int a[100];

void work(int n, int a[], map<ll, int> &mp, map<ll, int> &mcnt) {
  for (int x = 0; x < (1 << n); x++) {
    ll tot = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      if (x >> i & 1) {
        tot += a[i];
        cnt++;
      }
    }

    if (mp[tot]) {
      if (mcnt[tot] == cnt)
        mcnt[tot] = cnt;
      else
        mcnt[tot] = -1;
    } else
      mcnt[tot] = cnt;

    mp[tot]++;
  }
}

int main() {
  int t;
  int case_id = 1;
  scanf("%d", &t);
  while (t--) {
    int n;
    ll d;
    scanf("%d%lld", &n, &d);

    // 记录当期值出现几次
    map<ll, int> ml, mr;
    // 记录物品数量
    map<ll, int> lcnt, rcnt;
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    int mid = n / 2;

    // [0,mid)
    work(mid, a, ml, lcnt);
    // [mid,n)
    work(n - mid, a + mid, mr, rcnt);

    int ans = 0;
    int cnt = 0;

    for (auto [a, ci] : ml) {
      if (!mr[d - a])
        continue;

      // printf("%lld %lld\n", a, d - a);
      ans += ci * mr[d - a];

      if (lcnt[a] == -1 || rcnt[d - a] == -1)
        cnt = -1;
      else if (cnt == 0) {
        cnt = lcnt[a] + rcnt[d - a];
      } else if (cnt != lcnt[a] + rcnt[d - a])
        cnt = -1;
    }

    printf("Case #%d: ", case_id);

    if (ans == 0)
      printf("IMPOSSIBLE\n");
    else if (cnt != -1)
      printf("%d\n", cnt);
    else
      printf("AMBIGIOUS\n");
    case_id++;
  }

  return 0;
}
