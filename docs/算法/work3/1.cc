#include <algorithm>
#include <cstdio>

const int N = 210;
const int INF = 0x3f3f3f3f;

int n, m;
int c[N];
int f[N][N];

int main() {
  scanf("%d%*d%d", &m, &n);

  for (int i = 1; i <= n; i++)
    scanf("%d", &c[i]);
  std::sort(c + 1, c + n + 1);

  // 　每次决策就是决策一个模板选围住多少个
  // 状态就是当前已经围到了哪里，并且使用了多少个木板

  for (int i = 1; i <= n; i++) {
    f[i][0] = INF;
    for (int j = 1; j <= m; j++) {
      f[i][j] = f[i][j - 1];

      for (int pre = 0; pre < i; pre++) {
        f[i][j] = std::min(f[i][j], f[pre][j - 1] + c[i] - c[pre + 1] + 1);
      }
    }
  }

  printf("%d", f[n][m]);

  return 0;
}
