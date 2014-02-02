/** @file BreadthFirstSearch.h
 *
 * Definição de algoritmo de busca em largura.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 10/2012 */

#ifndef IIA_SEARCH_UNINFORMED_BREADTH_FIRST_H
#define IIA_SEARCH_UNINFORMED_BREADTH_FIRST_H

#include "Problem.hpp"
#include "SearchResult.hpp"

namespace IIA {
namespace Search {
namespace Uninformed {
/** Implementação da busca em largura (@em Breadth-first). A
 * <a href="http://pt.wikipedia.org/wiki/Busca_em_largura">busca em largura</a>
 * é um método de busca não-informada que expande e examina sistematicamente
 * todos os nós de cada nível de uma árvore, em busca de uma solução. */
namespace BreadthFirst {
/** Busca a solução do problema usando uma árvore (aceita nós com estados já
 * visitados).
 *
 * @param problem o problema a ser solucionado. */
template <class state_t>
Result<state_t> search_tree(const Problem<state_t> &problem) {
	std::deque<Node<state_t> *> frontier(1, new Node<state_t>(problem.initial_state));
	Result<state_t> result(Result<state_t>::FAILURE, nullptr, 1);

	while(!frontier.empty()) {
		Node<state_t> *node = frontier.front();
		frontier.pop_front(); // FIFO

		if(problem.is_goal(node->state)) {
			result = Result<state_t>(Result<state_t>::SUCCESS, node, result.expanded_nodes);
			delete node;
			break;
		}

		std::deque<Action<state_t> *> actions = problem.actions(node->state);
		std::deque<Node<state_t> *>  children = children_nodes(node, actions);

		result.expanded_nodes += children.size();
		Utils::empty(actions);

		frontier.insert(frontier.end(), children.begin(), children.end());
	}

	Utils::empty(frontier);

	return result;
}

/** Busca a solução do problema usando um grafo (@em não aceita nós com estados
 * já visitados).
 *
 * @param problem o problema a ser solucionado. */
template <class state_t>
Result<state_t> search_graph(const Problem<state_t> &problem) {
	if(problem.is_goal(problem.initial_state)) {
		Node<state_t> node(problem.initial_state);
		return Result<state_t>(Result<state_t>::SUCCESS, &node, 1);
	}

	std::deque<Node<state_t> *> frontier(1, new Node<state_t>(problem.initial_state));
	std::deque<Node<state_t> *> explored;

	Result<state_t> result(Result<state_t>::FAILURE, nullptr, frontier.size());

	while(!frontier.empty() && result.status != Result<state_t>::SUCCESS) {
		Node<state_t> *node = frontier.front();
		frontier.pop_front(), explored.push_back(node);

		auto actions = problem.actions(node->state);
		for(auto action : actions) {
			Node<state_t> *child = child_node(node, action);
			++result.expanded_nodes;
			if( contains_ptr_state(explored, child->state) || 
				contains_ptr_state(frontier, child->state)) {
				delete child;
			} else {
				if(problem.is_goal(child->state)) {
					result = Result<state_t>(Result<state_t>::SUCCESS, child, result.expanded_nodes);
					//delete child;
					break;
				}
				frontier.push_back(child); // FIFO
			}
		}
		Utils::empty(actions);
	}
	Utils::empty(frontier), Utils::empty(explored);

	return result;
}

/** Busca a solução do problema.
 *
 * @param problem o problema a ser solucionado.
 *
 * @see Result<state_t> search_graph(const Problem<state_t> &)
 *
 * Exemplo de uso:
 * @code
 * using namespace IIA::Search;
 *
 * ZeroToFour problem;
 * Result<Integer> result = Uninformed::BreadthFirst::search(problem);
 * @endcode */
template <class state_t>
Result<state_t> search(const Problem<state_t> &problem) {
	return search_graph(problem);
}
} // namespace BreadthFirst
} // namespace Uninformed
} // namespace Search
} // namespace IIA

#endif // IIA_SEARCH_UNINFORMED_BREADTH_FIRST_H
