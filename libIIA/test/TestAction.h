/** @file TestAction.h
 * 
 * Implementa testes para a classe IIA::Action.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#ifndef IIA_TEST_ACTION_H
#define IIA_TEST_ACTION_H

#include "Action.hpp"
#include "Utils.h"
 
#include "TestState.h"

namespace IIA {
namespace Test {
namespace Action {
/** Define a classe base para operações em números. */
class Operation : public IIA::Action<State::Integer> {
public:
	Operation(const int num, double cost) : IIA::Action<State::Integer>(cost), number(num) {}
	int number;
};

/** Define a ação "adicionar", que adiciona o número especificado ao estado. */
class Add : public Operation {
public:
	Add(const int num, double cost = 0.5) : Operation(num, cost) {}
	Add(const Add &add) : Operation(add.number, add.cost) {}
	Add *clone() const {return new Add(*this);}
	void execute(State::Integer&state) const {state.number += this->number;}
	std::string to_string() const {
		if(number < 0)
			return IIA::Utils::String::to_string(number);
		return "+" + IIA::Utils::String::to_string(number);
	}
};

/** Define a ação "multiplicar", que multiplica o estado pelo número especificado. */
class Multiply : public Operation {
public:
	Multiply(int num, double cost = 0.75) : Operation(num, cost) {}
	Multiply(const Multiply &multiply) : Operation(multiply.number, multiply.cost) {}
	Multiply *clone() const {return new Multiply(*this);}
	void execute(State::Integer&state) const {state.number *= this->number;}
	std::string to_string() const {
		if(number < 0)
			return "*(" + IIA::Utils::String::to_string(number) +")";
		return "*" + IIA::Utils::String::to_string(number);
	}
};
} // namespace Action
} // namespace Test
} // namespace IIA

#endif // IIA_TEST_ACTION_H
