#include "matrix.h"

#include <cmath>
#include <cstdio>

// 枚举所有分解类型
enum Reduction { ModifiedGramdSchmid, Householder, GIVENS };

// 配置
struct Config {
  // 使用那种方法分解
  Reduction type;
  // 是否进行方程组求解
  bool isEquation;
};

class QRReduction {
private:
  int n, m;
  Matrix a, b;
  Matrix Q, R;
  Config config;

public:
  QRReduction(Matrix a, Matrix b, const Config &config)
      : a(a), b(b), n(a.getRowNumber()), m(a.getColNumber()), Q(0, 0), R(0, 0),
        config(config) {};

  // 修改后的ModifiedGramdSchmid
  void ModifiedGramdSchmid();

  void Householder();

  void Givens();

  // show
  void show();

  void run();
};
