#include <gtest.h>
#include "HashTableC.h"

TEST(HashTable, InsertAndSearch) {
    HashTable ht(10);
    Polinom p1("4x^5y^9z^8+2x^3y^4z^5"), p2("4x^5y^9z^8+2x^3y^4z^5");

    ht.Insert("key1", p1);
    ht.Insert("key2", p2);

    EXPECT_NO_THROW(ht.Find("key1"));
    EXPECT_NO_THROW(ht.Find("key2"));
}

TEST(HashTable, UpdateValue) {
    HashTable ht(10);
    Polinom p1("4x^5y^9z^8+2x^3y^4z^5"), p2("4x^5y^9z^8+2x^3y^4z^5");

    ht.Insert("key", p1);
    ht.Insert("key", p2); // Обновление

    EXPECT_TRUE(ht.Find("key") == p2);
}

TEST(HashTable, RemoveKey) {
    HashTable ht(10);
    Polinom p("4x^5y^9z^8+2x^3y^4z^5");

    ht.Insert("key", p);
    ht.Delete("key");

    EXPECT_THROW(ht.Find("key"), std::out_of_range);
}

TEST(HashTable, HandleCollisions) {
    HashTable ht(2); // Маленькая таблица для коллизий
    Polinom p1("4x^5y^9z^8+2x^3y^4z^5"), p2("4x^5y^9z^8+2x^3y^4z^5"), p3("4x^5y^9z^8+2x^3y^4z^5");

    ht.Insert("a", p1);
    ht.Insert("b", p2);
    ht.Insert("c", p3);

    EXPECT_NO_THROW(ht.Find("a"));
    EXPECT_NO_THROW(ht.Find("b"));
    EXPECT_NO_THROW(ht.Find("c"));
}

TEST(HashTable, SearchNonExistent) {
    HashTable ht(10);
    EXPECT_THROW(ht.Find("ghost_key"), std::out_of_range);
}

TEST(HashTable, SpecialKeys) {
    HashTable ht(100);
    Polinom p("4x^5y^9z^8+2x^3y^4z^5");

    ht.Insert("", p); // Пустой ключ
    ht.Insert("!@#$%", p); // Спецсимволы
    ht.Insert("длинный_ключ_с_unicode_символами_😊", p);

    EXPECT_NO_THROW(ht.Find(""));
    EXPECT_NO_THROW(ht.Find("!@#$%"));
}

TEST(HashTable, CapacityOne) {
    HashTable ht(1);
    Polinom p1("4x^5y^9z^8+2x^3y^4z^5"), p2("4x^5y^9z^8+2x^3y^4z^5");

    ht.Insert("first", p1);
    ht.Insert("second", p2);

    EXPECT_NO_THROW(ht.Find("first"));
    EXPECT_NO_THROW(ht.Find("second"));
}

TEST(HashTable, RemoveFromEmpty) {
    HashTable ht(10);
    EXPECT_NO_THROW(ht.Delete("non_existent"));
}

TEST(HashTable, RehashStress) {
    HashTable ht(10);
    Polinom p("4x^5y^9z^8+2x^3y^4z^5");

    // Вставка 1000 элементов
    for (int i = 0; i < 1000; ++i) {
        ht.Insert("key" + std::to_string(i), p);
    }

    // Проверка всех элементов
    for (int i = 0; i < 1000; ++i) {
        EXPECT_NO_THROW(ht.Find("key" + std::to_string(i)));
    }
}

TEST(HashTable, InsertMillionElements) {
    HashTable t1(1000000);

    Polinom p1("4x^5y^9z^8+2x^3y^4z^5");
    const int million = 1000000;

    for (int i = 0; i < million; i++) {
        t1.Insert(to_string(i), p1);
        if (i % 100000 == 0) cout << i << "\n";
    }
}

TEST(HashTable, InsertDeleteManyElements) {
    const int many = 100000;
    HashTable h1(many);
    Polinom p1("4x^5y^9z^8+2x^3y^4z^5");


    for (int i = 0; i < many; i++) {
        h1.Insert(to_string(i), p1);
        if (i % 1000 == 0) cout << i << "\n";
    }
    for (int i = 0; i < many; i++) {
        h1.Delete(to_string(i));
        if (i % 1000 == 0) cout << many - i << "\n";
    }
}