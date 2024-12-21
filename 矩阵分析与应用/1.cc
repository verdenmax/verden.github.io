#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>

// 将 n * m 的矩阵转置，返回
int **transpose(int **a, int **b, int n, int m) {
  // 申请 m * n 的空间
  b = (int **)malloc(m * sizeof(int *));
  for (int i = 0; i < m; i++) {
    b[i] = (int *)malloc(n * sizeof(int));
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      b[j][i] = a[i][j];
    }
  }
  return b;
}

struct truple {
  int x, y, value;
};

struct Matrix {
  int cell_count; // 稀疏矩阵非0个数
  std::vector<struct truple> cell_vec;

  // 稀疏矩阵转置
  void transpose() {
    for (auto &cell : cell_vec) {
      std::swap(cell.x, cell.y); // 交换行和列
    }
  }
};

int main() {
  int a[2][3] = {{1, 2, 3}, {2, 3, 4}};

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++)
      printf("%d%c", a[i][j], " \n"[j == 2]);

  // 将静态数组 a 转换为动态数组
  int **dynamic_a = (int **)malloc(2 * sizeof(int *));
  for (int i = 0; i < 2; i++) {
    dynamic_a[i] = (int *)malloc(3 * sizeof(int));
    for (int j = 0; j < 3; j++) {
      dynamic_a[i][j] = a[i][j];
    }
  }

  int **b;
  transpose(dynamic_a, b, 2, 3);

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++)
      printf("%d%c", b[i][j], " \n"[j == 1]);
  return 0;
}
