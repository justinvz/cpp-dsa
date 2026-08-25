#include "vector.hpp"

#include <gtest/gtest.h>

#include <cstddef>
#include <print>
#include <stdexcept>
#include <utility>

struct Entry {
  int value{0};
};

TEST(Vector, EntryObject) {
  jtd::vector<Entry> vector;

  EXPECT_TRUE(vector.empty()) << "default vector is empty";
  EXPECT_EQ(vector.capacity(), jtd::defaultSize) << "default vector capacity";

   constexpr int elements{1000000};

   for (std::size_t i = 0; i < elements; i++) {
     Entry entry;
     entry.value = i;
     vector.push_back(entry);
   }
  

   std::println("With move");
   {
     vector.reserve(elements * 2);
   }

   std::println("Without move");
   vector.movable = false;
   {
     vector.reserve(elements * 2);
   }
}

TEST(Vector, MoveConstruction) {
  jtd::vector<int> vector;
  vector.push_back(1);
  vector.push_back(2);
  vector.push_back(3);
  {
    auto newVector = jtd::vector(std::move(vector));

    ASSERT_EQ(newVector.size(), std::size_t{3});
    EXPECT_EQ(newVector.at(0), 1) << "move preserves first value";
    EXPECT_EQ(newVector.at(1), 2) << "move preserves middle value";
    EXPECT_EQ(newVector.at(2), 3) << "move preserves last value";

    newVector.push_back(4);
    EXPECT_EQ(newVector.at(3), 4) << "moved vector remains usable";
  }

  vector.push_back(5);
  EXPECT_FALSE(vector.empty()) << "moved-from vector remains usable";
}

TEST(Vector, CopyConstruction) {
  jtd::vector<int> vector;
  vector.push_back(1);
  vector.push_back(2);
  vector.push_back(3);
  {
    auto newVector = vector;

    EXPECT_EQ(vector.capacity(), newVector.capacity())
        << "copy preserves capacity";
    ASSERT_EQ(vector.size(), newVector.size());
    EXPECT_EQ(newVector.at(0), 1) << "copy preserves first value";
    EXPECT_EQ(newVector.at(1), 2) << "copy preserves middle value";
    EXPECT_EQ(newVector.at(2), 3) << "copy preserves last value";
    EXPECT_NE(&vector[0], &newVector[0]) << "copy owns separate storage";

    newVector[0] = 99;
    EXPECT_EQ(vector.at(0), 1) << "changing copy does not change original";

    newVector.push_back(4);
    EXPECT_EQ(vector.size(), std::size_t{3})
        << "growing copy does not change original";
  }

  EXPECT_EQ(vector.at(0), 1) << "original survives copied vector destruction";
}

TEST(Vector, GrowthPreservesValues) {
  jtd::vector<int> vector;
  constexpr std::size_t elements{32};

  for (std::size_t i = 0; i < elements; ++i) {
    vector.push_back(static_cast<int>(i * 3));
  }

  ASSERT_EQ(vector.size(), elements);
  EXPECT_GE(vector.capacity(), vector.size())
      << "capacity contains all elements";

  for (std::size_t i = 0; i < elements; ++i) {
    EXPECT_EQ(vector.at(i), static_cast<int>(i * 3))
        << "growth preserves element value";
  }
}

TEST(Vector, AtRejectsInvalidIndexes) {
  jtd::vector<int> vector;
  EXPECT_THROW(vector.at(0), std::out_of_range);

  vector.push_back(7);
  EXPECT_THROW(vector.at(vector.size()), std::out_of_range);
}

TEST(Vector, EmptyCopyAndMove) {
  jtd::vector<int> empty;
  auto copy = empty;
  auto moved = jtd::vector(std::move(empty));

  EXPECT_TRUE(copy.empty()) << "copying empty vector stays empty";
  EXPECT_TRUE(moved.empty()) << "moving empty vector stays empty";
}

TEST(Vector, CopyAssignment) {
  jtd::vector<int> source;
  source.push_back(1);
  source.push_back(2);

  jtd::vector<int> destination;
  destination.push_back(99);
  destination = source;

  EXPECT_EQ(destination.size(), source.size())
      << "copy assignment preserves size";
  EXPECT_EQ(destination.at(0), 1) << "copy assignment preserves first value";
  EXPECT_EQ(destination.at(1), 2) << "copy assignment preserves last value";
  EXPECT_NE(&destination[0], &source[0])
      << "copy assignment owns separate storage";

  destination[0] = 42;
  EXPECT_EQ(source.at(0), 1) << "assigned copy is independent";

  auto *sourceAlias = &source;
  source = *sourceAlias;
  EXPECT_EQ(source.at(0), 1) << "self-copy assignment preserves values";
}

TEST(Vector, MoveAssignment) {
  jtd::vector<int> source;
  source.push_back(1);
  source.push_back(2);
  const void *sourceStorage = static_cast<const void *>(&source[0]);

  jtd::vector<int> destination;
  destination.push_back(99);
  destination = std::move(source);

  EXPECT_EQ(destination.size(), std::size_t{2})
      << "move assignment preserves size";
  EXPECT_EQ(destination.at(0), 1) << "move assignment preserves first value";
  EXPECT_EQ(destination.at(1), 2) << "move assignment preserves last value";
  EXPECT_EQ(static_cast<const void *>(&destination[0]), sourceStorage)
      << "move assignment transfers storage";
  EXPECT_TRUE(source.empty()) << "move assignment empties source";

  source.push_back(3);
  EXPECT_EQ(source.at(0), 3) << "move-assigned source remains usable";

  auto *destinationAlias = &destination;
  destination = std::move(*destinationAlias);
  EXPECT_EQ(destination.at(0), 1) << "self-move assignment preserves values";
}

TEST(Vector, Clear) {
  jtd::vector<int> vector;
  for (int i{0}; i < 100; ++i) {
    vector.push_back(i);
  }

  ASSERT_FALSE(vector.empty());
  vector.clear();
  EXPECT_TRUE(vector.empty());
  EXPECT_EQ(vector.size(), std::size_t{0});

  vector.pop_back();
}
