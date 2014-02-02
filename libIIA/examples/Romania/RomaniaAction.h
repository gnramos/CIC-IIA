/** @file RomaniaAction.h
 *
 * Descreve as ações para o problema da Romênia.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 06/2012 */
 
#ifndef IIA_EXAMPLES_ROMANIA_ACTION_H
#define IIA_EXAMPLES_ROMANIA_ACTION_H

#include "Action.hpp"
#include "RomaniaState.h"

namespace IIA {
namespace Examples {
namespace Romania {
/** Define a ação de mover da [chave] origem para [a chave] destino. */
class Move : public IIA::Action<RomaniaState> {
public:
	/** Construtor. Instancia armazenando as chaves origem e destino, bem como o 
	 * custo associado a mover-se da primeira para a segunda. */
	Move(const std::string &from, const std::string &to, double cost)
	: IIA::Action<RomaniaState>(cost), origin(from), destination(to) {}
	
	/** Construtor. Instancia como cópia da ação dada. */
	Move(const Move &move)
	: IIA::Action<RomaniaState>(move.cost), origin(move.origin), destination(move.destination) {}
	
	/** Retorna uma cópia da ação. */
	Move *clone() const { return new Move(*this); }

	/** Executa a ação no estado dado. */
	void execute(RomaniaState&state) const {
		if(state.key != origin) throw std::invalid_argument("Cannot move from this origin.");
		state.key = destination;
	}
	
	/** Retorna uma descrição da ação. */
	std::string to_string() const {
		return "Move from " + Utils::String::to_string(origin) + " to " + Utils::String::to_string(destination);
	}

	// Attributes
	const std::string origin;      /** A [chave da] origem. */
	const std::string destination; /**< A [chave do] destino. */
};
} // namespace Romania
} // namespace Examples
} // namespace IIA

#endif // IIA_EXAMPLES_ROMANIA_ACTION_H
