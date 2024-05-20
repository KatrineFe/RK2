#include <gtest/gtest.h>
#include <iostream>
#include <thread>
#include <vector>

// Подключение основного файла singleton.cpp
#include "singleton.cpp"

// Тест на создание единственного экземпляра без использования потоков
TEST(SingletonTest, SingleInstanceWithoutThreads) {
    Singleton* sgn1 = Singleton::getInstance();
    Singleton* sgn2 = Singleton::getInstance();
    ASSERT_EQ(sgn1, sgn2);
}

// Тест на потокобезопасность
TEST(SingletonTest, ThreadSafety) {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([]() {
            Singleton::getInstance();
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    Singleton* sgn1 = Singleton::getInstance();
    Singleton* sgn2 = Singleton::getInstance();
    ASSERT_EQ(sgn1, sgn2);
}

// Тест на создание нескольких экземпляров без обеспечения потокобезопасности
TEST(SingletonTest, MultipleInstancesWithoutThreadSafety) {
    Singleton* sgn1 = Singleton::getInstance();
    Singleton* sgn2 = nullptr;
    Singleton* sgn3 = nullptr;

    std::thread t1([&]() {
        sgn2 = new Singleton();
    });

    std::thread t2([&]() {
        sgn3 = new Singleton();
    });

    t1.join();
    t2.join();

    ASSERT_NE(sgn1, sgn2);
    ASSERT_NE(sgn1, sgn3);
    ASSERT_NE(sgn2, sgn3);
}

