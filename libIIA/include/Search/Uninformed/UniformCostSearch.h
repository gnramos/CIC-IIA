/** @file UniformCostSearch.h
 *
 * Definição de algoritmo de busca com custo uniforme.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 10/2011 */

#ifndef IIA_UNINFORMED_SEARCH_UNIFORM_COST_H
#define IIA_UNINFORMED_SEARCH_UNIFORM_COST_H

#include <algorithm>

#include "Problem.hpp"
#include "SearchResult.hpp"

namespace IIA {
namespace Search {
namespace Uninformed {
/** Implementação da busca om custo uniforme (@em Uniform-Cost). A
 * <a href="http://en.wikipedia.org/wiki/Uniform_cost_search">busca com custo
 * uniforme</a> é um método de busca não-informada que progride através da
 * expansão do nó filho da árvore de busca não explorado com o menor custo desde
 * a raiz. */
namespace UniformCost {
namespace {
// Compara os nós, indicando se o custo do caminho do primeiro argumento é menor
// que o do segundo.
template <class node_t>
bool compare_path_costs(const node_t *lhs, const node_t *rhs) {
	return (lhs->path_cost < rhs->path_cost);
}
} // unnamed namespace

/** Busca a solução do problema usando um grafo (@em não aceita nós com estados
 * já visitados).
 *
 * @param problem o problema a ser solucionado.
 *
 * Exemplo de uso:
 * @code
 * using namespace IIA::Search;
 *
 * ZeroToFour problem;
 * Result<Integer> result = Uninformed::UniformCost::search(problem);
 * @endcode */
template <class state_t>
Result<state_t> search(const Problem<state_t> &problem) {
	std::deque<Node<state_t> *> frontier(1, new Node<state_t>(problem.initial_state));
	std::deque<Node<state_t> *> explored;

	Result<state_t> result(Result<state_t>::FAILURE, nullptr, 1);
	while(!frontier.empty()) {
		std::sort(frontier.begin(), frontier.end(), compare_path_costs<Node<state_t> >);

		Node<state_t> *node = frontier.front();

		frontier.pop_front();
		explored.push_back(node);

		if(problem.is_goal(node->state)) {
			result = Result<state_t>(Result<state_t>::SUCCESS, node, result.expanded_nodes);
			break;
		}

		std::deque<Action<state_t> *> actions = problem.actions(node->state);
		for(Action<state_t> *action : actions) {
			Node<state_t> *child = child_node(node, action);
			result.expanded_nodes++;
			if(!contains_ptr_state(frontier, child->state)) {
				if(!contains_ptr_state(explored, child->state)) {
					frontier.push_back(child);
				} else delete child;
			} else {
				for(Node<state_t> *aux_node : frontier) {
					if(child->state == aux_node->state && child->path_cost < aux_node->path_cost) {
						/** @todo verificar onde mais child está sendo deletada (delete aqui leva a "double free or corruption (out)" */
						*aux_node = *child;
						//delete child;
						break;
					}
				}
			}
		}
		Utils::empty(actions);
	}

	Utils::empty(frontier);
	Utils::empty(explored);

	return result;
}
} // namespace UniformCost
} // namespace Uninformed
} // namespace Search
} // namespace IIA

#endif // IIA_UNINFORMED_SEARCH_UNIFORM_COST_H
