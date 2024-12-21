
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

class Data {
public:
  std::vector<double> input, target;
  std::vector<double> z, hidden;

  Data(std::vector<double> input, std::vector<double> target,
       std::vector<double> z)
      : input(input), target(target), z(z) {}
};

std::vector<double> Target[3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

// 初始化权重参数
void initWeights(std::vector<std::vector<double>> &weights) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> dis(0, 1.0);

  for (auto &row : weights) {
    for (auto &w : row) {
      w = dis(gen);
    }
  }
}

// 定义一些激活函数相关信息
typedef double (*ActivationFunction)(double);

double sigmoid(double x) { return 1.0 / (1.0 + std::exp(-x)); }

double sigmoidDerivative(double x) { return sigmoid(x) * (1 - sigmoid(x)); }

// 双曲正切使用标准库中 std::tanh(x);

// 双曲正切函数导数
double tanhDerivative(double x) { return (-tanh(x) * tanh(x)) + 1; }

std::vector<double> calc(int n, std::vector<double> value,
                         std::vector<std::vector<double>> weights,
                         ActivationFunction func) {
  std::vector<double> ans(n);

  for (int j = 0; j < n; j++) {
    ans[j] = 0;
    for (int i = 0; i < value.size(); i++) {
      ans[j] += value[i] * weights[i][j];
    }

    // 通过激活函数
    ans[j] = func(ans[j]);
  }
  return ans;
}

// 计算净输入
std::vector<double> calcnet(int n, std::vector<double> value,
                            std::vector<std::vector<double>> weights) {
  std::vector<double> ans(n);

  for (int j = 0; j < n; j++) {
    ans[j] = 0;
    for (int i = 0; i < value.size(); i++) {
      ans[j] += value[i] * weights[i][j];
    }
  }
  return ans;
}

int main() {
  // 学习率
  double eta = 1;
  // 每个样本的数量
  int n = 10;

  // 第一行，读入数据n和学习率
  std::cin >> n >> eta;

  std::vector<Data> v;
  // 读入所有训练集数据
  for (int i = 0; i < 3 * n; i++) {
    std::vector<double> tot;
    for (int j = 0; j < 3; j++) {
      double x;
      std::cin >> x;
      tot.push_back(x);
    }

    v.push_back(Data(tot, Target[i / n], Target[i / n]));
  }

  // for (int i = 0; i < 3 * n; i++) {
  //   std::cout << v[i].input[0] << " " << v[i].input[1] << " " <<
  //   v[i].input[2]
  //             << "\n";
  //   std::cout << v[i].target[0] << " " << v[i].target[1] << " "
  //             << v[i].target[2] << "\n";
  // }

  // 定义隐含层结点个数为10个
  int H = n;
  std::vector<std::vector<double>> w1, w2;
  w1.resize(3, std::vector<double>(H));
  w2.resize(H, std::vector<double>(3));

  // 初始化随机参数
  initWeights(w1);
  initWeights(w2);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, v.size() - 1);

  for (auto &data : v) {
    auto hidden = calc(H, data.input, w1, std::tanh);
    auto z = calc(3, hidden, w2, sigmoid);

    data.z = z;
    data.hidden = hidden;
  }

  int traincnt = 0;
  do {
    // 进行训练

    // 反向更新权值
    // 这里需要 eta, delta , y_h
    // 其中每个数据的 delta,y_h 都可以现场计算

    int random_number = dis(gen);
    {

      auto &data = v[random_number];
      // 重新计算data的z，输出层
      // data.z = calc(3, data.hidden, w2, sigmoid);

      // 计算出输出层的净输入
      auto netOut = calcnet(3, data.hidden, w2);
      // 计算出隐含层的净输入
      auto netHidden = calcnet(H, data.input, w1);
      // 更新输入层到隐含层的权重
      for (int i = 0; i < 3; i++) {
        for (int h = 0; h < H; h++) {

          double deltah = 0;
          for (int j = 0; j < 3; j++) {
            // 这里是计算 w_hj * \delta_j
            deltah += w2[h][j] * sigmoidDerivative(netOut[j]) *
                      (data.target[j] - data.z[j]);
          }

          deltah *= tanhDerivative(netHidden[h]);

          // 更新从输入层到隐含层的权重
          w1[i][h] += eta * deltah * data.input[i];
        }
      }

      for (int h = 0; h < H; h++) {
        for (int j = 0; j < 3; j++) {
          // 更新隐含层到输出层的权重
          // 其中 data.hidden[h] 为边起始结点的输出
          w2[h][j] += eta * sigmoidDerivative(netOut[j]) *
                      (data.target[j] - data.z[j]) * data.hidden[h];
        }
      }
    }

    double deltaJ = 0;
    for (auto &data : v) {
      auto hidden = calc(H, data.input, w1, std::tanh);
      auto z = calc(3, hidden, w2, sigmoid);

      data.z = z;
      data.hidden = hidden;

      double totDelta = 0;
      for (int j = 0; j < 3; j++) {
        totDelta += (data.target[j] - data.z[j]) * (data.target[j] - data.z[j]);
      }
      totDelta /= 2;

      deltaJ += totDelta;

      // std::cout << "\nz输出：";
      // for (int j = 0; j < 3; j++) {
      //   std::cout << data.z[j] << " ";
      // }
      //
      // std::cout << "\n目标：";
      // for (int j = 0; j < 3; j++) {
      //   std::cout << data.target[j] << " ";
      // }
    }

    traincnt++;

    if (traincnt % 1000 == 0)
      std::cout << "迭代次数:" << traincnt << ", 当前平方误差：" << deltaJ
                << "\n";

  } while (1);

  return 0;
}
