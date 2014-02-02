/** @file State.hpp
 *
 * Definição de um estado.
 *
 * @author Guilherme Ramos (gnramos@unb.br)
 * @date October, 2012 */

#ifndef IIA_STATE_HPP
#define IIA_STATE_HPP

namespace IIA {
/** Força a definição da função de atribuição para a classe. */
template <class class_t>
class Assignable {
public:
	/** Define a instância como cópia da instância dada como argumento. */
	virtual class_t &operator= (const class_t &that) = 0;
};

/** Força a definição das funções de comparação para a classe. */
template <class class_t>
class Comparable {
public:
	/** Indica se a instância é igual a instância dada como argumento. */
	virtual bool operator== (const class_t &that) const = 0;
	/** Indica se a instância é diferente a instância dada como argumento. */
	bool operator!= (const class_t &that) const {
		return !(*this == that);
	}
	/** Indica se a instância é menor que a instância dada como argumento. */
	virtual bool operator< (const class_t &that) const = 0;
	/** Indica se a instância é maior que a instância dada como argumento. */
	bool operator> (const class_t &that) const { 
		return (!(*this < that) && !(*this == that));
	}
	/** Indica se a instância é menor ou igual a instância dada como argumento. */
	virtual bool operator<= (const class_t &that) const {
		return (*this < that || *this == that);
	}
	/** Indica se a instância é maior ou igual a instância dada como argumento. */
	bool operator>= (const class_t &that) {
		return (*this > that || *this == that);
	}
};

/** Classe abstrata para definir um estado, que representa o ambiente de tarefas
 * em um determinado instante. Força a implementação operadores para comparação
 * entre instâncias.
 *
 * Exemplo de implementação:
 * @code
 * // Define um estado como um número inteiro.
 * class Integer : public State<Integer> {
 * public:
 * 	Integer(int num = 0)
 *		: number(num) {
 *	}
 *
 *	bool operator<(const Integer &that) const {
 *		return this->number < that.number;
 *	}
 *
 *	bool operator==(const Integer &that) const {
 *		return this->number == that.number;
 *	}
 *
 *	Integer &operator=(const Integer &that) {
 *		if(this != &that) this->number = that.number;
 *		return *this;
 *	}
 *
 *	int number;
 * };
 * @endcode */
template <class state_t>
class State : public Assignable<state_t>, public Comparable<state_t> {};

namespace { // State
/** Verifica se o container dado contém o estado. O primeiro argumento deve ser
 * iterável. */
template <class container_t, class state_t>
bool contains_state(const container_t &container, const state_t &state) {
	for(state_t s : container) if(s == state) return true;
	return false;
}

/** Verifica se o container dado contém o estado. O primeiro argumento deve
 * ser iterável e conter <b>ponteiros</b> para estruturas/classes que possuam um
 * atributo <i>state</i>. */
template <class container_t, class state_t>
bool contains_ptr_state(const container_t &container, const state_t &state) {
	for(auto ptr : container) if(ptr->state == state) return true;

	return false;
}
} // unnamed namespace // State
} // namespace IIA

#endif // IIA_STATE_HPP
