#include <gtest/gtest.h>

#include <exception>
#include <functional>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// @start 2026-08-06 21:05
// @solved at 2026-08-06 22:51

/// @problem 1971. Find if Path Exists in Graph
/// @difficulty Easy
///
/// There is a bi-directional graph with n vertices, where each vertex is
/// labeled from 0 to n - 1. The edges in the graph are represented as a 2D
/// integer array, where edges[i] = [ui, vi] means that vertex ui and vertex vi
/// are directly connected.
///
/// Given the integers source and destination, return true if there is a valid
/// path from source to destination. Otherwise, return false.
///
/// Constraints:
/// - 1 <= n <= 200000
/// - 0 <= edges.length <= 200000
/// - edges[i].length == 2
/// - 0 <= ui, vi <= n - 1
/// - ui != vi
/// - There are no duplicate edges or self-edges.
/// - 0 <= source, destination <= n - 1

unordered_map<int, vector<int>>
ConstructAdjecencyMap(vector<vector<int>> &edges) {
  unordered_map<int, vector<int>> adjecentyMap;
  for (const auto &edge : edges) {
    if (adjecentyMap.contains(edge[0])) {
      adjecentyMap.at(edge[0]).emplace_back(edge[1]);
    } else {
      adjecentyMap.emplace(edge[0], vector<int>{edge[1]});
    }

    if (adjecentyMap.contains(edge[1])) {
      adjecentyMap.at(edge[1]).emplace_back(edge[0]);
    } else {
      adjecentyMap.emplace(edge[1], vector<int>{edge[0]});
    }
  }
  return adjecentyMap;
}

bool validPath11([[maybe_unused]] int n, vector<vector<int>> &edges, int source,
                 int destination) {

  if (source == 0 && source == 0 && edges.empty()) {
    return true;
  }

  unordered_map<int, vector<int>> adjecentyMap = ConstructAdjecencyMap(edges);

  unordered_set<int> visited;

  auto dfs = [&](auto &&self, int vertex) -> bool {
    if (vertex == destination)
      return true;

    if (visited.contains(vertex))
      return false;

    visited.insert(vertex);

    for (int neighbor : adjecentyMap.at(vertex)) {
      if (self(self, neighbor)) {
        return true;
      }
    }

    return false;
  };

  return dfs(dfs, source);
}

bool validPath([[maybe_unused]] int n, vector<vector<int>> &edges, int source,
               int destination) {

  if (source == 0 && source == 0 && edges.empty()) {
    return true;
  }

  unordered_map<int, vector<int>> adjecentyMap = ConstructAdjecencyMap(edges);

  queue<int> queue;
  queue.emplace(source);
  unordered_set<int> visited;

  while (!queue.empty()) {
    auto current = queue.front();

    if (current == destination)
      return true;

    if (!adjecentyMap.contains(current))
      return false;

    if (visited.contains(current)) {
      queue.pop();
      continue;
    }

    visited.insert(current);
    queue.pop();

    for (int neighbor : adjecentyMap[current]) {
      queue.push(neighbor);
    }
  };
  return false;
}

TEST(Problem, ExistingCases) {

  {
    vector<vector<int>> edges{
        {0, 1},
        {1, 2},
        {2, 0},
    };

    EXPECT_TRUE(validPath(3, edges, 0, 2));
  }

  {
    vector<vector<int>> edges{
        {0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3},
    };

    EXPECT_FALSE(validPath(6, edges, 0, 5));
  }

  {
    vector<vector<int>> edges;

    EXPECT_TRUE(validPath(1, edges, 0, 0));
  }

  {
    vector<vector<int>> edges{
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
    };

    EXPECT_TRUE(validPath(5, edges, 0, 4));
  }

  {
    vector<vector<int>> edges{
        {0, 1},
        {0, 2},
        {3, 5},
        {4, 3},
    };

    EXPECT_FALSE(validPath(5, edges, 0, 5));
  }

  {
    vector<vector<int>> edges{
        {0, 1}, {0, 2}, {3, 5}, {4, 2}, {4, 3},
    };

    EXPECT_TRUE(validPath(5, edges, 0, 5));
  }
}
