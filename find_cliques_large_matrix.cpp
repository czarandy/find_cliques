#include "find_cliques.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <sys/time.h>

int main() {

  /**
   * Example that loads a large matrix from a file and then finds cliques.
   */

  std::vector<const char*> files{"large_matrix_50", "large_matrix_100", "large_matrix_200"};

  for (const auto file : files) {

    std::ifstream fin(file);
    int numVertices;
    fin >> numVertices;

    std::vector<int> matrix(numVertices * numVertices);
    int val;
    int cur = 0;
    while (fin >> val) {
      matrix[cur++] = val;
    }

    auto edgeFunc = [&matrix, numVertices](int a, int b) {
      if (a == b) {
        return true;
      }
      return matrix[a * numVertices + b] == 1;
    };

    int count = 0;
    timeval start;
    gettimeofday(&start, NULL);
    cliques::findCliques(numVertices, edgeFunc, [&count](const cliques::CliqueType& clique) {
      ++count;
    });
    timeval stop, result;
    gettimeofday(&stop, NULL);
    timersub(&stop, &start, &result);
    double time = result.tv_sec * 1000000.0 + result.tv_usec;

    std::cout
      << "Matrix Size: " << numVertices
      << ", # of Cliques: " << count
      << ", Microseconds: " << time
      << std::endl;
  }

}
