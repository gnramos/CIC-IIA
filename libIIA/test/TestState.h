/** @file TestState.h
 * 
 * Implementa um estado para testes.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */
 
#ifndef IIA_TEST_STATE_H
#define IIA_TEST_STATE_H

#include <ostream>

#include "State.hpp"

namespace IIA {
namespace Test {
namespace State {
/** Define um estado como um número inteiro. */
class Integer : public IIA::State<Integer> {
public:
	/** Construtor. */
	Integer(int num = 0) : number(num) {}
	
	/** Indica se a instância é menor que o argumento dado. */
	bool operator< (const Integer &that) const {return this->number < that.number;}
	/** Indica se a instância é igual ao argumento dado. */
	bool operator== (const Integer &that) const {return this->number == that.number;}
	/** Atribui à instância o argumento dado. */
	Integer &operator= (const Integer &that) {
		if(this != &that) this->number = that.number;
		return *this;
	}
	/** Converte a coordenada em string. */
	friend std::ostream &operator <<(std::ostream &os, const Integer &state) {
		os << state.number;
		return os;
	}
	/** Armazena o número. */
	int number;
};
} // namespace State
} // namespace Test
} // namespace IIA

#endif // IIA_TEST_STATE_H
