#include <cmath>
#include <cstring>
#include <stdio.h>
#include <vector>

using namespace std;

const int N = 11000;

vector<int> ans[N];

// 对于一个长度为 n 的问题，假设解为 a_1,a_2,...,a_n
// 那么将上面值乘2，拼接上乘2加1
// 即为 2*a_1,2*a_2, .... ,2 * a_n , a*a_1+1,2*a_2+1,.... , 2*a_n+1
// 那么前半部分，后半部分肯定满足条件
// 再看跨越，一部分选一个，另一部分选两个数，
// 那么这三个数中必然有一个数与其他两个数奇偶性不同，那比不可能是等差

void calc(int n) {
  // 记忆化
  if (!ans[n].empty())
    return;

  // 分解成 nx 长度的问题
  int nx = (n + 1) / 2;
  calc(nx);

  for (int x : ans[nx]) {
    ans[nx * 2].push_back(2 * x);
    ans[nx * 2 - 1].push_back(2 * x);
  }

  for (int x : ans[nx]) {
    ans[nx * 2].push_back(2 * x + 1);

    if (2 * x + 1 < nx * 2 - 1)
      ans[nx * 2 - 1].push_back(2 * x + 1);
  }
}

int main() {
  ans[1].push_back(0);
  ans[2].push_back(0);
  ans[2].push_back(1);
  int n;
  while (scanf("%d", &n), n) {
    calc(n);

    printf("%d:", n);

    for (int x : ans[n])
      printf(" %d", x);
    printf("\n");
  }

  return 0;
}
