// This class will be my representation on an implementation of a dynamic array.
//
// So what I want to do is, I want to stay a bit consistent to the cpp
// containers, so that I potentially can swap containers out.

#include <print>
export module jtd.vector;

import std;

export namespace jtd {

template <typename T> class vector {
private:
  T *start = nullptr;
  T *end = nullptr;
  std::size_t m_size = 0;
  std::size_t m_capacity = 0;

public:
  static constexpr std::size_t defaultSize = 10;

  vector() {
    start = new T[defaultSize];
    m_capacity = defaultSize;
    end = start + defaultSize;
  }

  ~vector() { delete[] start; }
  vector(vector &other) = default;  // Copy constructor
  vector(vector &&other) = default; // Move constructor
  vector(const vector &) = default;
  vector(const vector &&) = default;

  bool empty() const { return m_size == 0; }
  std::size_t size() const { return m_size; }
  std::size_t capacity() const { return m_capacity; }

  T at(std::size_t index) { return start[index]; }

  void push_back(T val) {
    std::cout << "Here!";

    std::println("hi");
  }

  void pop_back();

  void clear();

  // size_t max_size() const;
  // void reserve() const;
};

} // namespace jtd
