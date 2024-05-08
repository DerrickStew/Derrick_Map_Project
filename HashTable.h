#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

// Hash table class using separate chaining
template <typename K, typename V> class HashTable {
private:
  std::vector<std::list<std::pair<K, V>>> table;
  size_t size;                                   // Number items in the table
  size_t buckets;                                // Max capacity of the table
  std::function<size_t(const K &)> hashFunction; // User supplied hash function

  // Double the table size and rehash all elements
  void resizeTable() {
    size_t newTableSize = table.buckets() * 2;
    std::vector<std::list<std::pair<K, V>>> newTable(newTableSize);
    for (const auto &chain : table) {
      for (const auto &pair : chain) {
        size_t index = hashFunction(pair.first) % newTableSize;
        newTable[index].push_back(pair);
      }
    }
    table = std::move(newTable);
    buckets = newTableSize;
  }

public:
  // Constructor
  HashTable(size_t initialSize = 10,
            std::function<size_t(const K &)> hashFunc = std::hash<K>{})
      : size(0), hashFunction(hashFunc) {
    table.resize(initialSize);
    buckets = table.capacity();
  }

  // Precondition - Takes a reference to a key object and a value object
  // Postcondition - If the key already exists, updates the value object 
  // for that key, otherwise uses the key to insert the value object
  // into the hashtable
  void insert(const K &key, const V &value) {
    size_t index = hashFunction(key) % buckets;
    for (auto &pair : table[index]) {
      if (pair.first == key) {
        // Key already exists; update the value
        pair.second = value;
        return;
      }
    }
    // Key doesn't exist; add a new key-value pair
    table[index].push_back(std::make_pair(key, value));
    size++;
  }

  // Precondition - Takes a reference to a key object and a value object
  // Postcondition - returns true if the key was found in the table and 
  // stores the value item in the value parameter, returns false 
  // if the key was not found and the value parameter is not valid
  bool get(const K &key, V &value) {
    size_t index = hashFunction(key) % buckets;
    for (const auto &pair : table[index]) {
      if (pair.first == key) {
        value = pair.second;
        return true;
      }
    }
    return false; // Key not found
  }

  // Precondition - Takes an index into the hash table 
  // Postcondition - if the index is within the bounds of the vector,
  // returns a vector of the items that hashed to that index. Returns
  // an empty vector if the bucket at that index is empty or if the 
  // index is out of range
  std::vector<V> getByIndex(size_t index) {
    if (index < 0 || index > buckets-1)
      return std::vector<V>();
    if (table[index].size() > 0) {
      std::vector<V> items(table[index].size());
      int i = 0;
      for (const auto &pair : table[index]) {
        items[i] = pair.second;
        i++;
      }
      return items;
    }
    return std::vector<V>();
  }

  // Precondition - Takes a reference to a key object
  // Postcondition - If the key hashes to an index and the index has one 
  // or more items in the chain at that index, searches for the key 
  // and if found, deletes the record from the chain and returns true. 
  // If the bucket is empty or the key is not found, returns false.
  bool remove(const K &key) {
    size_t index = hashFunction(key) % buckets;
    auto &chain = table[index];
    auto it = chain.begin();
    while (it != chain.end()) {
      if (it->first == key) {
        it = chain.erase(it);
        size--;
        return true;
      } else {
        ++it;
      }
    }
    return false; // Key not found
  }

  // Returns the number of items in the hashtable
  size_t getSize() const { return size; }

  // **begin() function:** Returns an iterator pointing to the first element in the hash table.
  typename std::list<std::pair<K, V>>::iterator begin() const {
      // Iterate through the table vector and find the first non-empty list
      for (auto it = table.begin(); it != table.end(); ++it) {
          if (!it->empty()) {
              return it->begin(); // Return the iterator to the first element in that list
          }
      }
      // If no non-empty lists are found, return an end iterator
      return table.front().end(); // Can also use any empty list's end iterator
  }

  // **end() function:** Returns an iterator pointing to the element past the last element in the hash table.
  typename std::list<std::pair<K, V>>::iterator end() const {
      // Iterate through the table vector and find the last non-empty list
      for (auto it = table.rbegin(); it != table.rend(); ++it) {
          if (!it->empty()) {
              return std::next(it->end()); // Return the iterator past the last element in that list
          }
      }
      // If no non-empty lists are found, return the end iterator of the entire table vector
      return table.end();
  }

  // Displays all the key-value pairs in the hash table grouped by chain
  void display() {
    for (size_t i = 0; i < table.size(); i++) {
      std::cout << "Bucket " << i << ": ";
      for (const auto &pair : table[i]) {
        std::cout << "(" << pair.first << ") ";
      }
      std::cout << std::endl;
    }
  }

  // Precondition - reference to a user-defined hash function
  // Postcondition - Assigns the input to the hashFunction instance variable
  void setHashFunction(std::function<size_t(const K &)> hashFunc) {
    hashFunction = hashFunc;
  }

  // Precondition - Receives a reference to a key object
  // Postcondition - Returns the index that the key hashes to
  size_t hash(const K &key) { return hashFunction(key) % table.size(); }

  // Returns the number of buckets in the table
  int getBuckets() const { return buckets; }

  // Returns the load factor for the table
  double getLoadFactor() const {
    double loadFactor=0;
    loadFactor = static_cast<double>(size) / buckets;
    return loadFactor;
  }

  // Calculates and returns the number collisions 
  int countCollisions() const {
    int collisionCount = 0;
    for (const auto& chain : table) {
        if (chain.size() > 1) {
            collisionCount += chain.size() - 1;
        }
    }
    return collisionCount;
  }

  // Finds and returns the size of the bucket with the longest chain
  int maxBucketSize() const {
    int largestBucket = 0;
    for (const auto& chain : table) {
        largestBucket = max(largestBucket, static_cast<int>(chain.size()));
    }
    return largestBucket;
  }

};
