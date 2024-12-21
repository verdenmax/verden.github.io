#include <algorithm>
#include <cmath>
#include <cstring>
#include <stdio.h>
#include <vector>

using namespace std;

const int N = 2100;
const double MAX_D = 3000000000.0;

int n;
struct Point {
  int x, y;
  bool type;
} p[N];

double dist(int a, int b) {
  if (p[a].type == p[b].type)
    return MAX_D;
  double dx = p[a].x - p[b].x;
  double dy = p[a].y - p[b].y;
  return sqrt(dx * dx + dy * dy);
}

// 就是先对x进行排序
// 然后对x进行分治
// 求出左边距离，求出右边距离
// 找到最小距离ans后，这时需要求出跨越分界点midx的两个点的距离
// 这时这个点的横座标与midx差值肯定不会超过ans，否则距离不可能小于ans
// 在这个范围内，对于一个y来说，y到y+ans 范围内的值肯定很少，个位数
// 如果这个范围内点很多，就会违背之前求出的最小距离是ans的信息了，
// 所以这个范围内很小，直接进行求解即可。

double calc(int l, int r) {
  if (l == r)
    return MAX_D;
  if (l + 1 == r)
    return dist(l, r);

  int mid = (l + r) / 2;

  double ans = min(calc(l, mid), calc(mid + 1, r));

  vector<int> tmp;

  double midx = p[mid].x;
  for (int i = l; i <= r; i++) {
    if (fabs(midx - p[i].x) <= ans) {
      tmp.push_back(i);
    }
  }

  sort(tmp.begin(), tmp.end(), [](int a, int b) { return p[a].y < p[b].y; });

  for (int i = 0; i < tmp.size(); i++) {
    for (int j = i + 1;
         j < tmp.size() && fabs(p[tmp[j]].y - p[tmp[i]].y) <= ans; j++) {

      ans = min(ans, dist(tmp[i], tmp[j]));
    }
  }

  return ans;
}

int main() {
  int t;
  scanf("%d", &t);

  while (t--) {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
      scanf("%d%d", &p[i].x, &p[i].y);
      p[i].type = 0;
    }

    for (int i = n; i < 2 * n; i++) {
      scanf("%d%d", &p[i].x, &p[i].y);
      p[i].type = 1;
    }

    sort(p, p + 2 * n, [](Point a, Point b) {
      if (a.x == b.x) {
        return a.y < b.y;
      }
      return a.x < b.x;
    });

    double ans = calc(0, 2 * n - 1);

    printf("%.3f\n", ans);
  }
  return 0;
}
