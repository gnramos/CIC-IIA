/** @file Action.hpp
 *
 * Definição de uma ação (em um estado).
 *
 * @author Guilherme Ramos (gnramos@unb.br)
 * @date October, 2012 */

#ifndef IIA_ACTION_HPP
#define IIA_ACTION_HPP

#include <string>

namespace IIA {
/** Template para definir uma ação (em um estado). Uma ação geralmente representa
 * uma transição entre estados.
 *
 * Exemplo de implementação:
 * @code
 * // Define a ação que adiciona o número especificado a um estado.
 * class Add : public Action<Integer> {
 * public:
 * 	Add(const int num, double cost = 0.5)
 *		: Action<Integer>(cost), number(num) {
 *	}
 *
 * 	Add(const Add &add)
 *		: Action<Integer>(add.cost), number(add.number) {
 *	}
 *
 * 	Add *clone() const {
 *		return new Add(*this);
 *	}
 *
 * 	void execute(Integer &state) const {
 *		state.number += this->number;
 *	}
 *
 *	std::string to_string() const {
 *		return "" + number;
 *	}
 *
 * 	int number;
 * };
 * @endcode */
template <class state_t>
class Action {
public:
	/** Cria uma nova instância com o custo dado.
	 *
	 * @param c o custo associado a execução da ação.*/
	Action(const double c = 0) : cost(c) {}
	
	/** Destrutor. */
	virtual ~Action() {}

	/** Retorna a referência para uma cópia desta instância. */
	virtual Action<state_t> *clone() const = 0;

	/** Executa a ação no estado fornecido e retorna o estado resultante da
	 * execução da ação no argumento.
	 *
	 * @param state estado em que a ação será executada.
	 * @see void execute(state_t &state) const */
	state_t *result(const state_t &state) const {
		state_t *new_state = new state_t(state);
		execute(*new_state);
		return new_state;
	}

	/** Executa a ação no estado fornecido e o altera de acordo.
	 *
	 * @param state estado em que a ação será executada. */
	virtual void execute(state_t &state) const = 0;

	/** Descreve a ação. */
	virtual std::string to_string() const = 0;

	// Attributes
	/** Custo associado a execução da ação. */
	const double cost;
};

/** Define uma ação que <b>não</b> altera o estado a custo @em zero. */
template <class state_t>
class DoNothing : public Action<state_t> {
public:
	/** Construtor. */
	DoNothing(double cost = 0) : Action<state_t>(0) {}
	/** Construtor. */
	DoNothing(const DoNothing &action) : Action<state_t>(action.cost) {}
	//overload
	DoNothing *clone() const {return new DoNothing(*this);}
	// overload
	void execute(state_t &s) const {}
	// overload
	std::string to_string() const { return "Do nothing."; }
};
} // namespace IIA

#endif // IIA_ACTION_HPP
