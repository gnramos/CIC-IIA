/** @file BreadthFirstSearch.h
 *
 * Definição de algoritmo de busca busca em profundidade limitada.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 10/2011 */

#ifndef IIA_SEARCH_UNINFORMED_DEPTH_LIMITED_H
#define IIA_SEARCH_UNINFORMED_DEPTH_LIMITED_H

#include "Problem.hpp"
#include "SearchResult.hpp"

namespace IIA {
namespace Search {
namespace Uninformed {
/** Implementação da busca profundidade limitada (@em Depth-limited). A
 * <a href="http://pt.wikipedia.org/wiki/Busca_em_profundidade">busca em
 * profundidade</a> é um método de busca não-informada que progride através da
 * expansão do primeiro nó filho da árvore de busca, e se aprofunda cada vez
 * mais, até que o alvo da busca seja encontrado ou até que ele se depare com um
 * nó que não possui filhos (nó folha). Então a busca retrocede em busca de uma
 * solução. */
namespace  DepthLimited {
namespace { //unnamed
/* Busca recursivamente uma solução partindo de um nó, de acordo com a definição
 * do problema, até o limite de profundidade, utilizando uma árvore (aceita nós
 * com estados já visitados).
 *
 * @param node nó inicial para a busca.
 * @param problem problema a ser resolvido.
 * @param limit limite de profundidade para busca.*/
template <class state_t>
Result<state_t> recursive_search(Node<state_t> *node,
								 const Problem<state_t> &problem,
								 unsigned int limit) {
	if(problem.is_goal(node->state))
		return Result<state_t>(Result<state_t>::SUCCESS, node, 0);

	if(limit < 1)
		return Result<state_t>(Result<state_t>::CUTOFF, 0);

	bool cutoff_occurred = false;
	IIA::Search::Result<state_t> result;

	long unsigned int expanded_nodes = 0;
	std::deque<Action<state_t> *> actions = problem.actions(node->state);
	for(Action<state_t> *action : actions) {
		Node<state_t> *child = child_node(node, action);
		result = recursive_search(child, problem, limit - 1);
		expanded_nodes += result.expanded_nodes + 1; // contabilizar o nó criado por child_node
		delete child;

		if(result.status == Result<state_t>::CUTOFF)
			cutoff_occurred = true;
		else if(result.status != Result<state_t>::FAILURE)
			break;
	}
	Utils::empty(actions);
	result.expanded_nodes = expanded_nodes;

	if(result.status == Result<state_t>::SUCCESS)
		return result;
	if(cutoff_occurred)
		return IIA::Search::Result<state_t>(Result<state_t>::CUTOFF, nullptr, expanded_nodes);

	return result;
}
} // unnamed namespace

/** Busca a solução do problema usando uma árvore (aceita nós com estados já
 * visitados).
 *
 * @param problem o problema a ser solucionado.
 * @param limit a profundidade máxima a procurar. */
template <class state_t>
Result<state_t> search(const Problem<state_t> &problem, 
	const unsigned int limit) {
	Node<state_t> *node = new Node<state_t>(problem.initial_state);
	Result<state_t> result = recursive_search(node, problem, limit);
	++result.expanded_nodes; // contabilizar o nó criado por "new Node".
	delete node;

	return result;
}
/** Busca a solução do problema usando uma árvore (aceita nós com estados já
 * visitados). Busca até um limite de 20.
 *
 * @param problem o problema a ser solucionado.
 *
 * Exemplo de uso:
 * @code
 * using namespace IIA::Search;
 *
 * ZeroToFour problem;
 * Result<Integer> result = Uninformed::DepthLimited::search(problem);
 * @endcode */
template <class state_t>
Result<state_t> search(const Problem<state_t> &problem) {
	return search(problem, 20);
}
} // namespace DepthLimited
} // namespace Uninformed
} // namespace Search
} // namespace IIA

#endif // IIA_SEARCH_UNINFORMED_DEPTH_LIMITED_H
