#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <print>
#include <stdexcept>
#include <sys/stat.h>
#include <utility>

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
  std::allocator<T> alloc;

public:
  bool movable{true};

  vector(std::size_t p_capacity = defaultSize)
      : start(alloc.allocate(p_capacity)), end(start), m_capacity(p_capacity) {
    std::println("Constructor allocated {} bytes", sizeof(T) * p_capacity);
  }

  ~vector() {
    std::println("Destructor deallocated {} bytes", sizeof(T) * m_capacity);
    alloc.deallocate(start, m_capacity);
  }

  vector(const vector &other) : vector(other.m_capacity) {
    std::copy_n(other.start, other.m_size, start);
    m_size = other.m_size;
    end = start + m_size;
    movable = other.movable;

    std::println("Copy");
  }

  vector(vector &&other) noexcept
      : start(other.start), end(other.end), m_size(other.m_size),
        m_capacity(other.m_capacity), movable(other.movable) {
    other.start = nullptr;
    other.end = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
    other.movable = true;

    std::println("Moved");
  }

  vector &operator=(const vector &other) {
    if (this == &other) {
      return *this;
    }

    vector copy(other);
    swap(copy);
    return *this;
  }

  vector &operator=(vector &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    alloc.deallocate(start, m_capacity);

    start = other.start;
    end = other.end;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    movable = other.movable;

    other.start = nullptr;
    other.end = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
    other.movable = true;

    return *this;
  }

  void swap(vector &other) noexcept {
    using std::swap;

    swap(start, other.start);
    swap(end, other.end);
    swap(m_size, other.m_size);
    swap(m_capacity, other.m_capacity);
    swap(movable, other.movable);
  }

  T &operator[](std::size_t index) noexcept { return start[index]; }

  T at(std::size_t index) {
    if (index >= m_size) {
      throw std::out_of_range(
          std::format("Index {} out of ranges size {}", index, m_size));
    }
    return start[index];
  }

  bool empty() const { return m_size == 0; }
  std::size_t size() const { return m_size; }
  std::size_t capacity() const { return m_capacity; }

  // Move all elements to a bigger piece of allocated memory
  void reserve(size_t newCapacity) {
    T *newStart = alloc.allocate(newCapacity);

    if (movable) {
      std::move(start, start + m_size, newStart);
    } else {
      std::copy(start, start + m_size, newStart);
    }

    alloc.deallocate(start, m_capacity);
    start = newStart;

    std::println("Vector grows from {} to {} allocated {} bytes", m_capacity,
                 newCapacity, sizeof(T) * newCapacity);
    m_capacity = newCapacity;
    end = start + m_size;
  }

  void push_back(T val) {
    if (m_size >= m_capacity) {
      reserve(m_capacity == 0 ? defaultSize : m_capacity * 2);
    }

    std::construct_at(start + m_size, val);
    m_size++;

    end++;
  }

  void pop_back() {

    if (end == start) {
      throw std::out_of_range("Can't remove more, alrady at the end");
    }

    std::destroy_at(end);
    end--;
  }

  void clear() {
    for (size_t i = 0; i < m_size; i++) {
      std::destroy_at(end);
      end--;
    }

    m_size = 0;
    reserve(defaultSize);
  };
};

} // namespace jtd
