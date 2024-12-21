#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <stdio.h>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

const int N = 2e5 + 100;

int n;
int h[N], e[N], ne[N], idx;
int d[N]; // 统计度
int dep[N], dep2[N], fdep[N];
int father[N];
int st[N];
int costn[N], timestamp;
int res[N];

void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }

void dfs(int u, int fa) {
  dep[u] = dep2[u] = n;

  bool flag = 0;
  for (int i = h[u]; ~i; i = ne[i]) {
    int j = e[i];
    if (j == fa || st[j])
      continue;

    flag = 1;
    dfs(j, u);

    if (dep[j] + 1 < dep[u])
      dep2[u] = dep[u], dep[u] = dep[j] + 1;
    else if (dep[j] + 1 < dep2[u])
      dep2[u] = dep[j] + 1;
  }

  if (!flag)
    dep[u] = 0;
  // if (d[u] == 1)
  //   dep[u] = 0;
  // // cout << " 111???" << u << " " << d[u] << " " << " " << dep[u] << "\n";
}

void dfs2(int u, int fa) {
  for (int i = h[u]; ~i; i = ne[i]) {
    int j = e[i];
    if (j == fa || st[j])
      continue;

    // 若换根的时候，换到了当初最小的一个
    if (dep[u] == dep[j] + 1) {
      fdep[j] = min(dep2[u] + 1, fdep[u] + 1);
    } else {
      fdep[j] = min(dep[u] + 1, fdep[u] + 1);
    }

    // cout << " >>>" << j << " " << fdep[j] << " " << dep[j] << "\n";

    dfs2(j, u);
  }
}

int getdep(int u) { return min(dep[u], fdep[u]); }

pii find(int u, int fa) {
  father[u] = fa;
  pii ans = {u, fa};

  if (fdep[u] > dep[u])
    for (int i = h[u]; ~i; i = ne[i]) {
      int j = e[i];
      if (j == fa || st[j])
        continue;
      if (ans.second == fa)
        ans.second = j;
      else if (dep[j] < dep[ans.second])
        ans.second = j;
    }

  for (int i = h[u]; ~i; i = ne[i]) {
    int j = e[i];
    if (j == fa || st[j])
      continue;

    pii tot = find(j, u);

    // 更新 dep
    if (getdep(tot.first) > getdep(ans.first))
      ans = tot;
  }
  return ans;
}

void dfs_ans(int u, int fa, int tot_id) {
  res[u] += costn[tot_id];

  for (int i = h[u]; ~i; i = ne[i]) {
    int j = e[i];
    if (j == fa || (st[j] && st[j] <= tot_id))
      continue;

    dfs_ans(j, u, tot_id);
  }
}

void work(int u, int type, int costid) {
  // 进行第一遍dfs，寻找到当前 u 的中点
  dfs(u, -1);
  // 先将 u 的 fdep 进行初始化值
  fdep[u] = n;
  // 进行换根dp，第二次dfs
  dfs2(u, -1);

  pii tot_info = find(u, -1);

  int mid = tot_info.first;
  int nx_node = tot_info.second;

  int tot_id = ++timestamp;
  st[mid] = tot_id;
  //
  // // 结束递归
  // if (nx_node == -1)
  //   return;

  printf("---> %d %d\n", mid, nx_node);
  printf("??? %d %d\n", costid, tot_id);
  costn[costid]++;
  costn[tot_id]--;

  {
    for (int i = h[mid]; ~i; i = ne[i]) {
      int j = e[i];
      if (st[j])
        continue;

      if (j == nx_node) {
        work(j, 0, tot_id);
      } else {
        work(j, 1, tot_id);
      }
    }
  }

  if (type)
    costn[costid] += costn[tot_id] + 1, cout << "..." << costid << " " << tot_id
                                             << " " << costn[tot_id] << endl;
  // costn 代表当前子树 nx_node 子树的信息

  dfs_ans(nx_node, -1, tot_id);
}

int main() {
  memset(h, -1, sizeof h);

  scanf("%d", &n);

  for (int i = 1; i <= n - 1; i++) {
    int a, b;
    scanf("%d%d", &a, &b);

    d[a]++, d[b]++;
    add(a, b), add(b, a);
  }

  // 进行 dfs
  // 思路反过来，看每个点对于其他点的总贡献。
  // 先找到到所有根结点最短的结点，然后通过这个点进行分治
  // 分成最短的子树，和非最短子树
  // 这里先将非最短子树的贡献加上
  // 最短子树的贡献，这个最短子树可以直接分成子问题
  // 对于剩下的非最短子树，虽然也是子问题，但是加贡献的时候要加上这个全部

  work(1, 0, 0);

  for (int i = 1; i <= n; i++) {
    if (d[i] == 1)
      printf("%d\n", 1);
    else
      printf("%d\n", res[i] + costn[0]);
  }
  return 0;
}
