#include <algorithm>
#include <cstdio>
#include <queue>
#include <utility>

const int N = 2e5 + 100;
using pii = std::pair<int, int>;

int n;
pii p[N];

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
      scanf("%d%d", &p[i].first, &p[i].second);

    std::sort(p + 1, p + n + 1);

    pii tot;
    scanf("%d%d", &tot.first, &tot.second);

    if (tot.second >= tot.first) {
      printf("%d\n", 0);
      continue;
    }

    std::priority_queue<int> q;
    bool fg = 0;
    int idx = n;
    int ans = 0;
    do {
      fg = 1;

      while (idx > 0 && p[idx].first >= tot.first - tot.second) {
        q.push(p[idx].second);
        idx--;
      }

      if (!q.empty()) {
        tot.second += q.top();

        // printf("%d %d\n", q.top(), tot.second);
        q.pop();
        ans++;
      } else {
        fg = 0;
      }

      if (tot.second >= tot.first)
        fg = 0;
    } while (fg);

    if (tot.second >= tot.first)
      printf("%d\n", ans);
    else
      printf("-1\n");
  }

  return 0;
}
