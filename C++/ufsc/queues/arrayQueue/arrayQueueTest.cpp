/*
g++ -std=c++17 -o test arrayQueueTest.cpp \
    -I/opt/homebrew/Cellar/googletest/1.16.0/include \
    -L/opt/homebrew/Cellar/googletest/1.16.0/lib \
    -lgtest -lgtest_main -pthread && ./test
*/

#include "genArrayQueue.h"
#include <gtest/gtest.h>

// Teste para verificar se a fila começa vazia
TEST(ArrayQueueTest, IsEmptyInitially) {
    ArrayQueue<int> queue;
    EXPECT_TRUE(queue.isEmpty());
}

// Teste para adicionar um elemento e verificar se não está vazia
TEST(ArrayQueueTest, Enqueue) {
    ArrayQueue<int> queue;
    queue.enqueue(10);
    EXPECT_FALSE(queue.isEmpty());
}

// Teste para remover um elemento e verificar se a fila volta a ficar vazia
TEST(ArrayQueueTest, Dequeue) {
    ArrayQueue<int> queue;
    queue.enqueue(20);
    int value = queue.dequeue();
    EXPECT_EQ(value, 20);
    EXPECT_TRUE(queue.isEmpty());
}

// Teste para verificar a exceção ao tentar remover de uma fila vazia
TEST(ArrayQueueTest, DequeueEmptyQueueThrows) {
    ArrayQueue<int> queue;
    EXPECT_THROW(queue.dequeue(), std::out_of_range);
}

// Teste para verificar se a fila cheia gera exceção
TEST(ArrayQueueTest, EnqueueFullQueueThrows) {
    ArrayQueue<int, 2> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    EXPECT_THROW(queue.enqueue(3), std::out_of_range);
}

// Função principal do GoogleTest
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
