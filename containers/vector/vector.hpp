#pragma once

#include <cstddef>
#include <iostream>

// This class is an implementation of a dynamic array. Its interface follows
// the standard containers where practical so containers can be swapped.
namespace jtd {

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

  void push_back(T val) { std::cout << "Here!"; }

  void pop_back();

  void clear();

  // std::size_t max_size() const;
  // void reserve() const;
};

} // namespace jtd
