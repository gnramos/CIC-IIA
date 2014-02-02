/** @file IterativeDeepeningSearch.h
 *
 * Definição de algoritmo de busca em profundidade iterativa.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 10/2011 */

#ifndef IIA_SEARCH_UNINFORMED_ITERATIVE_DEEPENING_H
#define IIA_SEARCH_UNINFORMED_ITERATIVE_DEEPENING_H

#include <limits>

#include "Uninformed/DepthLimitedSearch.h"

namespace IIA {
namespace Search {
namespace Uninformed {
/** Implementação da busca iterativa em profundidade (<i>Iterative Deepening</i>).
 * Utiliza a busca em profundidade limitada (DepthLimited) com limites
 * incrementalmente maiores. */
namespace IterativeDeepening {
/** Busca a solução do problema usando uma árvore (aceita nós com estados já
 * visitados).
 *
 * @param problem o problema a ser solucionado.
 *
 * @see IIA::Search::Result<state_t> DepthLimited::search<Node<state_t>, problem_t, state_t, Action<state_t> >(node_t, problem_t, const unsigned int)
 *
 * Exemplo de uso:
 * @code
 * using namespace IIA::Search;
 *
 * ZeroToFour problem;
 * Result<Integer> result = Uninformed::IterativeDeepening::search(problem);
 * @endcode */
template <class state_t>
Result<state_t> search(const Problem<state_t> &problem) {
	long unsigned int expanded_nodes = 0;
	Result<state_t> result;
	for(int limit = 0; limit < std::numeric_limits<int>::max(); ++limit) {
		result = DepthLimited::search(problem, limit);
		expanded_nodes += result.expanded_nodes;

		if(result.status != Result<state_t>::CUTOFF) break;
	}

	result.expanded_nodes = expanded_nodes;
	return result;
}
} // namespace IterativeDeepening
} // namespace Uninformed
} // namespace Search
} // namespace IIA

#endif // IIA_SEARCH_UNINFORMED_ITERATIVE_DEEPENING_H
