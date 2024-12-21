import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import glob
import os

# 获取所有 CSV 文件的路径
csv_files = glob.glob('./*.csv')  # 修改为你的 CSV 文件路径

# 创建一个颜色列表
colors = plt.cm.viridis(np.linspace(0, 1, len(csv_files)))

# 创建绘图
plt.figure(figsize=(10, 6))

# 遍历每个 CSV 文件
for idx, file in enumerate(csv_files):
    # 读取 CSV 文件
    data = pd.read_csv(file, header=None)  # 不使用列名

    # 将每行数据分割为 x 和 y
    x = data[0]  # 第一列
    y = data[1]  # 第二列
    
     # 提取文件名并去掉扩展名
    filename = os.path.basename(file).replace('.csv', '')
    
    # 绘制曲线并设置文件名为标签
    plt.plot(x, y, color=colors[idx], label=filename)

# 添加图例和标签
plt.title('square window')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.legend()
plt.grid()

# 显示图形
# plt.show()
plt.savefig('output_plot.png')  # 你可以指定文件名和路径

