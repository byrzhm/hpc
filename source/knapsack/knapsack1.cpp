#include <cstdio>
#include <vector>

int knapsack(int W, const std::vector<int> &w, const std::vector<int> &v) {
  int N = w.size();
  std::vector<int> dp(W + 1);
  for (int i = 0; i < N; i++) {
    for (int j = W; j >= w[i]; j--) {
      dp[j] = std::max(dp[j], dp[j - w[i]] + v[i]);
    }
  }
  return dp[W];
}

int main(int argc, char *argv[]) {
  int N, W;
  scanf("%d %d", &N, &W);
  std::vector<int> w(N), v(N);
  for (int i = 0; i < N; i++) {
    scanf("%d %d", &w[i], &v[i]);
  }
  printf("%d\n", knapsack(W, w, v));
  return 0;
}