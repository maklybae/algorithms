#ifndef TREE_H
#define TREE_H

#include <memory>

template <typename Comparable>
class BinarySearchTree {
 private:
  struct BinaryNode {
    BinaryNode *parent;
    BinaryNode *left;
    BinaryNode *right;
    Comparable element;

    BinaryNode(const Comparable &element, BinaryNode *parent, BinaryNode *lt, BinaryNode *rt)
        : element{element}, parent{parent}, left{lt}, right{rt} {
    }

    BinaryNode(Comparable &&element, BinaryNode *parent, BinaryNode *lt, BinaryNode *rt)
        : element{std::move(element)}, parent{parent}, left{lt}, right{rt} {
    }
  };

  BinaryNode *header_;
  // root is left child of header_

  static void Insert(Comparable &&x, BinaryNode *&t, BinaryNode *parent) {
    if (!t) {
      t = new BinaryNode{std::forward<Comparable>(x), parent, nullptr, nullptr};
    } else if (x < t->element) {
      Insert(std::forward<Comparable>(x), t->left, t);
    } else if (t->element < x) {
      Insert(std::forward<Comparable>(x), t->right, t);
    }
  }

  static void Remove(const Comparable &x, BinaryNode *&t) {
    if (!t) {
      return;
    }

    if (x < t->element) {
      Remove(x, t->left);
    } else if (t->element < x) {
      Remove(x, t->right);
    } else if (t->left && t->right) {
      t->element = FindMin(t->right)->element;
      Remove(t->element, t->right);
    } else {
      BinaryNode *old = t;
      t = (t->left) ? t->left : t->right;
      delete old;
    }
  }

  static BinaryNode *FindMin(BinaryNode *t) {
    if (t) {
      while (t->left) {
        t = t->left;
      }
    }
    return t;
  }

  static BinaryNode *FindMax(BinaryNode *t) {
    if (t) {
      while (t->right) {
        t = t->right;
      }
    }
    return t;
  }

  static bool Contains(const Comparable &x, BinaryNode *t) {
    if (!t) {
      return false;
    }

    if (x < t->element) {
      return Contains(x, t->left);
    }
    if (x > t->element) {
      return Contains(x, t->right);
    }
    return true;
  }

  static void MakeEmpty(BinaryNode *&t) {
    if (t) {
      MakeEmpty(t->left);
      MakeEmpty(t->right);
      delete t;
    }
    t = nullptr;
  }

  static BinaryNode *Clone(BinaryNode *t) {
    if (!t) {
      return nullptr;
    }
    return new BinaryNode{t->element, t, Clone(t->left), Clone(t->right)};
  }

  static BinaryNode *FindPredecessor(BinaryNode *t) {
    if (!t) {
      return nullptr;
    }

    if (t->left) {
      return FindMax(t->left);
    }

    BinaryNode *parent{t->parent};
    while (parent && t == parent->left) {
      t = parent;
      parent = parent->parent;
    }

    return parent;
  }

  static BinaryNode *FindSuccessor(BinaryNode *t) {
    if (!t) {
      return nullptr;
    }

    if (t->right) {
      return FindMin(t->right);
    }

    BinaryNode *parent{t->parent};
    while (parent && t == parent->right) {
      t = parent;
      parent = parent->parent;
    }

    return parent;
  }

 public:
  struct Iterator {
    using iterator_category = std::bidirectional_iterator_tag;  // NOLINT
    using difference_type = std::ptrdiff_t;                     // NOLINT
    using value_type = Comparable;                              // NOLINT
    using pointer = value_type *;                               // NOLINT
    using reference = value_type &;                             // NOLINT

    explicit Iterator(BinaryNode *node) : node_{node} {
    }

    reference operator*() const {
      return node_->element;
    }

    pointer operator->() const {
      return &node_->element;
    }

    Iterator &operator++() {
      node_ = FindSuccessor(node_);
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    Iterator &operator--() {
      node_ = FindPredecessor(node_);
      return *this;
    }

    Iterator operator--(int) {
      Iterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const Iterator &other) const {
      return node_ == other.node_;
    }

    bool operator!=(const Iterator &other) const {
      return node_ != other.node_;
    }

   private:
    BinaryNode *node_{};
  };

  BinarySearchTree() {
    header_ = new BinaryNode{Comparable{}, nullptr, nullptr, nullptr};
  }
  BinarySearchTree(const BinarySearchTree &rhs) {
    header_ = Clone(rhs.header_);
  }
  BinarySearchTree(BinarySearchTree &&rhs) noexcept
      : header_{std::exchange(rhs.header_, nullptr)} {  // rhs is not longer valid
  }
  ~BinarySearchTree() {
    MakeEmpty();
    delete header_;
  }

  const Comparable &FindMin() const {
    return FindMin(header_->left)->element;
  }

  const Comparable &FindMax() const {
    return FindMax(header_->left)->element;
  }

  bool Contains(const Comparable &x) const {
    return Contains(x, header_->left);
  }

  bool IsEmpty() const {
    return !header_->left;
  }

  void MakeEmpty() {
    MakeEmpty(header_->left);
  }

  void Insert(Comparable &&x) {
    Insert(std::forward<Comparable>(x), header_->left, header_);
  }

  void Remove(const Comparable &x) {
    Remove(x, header_->left);
  }

  BinarySearchTree &operator=(const BinarySearchTree &rhs) {
    if (this == &rhs) {
      return *this;
    }

    MakeEmpty();
    header_->left = Clone(rhs.root_);
    header_->left->parent = header_;

    return *this;
  }

  BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
    if (this == &rhs) {
      return *this;
    }

    MakeEmpty();
    delete header_;
    header_ = rhs.header_;
    rhs.header_ = nullptr;

    return *this;
  }

  Iterator begin() {  // NOLINT
    if (!header_->left) {
      return Iterator{header_};
    }
    return Iterator{FindMin(header_->left)};
  }

  Iterator end() {  // NOLINT
    return Iterator{header_};
  }
};

#endif