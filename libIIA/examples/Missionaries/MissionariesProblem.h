/** @file MissionariesProblem.h
 *
 * Descreve o problema de Missionários e Canibais.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  10/2011 */

#ifndef IIA_EXAMPLES_MISSIONARIES_PROBLEM_H
#define IIA_EXAMPLES_MISSIONARIES_PROBLEM_H

#include "Problem.hpp"
#include "MissionariesState.h"

namespace IIA {
namespace Examples {
/** Define o escopo do problema dos Missionários e Canibais. */
namespace Missionaries {
/** Define o problema. */
class MissionariesProblem : public IIA::Problem<MissionariesState> {
public:
	/** Construtor. Inicializa o problema com um estado inicial e um objetivo. */
	MissionariesProblem(const MissionariesState &state, const MissionariesState &goal) :
	IIA::Problem<MissionariesState>(state, goal) {}

	/** Construtor. Inicializa o problema com um estado inicial e um conjunto de
	 * objetivos. */
	MissionariesProblem(const MissionariesState &state, const std::deque<MissionariesState> &goals) :
	IIA::Problem<MissionariesState>(state, goals) {}

	/** Define as ações possíveis conforme o estado dado. */
	std::deque<IIA::Action<MissionariesState> *> actions(const MissionariesState &state) const {
		std::deque<IIA::Action<MissionariesState> *> actions;

		const unsigned int capacidade_da_canoe = 2;
		const Margin *from, *to;
		if(state.left.canoe)
			from = &(state.left), to = &(state.right);
		else
			from = &(state.right), to = &(state.left);
		for(unsigned int missionaries = 0; missionaries <= std::min(from->missionaries, capacidade_da_canoe); ++missionaries) {
			for(unsigned int cannibals = 0; cannibals <= std::min(from->cannibals, capacidade_da_canoe - missionaries); ++cannibals) {
				if(missionaries + cannibals > 0)
					if(restricao_ok(from->missionaries - missionaries, from->cannibals - cannibals)
				&& restricao_ok(to->missionaries + missionaries, to->cannibals + cannibals))

				actions.push_back(new Cross(missionaries, cannibals));
			}
		}

		return actions;
	}

	/** Define os possíveis pares estado/ação de modo que a ação aplicada ao 
	 * estado associado resultaria no estado dado como parâmetro. */
	std::deque<std::pair<MissionariesState, Action<MissionariesState> *> > predecessors(const MissionariesState &state) const {
		std::deque<std::pair<MissionariesState, Action<MissionariesState> *> > pairs;

		const unsigned int capacidade_da_canoe = 2;
		const Margin *to = (state.right.canoe ? &(state.right) : &(state.left));

		for(unsigned int missionaries = 0; missionaries <= std::min(to->missionaries, capacidade_da_canoe); ++missionaries) {
			for(unsigned int cannibals = 0; cannibals <= std::min(to->cannibals, capacidade_da_canoe - missionaries); ++cannibals) {
					if(missionaries + cannibals == 0) continue;

					MissionariesState prev_state = state;
					Margin *prev_from, *prev_to;
					if(prev_state.left.canoe)
						prev_from = &(prev_state.right), prev_to = &(prev_state.left);
					else
						prev_from = &(prev_state.left), prev_to = &(prev_state.right);

					prev_from->missionaries += missionaries, prev_to->missionaries -= missionaries;
					prev_from->cannibals += cannibals, prev_to->cannibals -= cannibals;
					prev_from->canoe = true, prev_to->canoe = false;
					if(restricao_ok(prev_from->missionaries, prev_from->cannibals)
					&& restricao_ok(prev_to->missionaries, prev_to->cannibals))
						pairs.push_back(std::pair<MissionariesState, Action<MissionariesState> *> (prev_state, new Cross(missionaries, cannibals)));
			}
		}

		return pairs;
	}

private:
	bool restricao_ok(int miss, int cann) const {
		return (miss == 0 || cann <= miss);
	}
};
} // namespace Missionarios
} // namespace Examples
} // namespace IIA

#endif	/* IIA_EXAMPLES_MISSIONARIES_PROBLEM_H */
