#include "find_cliques.h"

#include <iostream>
#include <iterator>

int main() {

  /**
   * Example that finds cliques in a small matrix.
   */

  const int numVertices = 7;
  const int matrix[numVertices][numVertices] = {
    { 1, 1, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 1, 1 },
    { 0, 0, 1, 1, 1, 1, 0 },
    { 0, 0, 1, 1, 0, 0, 1 },
    { 0, 0, 1, 0, 1, 1, 1 },
    { 1, 1, 1, 0, 1, 1, 1 },
    { 1, 1, 0, 1, 1, 1, 1 },
  };

  auto edgeFunc = [matrix](int a, int b) {
    return matrix[a][b] == 1;
  };

  cliques::CliqueType maxClique = cliques::findMaxClique(numVertices, edgeFunc);

  std::cout << "Largest clique is: ";
  std::copy(maxClique.begin(), maxClique.end(), std::ostream_iterator<int>(std::cout, ", "));
  std::cout << "\n";

  int count = 0;
  cliques::findCliques(numVertices, edgeFunc, [&count](const cliques::CliqueType& clique) {
    ++count;
  });

  std::cout << "And there are " << count << " total cliques\n";

}
