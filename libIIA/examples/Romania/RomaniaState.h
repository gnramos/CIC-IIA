/** @file RomaniaState.h
 *
 * Descreve um estado.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 06/2012 */
 
#ifndef IIA_EXAMPLES_ROMANIA_STATE_H
#define IIA_EXAMPLES_ROMANIA_STATE_H

#include <string>

#include "State.hpp"

namespace IIA {
namespace Examples {
/** Define o escopo do problema de movimentação na Romênia. */
namespace Romania {
/** Define um estado para o problema (nome da cidade). */
class RomaniaState : public IIA::State<RomaniaState> {
public:
	/** Construtor. */
	RomaniaState(const std::string &k = "") : key(k) {}
	
	/** Construtor. */
	RomaniaState(const RomaniaState &state) : key(state.key) {}

	
	/** Indica se a instância é igual ao estado dado. */
	bool operator==(const RomaniaState &that) const {return key == that.key;}
	/** Indica se a instância é menor que o estado dado. */
	bool operator<(const RomaniaState &that) const {return key < that.key;}
	/** Atribui a instância o estado dado. */
	RomaniaState &operator= (const RomaniaState &that) {
		if(this != &that) this->key = that.key;
		return *this;
	}
	
	/** Transforma em string. */
	friend std::ostream &operator <<(std::ostream &os, const RomaniaState &state) {
		os << state.key;
		return os;
	}
	
	// Atributes
	/** Armazena o nome da cidade (chave). */
	std::string key;
};
} // namespace Romania
} // namespace Examples
} // namespace IIA

#endif // IIA_EXAMPLES_ROMANIA_STATE_HPP
