% 清空工作空间
clear all;
load ORLData_25;

% 数据准备
X = ORLData'; % 转置数据
X = double(X);
[n, dim] = size(X);

% 获取样本标签
labels = X(:, dim); % 获取各样本的类别标签
labels = floor(double(labels));
c = max(labels); % 类别数

% 获取样本数据
X(:, dim) = []; 
clear ORLData;

% 设置随机种子以确保可重复性
rng(1);

% 划分训练集和测试集
train_ratio = 0.8;
num_train = round(n * train_ratio);

% 先获得所有下标随机化
indices = randperm(n);

% 获得训练集所有下标
train_indices = indices(1:num_train);
% 获得测试集所有下标
test_indices = indices(num_train + 1:end);

X_train = X(train_indices, :);
label_train = labels(train_indices);
X_test = X(test_indices, :);
label_test = labels(test_indices);

function [W, ans] = PCA(X, k)
    % 中心化数据
    X_centered = X - mean(X);

    % 计算协方差矩阵
    cov_matrix = cov(X_centered);

    % 计算特征值和特征向量
    [eig_vectors, eig_values] = eig(cov_matrix);

    % 将特征值按降序排列
    [~, idx] = sort(diag(eig_values), 'descend');
    eig_vectors = eig_vectors(:, idx);
    
    % 选择前k个特征向量
    W = eig_vectors(:, 1:k);
    
    % 计算降维后的数据
    ans = X_centered * W;
end

% PCA降维
% 设置降维后的维数
k = 5;
[coeff, X_train_pca] = PCA(X_train, k);

% 对测试集进行操作，进行降维
X_test_centered = X_test - mean(X_train);
X_test_pca = X_test_centered * coeff;

% 实现1-NN分类器
num_test = size(X_test_pca, 1);
label_pred = zeros(num_test, 1);

for i = 1:num_test
    % 计算测试样本与所有训练样本的欧几里得距离
    distances = sqrt(sum((X_train_pca - X_test_pca(i, :)).^2, 2));
    
    % 找到最近邻的索引
    [~, nearest_index] = min(distances);
    
    % 预测标签
    label_pred(i) = label_train(nearest_index);
end

% 计算分类准确率
accuracy = sum(label_pred == label_test) / length(label_test);
fprintf('分类准确率: %.2f%%\n', accuracy * 100);
