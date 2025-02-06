#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>

// Элемент хеш-таблицы - список объектов с одним хешем
template <class KeyType, class ValueType>
struct Node {
  KeyType key{};
  ValueType value{};
  Node *next{};

  Node(KeyType key, ValueType value) : key(std::move(key)), value(std::move(value)) {
  }
};

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
  using Node = Node<KeyType, ValueType>;

 public:
  HashTable() : buckets_(m_) {};

  HashTable(Func hasher) : hasher_(std::move(hasher)), buckets_(m_, nullptr) {
  }

  HashTable(size_t m, double max_load_factor, Func hasher = std::hash<KeyType>())
      : m_{m}, hasher_(std::move(hasher)), buckets_(m_, nullptr) {
    if (0 < max_load_factor && max_load_factor <= 1) {
      max_load_factor_ = max_load_factor;
    }
  }

  ~HashTable() {
    for (auto bucket : buckets_) {
      DeleteBucket(bucket);
    }
  }

  void insert(KeyType key, ValueType value) {
    ++n_;
    if (LoadFactor() > max_load_factor_) {
      Rehash();
    }
    InsertImpl(std::move(key), std::move(value));
  }

  ValueType *find(KeyType key) {
    auto hash = hasher_(key) % m_;

    for (auto node = buckets_[hash]; node; node = node->next) {
      if (key == node->key) {
        return &node->value;
      }
    }

    return nullptr;
  }

  void erase(KeyType key) {
    auto hash = hasher_(key) % m_;

    if (!buckets_[hash]) {
      return;
    }

    if (buckets_[hash]->key == key) {
      auto to_delete = buckets_[hash];
      buckets_[hash] = to_delete->next;
      delete to_delete;
      --n_;
      return;
    }

    auto prev = buckets_[hash];
    auto cur = prev->next;
    for (; cur; prev = cur, cur = cur->next) {
      if (cur->key == key) {
        prev->next = cur->next;
        delete cur;
        --n_;
        return;
      }
    }
  }

  Node &operator[](uint64_t hash) {
    if (hash >= m_) {
      throw std::out_of_range{"dumb user"};
    }
    if (!buckets_[hash]) {
      throw std::runtime_error{"oh no..."};
    }
    return *buckets_[hash];
  }
  Node at(uint64_t hash) {
    if (hash >= m_) {
      throw std::out_of_range{"dumb user"};
    }
    if (!buckets_[hash]) {
      throw std::runtime_error{"oh no..."};
    }
    return *buckets_[hash];
  }

  int size() const {
    return n_;
  }
  int capacity() const {
    return m_;
  }

 private:
  void Rehash() {
    m_ *= 2;

    std::vector<Node *> old_buckets = std::exchange(buckets_, std::vector<Node *>(m_));

    for (auto bucket : old_buckets) {
      while (bucket) {
        auto next = bucket->next;
        InsertNode(bucket);
        bucket = next;
      }
    }
  }

  void InsertNode(Node *node) {
    node->next = nullptr;
    auto hash = hasher_(node->key) % m_;
    if (!buckets_[hash]) {
      buckets_[hash] = node;
      return;
    }

    auto insert_next = buckets_[hash];
    for (; insert_next->next; insert_next = insert_next->next) {
    }

    insert_next->next = node;
  }

  void InsertImpl(KeyType key, ValueType value) {
    auto hash = hasher_(key) % m_;
    if (!buckets_[hash]) {
      buckets_[hash] = new Node(std::move(key), std::move(value));
      return;
    }

    if (buckets_[hash]->key == key) {
      buckets_[hash]->value = value;
      --n_;
      return;
    }

    auto insert_next = buckets_[hash];
    for (; insert_next->next; insert_next = insert_next->next) {
      if (insert_next->next->key == key) {
        insert_next->next->value = value;
        --n_;
        return;
      }
    }

    insert_next->next = new Node(std::move(key), std::move(value));
  }

  double LoadFactor() const {
    return static_cast<double>(n_) / m_;
  }

  static void DeleteBucket(Node *head) {
    if (!head) {
      return;
    }
    DeleteBucket(head->next);
    delete head;
  }

  size_t n_{};
  size_t m_{100};
  double max_load_factor_{0.5};
  Func hasher_{};
  std::vector<Node *> buckets_{};
};
