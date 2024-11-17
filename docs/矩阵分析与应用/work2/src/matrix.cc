#include "matrix.h"
#include <utility>

Matrix::Matrix(int _n, int _m) : n(_n), m(_m) {
  data.resize(n);

  for (int i = 0; i < n; i++) {
    data[i].resize(m);

    for (int j = 0; j < m; j++)
      data[i][j] = 0;
  }
}

int Matrix::getRowNumber() { return n; }

int Matrix::getColNumber() { return m; }

void Matrix::show() {
  std::printf("-------------------\n");
  std::printf("%d %d\n", n, m);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      std::printf("%.6lf%c", data[i][j], " \n"[j == m - 1]);
}

Matrix Matrix::operator*(const Matrix &other) {
  Matrix a(n, other.m);
  for (int k = 0; k < m; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < other.m; j++) {
        a[i][j] += (*this)[i][k] * other[k][j];
      }
    }
  }
  return a;
}

void Matrix::mul(double value) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      (*this)[i][j] *= value;
    }
  }
}

Matrix Matrix::operator+(const Matrix &other) {
  Matrix ans(n, m);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ans[i][j] = (*this)[i][j] + other[i][j];
    }
  }

  return ans;
}

Matrix Matrix::operator-(const Matrix &other) {
  Matrix ans(n, m);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ans[i][j] = (*this)[i][j] - other[i][j];
    }
  }

  return ans;
}

Matrix &Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    // 拷贝赋值逻辑
    n = other.n;
    m = other.m;
    data = other.data;
  }
  return *this;
}

Matrix Matrix::getCol(int index) {
  Matrix ans(n, 1);

  for (int i = 0; i < n; i++) {
    ans[i][0] = (*this)[i][index];
  }
  return ans;
}

double Matrix::FNorm() {
  double ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ans += data[i][j] * data[i][j];
    }
  }
  return ans;
}

void Matrix::initIMatrix() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i == j)
        data[i][j] = 1;
      else
        data[i][j] = 0;
    }
  }
}

void Matrix::transposition() {
  std::vector<std::vector<double>> newData;

  newData.resize(m);

  for (int i = 0; i < m; i++) {
    newData[i].resize(n);

    for (int j = 0; j < n; j++)
      newData[i][j] = data[j][i];
  }

  std::swap(n, m);
  this->data = newData;
}
