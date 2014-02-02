/** @file JugsAction.h
 *
 * Descreve as ações em uma jarra.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  10/2011 */

#ifndef IIA_EXAMPLES_JUGS_ACTION_H
#define IIA_EXAMPLES_JUGS_ACTION_H

#include "JugsState.h"
#include "Action.hpp"

namespace IIA {
namespace Examples {
/** Define o escopo do problema das Jarras. */
namespace Jugs {
/** Define a ação de encher uma jarra. */
class Fill : public IIA::Action<JugsState> {
public:
	/** Construtor. Inicializa a ação, cujo custo é definido
	 * com o valor 1. */
	Fill(const unsigned int ji, /**< índice da jarra a ser enchida */
	     const double cost = 1 /**< o custo de executar a ação */ )
		: IIA::Action<JugsState>(cost), jug_index(ji) {}

	/** Retorna uma cópia da ação. */
	Fill *clone() const { return new Fill(jug_index, cost); }

	/** Executa a ação no estado dado. */
	void execute(JugsState &state) const { state.jugs[jug_index].fill(); }

	/** Retorna uma descrição da ação. */
	std::string to_string() const {
		return "encher J" + IIA::Utils::String::to_string(jug_index);
	}

private:
	unsigned int jug_index; /**< Indica a jarra a ser enchida. */
};

/** Define a ação de esvaziar uma jarra. */
class Empty : public IIA::Action<JugsState> {
public:

	/** Construtor. */
	Empty(const unsigned int ji, /**< indica o índice da jarra a ser enchida */
	      const double cost = 1 /**< o custo de executar a ação */
		 )
	: IIA::Action<JugsState>(cost), jug_index(ji) {}

	/** Retorna uma cópia da ação. */
	Empty *clone() const {return new Empty(jug_index, cost);}
	/** Executa a ação no estado dado. */
	void execute(JugsState &state) const {state.jugs[jug_index].empty();}
	/** Retorna uma descrição da ação. */
	std::string to_string() const {
		return "esvaziar J" + IIA::Utils::String::to_string(jug_index);
	}

private:
	unsigned int jug_index; /**< Indica a jarra a ser esvaziada. */
};

/** Define a ação de por 1 litro em uma jarra. */
class Put1 : public IIA::Action<JugsState> {
public:

	/** Construtor. */
	Put1(const unsigned int ji, /**< índice da jarra a ser enchida */
	     const double cost = 50 /**< o custo de executar a ação */ )
	: IIA::Action<JugsState>(cost), jug_index(ji) {}

	/** Retorna uma cópia da ação. */
	Put1 *clone() const {return new Put1(jug_index, cost);}

	/** Executa a ação no estado dado. */
	void execute(JugsState &state) const {
		state.jugs[jug_index].put(1);
	}
	
	/** Retorna uma descrição da ação. */
	std::string to_string() const {
		return "por 1L em J" + IIA::Utils::String::to_string(jug_index);
	}

private:
	unsigned int jug_index; /**< Indica a jarra a colocar 1 L. */
};


/** Define a ação de servir de uma jarra para outra. */
class Transfer : public IIA::Action<JugsState> {
public:
	/** Construtor. Inicializa a ação, cujo custo é definido
	 * com o valor 3.
	 *
	 * @param from o índice da jarra de onde se tira água.
	 * @param to o índice da jarra onde se coloca água.
	 * @param cost o custo de executar a ação. */
	Transfer(const unsigned int from, const unsigned int to, const double cost = 1) 
	: IIA::Action<JugsState>(cost), from_jug(from), to_jug(to) {}

	/** Retorna uma cópia da ação. */
	Transfer *clone() const {return new Transfer(from_jug, to_jug, cost);}

	/** Executa a ação no estado dado. */
	void execute(JugsState &state) const {
		double vol = std::min(state.jugs[from_jug].get_volume(), state.jugs[to_jug].get_capacity() - state.jugs[to_jug].get_volume());
		state.jugs[from_jug].take(vol);
		state.jugs[to_jug].put(vol);
	}

	/** Retorna uma descrição da ação. */
	virtual std::string to_string() const {
		return "transferir de J" + IIA::Utils::String::to_string(from_jug) +" para J" + IIA::Utils::String::to_string(to_jug);
	}

private:
	/** Índice da jarra de onde se tira água. */
	unsigned int from_jug;
	/** Índice da jarra onde se coloca água. */
	unsigned int to_jug;
};
} // namespace Jugs
} // namespace Examples
} // namespace IIA

#endif	/* IIA_EXAMPLES_JUGS_ACTION_H */
