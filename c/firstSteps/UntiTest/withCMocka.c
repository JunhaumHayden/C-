/*
Comando para executar o teste com cmocka:
gcc -o test withCmoka.c -I/opt/homebrew/include -L/opt/homebrew/lib -lcmocka && ./test
*/

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

int soma(int a, int b) {
    return a + b;
}

static void test_soma(void **state) {
    assert_int_equal(soma(2, 3), 5);
    assert_int_equal(soma(-1, 1), 0);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_soma),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
