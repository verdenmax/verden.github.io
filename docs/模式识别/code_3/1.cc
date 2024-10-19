#include <algorithm>
#include <cmath>
#include <cstdio>

int n = 50;

double d;         // 方窗大小
double data[110]; // 所有样本点

double calc1(double idx) { // 计算方窗函数的概率
  double ans = 0;
  for (int i = 0; i < n; i++) {
    if (fabs(data[i] - idx) <= d / 2) {
      ans += 1.0 / d;
    }
  }
  return ans / n;
}

double calc2(double idx) { // 使用高斯窗进行计算
  double ans = 0;
  for (int i = 0; i < n; i++) {
    ans += exp(-(idx - data[i]) * (idx - data[i]) / (2 * d * d)) /
           (d * sqrt(2 * 3.14));
  }
  return ans / n;
}

int main() {

  for (int i = 0; i < n; i++)
    scanf("%lf %*c", &data[i]);

  double l = data[0];
  double r = data[0];
  double step = 0.001; // 步长

  for (int i = 0; i < n; i++)
    l = std::min(l, data[i]), r = std::max(r, data[i]);

  l -= step, r += step;

  char filename[100];
  for (double md = 0.01; md <= 1; md += 0.1) { // 枚举不同的窗宽度
    FILE *file;

    sprintf(filename, "%.2lf.csv", md);

    // 打开文件以写入（"w"模式会创建文件或覆盖已存在的文件）
    file = fopen(filename, "w");

    d = md;
    for (double idx = l; idx < r; idx += step) {
      fprintf(file, "%lf,%lf\n", idx, calc1(idx));
    }

    fclose(file);
  }

  return 0;
}
