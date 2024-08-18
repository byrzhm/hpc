#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <gmp.h>
#include <omp.h>

#define PREC 100008

int main() {
  mpz_t ans, base;
  unsigned long int k;
  char *res_str;

  mpz_init(ans);
  mpz_init(base);
  mpz_init_set_ui(base, 16);

  // spawn threads
  #pragma omp parallel
  {
    mpz_t a, b, c, d, denom;
    mpz_t v, tmp;
    mpz_t local_ans;

    mpz_init(a);
    mpz_init(b);
    mpz_init(c);
    mpz_init(d);
    mpz_init(denom);
    mpz_init(tmp);
    mpz_init(local_ans);
    mpz_set_ui(local_ans, 0);

    // distribute iterations
    #pragma omp for
    for (k = 0; k < PREC; ++k) {
      mpz_init_set_ui(v, PREC - k);
      mpz_pow_ui(tmp, base, mpz_get_ui(v));

      // Calculate a = tmp * 4 // (8 * k + 1)
      mpz_mul_ui(a, tmp, 4);
      mpz_set_ui(denom, 8 * k + 1);
      mpz_fdiv_q(a, a, denom); // Floor division

      // Calculate b = tmp * 2 // (8 * k + 4)
      mpz_mul_ui(b, tmp, 2);
      mpz_set_ui(denom, 8 * k + 4);
      mpz_fdiv_q(b, b, denom);

      // Calculate c = tmp // (8 * k + 5)
      mpz_set_ui(denom, 8 * k + 5);
      mpz_fdiv_q(c, tmp, denom);

      // Calculate d = tmp // (8 * k + 6)
      mpz_set_ui(denom, 8 * k + 6);
      mpz_fdiv_q(d, tmp, denom);

      // Update local_ans: local_ans += a - b - c - d
      mpz_sub(a, a, b);
      mpz_sub(a, a, c);
      mpz_sub(a, a, d);
      mpz_add(local_ans, local_ans, a);
    }

    #pragma omp critical
    mpz_add(ans, ans, local_ans);

    mpz_clear(local_ans);
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(c);
    mpz_clear(d);
    mpz_clear(denom);
    mpz_clear(tmp);
  }

  res_str = mpz_get_str(NULL, 16, ans);
  printf("%.*s\n", (int)strlen(res_str) - 8, res_str);
  free(res_str);

  mpz_clear(ans);
  mpz_clear(base);

  return 0;
}