#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int N = 55;

int n, m;
int cost[N][N];
int f[210][N][N];
int dx[] = {1, 1, 0, 0};
int dy[] = {1, 0, 1, 0};

// void dfs(int x1, int y1, int x2, int y2) {
//   for (int idx1 = 0; idx1 < 2; idx1++) {
//     for (int idx2 = 0; idx2 < 2; idx2++) {
//       int nx1 = x1 + dx[idx1], ny1 = y1 + dy[idx1];
//       int nx2 = x2 + dx[idx2];
//       int ny2 = nx1 + ny1 - nx2;
//
//       if (nx1 >= n || ny1 >= m)
//         continue;
//       if (nx2 >= n || ny2 >= m)
//         continue;
//
//       f[nx1][ny1][nx2] = max(f[nx1][ny1][nx2],
//                              f[x1][y1][x2] + cost[nx1][ny1] +
//                              cost[nx2][ny2]);
//
//       // if (nx1 == nx2 && ny1 == ny2)
//       //   continue;
//       if (nx1 >= nx2 || ny1 <= ny2)
//         continue;
//       // printf("%d %d %d %d %d\n", nx1, ny1, nx2, ny2,
//       f[nx1][ny1][nx2][ny2]);
//
//       dfs(nx1, ny1, nx2, ny2);
//     }
//   }
// }
//
int main() {
  scanf("%d%d", &n, &m);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", &cost[i][j]);

  if (n == 1 || m == 1) {
    printf("0");
    return 0;
  }

  f[1][0][1] = cost[0][1] + cost[1][0];
  for (int len = 1; len < n + m - 2; len++) {
    int mlen = min(len, n - 1);
    int mi = min(0, len - m + 1);
    for (int x1 = mi; x1 <= mlen; x1++) {
      for (int x2 = x1 + 1; x2 <= mlen; x2++) {
        for (int idx = 0; idx < 4; idx++) {
          int nx1 = x1 + dx[idx], nx2 = x2 + dy[idx];
          int ny1 = len + 1 - nx1, ny2 = len + 1 - nx2;

          if (nx1 >= n || ny1 >= m)
            continue;
          if (nx2 >= n || ny2 >= m)
            continue;

          f[len + 1][nx1][nx2] =
              max(f[len + 1][nx1][nx2],
                  f[len][x1][x2] + cost[nx1][ny1] + cost[nx2][ny2]);

          // printf("%d %d %d %d %d\n", nx1, ny1, nx2, ny2, f[len +
          // 1][nx1][nx2]);
        }
      }
    }
  }

  printf("%d\n", f[n + m - 2][n - 1][n - 1]);
  return 0;
}
