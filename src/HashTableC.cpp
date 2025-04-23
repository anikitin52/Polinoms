#include "HashTableC.h"

size_t HashTable::stringToNumber(const std::string& key) const
{
    const size_t base = 31; 
    size_t hash = 0;
    for (char c : key) {
        hash = (hash * base + static_cast<unsigned char>(c)) % p;
    }
    return hash;
}

size_t HashTable::hash(string key)
{
    size_t x = stringToNumber(key);
    return ((a * x + b) % p) % capacity;
}


HashTable::HashTable(int size = 10): capacity(size), data(size)
{
    // Генерация случайных a и b
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(1, p - 1);

    a = dist(gen);
    b = dist(gen);

    // Гарантируем, что a != 0
    if (a == 0) a = 1;
}

void HashTable::Insert(string key, Polinom value)
{
    size_t index = hash(key);
    for (auto& pair : data[index]) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    data[index].emplace_back(key, value);
}

void HashTable::Delete(string key)
{
    size_t index = hash(key);
    auto& chain = data[index];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (it->first == key) {
            chain.erase(it);
            return;
        }
    }
}

Polinom HashTable::Find(string key)
{
    size_t index = hash(key);
    for (const auto& pair : data[index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    throw std::out_of_range("Key '" + key + "' not found");
}
