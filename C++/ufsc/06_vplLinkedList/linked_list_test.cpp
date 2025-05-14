/*
g++ -std=c++17 -o test linked_list_test.cpp \
    -I/opt/homebrew/Cellar/googletest/1.16.0/include \
    -L/opt/homebrew/Cellar/googletest/1.16.0/lib \
    -lgtest -lgtest_main -pthread && ./test
 */

#include "gtest/gtest.h"
#include "linked_list.h"

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class LinkedListTest: public ::testing::Test {
protected:
    structures::LinkedList<int> list{};
};


TEST_F(LinkedListTest, BasicPushBack) {
    list.push_back(0);
    ASSERT_EQ(1u, list.size());
    ASSERT_EQ(0, list.at(0));

    list.push_back(-1);
    ASSERT_EQ(2u, list.size());
    ASSERT_EQ(0, list.at(0));
    ASSERT_EQ(-1, list.at(1));
}

TEST_F(LinkedListTest, PushBack) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }

    ASSERT_EQ(10u, list.size());

    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_EQ(i, list.at(i));
    }
}

TEST_F(LinkedListTest, BasicPushFront) {
    list.push_front(0);
    ASSERT_EQ(1u,list.size());
    ASSERT_EQ(0, list.at(0));

    list.push_front(-1);
    ASSERT_EQ(2u, list.size());
    ASSERT_EQ(-1, list.at(0));
    ASSERT_EQ(0, list.at(1));
}

TEST_F(LinkedListTest, PushFront) {
    for (auto i = 0; i < 10; ++i) {
        list.push_front(i);
    }

    ASSERT_EQ(10u, list.size());
    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_EQ(9-i, list.at(i));
    }
}

TEST_F(LinkedListTest, Empty) {
    ASSERT_TRUE(list.empty());
}

TEST_F(LinkedListTest, NotEmpty) {
    ASSERT_TRUE(list.empty());
    list.push_back(1);
    ASSERT_FALSE(list.empty());
}

TEST_F(LinkedListTest, Clear) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    list.clear();
    ASSERT_EQ(0u, list.size());
}

TEST_F(LinkedListTest, Find) {
    for (auto i = 0u; i < 10u; ++i) {
        list.push_back(i);
    }

    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_EQ(i, list.find(i));
    }
    ASSERT_EQ(list.size(), list.find(10));
}

TEST_F(LinkedListTest, Contains) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    ASSERT_TRUE(list.contains(0));
    ASSERT_TRUE(list.contains(5));
    ASSERT_FALSE(list.contains(10));
}

TEST_F(LinkedListTest, AccessAt) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_EQ(i, list.at(i));
    }
    list.clear();
    for (auto i = 10; i > 0; --i) {
        list.push_back(i);
    }
    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_EQ(10-i, list.at(i));
    }
}

TEST_F(LinkedListTest, AccessAtBoundCheck) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    for (auto i = 0; i < 10; ++i) {
        ASSERT_NO_THROW(list.at(i));
    }
    ASSERT_NO_THROW(list.at(0));
    ASSERT_THROW(list.at(-1), std::out_of_range);
}

TEST_F(LinkedListTest, Insert) {
    for (auto i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    for (auto i = 6; i < 10; ++i) {
        list.push_back(i);
    }
    list.insert(5, 5u);

    for (auto i = 0; i < 10; ++i) {
        ASSERT_EQ(i, list.at(i));
    }
}

TEST_F(LinkedListTest, InsertInOrder) {
    for (auto i = 9; i >= 0; --i) {
        list.insert_sorted(i);
    }
    for (auto i = 0; i < 10; ++i) {
        ASSERT_EQ(i, list.at(i));
    }

    list.clear();

    list.insert_sorted(10);
    list.insert_sorted(-10);
    list.insert_sorted(42);
    list.insert_sorted(0);
    ASSERT_EQ(-10, list.at(0));
    ASSERT_EQ(0, list.at(1));
    ASSERT_EQ(10, list.at(2));
    ASSERT_EQ(42, list.at(3));
}

TEST_F(LinkedListTest, InsertionBounds) {
    ASSERT_THROW(list.insert(1u, 1), std::out_of_range);
    ASSERT_THROW(list.insert(-1, 1), std::out_of_range);
}

TEST_F(LinkedListTest, EmptyPopBack) {
    ASSERT_THROW(list.pop_back(), std::out_of_range);
}

TEST_F(LinkedListTest, PopBack) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    for (auto i = 9; i >= 0; --i) {
        ASSERT_EQ(i, list.pop_back());
    }
    ASSERT_TRUE(list.empty());
}

