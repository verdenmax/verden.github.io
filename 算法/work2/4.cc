#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int N = 2e5 + 100;

int n;
char s[2][N];
bool st[2][N];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {

    scanf("%d", &n);

    scanf("%s%s", s[0], s[1]);

    for (int i = 0; i <= n; i++)
      st[0][i] = st[1][i] = 0;
    st[0][0] = 1;

    for (int y = 0; y < n; y++) {
      for (int x = 0; x < 2; x++) {
        if (!st[x][y])
          continue;

        for (int idx = 0; idx < 4; idx++) {
          int nx = x + dx[idx], ny = y + dy[idx];

          if (nx < 0 || nx > 1)
            continue;
          if (ny < 0 || ny >= n)
            continue;

          if (s[nx][ny] == '>')
            ny++;
          else
            ny--;

          st[nx][ny] = 1;
        }
      }
    }

    if (st[1][n - 1])
      printf("YES\n");
    else
      printf("NO\n");
  }

  return 0;
}
