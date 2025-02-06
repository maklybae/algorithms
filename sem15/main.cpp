#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

class HashLPTable {
 public:
  using KeyValueT = std::pair<int, int>;

  explicit HashLPTable(int m) {
    assert(m > 1);
    m_ = m;
    data_.resize(m);
    used_.resize(m);
  }

  int Size() const {
    return size_;
  }

  bool Insert(int key, int value) {
    if (size_ + 1 > m_ / 2) {
      Rehash();
    }

    auto hash = Hash(key);
    for (int diff = 0; diff < m_; ++diff) {
      int i = (hash + diff) % m_;

      if (!used_[i]) {
        ++size_;
        used_[i] = true;
        data_[i] = {key, value};
        return true;
      }
      if (used_[i] && data_[i].first == key) {
        return false;
      }
    }

    return false;
  }

  int operator[](int key) const {
    auto hash = Hash(key);

    for (int diff = 0; diff < m_; ++diff) {
      int i = (hash + diff) % m_;

      if (!used_[i]) {
        return {};
      }
      if (used_[i] && data_[i].first == key) {
        return data_[i].second;
      }
    }
    return {};
  }

  bool Contains(int key) const {
    auto hash = Hash(key);

    for (int diff = 0; diff < m_; ++diff) {
      int i = (hash + diff) % m_;

      if (!used_[i]) {
        return false;
      }
      if (used_[i] && data_[i].first == key) {
        return true;
      }
    }
    return false;
  }

  bool Erase(int key) {
    auto hash = Hash(key);

    for (int diff = 0; diff < m_; ++diff) {
      int i = (hash + diff) % m_;

      if (!used_[i]) {
        return false;
      }
      if (used_[i] && data_[i].first == key) {
        --size_;

        // shift
        int write_ind = i;
        for (int read_ind = (i + 1) % m_; read_ind < m_; read_ind = (read_ind + 1) % m_) {
          if (!used_[read_ind]) {
            break;
          }
          if (Hash(data_[read_ind].first) == hash) {
            data_[write_ind] = data_[read_ind];
            write_ind = read_ind;
          }
        }
        used_[write_ind] = false;

        return true;
      }
    }
    return false;
  }

  void Rehash() {
    std::vector<KeyValueT> old_data = std::move(data_);
    std::vector<bool> old_used = std::move(used_);

    m_ *= 2;
    data_.resize(m_);
    used_.resize(m_);

    for (int i = 0; i < old_used.size(); ++i) {
      if (old_used[i]) {
        Insert(old_data[i].first, old_data[i].second);
      }
    }
  }

 private:
  std::vector<KeyValueT> data_;
  std::vector<bool> used_;
  int size_{};
  int m_{};

  int Hash(int key) const {
    return key % m_;
  }
};

int main() {
  {
    HashLPTable table(10);
    assert(table.Insert(1, 10));
    assert(table.Insert(2, 20));
    assert(!table.Insert(1, 30));  // Duplicate key
    assert(table.Size() == 2);
    std::cout << "TestInsert passed!" << std::endl;
  }
  {
    HashLPTable table(5);
    table.Insert(1, 10);
    table.Insert(2, 20);
    assert(table.Contains(1));
    assert(table.Contains(2));
    assert(!table.Contains(3));
    std::cout << "TestContains passed!" << std::endl;
  }
  {
    HashLPTable table(5);
    table.Insert(1, 10);
    table.Insert(2, 20);
    assert(table.Erase(1));
    assert(!table.Contains(1));
    assert(table.Contains(2));
    assert(!table.Erase(3));  // Non-existent key
    std::cout << "TestErase passed!" << std::endl;
  }
  {
    HashLPTable table(5);
    for (int i = 0; i < 100; ++i) {
      table.Insert(i, i * 10);
    }
    for (int i = 0; i < 100; ++i) {
      assert(table.Contains(i));
    }
    for (int i = 0; i < 100; ++i) {
      assert(table.Erase(i));
    }
    for (int i = 0; i < 100; ++i) {
      assert(!table.Contains(i));
    }
    std::cout << "TestManyValues passed!" << std::endl;
  }
  {
    HashLPTable table(1000);
    for (int i = 1; i <= 10; ++i) {
      table.Insert(i * 1000, i);
    }
    for (int i = 1; i <= 10; ++i) {
      assert(table.Contains(i * 1000));
    }
    for (int i = 1; i <= 10; ++i) {
      assert(table.Erase(i * 1000));
    }
    for (int i = 1; i <= 10; ++i) {
      assert(!table.Contains(i * 1000));
    }
    std::cout << "TestBreakHash passed!" << std::endl;
  }
}