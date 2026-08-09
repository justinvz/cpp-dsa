#pragma once

#include <cstddef>
#include <print>

// This class is an implementation of a dynamic array. Its interface follows
// the standard containers where practical so containers can be swapped.
namespace jtd {
static constexpr std::size_t defaultSize = 2;

template <typename T> class vector {
private:
  T *start = nullptr;
  T *end = nullptr;
  std::size_t m_size = 0;
  std::size_t m_capacity = 0;

public:
  vector() {
    std::println("Constructor");
    start = new T[defaultSize];
    m_capacity = defaultSize;
    end = start + defaultSize;
  }

  ~vector() {
    std::println("Destructor");
    delete[] start;
  }

  vector(vector &other) = default;  // Copy constructor
  vector(vector &&other) = default; // Move constructor
  vector(const vector &) = default;
  vector(const vector &&) = default;

  T &operator[](std::size_t index) noexcept { return start[index]; }

  T at(std::size_t index) {
    if (index >= m_size) {
      std::println("Index {} out of ranges size {}", index, m_size);
    }
    return start[index];
  }

  bool empty() const { return m_size == 0; }
  std::size_t size() const { return m_size; }
  std::size_t capacity() const { return m_capacity; }

  // Move all elements to a bigger piece of allocated memory
  void grow(size_t newCapacity) {
    T *newStart = new T[newCapacity];

    // For now easy way is to just copy.
    for (size_t i{0}; i < m_size; i++) {
      newStart[i] = start[i];
    }

    free(start);

    std::println("Vector grows from {} to {}", m_capacity, newCapacity);

    start = newStart;
    m_capacity = newCapacity;
    end = start + newCapacity;
  }

  void push_back(T val) {
    if (m_size >= m_capacity) {
      grow(m_capacity * 2);
    }

    start[m_size] = val;
    m_size++;

    std::println("Pushed back value {} size {} capacity {}", val, m_size,
                 m_capacity);
  }

  void pop_back();

  void clear();

  // std::size_t max_size() const;
  // void reserve() const;
};

} // namespace jtd
