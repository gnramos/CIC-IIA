/** @file LocalSearch.h
 *
 * Definição de algoritmos de busca local.
 *
 * @author Guilherme Ramos
 * @date October, 2012 */

#ifndef IIA_SEARCH_LOCAL_H
#define	IIA_SEARCH_LOCAL_H

#include <algorithm>

#include "Problem.hpp"
#include "SearchResult.hpp"

namespace IIA {
namespace Search {
/** @todo Documentação */
namespace Local {
/** Define uma função de avaliação que fornece a utilidade do estado dado, em
 * função do problema. */
template <class state_t> double eval(const Problem<state_t> &problem, const state_t &state) {
	return 0;
}
namespace { // unnamed
template <class state_t>
class EvalComparison {
public:
	EvalComparison(const Problem<state_t> &p) : problem(&p) {}
	/*bool operator()(const state_t *lhs, const state_t *rhs) const {
		return (*this)(*lhs, *rhs);
	}*/
	bool operator()(const state_t &lhs, const state_t &rhs) const {
		return (eval<state_t>(*problem, lhs) < eval<state_t>(*problem, rhs));
	}
private:
	const Problem<state_t> *problem;
};
} // unnamed namespace

namespace HillClimbing {
/** Retorna um estado que o máximo local. */
template <class state_t>
state_t search(const Problem<state_t> &problem) {
	state_t current = problem.initial_state;
	EvalComparison<state_t> &e_cmp(problem);

	while(true) {
		std::deque<state_t *> sucessors = problem.sucessors(current);
		std::sort(sucessors.begin(), sucessors.end(), e_cmp);
		state_t neighbor = *sucessors.front();
		Utils::empty(sucessors);

		if(e_cmp(current, neighbor)) return current;
		current = neighbor;
	}
}
} // namespace HillClimbing

static double schedule(int t) {
	return 0;
}

/** @todo Documentação */
template <class problem_t, class state_t>
state_t simulated_annealing(const problem_t &problem) {
	state_t current = problem.initial_state;
	state_t next;
	double T; //temperatura
	double delta;
	for(int t = 1; t < std::numeric_limits<int>::infinity(); ++t) {
		T = schedule(t);
		if(T == 0) return current;
		//next  = Utils::Random::get_random() (current.children)
		delta = eval(next) - eval(current);
		if(delta > 0)
			current = next;
		else {
			if(Utils::Random::get_random_dbl() < exp(delta / T))
				current = next;
		}
		return current;
	}
}
} // namespace Local
} // namespace Search
} // namespace IIA

#endif // IIA_SEARCH_LOCAL_H
