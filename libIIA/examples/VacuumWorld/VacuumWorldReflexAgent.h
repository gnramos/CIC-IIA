/* @file VacuumWorldReflexAgent.h
 *
 * Descreve um agente reflexivo simples para o mundo do aspirador.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 02/2012 */

#ifndef IIA_EXAMPLES_VACUUMWORLD_REFLEX_AGENT_H
#define IIA_EXAMPLES_VACUUMWORLD_REFLEX_AGENT_H

#include "Agent.hpp"
#include "VacuumWorldState.h"

namespace IIA {
namespace Examples {
/** Define o escopo para o aspirador de pó como agente. */
namespace VacuumWorld {
/** Define um aspirador de pó reflexivo. */
class ReflexVacuumAgent : public IIA::Agents::Agent<VacuumWorldState, VacuumWorldState> {
public:
	/** Construtor. */
	ReflexVacuumAgent()
	: IIA::Agents::Agent<VacuumWorldState, VacuumWorldState>() {}
	
	/** Retorna a percepção do agente da situação atual. */
	VacuumWorldState percept() const {
		/** @todo "Implement ReflexVacuumAgent::percept" */
		throw std::logic_error("ReflexVacuumAgent::percept() not implemented.");
	}

	/** Interpreta a percepção. */
	VacuumWorldState interpret_input(const VacuumWorldState &percept) const { return percept; }

	/** Decide a ação baseado no estado dado. */
	IIA::Action<VacuumWorldState> *decide_action(const VacuumWorldState &state) {
		if(state.is_dirty(state.location())) return new Suck();
		if(state.location() == VacuumWorldState::A) return new Move(VacuumWorldState::B);
		return new Move(VacuumWorldState::A);
	}
};
} // namespace VacuumWorld
} // namespace Examples
} //namespace IIA

#endif	/* IIA_EXAMPLES_VACUUMWORLD_REFLEX_AGENT_H */
