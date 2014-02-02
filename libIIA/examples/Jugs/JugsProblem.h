/** @file JugsProblem.h
 *
 * Descreve uma jarra.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  10/2011 */

#ifndef IIA_EXAMPLES_JUGS_PROBLEM_H
#define IIA_EXAMPLES_JUGS_PROBLEM_H

#include "Problem.hpp"
#include "JugsState.h"

namespace IIA {
namespace Examples {
/** Define o escopo do problema das Jarras. */
namespace Jugs {
/** Define o problema. Dadas duas jarras com 3 e 4 litros de capacidade,
 * sem marcações de volume, e um reservatório infinito, como conseguir 2
 * litros em uma das jarras? */
class JugsProblem : public IIA::Problem<JugsState> {
public:
	/** Construtor. Inicializa o problema com um estado inicial e um objetivo. */
	JugsProblem(const JugsState &state, const JugsState &goal) :
	IIA::Problem<JugsState>(state, goal) {}

	/** Construtor. Inicializa o problema com um estado inicial e um conjunto de
	 * objetivos. */
	JugsProblem(const JugsState &state, const std::deque<JugsState> &goals):
	IIA::Problem<JugsState>(state, goals) {}

	/** Define as acoes possiveis conforme o estado dado. */
	std::deque<IIA::Action<JugsState> *> actions(const JugsState &state) const {
		std::deque<IIA::Action<JugsState> *> actions;

		for(unsigned int j = 0; j < state.jugs.size(); ++j) {
			if(!(state.jugs[j].is_full())) {
				//actions.push_back(new Put1(j));
				actions.push_back(new Fill(j));
			}
			for(unsigned int k = 0; k < state.jugs.size(); ++k) {
				if(j != k &&
				   !(state.jugs[j].is_empty()) &&
				   !(state.jugs[k].is_full()))
					actions.push_back(new Transfer(j, k));
			}
			if(!(state.jugs[j].is_empty()))
				actions.push_back(new Empty(j));
		}

		return actions;
	}
	
	/** Define os possíveis pares estado/ação de modo que a ação aplicada ao 
	 * estado associado resultaria no estado dado como parâmetro. */
	std::deque<std::pair<JugsState, Action<JugsState> *> > predecessors(const JugsState &state) const {
		std::deque<std::pair<JugsState, Action<JugsState> *> > pairs;

		for(unsigned int j = 0; j < state.jugs.size(); ++j) {
			if(state.jugs[j].is_full()) {
				JugsState new_state = state;
				new_state.jugs[j].empty();
				do {
					pairs.push_back(std::pair<JugsState, Action<JugsState> *> (new_state, new Fill(j)));
					// new_state.jugs[j].put(1);
				} while(!new_state.jugs[j].is_full());
			}
			if(state.jugs[j].is_empty()) {
				JugsState new_state = state;
				do {
					new_state.jugs[j].put(1);
					pairs.push_back(std::pair<JugsState, Action<JugsState> *> (new_state, new Empty(j)));
				} while(!new_state.jugs[j].is_full());
			}
			
			if(state.jugs[j].get_volume() > 0) {
				JugsState new_state = state;
				new_state.jugs[j].take(1);
				pairs.push_back(std::pair<JugsState, Action<JugsState> *> (new_state, new Put1(j)));
			}
		}

		return pairs;
	}
};
} // namespace Jugs
} // namespace Examples
} // namespace IIA

#endif	/* IIA_EXAMPLES_JUGS_PROBLEM_H */
