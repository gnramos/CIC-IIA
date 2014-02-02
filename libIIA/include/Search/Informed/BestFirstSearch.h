/** @file BestFirstSearch.h
 *
 * Definição do algoritmo de busca com informação "melhor-primeiro".
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 10/2011 */

#ifndef IIA_SEARCH_INFORMED_BEST_FIRST_H
#define IIA_SEARCH_INFORMED_BEST_FIRST_H

#include <limits>

#include "Problem.hpp"
#include "SearchResult.hpp"
#include "Informed/HeuristicSearchNode.hpp"

namespace IIA {
namespace Search {
namespace Informed {
/** Define o algoritmo de busca "Melhor-primeiro". Ele explora o grafo
 * selecionando o nó mais promissor, o de menor custo associado. Neste caso,
 * o custo considerado é apenas a estimativa do nó até o objetivo , i.e.
 * f(n) = h(n). */
namespace BestFirst {
namespace { // unnamed
/** Busca uma solução partindo de um nó, de acordo com a definição do problema,
 * até o limite de profundidade.
 *
 * @param [in] node nó inicial para a busca.
 * @param [in] problem problema a ser resolvido.
 * @param [in] h_calc funçãoo que estiva o custo do nó até o objetivo.
 * @param [out] f_limit limite de profundidade para busca.
 *
 * @return Result o resultado da busca. */
template <class state_t>
Result<state_t> RBFS(const Problem<state_t> &problem,
					 HeuristicNode<state_t> *node, 
					 const HeuristicCalc<state_t> &h_calc,
					 double &f_limit) {
	if(problem.is_goal(node->state))
		return IIA::Search::Result<state_t>(Result<state_t>::SUCCESS, node, 0);

	std::deque<HeuristicNode<state_t> *> successors;
	long unsigned int expanded_nodes = 0;

	std::deque<Action<state_t> *> actions = problem.actions(node->state);
	for(Action<state_t> *action : actions) {
		HeuristicNode<state_t> *child = child_node(node, action, h_calc);
		++expanded_nodes;
		if(in_parent_node(node, child->state))
			delete child;
		else
			successors.push_back(child);
	}
	Utils::empty(actions);

	if(successors.empty()) {
		f_limit = std::numeric_limits<double>::max();
		return Result<state_t>(Result<state_t>::FAILURE, nullptr, expanded_nodes);
	}

	// update f with value from previous search, if any
	for(HeuristicNode<state_t> *successor : successors) {
		if(successor->f_cost() < node->f_cost()) {
			successor->path_cost = node->path_cost;
			successor->h_cost = node->h_cost;
		}
	}

	Result<state_t> result(Result<state_t>::FAILURE);
	while(true) {
		HeuristicNode<state_t> *best = successors.front();
		double alternative = std::numeric_limits<double>::infinity();
		for(HeuristicNode<state_t> *successor : successors) {
			if(best->f_cost() > successor->f_cost())
				best = successor;
			else if(alternative > successor->f_cost())
				alternative = successor->f_cost();
		}

		if(best->f_cost() > f_limit) {
			f_limit = best->f_cost();
			result = Result<state_t>(Result<state_t>::FAILURE, nullptr, expanded_nodes);
			break;
		}

		f_limit = std::min(f_limit, alternative);
		result = RBFS(problem, best, h_calc, f_limit);
		result.expanded_nodes += expanded_nodes;
		best->h_cost = f_limit - best->path_cost; // best->f_cost = f_limit

		if(result.status != Result<state_t>::FAILURE)
			break;
	}

	Utils::empty(successors);

	return result;
}
} // unnamed namespace

/** Busca a solução do problema aumentando iterativamente a profundidade.
 *
 * @param problem o problema a ser solucionado.
 * @param h_calc funçãoo que estiva o custo do nó até o objetivo.
 * @param limit a profundidade máxima a procurar.
 * @return IIA::Search::Result o resultado da busca.
 *
 * Exemplo de uso:
 * @code
 * using namespace IIA::Search;
 *
 * ZeroToFour problem;
 * Result<Integer> result = Informed::BestFirst::search(problem);
 * @endcode */
template <class state_t>
Result<state_t> search(const Problem<state_t> &problem, const HeuristicCalc<state_t> &h_calc, double limit) {
	double f_limit = limit;
	HeuristicNode<state_t> *node = new HeuristicNode<state_t>(problem.initial_state, nullptr, nullptr, 0, h_calc.eval(problem.initial_state));
	Result<state_t> result = RBFS<state_t>(problem, node, h_calc, f_limit);
	delete node;

	return result;
}
/** Busca a solução do problema aumentando iterativamente a profundidade.
 *
 * @param problem o problema a ser solucionado.
 * @param h_calc a heurística a ser utilizada.
 *
 * @return IIA::Search::Result o resultado da busca.*/
template <class state_t>
Result<state_t> search(const Problem<state_t> &problem, const HeuristicCalc<state_t> &h_calc) {
	return search(problem, h_calc, std::numeric_limits<double>::infinity());
}
} // namespace BestFirst
} // namespace Informed
} // namespace Search
} // namespace IIA

#endif // IIA_SEARCH_INFORMED_BEST_FIRST_H
