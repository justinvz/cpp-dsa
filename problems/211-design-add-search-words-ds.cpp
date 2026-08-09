#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <memory>
#include <string>

/// @starttim 19:30 19-07-2026

struct TrieNode {
  // Can have 26 nodes, where each node represents a letter in the alphabet.
  std::array<std::unique_ptr<TrieNode>, 26> children;

  bool isLeaf{false};

  TrieNode() {
    for (int i = 0; i < 26; i++) {
      children[i] = nullptr;
    }
  }
};

class WordDictionary {
private:
  TrieNode rootNode;

public:
  WordDictionary() { rootNode = TrieNode(); }

  void addWord(std::string word) {
    TrieNode *currentNode = &rootNode;

    for (const auto &c : word) {

      auto charIndex = static_cast<int>(c) - 'a';

      if (!currentNode->children[charIndex]) {
        currentNode->children[charIndex] = std::make_unique<TrieNode>();
      }

      currentNode = currentNode->children[charIndex].get();
    }

    // Indicate that this is a word.
    currentNode->isLeaf = true;
  }

  bool dfs(std::string &word, std::size_t index, TrieNode *rootNode) {
    auto currentNodeDfs = rootNode;

    for (std::size_t i = index; i < word.size(); i++) {
      auto c = word[i];
      auto charIndex = static_cast<int>(c) - 'a';

      if (c == '.') {
        for (auto &child : currentNodeDfs->children) {
          if (!child)
            continue;

          if (dfs(word, i + 1, child.get())) {
            return true;
          }
        }

        return false;
      } else {
        if (!currentNodeDfs->children[charIndex]) {
          return false;
        }
        currentNodeDfs = currentNodeDfs->children[charIndex].get();
      }
    }

    return currentNodeDfs->isLeaf;
  };

  bool search(std::string word) { return dfs(word, 0, &rootNode); }
};

TEST(Problem, ExistingCases) {
  WordDictionary dict;
  dict.addWord("bad");
  dict.addWord("dad");
  dict.addWord("mad");

  EXPECT_FALSE(dict.search("pad"));

  EXPECT_TRUE(dict.search("bad"));
  EXPECT_TRUE(dict.search(".ad"));

  EXPECT_TRUE(dict.search("b.."));
}
