/* @file VacuumWorldAction.h
 *
 * Descreve uma ação no mundo do aspirador.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  02/2012 */

#ifndef IIA_EXAMPLES_VACUUMWORLD_ACTION_H
#define IIA_EXAMPLES_VACUUMWORLD_ACTION_H

#include "Action.hpp"
#include "VacuumWorldState.h"

namespace IIA {
namespace Examples {
/** Define o escopo para o aspirador de pó como agente. */
namespace VacuumWorld {
/** Define a ação "limpar". */
class Suck : public IIA::Action<VacuumWorldState> {
public:
	/** Instancia a ação.
	 *
	 * @param cost o custo da ação. */
	Suck(const double cost = 1) : IIA::Action<VacuumWorldState>(cost) {}
	
	/** Instancia a ação como cópia da ação dada. */
	Suck(const Suck &suck) : IIA::Action<VacuumWorldState>(suck.cost) {}
	
	/** Retorna a referência para uma nova instância que é cópia desta. */
	Suck *clone() const { return new Suck(cost); }

	/** Retorna uma representação da ação como string. */
	std::string to_string() const { return std::string("limpar"); }
	
	/** Executa a ação no estado dado. */
	void execute(VacuumWorldState &state) const {
		state.dirty_locations[state.location()] = false;
	}
};

/** Define a ação "mover". */
class Move : public IIA::Action<VacuumWorldState> {
public:
	/** Instancia a ação.
	 *
	 * @param l para onde se mover .
	 * @param cost o custo da ação. */
	Move(VacuumWorldState::Location l, const double cost = 1) :
	IIA::Action<VacuumWorldState>(cost), location(l) {}
	
	/** Instancia a ação como cópia da ação dada. */
	Move(const Move &move) :
	IIA::Action<VacuumWorldState>(move.cost), location(move.location) {}
	
	/** Retorna a referência para uma nova instância que é cópia desta. */
	Move *clone() const { return new Move(location, cost); }

	/** Retorna uma representação da ação como string. */
	std::string to_string() const{
		std::string str("mover para ");
		return str + Utils::String::to_string(location);
	}
	
	/** Executa a ação no estado dado. */
	void execute(VacuumWorldState &state) const{ state.vc_location = location; }
private:
	/** O destino para onde se mover. */
	VacuumWorldState::Location location;
};
} // namespace VacuumWorld
} // namespace Examples
} //namespace IIA

#endif	/* IIA_EXAMPLES_VACUUMWORLD_ACTION_H */
