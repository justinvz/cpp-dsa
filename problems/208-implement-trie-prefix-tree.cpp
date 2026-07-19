#include "testSuite.h"
#include <memory>

/// @starttim 19:10 19-07-2026
/// @endtime 19:25 19-07-2026

using namespace std;

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

class Trie {
private:
  TrieNode rootNode;

public:
  Trie() { rootNode = TrieNode(); }

  void insert(string word) {

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
  };

  bool search(string word) {
    TrieNode *currentNode = &rootNode;

    for (const auto &c : word) {
      auto charIndex = static_cast<int>(c) - 'a';

      if (!currentNode->children[charIndex]) {
        return false;
      }

      currentNode = currentNode->children[charIndex].get();
    }

    if (!currentNode->isLeaf) {
      return false;
    }

    return true;
  };

  bool startWith(string prefix) {
    TrieNode *currentNode = &rootNode;

    for (const auto &c : prefix) {
      auto charIndex = static_cast<int>(c) - 'a';

      if (!currentNode->children[charIndex]) {
        return false;
      }

      currentNode = currentNode->children[charIndex].get();
    }

    return true;
  };
};

int main() {
  auto trie = make_unique<Trie>();

  trie->insert("apple");
  ExpectTrue(trie->search("apple"));
  ExpectFalse(trie->search("app"));

  ExpectTrue(trie->startWith("app"));

  trie->insert("app");
  ExpectTrue(trie->search("app"));
}
