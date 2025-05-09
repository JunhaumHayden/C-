/* Copyright [2016] <João Paulo Taylor Ienczak Zanette>
   Copyright [2021] <Andre Zanghelini>: MemoryManipulation */

   #include "gtest/gtest.h"
   #include "./array_queue.h"
   
   int main(int argc, char* argv[]) {
       std::srand(std::time(NULL));
       ::testing::InitGoogleTest(&argc, argv);
       return RUN_ALL_TESTS();
   }
   
   //! COmment
   class ArrayQueueTest: public ::testing::Test {
    protected:
   //! queue
     structures::ArrayQueue<int> queue{10u};
   };
   
   
   TEST_F(ArrayQueueTest, Enqueue) {
       queue.enqueue(0);
       ASSERT_EQ(1u, queue.size());
       ASSERT_EQ(0, queue.back());
   
       queue.enqueue(2);
       ASSERT_EQ(2, queue.back());
       queue.enqueue(-1);
       ASSERT_EQ(-1, queue.back());
       ASSERT_EQ(3u, queue.size());
   }
   
   TEST_F(ArrayQueueTest, Dequeue) {
       for (auto i = 0; i < 10; ++i) {
           queue.enqueue(i);
       }
   
       for (auto i = 0; i < 10; ++i) {
           ASSERT_EQ(i, queue.dequeue());
       }
       ASSERT_TRUE(queue.empty());
   }
   
   TEST_F(ArrayQueueTest, ClearQueue) {
       for (auto i = 0; i < 10; ++i) {
           queue.enqueue(i);
       }
       queue.clear();
       ASSERT_EQ(0u, queue.size());
   }
   
   TEST_F(ArrayQueueTest, EmptyQueue) {
       ASSERT_TRUE(queue.empty());
       ASSERT_THROW(queue.back(), std::out_of_range);
   }
   
   TEST_F(ArrayQueueTest, NotEmptyQueue) {
       ASSERT_TRUE(queue.empty());
       queue.enqueue(1);
       ASSERT_FALSE(queue.empty());
       queue.clear();
       ASSERT_TRUE(queue.empty());
       ASSERT_THROW(queue.back(), std::out_of_range);
       ASSERT_THROW(queue.dequeue(), std::out_of_range);
   }
   
   TEST_F(ArrayQueueTest, FullQueue) {
       ASSERT_FALSE(queue.full());
       for (auto i = 0; i < static_cast<int>(queue.max_size()); ++i) {
           queue.enqueue(i);
       }
       ASSERT_EQ(queue.max_size(), queue.size());
       ASSERT_TRUE(queue.full());
       ASSERT_THROW(queue.enqueue(0), std::out_of_range);
   }
   
   // public domain
   TEST_F(ArrayQueueTest, MemoryManipulation) {
       queue.clear();
       ASSERT_TRUE(queue.empty());
       for (auto i = 0; i < static_cast<int>(queue.max_size()); ++i) {
           queue.enqueue(i);
       }
       queue.dequeue();
       queue.enqueue(99);
       ASSERT_EQ(queue.back(), 99); // circularidade errada deve falhar aqui
       queue.dequeue();
       // core dump se nao cuidar dos indices (necessario varios porque poucos podem passar)
       for (auto i = 0; i < 2*static_cast<int>(queue.max_size()); ++i) {
           queue.enqueue(1);
           queue.dequeue();
       }
   }