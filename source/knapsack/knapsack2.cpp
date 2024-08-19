#include <cstdio>
#include <omp.h>
#include <vector>

int knapsack(int W, const std::vector<int> &w, const std::vector<int> &v) {
  int N = w.size();
  std::vector<int> dp0(W + 1);
  std::vector<int> dp1(W + 1);
  for (int i = 0; i < N; i++) {
    #pragma omp parallel for
    for (int j = W; j >= w[i]; j--) {
      dp1[j] = std::max(dp0[j], dp0[j - w[i]] + v[i]);
    }

    #pragma omp parallel for
    for (int j = 0; j < w[i]; j++) {
      dp1[j] = dp0[j];
    }

    dp0.swap(dp1);
  }
  return dp0[W];
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