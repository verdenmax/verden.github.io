#include <cstdio>
#include <vector>

class Matrix {
private:
  int n, m;

  std::vector<std::vector<double>> data;

public:
  // 初始化矩阵 n  \times m
  Matrix(int _n, int _m);

  // 拷贝构造
  Matrix(const Matrix &other) = default;

  // 移动构造
  Matrix(Matrix &&other) = default;

  // 析构函数
  ~Matrix() = default;

  // 获得行和列
  int getRowNumber();

  int getColNumber();

  // 打印矩阵
  void show();

  // 矩阵乘法
  Matrix operator*(const Matrix &other);

  // 数乘
  void mul(double value);

  // 矩阵加法
  Matrix operator+(const Matrix &other);

  // 矩阵减法
  Matrix operator-(const Matrix &other);

  // 拷贝赋值
  Matrix &operator=(const Matrix &other);

  class Row {
  private:
    std::vector<double> &rowData;

  public:
    Row(std::vector<double> &data) : rowData(data) {};

    const double &operator[](int index) const { return rowData[index]; }

    double &operator[](int index) { return rowData[index]; }
  };

  class ConstRow {
  private:
    const std::vector<double> &rowData;

  public:
    ConstRow(const std::vector<double> &data) : rowData(data) {};

    const double &operator[](int index) const { return rowData[index]; }
  };

  // 重载[]
  Row operator[](int index) { return Row(data[index]); }

  const ConstRow operator[](int index) const { return ConstRow(data[index]); }

  // 获取矩阵一行
  Matrix getCol(int index);

  // 获得F模平方，对于一个向量来说就是二模的平方
  double FNorm();

  // 单位矩阵
  void initIMatrix();

  // 转置
  void transposition();
};
