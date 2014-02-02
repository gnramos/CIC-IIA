/** @file BidirectionalSearch.h
 *
 * Definição de algoritmo de busca bidirecional.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 10/2011 */

#ifndef IIA_SEARCH_UNINFORMED_BIDIRECTIONAL_H
#define IIA_SEARCH_UNINFORMED_BIDIRECTIONAL_H

#include "Problem.hpp"
#include "SearchResult.hpp"

namespace IIA {
namespace Search {
namespace Uninformed {
/** @todo Documentação da busca bidirecional. Teste unitário */
namespace Bidirectional {

namespace {
template <class state_t>
Result<state_t> join_searches(Node<state_t> *fwd_node, Node<state_t> *bwd_node, const long unsigned int expanded_nodes) {
	std::deque<Node<state_t> *> bwd_children(1, fwd_node);
	while(bwd_node && bwd_node->action) {
		/** @todo Bidirectional::search -> "elegante" mas ineficiente. */
		bwd_children.push_back(child_node(bwd_children.back(), bwd_node->action));
		bwd_node = bwd_node->parent;
	}
	bwd_children.pop_front();
	Result<state_t> result = Result<state_t>(Result<state_t>::SUCCESS, bwd_children.back(), expanded_nodes + bwd_children.size());
	Utils::empty(bwd_children);
	return result;
}

template <class state_t>
void empty(std::deque<std::pair<state_t, IIA::Action<state_t> *> > &container) {
	for(std::pair<state_t, IIA::Action<state_t> *> &pair : container)
		delete pair.second;
	container.clear();
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
 * Result<Integer> result = Uninformed::Bidirectional::search(problem);
 * @endcode */
template <class state_t>
Result<state_t> search(const Problem<state_t> &problem) {
	if(problem.is_goal(problem.initial_state)) {
		Node<state_t> node(problem.initial_state);
		return Result<state_t>(Result<state_t>::SUCCESS, &node, 1);
	}

	std::deque<Node<state_t> *> fwd_frontier(1, new Node<state_t>(problem.initial_state));
	std::deque<Node<state_t> *> bwd_frontier;
	for(state_t state : problem.goal_states)
		bwd_frontier.push_back(new Node<state_t>(state));

	Result<state_t> result;
	result.expanded_nodes = fwd_frontier.size() + bwd_frontier.size();

	std::deque<Node<state_t> *> fwd_explored, bwd_explored;
	std::deque<const std::deque<Node<state_t> *> *> fwd_nodes, bwd_nodes;
	fwd_nodes.push_back(&fwd_frontier), fwd_nodes.push_back(&fwd_explored);
	bwd_nodes.push_back(&bwd_frontier), bwd_nodes.push_back(&bwd_explored);

	while(result.status != Result<state_t>::SUCCESS) {
		if(fwd_frontier.empty() && bwd_frontier.empty()) break;

		Node<state_t> *fwd_node, *bwd_node;

		if(!fwd_frontier.empty()) {
			fwd_node = fwd_frontier.front();
			fwd_frontier.pop_front(), fwd_explored.push_back(fwd_node);

			std::deque<Action<state_t> *> actions = problem.actions(fwd_node->state);
			for(Action<state_t> *action : actions) {
				Node<state_t> *child = child_node(fwd_node, action);
				++result.expanded_nodes;

				if(find_node(fwd_nodes, child->state)) {
					delete child;
					continue;
				}

				bwd_node = find_node(bwd_nodes, child->state);
				if(bwd_node) {
					result = join_searches(child, bwd_node, result.expanded_nodes);
					delete child;
					break;
				} else {
					fwd_frontier.push_back(child); // FIFO
				}
			}
			Utils::empty(actions);
		}
		
		// Volta
		if(result.status != Result<state_t>::SUCCESS && !bwd_frontier.empty()) {
			bwd_node = bwd_frontier.front();
			bwd_frontier.pop_front(), bwd_explored.push_back(bwd_node);

			std::deque<std::pair<state_t, IIA::Action<state_t> *> > predecessors = problem.predecessors(bwd_node->state);
			for(std::pair<state_t, IIA::Action<state_t> *> &pair : predecessors) {
				Node<state_t> *child = new Node<state_t>(pair.first, bwd_node, pair.second);
				++result.expanded_nodes;

				if(find_node(bwd_nodes, child->state)) {
					delete child;
					continue;
				}

				fwd_node = find_node(fwd_nodes, child->state);
				if(fwd_node) {
					result = join_searches(fwd_node, child, result.expanded_nodes);
					delete child;
					break;
				} else {
					bwd_frontier.push_back(child); // FIFO
				}
			}
			empty(predecessors);
		}
	}
	Utils::empty(fwd_frontier), Utils::empty(bwd_frontier);
	Utils::empty(fwd_explored), Utils::empty(bwd_explored);

	return result;
}
} // namespace Bidirectional
} // namespace Uninformed
} // namespace Search
} // namespace IIA

#endif // IIA_SEARCH_UNINFORMED_BIDIRECTIONAL_H
