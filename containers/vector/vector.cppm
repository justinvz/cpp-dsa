// This class will be my representation on an implementation of a dynamic array.
//
// So what I want to do is, I want to stay a bit consistent to the cpp
// containers, so that I potentially can swap containers out.

module;

#include <cstddef>

export module jtd.vector;

export namespace jtd {

class vector {
private:
  static constexpr size_t defaultSize = 10;

  int *start = nullptr;
  int *end = nullptr;
  size_t m_size = 0;
  size_t m_capacity = 0;

public:
  vector() {
    start = new int[defaultSize];
    m_capacity = defaultSize;
    end = start + defaultSize;
  }

  ~vector() { delete[] start; }

  bool empty() const { return m_size == 0; }
  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; }

  int at(size_t index) { return start[index]; }

  void push_back();
  void pop_back();

  void clear();

  // size_t max_size() const;
  // void reserve() const;
};

} // namespace jtd
