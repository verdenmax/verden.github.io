
#include <cstdio>
#include <fstream>
#include <iostream>

#include "QRReduction.h"

auto pharse(int argc, char **argv) -> Config {
  Config config = Config{.type = ModifiedGramdSchmid, .isEquation = 0};

  // 此时有参数，进行解析
  if (argc >= 2) {
    for (int idx = 0; argv[1][idx]; idx++) {
      // 参数分别是 -[M|H|G][E]
      switch (argv[1][idx]) {
      case 'M': {
        config.type = ModifiedGramdSchmid;
        break;
      }
      case 'H': {
        config.type = Householder;
        break;
      }
      case 'G': {
        config.type = GIVENS;
        break;
      }
      case 'E': {
        config.isEquation = true;
        break;
      }
      default:
        break;
      }
    }
  }

  return config;
}

int main(int argc, char **argv) {
  // 解析参数
  Config config = pharse(argc, argv);

  // std::ifstream data_stream("1.in", std::ios::in);

  // 读入矩阵A
  int n, m;
  std::cin >> n >> m;
  Matrix a(n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> a[i][j];
    }
  }

  // 读入系数b
  Matrix b(n, 1);
  if (config.isEquation)
    for (int i = 0; i < n; i++) {
      std::cin >> b[i][0];
    }

  QRReduction reduction(a, b, config);

  reduction.run();

  return 0;
}
