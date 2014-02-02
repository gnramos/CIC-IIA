/** @file Problem.hpp
 *
 * Definição de um problema.
 *
 * @author Guilherme Ramos
 * @date October, 2012 */

#ifndef IIA_PROBLEM_HPP
#define IIA_PROBLEM_HPP

#include <deque>
#include <utility>
#include <set>
#include <stdexcept>

#include "Action.hpp"
#include "State.hpp" // Declaração da a função contains_state

namespace IIA {
/** Classe base para a formulação de um problema cuja solução (sequência
 * de ações que leva de um estado inicial qualquer ao estado objetivo do
 * problema) deve ser buscada.
 *
 * Exemplo de implementação:
 * @code
 * // Define o problema de, partindo do número 0, atingir os valores 4 ou -4.
 * class ZeroToFour : public Problem<Integer> {
 * public:
 * 	ZeroToFour()
 *		: Problem<Integer>(Integer(0), Integer(0)) {
 * 		goal_states.clear();
 * 		goal_states.insert(Integer(4));
 * 		goal_states.insert(Integer(-4));
 * 	}
 *
 * 	// Para qualquer estado, apenas 3 ações são possíveis: +1, -1, *2.
 *	std::deque<Action<Integer> *> actions(const Integer &state) const {
 * 		std::deque<Action<Integer> *> actions;
 *
 * 		actions.push_back(new Add(1));
 * 		actions.push_back(new Add(-1));
 * 		actions.push_back(new Multiply(2));
 *
 * 		return actions;
 * 	}
 * };
 * @endcode */
template <class state_t>
class Problem {
public:
	/**  Cria uma nova instância do problema, definindo o estado inicial e o
	 * objetivo. */
	Problem(const state_t &initial, const state_t &goal) : 
		initial_state(initial) {
		goal_states.insert(goal);
	}

	/**  Cria uma nova instância do problema, definindo o estado inicial e um
	 * conjunto de possíveis objetivos. */
	Problem(const state_t &initial, const std::deque<state_t> &goals) :
		initial_state(initial), 
		goal_states(goals.begin(), goals.end()) {
		if(goals.empty())
			throw std::invalid_argument("Problem must have at least one goal state.");
	}

	/** Verifica se o estado dado como argumento é um (dos) objetivo(s) do problema.
	 *
	 * @param state estado a ser testado como objetivo. */
	virtual bool is_goal(const state_t &state) const {
		return contains_state(goal_states, state);
	}

	/** Define as ações que podem ser realizadas no estado dado como argumento.
	 * Cada referência retornada é uma nova instância de uma ação. */
	virtual std::deque<Action<state_t> *> actions(const state_t &state) const = 0;

	/** @todo documentar Problem::predecessors */
	virtual std::deque<std::pair<state_t, Action<state_t> *> > predecessors(const state_t &state) const {
		return std::deque<std::pair<state_t, Action<state_t> *> >();
	}

	// Attributes
public:
	/** O estado inicial do problema. */
	state_t initial_state;
	/** Estado(s) objetivo(s) do problema. */
	std::set<state_t> goal_states;
};
} // namespace IIA

#endif // IIA_PROBLEM_HPP
