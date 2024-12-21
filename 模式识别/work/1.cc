

#include <cmath>
#include <cstdio>
#include <vector>

struct triple {
  double x, y, z;

  void negate() {
    x = -x;
    y = -y;
    z = -z;
  }

  double time(struct triple b) { return x * b.x + y * b.y + z * b.z; }

  void add(struct triple b) {
    x += b.x;
    y += b.y;
    z += b.z;
  }

  void show() { printf("a = (%lf,%lf,%lf)\n", x, y, z); }
};

int main() {
  // 记录所有w_1,w_2
  std::vector<triple> w;

  // 10个向量
  int n = 10;

  // 读入向量
  for (int i = 0; i < n; i++) {
    struct triple tp;
    scanf("%lf%lf", &tp.x, &tp.y);
    tp.z = 1; // 增广
    w.push_back(tp);
  }

  for (int i = 0; i < n; i++) {
    struct triple tp;
    scanf("%lf%lf", &tp.x, &tp.y);
    tp.z = 1; // 增广

    // 对第二个分类进行 全部取反
    tp.negate();
    w.push_back(tp);
  }

  // printf("%.10f\n", 1e-8);
  // for (int i = 0; i < w.size(); i++) {
  //   w[i].show();
  // }
  // return 0;

  // 初始化向量a
  struct triple a = {0, 0, 0};

  int k = 0;
  bool flag = 0; // 是否迭代完成
  do {
    flag = 0;
    struct triple sy = {0, 0, 0};

    for (int i = 0; i < w.size(); i++) {
      if (a.time(w[i]) < 0 || fabs(a.time(w[i])) < 1e-8) {
        sy.add(w[i]);
        sy.show();
        flag = 1;
      }
    }

    a.add(sy);
    printf("%d ", k);
    a.show();
    k++;
    return 0;
  } while (flag);

  printf("迭代了 %d 次\n", k - 1);

  printf("a = (%lf,%lf,%lf)\n", a.x, a.y, a.z);
  return 0;
}
