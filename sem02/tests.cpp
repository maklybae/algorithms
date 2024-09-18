#include <iostream>
#include <stdexcept>

#include "queue.h"

void TestQueueOperations() {
  // Push and Front
  {
    Queue<int> q;
    q.Push(1);
    std::cout << "Test 1: " << (q.Front() == 1 ? "Pass" : "Fail") << std::endl;
    q.Push(2);
    std::cout << "Test 2: " << (q.Front() == 1 ? "Pass" : "Fail") << std::endl;
  }

  // Push and Pop with alternating operations
  {
    Queue<int> q;
    q.Push(10);
    std::cout << "Test 3: " << (q.Front() == 10 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 4: " << (q.Back() == 10 ? "Pass" : "Fail") << std::endl;
    q.Push(20);
    std::cout << "Test 5: " << (q.Front() == 10 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 6: " << (q.Back() == 20 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 7: " << (q.Pop() == 10 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 8: " << (q.Front() == 20 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 9: " << (q.Back() == 20 ? "Pass" : "Fail") << std::endl;
    q.Push(30);
    std::cout << "Test 10: " << (q.Front() == 20 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 11: " << (q.Back() == 30 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 12: " << (q.Pop() == 20 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 13: " << (q.Front() == 30 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 14: " << (q.Back() == 30 ? "Pass" : "Fail") << std::endl;
  }

  // Push and Pop with multiple elements
  {
    Queue<int> q;
    q.Push(5);
    q.Push(15);
    q.Push(25);
    std::cout << "Test 15: " << (q.Front() == 5 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 16: " << (q.Back() == 25 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 17: " << (q.Pop() == 5 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 18: " << (q.Front() == 15 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 19: " << (q.Back() == 25 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 20: " << (q.Pop() == 15 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 21: " << (q.Front() == 25 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 22: " << (q.Back() == 25 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 23: " << (q.Pop() == 25 ? "Pass" : "Fail") << std::endl;
  }

  // Push and Pop with single element
  {
    Queue<int> q;
    q.Push(42);
    std::cout << "Test 24: " << (q.Front() == 42 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 25: " << (q.Back() == 42 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 26: " << (q.Pop() == 42 ? "Pass" : "Fail") << std::endl;
  }

  // Push and Back
  {
    Queue<int> q;
    q.Push(1);
    std::cout << "Test 27: " << (q.Back() == 1 ? "Pass" : "Fail") << std::endl;
    q.Push(2);
    std::cout << "Test 28: " << (q.Back() == 2 ? "Pass" : "Fail") << std::endl;
  }

  // Pop
  {
    Queue<int> q;
    q.Push(2);
    q.Push(1);
    std::cout << "Test 29: " << (q.Pop() == 2 ? "Pass" : "Fail") << std::endl;
    std::cout << "Test 30: " << (q.Pop() == 1 ? "Pass" : "Fail") << std::endl;
  }

  // Min
  {
    Queue<int> q;
    q.Push(3);
    q.Push(1);
    q.Push(2);
    std::cout << "Test 31: " << (q.Min() == 1 ? "Pass" : "Fail") << std::endl;
    q.Pop();
    std::cout << "Test 32: " << (q.Min() == 1 ? "Pass" : "Fail") << std::endl;
    q.Pop();
    std::cout << "Test 33: " << (q.Min() == 2 ? "Pass" : "Fail") << std::endl;
  }

  // Min with negative numbers
  {
    Queue<int> q;
    q.Push(-1);
    q.Push(-3);
    q.Push(-2);
    std::cout << "Test 34: " << (q.Min() == -3 ? "Pass" : "Fail") << std::endl;
    q.Pop();
    std::cout << "Test 35: " << (q.Min() == -3 ? "Pass" : "Fail") << std::endl;
    q.Pop();
    std::cout << "Test 36: " << (q.Min() == -2 ? "Pass" : "Fail") << std::endl;
  }

  // Min with mixed positive and negative numbers
  {
    Queue<int> q;
    q.Push(5);
    q.Push(-1);
    q.Push(3);
    q.Push(-2);
    std::cout << "Test 37: " << (q.Min() == -2 ? "Pass" : "Fail") << std::endl;
    q.Pop();
    std::cout << "Test 38: " << (q.Min() == -2 ? "Pass" : "Fail") << std::endl;
    q.Pop();
    std::cout << "Test 39: " << (q.Min() == -2 ? "Pass" : "Fail") << std::endl;
    q.Pop();
    std::cout << "Test 40: " << (q.Min() == -2 ? "Pass" : "Fail") << std::endl;
  }

  // Min with duplicate minimum values
  {
    Queue<int> q;
    q.Push(4);
    q.Push(2);
    q.Push(2);
    q.Push(3);
    std::cout << "Test 41: " << (q.Min() == 2 ? "Pass" : "Fail") << std::endl;
    q.Pop();
    std::cout << "Test 42: " << (q.Min() == 2 ? "Pass" : "Fail") << std::endl;
    q.Pop();
    std::cout << "Test 43: " << (q.Min() == 2 ? "Pass" : "Fail") << std::endl;
    q.Pop();
    std::cout << "Test 44: " << (q.Min() == 3 ? "Pass" : "Fail") << std::endl;
  }

  // Min with all elements being the same
  {
    Queue<int> q;
    q.Push(7);
    q.Push(7);
    q.Push(7);
    std::cout << "Test 45: " << (q.Min() == 7 ? "Pass" : "Fail") << std::endl;
    q.Pop();
    std::cout << "Test 46: " << (q.Min() == 7 ? "Pass" : "Fail") << std::endl;
    q.Pop();
    std::cout << "Test 47: " << (q.Min() == 7 ? "Pass" : "Fail") << std::endl;
  }
}

int main() {
  TestQueueOperations();
  return 0;
}
