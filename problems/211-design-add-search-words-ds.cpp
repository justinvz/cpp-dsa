
#include "testSuite.h"
#include <memory>
#include <print>

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

  void addWord(string word) {
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

  bool dfs(string &word, size_t index, TrieNode *rootNode) {
    auto currentNodeDfs = rootNode;

    for (size_t i = index; i < word.size(); i++) {
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

  bool search(string word) { return dfs(word, 0, &rootNode); }
};

int main() {
  WordDictionary dict;
  dict.addWord("bad");
  dict.addWord("dad");
  dict.addWord("mad");

  ExpectFalse(dict.search("pad"));

  ExpectTrue(dict.search("bad"));
  ExpectTrue(dict.search(".ad"));

  ExpectTrue(dict.search("b.."));
}
