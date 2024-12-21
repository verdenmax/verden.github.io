#include "QRReduction.h"
#include <cmath>
#include <cstdio>

void QRReduction::ModifiedGramdSchmid() {
  // 先获得矩阵m个列向量
  std::vector<Matrix> v;

  for (int i = 0; i < m; i++) {
    v.push_back(a.getCol(i));
  }

  Matrix I(n, n);
  // n 乘n的单位阵，用于后面构造矩阵 E = I - u_k u_k^T
  I.initIMatrix();

  for (int k = 0; k < m; k++) {
    if (sqrt(v[k].FNorm()) < 1e-8)
      continue;

    // 第k步，对第k个向量进行单位化
    v[k].mul(1.0 / sqrt(v[k].FNorm())); // 进行单位化

    Matrix vkt = v[k];
    vkt.transposition();

    // 算出矩阵Ek
    Matrix Ek = I - v[k] * vkt;

    // 对k之后所有向量进行单位化
    for (int j = k + 1; j < m; j++) {
      v[j] = Ek * v[j];
    }
  }

  // 进行QR分解
  Matrix Q(n, m);

  // Q 其实就是上面构造出的标准正交向量的组合
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      Q[j][i] = v[i][j][0];

  Matrix QT = Q;
  QT.transposition();

  Matrix R = QT * a;

  this->Q = Q;
  this->R = R;

  // printf("ModifiedGramdSchmid  QR分解完成：\n");
  // printf("A矩阵：\n");
  // a.show();
  //
  // printf("Q矩阵：\n");
  // Q.show();
  // printf("R矩阵：\n");
  // R.show();
  // printf("Q * R矩阵：\n");
  // (Q * R).show();
}

void QRReduction::Householder() {
  Matrix totA = a;

  // Q 矩阵是所有下面Rk的乘积
  // 这里先进行初始化为单位阵
  Matrix totQ(n, n);
  totQ.initIMatrix();

  // householder 分解的步骤，一共n步
  for (int k = 0; k < n; k++) {
    // 构造u1
    // 这里先取出第k列，这里取出的是从第k行开始
    // 所以是一个n - k行，1列的向量
    Matrix x1(n - k, 1);
    Matrix e1(n - k, 1);
    for (int i = 0; i < n - k; i++) {
      x1[i][0] = totA[k + i][k];
      e1[i][0] = 0;
    }
    e1[0][0] = 1;

    // u = x1 +- \mu ||x1||e_1
    e1.mul(sqrt(x1.FNorm()));
    Matrix u = x1 - e1;

    // 如果u是0，那么跳过
    if (sqrt(u.FNorm()) < 1e-8)
      continue;

    u.mul(1 / sqrt(u.FNorm()));

    Matrix I(n - k, n - k);
    // n 乘n的单位阵，用于后面构造矩阵 R = I - 2 u u^T
    I.initIMatrix();

    Matrix uT = u;
    uT.transposition();

    u = u * uT;
    u.mul(2);

    // 构造Reflector
    Matrix R1 = I - u;

    // 构造整个矩阵，一个单位阵，然后右下角使用R1来填充
    Matrix Rk(n, n);
    Rk.initIMatrix();

    for (int i = 0; i < n - k; i++) {
      for (int j = 0; j < n - k; j++) {
        Rk[k + i][k + j] = R1[i][j];
      }
    }

    // totA.show();
    totA = Rk * totA;

    // Rk.show();
    // totA.show();

    totQ = totQ * Rk;
  }

  this->Q = totQ;
  this->R = totA;

  // printf("Householder QR分解完成：\n");
  // printf("A矩阵：\n");
  // a.show();
  //
  // printf("Q矩阵：\n");
  // totQ.show();
  // printf("R矩阵：\n");
  // totA.show();
  // printf("Q * R矩阵：\n");
  // (totQ * totA).show();
}

void QRReduction::Givens() {
  Matrix totA = a;

  Matrix totP(n, n);
  totP.initIMatrix();

  for (int k = 0; k < n; k++) {

    for (int step = k + 1; step < n; step++) {

      // 构造旋转矩阵，消除第k列的第step个数
      // 其中选定元素为
      // x_i = totA[k][k] ,x_j = totA[step][k]
      // c = x_i /(sqrt(x_i^2 + x_j^2))
      // s = x_j /(sqrt(x_i^2 + x_j^2))

      double x_i = totA[k][k];
      double x_j = totA[step][k];

      double len = sqrt(x_i * x_i + x_j * x_j);

      if (len < 1e-8)
        continue;

      double c = x_i / len;
      double s = x_j / len;

      Matrix Pstep(n, n);
      Pstep.initIMatrix();

      Pstep[k][k] = c;
      Pstep[k][step] = s;
      Pstep[step][k] = -s;
      Pstep[step][step] = c;

      totA = Pstep * totA;

      totP = Pstep * totP;
    }
  }

  Matrix Q = totP;
  Q.transposition();

  this->Q = Q;
  this->R = totA;
}

void QRReduction::show() {
  if (config.type == Reduction::ModifiedGramdSchmid)
    printf("ModifiedGramdSchmid");
  else if (config.type == Reduction::Householder)
    printf("Householder");
  else if (config.type == Reduction::GIVENS)
    printf("Givens");

  printf("QR分解完成：\n");
  printf("A矩阵：\n");
  a.show();

  printf("Q矩阵：\n");
  Q.show();
  printf("R矩阵：\n");
  R.show();
  printf("Q * R矩阵：\n");
  (Q * R).show();
}

void QRReduction::run() {
  switch (this->config.type) {
  case Reduction::ModifiedGramdSchmid: {
    ModifiedGramdSchmid();
    break;
  }
  case Reduction::Householder: {
    Householder();
    break;
  }
  case Reduction::GIVENS: {
    Givens();
    break;
  }
  default:
    break;
  }

  show();

  // Matrix x(m, 1);
  //
  // for (int i = 0; i < m; i++)
  //   x[i][0] = i;
  //
  // (a * x).show();

  if (this->config.isEquation) {
    // QR x = b
    // Rx = Q^T b
    Matrix QT = Q;
    QT.transposition();

    Matrix y = QT * b;

    // Rx = y
    // R 是一个上三角

    // R.show();
    // y.show();
    Matrix x(m, 1);

    // 从第n-1行开始，就是最后一个等式
    // 从R矩阵的第n行开始
    for (int i = R.getRowNumber() - 1; i >= 0; i--) {
      double ans = y[i][0];

      // 找到这一行主元位置
      int pivot = 0;
      for (int j = 0; j < m; j++) {
        if (fabs(R[i][j]) < 1e-8) {
          continue;
        } else {
          pivot = j;
          break;
        }
      }

      // printf("%---->%d\n", pivot);
      if (fabs(R[i][pivot]) < 1e-8)
        continue;

      for (int j = pivot + 1; j < m; j++) {
        ans -= R[i][j] * x[j][0];
      }

      x[pivot][0] = ans / R[i][pivot];
    }

    // 解为
    printf("x :\n");
    x.show();

    printf("最小二乘 (a x - b) :\n");
    (a * x - b).show();

    printf("平方和误差 \\sum (a x - b)^2 :\n");
    double af = (a * x - b).FNorm();
    printf("%lf", af);
  }
}
