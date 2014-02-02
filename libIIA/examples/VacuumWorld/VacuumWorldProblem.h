/** @file VacuumWorldProblem.h
 *
 * Descreve o problema do mundo do aspirador.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  02/2012 */

#ifndef IIA_EXAMPLES_VACUUMWORLD_PROBLEM_H
#define IIA_EXAMPLES_VACUUMWORLD_PROBLEM_H

#include "Problem.hpp"
#include "VacuumWorldAction.h"

namespace IIA {
namespace Examples {
/** Define o escopo para o aspirador de pó como agente. */
namespace VacuumWorld {
/**
 * Define o problema. Dadas duas jarras com 3 e 4 litros de capacidade,
 * sem marcações de volume, e um reservatório infinito, como
 * conseguir 2 litros em uma das jarras?
 */
class VacuumWorldProblem : public IIA::Problem<VacuumWorldState> {
public:
	/** Construtor. */
	VacuumWorldProblem(const VacuumWorldState &initial_state, const VacuumWorldState &goal_state) :
	IIA::Problem<VacuumWorldState>(initial_state, goal_state)
{}

	/** Construtor. */
	VacuumWorldProblem(const VacuumWorldState &initial_state, const std::deque<VacuumWorldState> &goal_states) :
	IIA::Problem<VacuumWorldState>(initial_state, goal_states)
{}

	/** Define as ações possíveis conforme o estado. */
	std::deque<IIA::Action<VacuumWorldState> *> actions(const VacuumWorldState &state) const  {
		std::deque<IIA::Action<VacuumWorldState> *> actions;

		if(state.is_dirty(state.location()))
			actions.push_back(new Suck());
		switch(state.location()) {
		case VacuumWorldState::A: 
			actions.push_back(new Move(VacuumWorldState::B));
			break;
		case VacuumWorldState::B: 
		            	actions.push_back(new Move(VacuumWorldState::A)); 
		            	break;
		default: ;//	actions.push_back(new DoNothing<VacuumWorldState>());
		}

		return actions;
	}
};
} // namespace VacuumWorld
} // namespace Examples
} //namespace IIA

#endif	/* IIA_EXAMPLES_VACUUMWORLD_PROBLEM_H */