TEST_F(LinkedListTest, EmptyPopFront) {
    ASSERT_THROW(list.pop_front(), std::out_of_range);
}

TEST_F(LinkedListTest, PopFront) {
    for (auto i = 9; i >= 0; --i) {
        list.push_front(i);
    }
    for (auto i = 0; i < 10; ++i) {
        ASSERT_EQ(i, list.pop_front());
    }
    ASSERT_TRUE(list.empty());
}

TEST_F(LinkedListTest, PopAt) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    ASSERT_EQ(5, list.pop(5));
    ASSERT_EQ(6, list.pop(5));
    ASSERT_EQ(8u, list.size());
    ASSERT_THROW(list.pop(8), std::out_of_range);
}

TEST_F(LinkedListTest, RemoveElement) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    list.remove(4);
    ASSERT_EQ(9u, list.size());
    ASSERT_FALSE(list.contains(4));
}

// TESTES PARA NOVAS FUNÇÕES

TEST_F(LinkedListTest, Clone) {
    for (int i = 1; i <= 5; ++i) {
        list.push_back(i);
    }

    auto cloned = list.clone();
    ASSERT_EQ(list.size(), cloned.size());

    for (std::size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list.at(i), cloned.at(i));
    }

    // Modificar lista original não deve afetar o clone
    list.pop_back();
    ASSERT_NE(list.size(), cloned.size());
}

TEST_F(LinkedListTest, Invert) {
    for (int i = 1; i <= 5; ++i) {
        list.push_back(i);  // [1, 2, 3, 4, 5]
    }
    list.invert();          // Esperado: [5, 4, 3, 2, 1]

    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(5 - i, list.at(i));
    }
}

TEST_F(LinkedListTest, SlicingDefaultStep) {
    for (int i = 1; i <= 6; ++i) {
        list.push_back(i);  // [1, 2, 3, 4, 5, 6]
    }

    auto slice = list.slicing(1, 5, 1);  // Esperado: [2, 3, 4, 5]
    ASSERT_EQ(4u, slice.size());
    ASSERT_EQ(2, slice.at(0));
    ASSERT_EQ(5, slice.at(3));
}

TEST_F(LinkedListTest, SlicingWithStep) {
    for (int i = 1; i <= 10; ++i) {
        list.push_back(i);  // [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    }

    auto slice = list.slicing(0, 10, 2);  // Esperado: [1, 3, 5, 7, 9]
    ASSERT_EQ(5u, slice.size());
    ASSERT_EQ(1, slice.at(0));
    ASSERT_EQ(9, slice.at(4));
}
/*
TEST_F(LinkedListTest, Halve) {
    for (int i = 1; i <= 6; ++i) {
        list.push_back(i);  // [1, 2, 3, 4, 5, 6]
    }

    auto second_half = list.halve();  // lista = [1, 2, 3]; second_half = [4, 5, 6]
    ASSERT_EQ(3u, list.size());
    ASSERT_EQ(3u, second_half.size());

    ASSERT_EQ(1, list.at(0));
    ASSERT_EQ(4, second_half.at(0));
}


TEST_F(LinkedListTest, Append) {
    for (int i = 1; i <= 3; ++i) {
        list.push_back(i);  // [1, 2, 3]
    }

    structures::LinkedList<int> extra;
    for (int i = 4; i <= 6; ++i) {
        extra.push_back(i);  // [4, 5, 6]
    }

    list.append(extra);  // Esperado: [1, 2, 3, 4, 5, 6]
    ASSERT_EQ(6u, list.size());

    for (int i = 0; i < 6; ++i) {
        ASSERT_EQ(i + 1, list.at(i));
    }

    ASSERT_TRUE(extra.empty());  // A lista extra deve estar vazia após o append
}
*/
