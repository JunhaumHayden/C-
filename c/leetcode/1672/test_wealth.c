/*
gcc -o test_wealth test_wealth.c -I/opt/homebrew/include -L/opt/homebrew/lib -lcmocka && ./test_wealth
*/
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "1672.c"  // Incluímos a implementação para teste

// Teste 1: Matriz [[1,2,3], [3,2,1]] deve retornar 6
static void test_case_1(void **state) {
    (void) state;  // Evita warning de parâmetro não utilizado

    int row1[] = {1, 2, 3};
    int row2[] = {3, 2, 1};

    int* accounts[] = {row1, row2};
    int accountsColSize[] = {3, 3};
    
    int result = maximumWealth(accounts, 2, accountsColSize);
    assert_int_equal(result, 6);
}

// Teste 2: Matriz [[1,5], [7,3], [3,5]] deve retornar 10
static void test_case_2(void **state) {
    (void) state;

    int row1[] = {1, 5};
    int row2[] = {7, 3};
    int row3[] = {3, 5};

    int* accounts[] = {row1, row2, row3};
    int accountsColSize[] = {2, 2, 2};
    
    int result = maximumWealth(accounts, 3, accountsColSize);
    assert_int_equal(result, 10);
}

// Teste 3: Matriz [[2,8,7], [7,1,3], [1,9,5]] deve retornar 17
static void test_case_3(void **state) {
    (void) state;

    int row1[] = {2, 8, 7};
    int row2[] = {7, 1, 3};
    int row3[] = {1, 9, 5};

    int* accounts[] = {row1, row2, row3};
    int accountsColSize[] = {3, 3, 3};
    
    int result = maximumWealth(accounts, 3, accountsColSize);
    assert_int_equal(result, 17);
}

// Função principal que executa os testes
int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_case_1),
        cmocka_unit_test(test_case_2),
        cmocka_unit_test(test_case_3),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
