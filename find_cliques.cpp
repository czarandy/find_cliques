#include "find_cliques.h"

#include <algorithm>
#include <cassert>

namespace cliques {

  namespace {

    void findCliquesHelper(
      CliqueType& old,
      int ne,
      const int ce,
      CliqueType& currentClique,
      std::function<bool(int a, int b)> edgeFunc,
      std::function<void(const CliqueType& clique)> callback) {

      int nod = 0;
      int fixp = -1;
      int s = -1;
      int minnod = ce;

      CliqueType new_(ce);
      std::fill(new_.begin(), new_.end(), 0);

      // Determine each counter value and look for minimum
      if (old.size() == 3) {
        int k = 5 + 7;
      }
      for (int i = 0; i < ce && minnod != 0; ++i) {
        int count = 0;
        int pos = 0;
        // Count disconnections
        for (int j = ne; j < ce && count < minnod; ++j) {
          if (!edgeFunc(old[i], old[j])) {
            ++count;
            pos = j; // Save position of potential candidate
          }
        }
        // Test new minimum
        if (count < minnod) {
          fixp = old[i];
          minnod = count;
          if (i < ne) {
            s = pos;
          } else {
            s = i;
            nod = 1;
          }
        }
      }

      // If a fixed point is initially chosen from candidates then
      // the number of disconnections will be preincreased by one.

      // Backtrackcycle
      for (nod = minnod + nod; nod >= 1; --nod) {
        std::swap(old[s], old[ne]);

        int newne = 0;
        for (int i = 0; i < ne; i++) {
          if (edgeFunc(old[ne], old[i])) {
            new_[newne++] = old[i];
          }
        }

        int newce = newne;
        for (int i = ne + 1; i < ce; i++){
          if (edgeFunc(old[ne], old[i])) {
            new_[newce++] = old[i];
          }
        }

        currentClique.push_back(old[ne]);

        if (newce == 0) {
          callback(currentClique);
        } else if (newne < newce) {
          findCliquesHelper(new_, newne, newce, currentClique, edgeFunc, callback);
        }

        if (!currentClique.empty()) {
          currentClique.pop_back();
        }

        ne++;
        if (nod > 1) {
          // Select a candidate disconnected to the fixed point
          for (s = ne; edgeFunc(fixp, old[s]); ++s){
            // empty loop
          }
        }
      }
    }

  }

  void findCliques(
    const int numVertices,
    std::function<bool(int a, int b)> edgeFunc,
    std::function<void(const CliqueType& clique)> callback) {

    std::vector<int> initial(numVertices);
    std::iota(initial.begin(), initial.end(), 0);
    std::vector<int> initialClique;
    findCliquesHelper(initial, 0, numVertices, initialClique, edgeFunc, callback);
  }

  CliqueType findMaxClique(
    const int numVertices,
    std::function<bool(int a, int b)> edgeFunc) {

    CliqueType maxClique;
    findCliques(numVertices, edgeFunc, [&](const CliqueType& clique) {
      if (clique.size() > maxClique.size()) {
        maxClique = clique;
      }
    });

    return maxClique;
  }

}
