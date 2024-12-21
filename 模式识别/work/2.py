import numpy as np

# 数据一
X_x1 = np.array([[0.1, 1.1],
                 [6.8, 7.1],
                 [-3.5, -4.1],
                 [2.0, 2.7],
                 [4.1, 2.8],
                 [3.1, 5.0],
                 [-0.8, -1.3],
                 [0.9, 1.2],
                 [5.0, 6.4],
                 [3.9, 4.0]])

# 数据二
X_x2 = np.array([[7.1, 4.2],
                 [-1.4, -4.3],
                 [4.5, 0.0],
                 [6.3, 1.6],
                 [4.2, 1.9],
                 [1.4, -3.2],
                 [2.4, -4.0],
                 [2.5, -6.1],
                 [8.4, 3.7],
                 [4.1, -2.2]])

# 数据三
X_y1 = np.array([[-3.0, -2.9],
                 [0.5, 8.7],
                 [2.9, 2.1],
                 [-0.1, 5.2],
                 [-4.0, 2.2],
                 [-1.3, 3.7],
                 [-3.4, 6.2],
                 [-4.1, 3.4],
                 [-5.1, 1.6],
                 [1.9, 5.1]])

# 数据四
X_y2 = np.array([[-2.0, -8.4],
                 [-8.9, 0.2],
                 [-4.2, -7.7],
                 [-8.5, -3.2],
                 [-6.7, -4.0],
                 [-0.5, -9.2],
                 [-5.3, -6.7],
                 [-8.7, -6.4],
                 [-7.1, -9.7],
                 [-8.0, -6.3]])

# 提取前8个样本并添加列
def process_data(data):
    # 提取前8个样本
    selected_samples = data[:8]
    # 在每一行最后添加1
    return np.hstack((selected_samples, np.ones((selected_samples.shape[0], 1))))

# 处理数据
processed_X_x1 = process_data(X_x1)
processed_X_x2 = process_data(X_x2)
processed_X_y1 = process_data(X_y1)
processed_X_y2 = process_data(X_y2)

# 训练数据
X_s = np.vstack((processed_X_x1, processed_X_x2, processed_X_y1, processed_X_y2)).T

Z = np.array([
             [1., 1., 1., 1., 1., 1., 1., 1., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
             [0., 0., 0., 0., 0., 0., 0., 0., 1., 1., 1., 1., 1., 1., 1., 1., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
             [0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 1., 1., 1., 1., 1., 1., 1., 1., 0., 0., 0., 0., 0., 0., 0., 0.],
             [0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 1., 1., 1., 1., 1., 1., 1., 1.],])


W = np.linalg.pinv(X_s@X_s.T)@X_s

W = W@Z.T



def process(data):
    selected_samples = data[8:]
    # 在每一行最后添加1
    return np.hstack((selected_samples, np.ones((selected_samples.shape[0], 1))))

# 处理数据
processed_X_x1 = process(X_x1)
processed_X_x2 = process(X_x2)
processed_X_y1 = process(X_y1)
processed_X_y2 = process(X_y2)

# 测试数据
X_test = np.vstack((processed_X_x1, processed_X_x2, processed_X_y1, processed_X_y2)).T

ans = W.T@X_test

# 找到每一列最大位置
max_indices = np.argmax(ans, axis=0)

# 输出测试集分类结果
print(max_indices)

