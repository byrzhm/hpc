---
layout: default
--- 

# GMP

> - [The GNU Multiple Precision Arithmetic Library](https://rocm.docs.amd.com/projects/HIP/en/latest/)

## 安装
    
1. 首先下载源文件。
```sh
wget https://gmplib.org/download/gmp/gmp-6.3.0.tar.xz
```

2. 解压tarball。
```sh
tar -xf gmp-6.3.0.tar.xz
```

3. 配置构建过程
```sh
cd gmp-6.3.0
./configure --prefix=$HOME/gmp # 因为没有 root 权限，只好安装到这
```

4. 编译 & 安装
```sh
make -j$(nproc) && make install
```

## 测试程序 - `gmp_test.c`

```c
#include <stdio.h>
#include <gmp.h>

int main() {
    // Initialize GMP variables
    mpz_t a, b, sum, difference, product, quotient;
    
    mpz_init(a);
    mpz_init(b);
    mpz_init(sum);
    mpz_init(difference);
    mpz_init(product);
    mpz_init(quotient);

    // Set values for a and b
    mpz_set_str(a, "123456789012345678901234567890", 10);
    mpz_set_str(b, "987654321098765432109876543210", 10);

    // Perform arithmetic operations
    mpz_add(sum, a, b);
    mpz_sub(difference, a, b);
    mpz_mul(product, a, b);
    if (mpz_cmp_ui(b, 0) != 0) {
        mpz_tdiv_q(quotient, a, b);
    } else {
        gmp_printf("Division by zero is not allowed.\n");
    }

    // Print results
    gmp_printf("a = %Zd\n", a);
    gmp_printf("b = %Zd\n", b);
    gmp_printf("a + b = %Zd\n", sum);
    gmp_printf("a - b = %Zd\n", difference);
    gmp_printf("a * b = %Zd\n", product);
    gmp_printf("a / b = %Zd\n", quotient);

    // Clear GMP variables
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(sum);
    mpz_clear(difference);
    mpz_clear(product);
    mpz_clear(quotient);

    return 0;
}
```
