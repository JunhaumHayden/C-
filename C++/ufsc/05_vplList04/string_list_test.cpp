//  "Copyright [2018] <Alexandre Goncalves Silva> (rev. nov2021)"
/*
g++ -std=c++17 -o test string_list_test.cpp \
    -I/opt/homebrew/Cellar/googletest/1.16.0/include \
    -L/opt/homebrew/Cellar/googletest/1.16.0/lib \
    -lgtest -lgtest_main -pthread && ./test
 */

#include "gtest/gtest.h"
#include "./string_list1.h"

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//! Comment
class ArrayListStringTest: public ::testing::Test {
 protected:
  //! Comment
  structures::ArrayListString list{10u};
};


TEST_F(ArrayListStringTest, BasicPushBack) {
    list.push_back("Palhoca");
    ASSERT_EQ(1u, list.size());
    ASSERT_STREQ("Palhoca", list[0]);

    list.push_back("Sao_Jose");
    ASSERT_EQ(2u, list.size());
    ASSERT_STREQ("Palhoca", list[0]);
    ASSERT_STREQ("Sao_Jose", list[1]);
}

TEST_F(ArrayListStringTest, PushBack) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 0; i < 10; ++i) {
        list.push_back(city[i]);
    }

    ASSERT_EQ(10u, list.size());

    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_STREQ(city[i], list[i]);
    }
}

TEST_F(ArrayListStringTest, BasicPushFront) {
    list.push_front("Chapeco");
    ASSERT_EQ(1u, list.size());
    ASSERT_STREQ("Chapeco", list[0]);

    list.push_front("Blumenau");
    ASSERT_EQ(2u, list.size());
    ASSERT_STREQ("Blumenau", list[0]);
    ASSERT_STREQ("Chapeco", list[1]);
}

TEST_F(ArrayListStringTest, PushFront) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 0; i < 10; ++i) {
        list.push_front(city[i]);
    }

    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_STREQ(city[9-i], list[i]);
    }
}

TEST_F(ArrayListStringTest, PushFrontBoundCheck) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 0; i < 10; ++i) {
        list.push_front(city[i]);
    }
    ASSERT_THROW(list.push_front("11"), std::out_of_range);
}

TEST_F(ArrayListStringTest, Empty) {
    ASSERT_TRUE(list.empty());
}

TEST_F(ArrayListStringTest, NotEmpty) {
    ASSERT_TRUE(list.empty());
    list.push_back("Sao_Jose");
    ASSERT_FALSE(list.empty());
}

TEST_F(ArrayListStringTest, Full) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 0; i < 10; ++i) {
        list.push_back(city[i]);
    }
    ASSERT_EQ(10u, list.size());
    ASSERT_THROW(list.push_back("Brusque"), std::out_of_range);
}

TEST_F(ArrayListStringTest, Clear) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 0; i < 10; ++i) {
        list.push_back(city[i]);
    }
    list.clear();
    ASSERT_EQ(0u, list.size());
}

TEST_F(ArrayListStringTest, Find) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 0u; i < 10u; ++i) {
        list.push_back(city[i]);
    }

    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_EQ(i, list.find(city[i]));
    }
    ASSERT_EQ(list.size(), list.find("Brusque"));
}

TEST_F(ArrayListStringTest, Contains) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 0; i < 10; ++i) {
        list.push_back(city[i]);
    }
    ASSERT_TRUE(list.contains("Blumenau"));
    ASSERT_TRUE(list.contains("Jaragua_do_Sul"));
    ASSERT_FALSE(list.contains("Brusque"));
}

TEST_F(ArrayListStringTest, AccessAt) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 0; i < 10; ++i) {
        list.push_back(city[i]);
    }
    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_STREQ(city[i], list.at(i));
    }
    list.clear();
    for (auto i = 9; i >= 0; --i) {
        list.push_back(city[i]);
    }
    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_STREQ(city[9-i], list.at(i));
    }
}

TEST_F(ArrayListStringTest, AccessAtBoundCheck) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 0; i < 10; ++i) {
        list.push_back(city[i]);
    }
    for (auto i = 0; i < 10; ++i) {
        ASSERT_NO_THROW(list.at(i));
    }
    ASSERT_NO_THROW(list.at(0));
    ASSERT_THROW(list.at(-1), std::out_of_range);
}

TEST_F(ArrayListStringTest, Insert) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 0; i < 5; ++i) {
        list.push_back(city[i]);
    }
    for (auto i = 6; i < 10; ++i) {
        list.push_back(city[i]);
    }
    list.insert(city[5], 5u);

    for (auto i = 0; i < 10; ++i) {
        ASSERT_STREQ(city[i], list[i]);
    }
}

TEST_F(ArrayListStringTest, InsertInOrder) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 9; i >= 0; --i) {
        list.insert_sorted(city[i]);
    }
    for (auto i = 0; i < 10; ++i) {
        ASSERT_STREQ(city[i], list[i]);
    }

    list.clear();

    list.insert_sorted("10");
    list.insert_sorted("-10");
    list.insert_sorted("42");
    list.insert_sorted("0");
    ASSERT_STREQ("-10", list[0]);
    ASSERT_STREQ("0", list[1]);
    ASSERT_STREQ("10", list[2]);
    ASSERT_STREQ("42", list[3]);
}

TEST_F(ArrayListStringTest, InsertionBounds) {
    ASSERT_THROW(list.insert("1", 10), std::out_of_range);
    ASSERT_THROW(list.insert("1", -1), std::out_of_range);
}

TEST_F(ArrayListStringTest, EmptyPopBack) {
    ASSERT_THROW(list.pop_back(), std::out_of_range);
}

TEST_F(ArrayListStringTest, PopBack) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 0; i < 10; ++i) {
        list.push_back(city[i]);
    }
    for (auto i = 9; i >= 0; --i) {
        char *tmp = list.pop_back();
        ASSERT_STREQ(city[i], tmp);
        delete [] tmp;
    }
    ASSERT_TRUE(list.empty());
    ASSERT_EQ(0u, list.size());
}

TEST_F(ArrayListStringTest, EmptyPopFront) {
    ASSERT_THROW(list.pop_front(), std::out_of_range);
}

TEST_F(ArrayListStringTest, PopFront) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 9; i >= 0; --i) {
        list.push_front(city[i]);
    }
    for (auto i = 0; i < 10; ++i) {
        char *tmp = list.pop_front();
        ASSERT_STREQ(city[i], tmp);
        delete [] tmp;
    }
    ASSERT_TRUE(list.empty());
    ASSERT_EQ(0u, list.size());
}

TEST_F(ArrayListStringTest, PopAt) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 0; i < 10; ++i) {
        list.push_back(city[i]);
    }
    char *tmp;
    tmp = list.pop(5);
    ASSERT_STREQ(city[5], tmp);
    delete [] tmp;
    tmp = list.pop(5);
    ASSERT_STREQ(city[6], tmp);
    delete [] tmp;
    ASSERT_EQ(8u, list.size());
    ASSERT_THROW(list.pop(8), std::out_of_range);
}

TEST_F(ArrayListStringTest, RemoveElement) {
    const char *city[10] = {"Blumenau", "Chapeco", "Criciuma", \
    "Florianopolis", "Itajai", "Jaragua_do_Sul", "Joinville", \
    "Lages", "Palhoca", "Sao_Jose"};
    for (auto i = 0; i < 10; ++i) {
        list.push_back(city[i]);
    }
    list.remove(city[4]);
    ASSERT_EQ(9u, list.size());
    ASSERT_FALSE(list.contains(city[4]));
}
