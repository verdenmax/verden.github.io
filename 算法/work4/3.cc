#include <algorithm>
#include <cstdio>

const int N = 300, M = 110;
const int INF = 0x3f3f3f3f;

int f[N][M];
int c[M], cost[M];

int main() {
  int n, p, m;
  scanf("%d%d%d", &n, &p, &m);

  for (int i = 0; i < p; i++) {
    scanf("%d%d", &c[i], &cost[i]);
  }

  for (int i = 1; i <= m; i++)
    for (int j = 0; j <= n; j++)
      f[i][j] = INF;
  f[0][0] = 0;

  for (int ti = 1; ti <= n; ti++) {
    for (int line = 0; line < p; line++) {
      int x = c[line];
      int y = cost[line];

      for (int j = 0; j <= m; j++) {

        f[j][ti] = std::min(f[j][ti], f[j][ti - 1]);
      }

      for (int j = 0; j <= m; j++) {

        int nx = std::min(m, j + y);
        f[nx][ti] = std::min(f[nx][ti], f[j][ti - 1] + x);
      }
    }
    // for (int j = m; j >= 0; j--) {
    //
    //   printf("%d :: ", j);
    //   for (int ti = 0; ti <= n; ti++) {
    //     printf("%d ", f[j][ti]);
    //   }
    //   printf("\n");
    // }
  }

  if (f[m][n] == INF)
    f[m][n] = -1;

  printf("%d\n", f[m][n]);
  return 0;
}
