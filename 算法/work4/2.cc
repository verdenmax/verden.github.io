#include <algorithm>
#include <cstdio>

const int N = 1e6 + 100;

int f[N];
int c[10];

int main() {
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    scanf("%d", &c[i]);
  }

  int v;
  scanf("%d", &v);

  for (int i = 1; i <= v; i++)
    f[i] = 4e6;

  for (int i = 0; i < n; i++) {
    int x = c[i];

    for (int j = x; j <= v; j++) {
      f[j] = std::min(f[j], f[j - x] + 1);
    }
  }

  if (f[v] == 4e6)
    f[v] = -1;

  printf("%d\n", f[v]);
  return 0;
}
