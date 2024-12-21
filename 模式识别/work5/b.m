clear all ;
load vehicle;

% 数据输入
out = UCI_entropy_data.train_data;

X = out'; 
X = double(X);
[n, dim] = size(X);  
labels = X(:, dim);   
labels = floor(double(labels));  % 获取各样本的类别标签
c = max(labels);             % c = 4
X(:, dim) = [];             % 获取样本数据
clear UCI_entropy_data;
clear out;

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


function [W, X_lda] = LDA(X, labels, k)
    % mu
    X_mu = mean(X) ;

    % 获得有多少种类型
    classes = unique(labels) ;
    label_nr = length(classes) ;

    [n, d] = size(X) ;

    % 进行计算Sw, Sb
    Sw = zeros(d, d) ;
    Sb = zeros(d, d) ;
    
    for idx = 1:label_nr 

        % 类型为 idx 的所有样本
        X_tot = X(labels == classes(idx), :) ;
        
        % 计算当前类别均值
        mu_k = mean(X_tot) ;

        Sw = Sw + (X_tot - mu_k)' * (X_tot - mu_k) ;

        % 属于 idx 类的样本个数
        ct = size(X_tot, 1) ;
        Sb = Sb + ct * (mu_k - X_mu)' * (mu_k - X_mu) ;
    end

    % LDA 剩下就是求解 Sb w = \lambda Sw w
    [V, D] = eig(Sb, Sw) ;

    % 特征值
    eig_values = diag(D) ;

    % 将特征值按降序排列
    [~, idx] = sort(eig_values, 'descend');
    eig_vectors = V(:, idx);
    
    % 选择前k个特征向量
    W = eig_vectors(:, 1:k);
    
    % 计算降维后的数据
    X_lda = X * W;
end


% 设置降维后的维数
k = 15;
[coeff, X_train_lda] = LDA(X_train, label_train, k);

% 对测试集进行操作，进行降维
% X_test_centered = X_test - mean(X_train);
X_test_lda = X_test * coeff;

% 实现1-NN分类器
num_test = size(X_test_lda, 1);
label_pred = zeros(num_test, 1);

for i = 1:num_test
    % 计算测试样本与所有训练样本的欧几里得距离
    distances = sqrt(sum((X_train_lda - X_test_lda(i, :)).^2, 2));
    
    % 找到最近邻的索引
    [~, nearest_index] = min(distances);
    
    % 预测标签
    label_pred(i) = label_train(nearest_index);
end

% 计算分类准确率
accuracy = sum(label_pred == label_test) / length(label_test);
fprintf('分类准确率: %.2f%%\n', accuracy * 100);

