#include <cstdio>
#include <vector>

int knapsack(int W, const std::vector<int> &w, const std::vector<int> &v) {
  int N = w.size();
  std::vector<std::vector<int>> dp(N + 1, std::vector<int>(W + 1, 0));
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= W; j++) {
      if (j < w[i - 1]) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
      }
    }
  }
  return dp[N][W];
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