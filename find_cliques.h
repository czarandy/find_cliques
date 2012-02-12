#pragma once

#include <functional>
#include <vector>

namespace cliques {

  typedef std::vector<int> CliqueType;

  /**
   * Code for finding maximal cliques in a graph.
   *
   * Assumptions:
   * 1. Vertices are numbered from 0 to numVertices - 1.
   * 2. Matrix is symmetric.
   * 3. edgeFunc(a, b) returns true iff (a, b) is an edge.
   * 4. edgeFunc(a, a) is always true.
   *
   * The callback will be called with every new clique. Each clique is just
   * a vector of vertices, in no particular order.
   */
  void findCliques(
    const int numVertices,
    std::function<bool(int a, int b)> edgeFunc,
    std::function<void(const CliqueType& clique)> callback
  );

  CliqueType findMaxClique(
    const int numVertices,
    std::function<bool(int a, int b)> edgeFunc
  );

}
