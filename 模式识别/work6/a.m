
% 从数据中读取X 变量
load('data1.mat', 'X');

% 设置聚类个数
k = 5

% 随机化mus
pkg load statistics
Sigma = [1, 0; 0, 1];
mu = [1, -1]; 
mus = mvnrnd(mu, Sigma, k);

function [mus, points_clusting] = kmeans(mus, points)

    % 固定 mu 更新所有的points
    points_nr = length(points) ;
    points_clusting = zeros(points_nr, 1);

    for idx = 1:points_nr
        % 计算 idx 这个点与所有 mus的距离
        distances = sqrt(sum((mus - points(idx, :)).^2, 2));

        % 找到最近的mus
        [~, nearest_index] = min(distances);

        points_clusting(idx) =  nearest_index;
    end

    % 利用聚类更新出新的mus
    mus_nr = length(mus) ;

    for idx = 1:mus_nr
        point_tot = points(points_clusting == idx,:) ;

        mus(idx, :) = mean(point_tot) ;
    end
end

points = X ;
epsilon = 0.00001 ;

% 开始训练
for i = 1:100
    pre_mus = mus ;
    [mus, points_clusting] = kmeans(mus, points) ;

    if norm(mus - pre_mus) < epsilon
        break;  % 聚类中心的变化很小，算法结束
    end
end

% 报告聚类精度，聚类中心，计算聚类中心与真实分布的均值之间的误差

disp('聚类精度：') ;

jingdu = 0 ;

for i = 1:5
    si = (i - 1) * 200 + 1 ;
    end_index = i * 200 ;

    segment = points_clusting(si :end_index) ;

    [counts, unique_elements] = hist(segment, unique(segment));
    
    jingdu += max(counts);
end

jingdu /= 1000 ;

jingdu

mus

% 真实的聚类中心
mu1 = [1, -1]; 
mu2 = [5.5, -4.5];
mu3 = [1, 4]; 
mu4 = [6, 4.5]; 
mu5 = [9, 0.0];
real_mus = [mu1; mu2; mu3; mu4; mu5];

real_mus = sort(real_mus) ;
mus = sort(mus) ;

errors = zeros(size(real_mus, 1), 1);  % 存储每对聚类中心之间的误差

for i = 1:size(real_mus, 1)
    % 计算第 i 对聚类中心之间的欧氏距离
    errors(i) = norm(real_mus(i, :) - mus(i, :));
end

disp('计算出的聚类中心与对应的真实分布均值之间的误差');
errors


colors = ['r', 'g', 'b', 'c', 'm', 'y'];
% 画出图
for i = 1:k
    point_tot = points(points_clusting == i,:) ;
    plot(point_tot(:,1), point_tot(:,2), '.', 'Color', colors(mod(i-1, length(colors)) + 1));
    hold on ;
end

uiwait(gcf);
