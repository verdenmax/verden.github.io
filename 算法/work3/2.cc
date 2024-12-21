#include <algorithm>
#include <cstdio>

const int N = 3e5 + 100;

int n, m;
char s[N];
int a[N];

int main() {
  scanf("%d %s", &n, s);

  int len = n;
  for (int i = 0; i < n; i++) {
    if (s[i] == '0')
      continue;

    int j = i;

    while (j < n && s[j] == '1')
      j++;

    int x = j - i;
    if (i == 0 || j == n) {
      len = std::min(len, x * 2 - 1);
    } else {
      len = std::min(len, x - (x % 2 == 0));
    }

    a[++m] = x;

    i = j - 1;
  }

  int ans = 0;
  for (int i = 1; i <= m; i++)
    ans += (a[i] + len - 1) / len;

  printf("%d", ans);
  return 0;
}
