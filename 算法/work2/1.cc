#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int N = 3100;
const ll INF = 3e12;

int a[N], b[N];
// f[i][j] 代表以 i 结束 j 个结点最小花费
ll f[N][3];

int main() {

  int n;
  scanf("%d", &n);

  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);

  for (int i = 1; i <= n; i++) {
    scanf("%d", &b[i]);

    f[i][0] = b[i];
  }

  int ans = 1;
  for (int i = 1; i <= n; i++) {
    for (int dep = 1; dep < 3; dep++) {
      f[i][dep] = INF;

      for (int pre = 1; pre < i; pre++) {
        if (a[pre] < a[i]) {
          f[i][dep] = min(f[i][dep], f[pre][dep - 1] + b[i]);
        }
      }
    }

    if (f[i][2] < f[ans][2])
      ans = i;
  }

  if (f[ans][2] == INF)
    printf("%d\n", -1);
  else
    printf("%lld\n", f[ans][2]);
  return 0;
}
