#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int N = 3100;

int n;
int a[N];
int f[N];

int main() {
  scanf("%d%d", &n, &a[0]);

  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);

  for (int i = 1; i <= n; i++)
    a[i] = a[i] + a[i - 1];

  f[0] = -a[0];
  for (int i = 1; i <= n; i++) {
    f[i] = a[i];

    for (int pre = 0; pre < i; pre++) {
      f[i] = min(f[i], f[pre] + a[i - pre] + a[0]);
    }
  }

  printf("%d\n", f[n]);
  return 0;
}
