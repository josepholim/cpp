#include <iostream>
#include <vector>

class HashMap {
public:
  HashMap(size_t initialCapacity = 1, double loadFactor = 1) : table(initialCapacity), loadFactor(loadFactor) {}

  size_t computeHash(int key, int sz) {
    return key % sz;
  }

  void insert(int key, int value) {
    if (size() >= table.size() * loadFactor) {
      resize();
    }
    size_t index = computeHash(key, table.size());
    table[index].push_back(std::make_pair(key, value));
  }

  int find(int key) {
    size_t index = computeHash(key, table.size());
    for (auto& pair : table[index]) {
      if (pair.first == key) {
        return pair.second;
      }
    }
    throw std::out_of_range("Key not found");
  }

  bool contains(int key) {
    try {
      find(key);
      return true;
    } catch (const std::out_of_range&) {
      return false;
    }
  }

  size_t size() const {
    size_t count = 0;
    for (const auto& bucket : table) {
      count += bucket.size();
    }
    return count;
  }

private:
  std::vector<std::vector<std::pair<int, int>>> table; 
  double loadFactor;

  void resize() {
    size_t newCapacity = table.size() * 2;
    std::vector<std::vector<std::pair<int, int>>> newTable(newCapacity);
    for (const auto& bucket : table) {
      for (const auto& pair : bucket) {
        size_t index = computeHash(pair.first, newCapacity);
        newTable[index].push_back(pair);
      }
    }
    table = std::move(newTable);
  }
};

int main() {
  HashMap hashMap;
  hashMap.insert(1, 10);
  hashMap.insert(2, 20);
  hashMap.insert(3, 30);
  hashMap.insert(13, 40);
  hashMap.insert(23, 50);

  std::vector<int> keys = {1, 2, 3, 13, 23};
  for (int& key : keys) {
    std::cout << hashMap.find(key) << '\n';
  }

  return 0;
}