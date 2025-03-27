/*
g++ -o test withGoogleTest.cpp \
    -I/opt/homebrew/Cellar/googletest/1.16.0/include \
    -L/opt/homebrew/Cellar/googletest/1.16.0/lib \
    -lgtest -lgtest_main -pthread && ./test
    
*/
#include <gtest/gtest.h>

// Função a ser testada
int soma(int a, int b) {
    return a + b;
}

// Teste unitário
TEST(SomaTest, TestaValores) {
    EXPECT_EQ(soma(2, 3), 5);
    EXPECT_EQ(soma(-1, 1), 0);
    EXPECT_NE(soma(2, 2), 5); // Deve ser diferente de 5
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
