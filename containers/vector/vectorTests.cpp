#include "testSuite.h"
#include "vector.hpp"

#include <print>
#include <utility>

struct Entry {
  int value{0};
};

void TestEntryObject() {
  jtd::vector<Entry> vector;

  ExpectTrue(vector.empty(), "default vector is empty");
  ExpectEq(vector.capacity(), jtd::defaultSize, "default vector capacity");

  constexpr int elements{1000000};

  for (size_t i = 0; i < elements; i++) {
    Entry entry;
    entry.value = i;
    vector.push_back(entry);
  }

  println("With move");
  {
    TestTimer timer;
    vector.reserve(elements * 2);
  }

  println("Without move");
  vector.movable = false;
  {
    TestTimer timer;
    vector.reserve(elements * 2);
  }
}

void TestMove() {
  jtd::vector<int> vector;
  vector.push_back(1);
  vector.push_back(2);
  vector.push_back(3);
  {
    auto newVector = jtd::vector(std::move(vector));

    ExpectEq(newVector.size(), std::size_t{3}, "move preserves size");
    ExpectEq(newVector.at(0), 1, "move preserves first value");
    ExpectEq(newVector.at(1), 2, "move preserves middle value");
    ExpectEq(newVector.at(2), 3, "move preserves last value");

    newVector.push_back(4);
    ExpectEq(newVector.at(3), 4, "moved vector remains usable");
  }

  vector.push_back(5);
  ExpectTrue(!vector.empty(), "moved-from vector remains usable");
}

void TestCopy() {
  jtd::vector<int> vector;
  vector.push_back(1);
  vector.push_back(2);
  vector.push_back(3);
  {
    auto newVector = vector;

    ExpectEq(vector.capacity(), newVector.capacity(),
             "copy preserves capacity");
    ExpectEq(vector.size(), newVector.size(), "copy preserves size");
    ExpectEq(newVector.at(0), 1, "copy preserves first value");
    ExpectEq(newVector.at(1), 2, "copy preserves middle value");
    ExpectEq(newVector.at(2), 3, "copy preserves last value");
    ExpectFalse(&vector[0] == &newVector[0], "copy owns separate storage");

    newVector[0] = 99;
    ExpectEq(vector.at(0), 1, "changing copy does not change original");

    newVector.push_back(4);
    ExpectEq(vector.size(), std::size_t{3},
             "growing copy does not change original");
  }

  ExpectEq(vector.at(0), 1, "original survives copied vector destruction");
}

void TestGrowthPreservesValues() {
  jtd::vector<int> vector;
  constexpr std::size_t elements{32};

  for (std::size_t i = 0; i < elements; ++i) {
    vector.push_back(static_cast<int>(i * 3));
  }

  ExpectEq(vector.size(), elements, "growth preserves size");
  ExpectTrue(vector.capacity() >= vector.size(),
             "capacity contains all elements");

  for (std::size_t i = 0; i < elements; ++i) {
    ExpectEq(vector.at(i), static_cast<int>(i * 3),
             "growth preserves element value");
  }
}

void TestAtRejectsInvalidIndexes() {
  jtd::vector<int> vector;
  bool emptyVectorThrew{false};

  try {
    vector.at(0);
  } catch (const std::out_of_range &) {
    emptyVectorThrew = true;
  }

  ExpectTrue(emptyVectorThrew, "at rejects access to empty vector");

  vector.push_back(7);
  bool pastEndThrew{false};

  try {
    vector.at(vector.size());
  } catch (const std::out_of_range &) {
    pastEndThrew = true;
  }

  ExpectTrue(pastEndThrew, "at rejects index equal to size");
}

void TestEmptyCopyAndMove() {
  jtd::vector<int> empty;
  auto copy = empty;
  auto moved = jtd::vector(std::move(empty));

  ExpectTrue(copy.empty(), "copying empty vector stays empty");
  ExpectTrue(moved.empty(), "moving empty vector stays empty");
}

void TestCopyAssignment() {
  jtd::vector<int> source;
  source.push_back(1);
  source.push_back(2);

  jtd::vector<int> destination;
  destination.push_back(99);
  destination = source;

  ExpectEq(destination.size(), source.size(), "copy assignment preserves size");
  ExpectEq(destination.at(0), 1, "copy assignment preserves first value");
  ExpectEq(destination.at(1), 2, "copy assignment preserves last value");
  ExpectFalse(&destination[0] == &source[0],
              "copy assignment owns separate storage");

  destination[0] = 42;
  ExpectEq(source.at(0), 1, "assigned copy is independent");

  auto *sourceAlias = &source;
  source = *sourceAlias;
  ExpectEq(source.at(0), 1, "self-copy assignment preserves values");
}

void TestMoveAssignment() {
  jtd::vector<int> source;
  source.push_back(1);
  source.push_back(2);
  const void *sourceStorage = static_cast<const void *>(&source[0]);

  jtd::vector<int> destination;
  destination.push_back(99);
  destination = std::move(source);

  ExpectEq(destination.size(), std::size_t{2},
           "move assignment preserves size");
  ExpectEq(destination.at(0), 1, "move assignment preserves first value");
  ExpectEq(destination.at(1), 2, "move assignment preserves last value");
  ExpectTrue(static_cast<const void *>(&destination[0]) == sourceStorage,
             "move assignment transfers storage");
  ExpectTrue(source.empty(), "move assignment empties source");

  source.push_back(3);
  ExpectEq(source.at(0), 3, "move-assigned source remains usable");

  auto *destinationAlias = &destination;
  destination = std::move(*destinationAlias);
  ExpectEq(destination.at(0), 1, "self-move assignment preserves values");
}

void TestClear() {
  vector<int> vector;
  for (int i{0}; 100.000 > i; i++) {
    vector.push_back(i);
  }

  vector.clear();
  ExpectTrue(vector.empty());
}

int main() {
  TestEntryObject();
  TestGrowthPreservesValues();
  TestAtRejectsInvalidIndexes();
  TestCopy();
  TestMove();
  TestEmptyCopyAndMove();
  TestCopyAssignment();
  TestMoveAssignment();
  return EXIT_SUCCESS;
}
