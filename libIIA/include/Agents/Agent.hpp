/** @file Agent.hpp
 *
 * Definição de agentes (racionais).
 *
 * @author Guilherme Ramos (gnramos@unb.br)
 * @date 5/2012 */

#ifndef IIA_AGENTS_AGENT_HPP
#define IIA_AGENTS_AGENT_HPP

#include "Action.hpp"

namespace IIA {
/** Define o escopo para implementações relacionadas a agentes (racionais). Um
 * agente é algo que percebe o ambiente (por meio de <i>sensores</i>) e age sobre
 * ele (por meio de <i>atuadores</i>). Um agente racional é aquele que, em função
 * de sua percepção, escolhe a ação que deve maximizar seu desempenho. */
namespace Agents {
/** Classe abstrata que deve ser implementada por cada agente. */
template <class perception_t, class state_t>
class Agent {
public:
	/** Construtor. */
	Agent() {};

	/** Retorna a percepção que o agente tem do ambiente. */
	virtual perception_t percept() const = 0;

	/** Interpreta a percepção dada e age de acordo, retornando o estado
	 * resultante.
	 *
	 * @see state_t interpret_input(const perception_t &) const
	 * @see void decide_and_act(state_t &) */
	virtual state_t act(const perception_t &perception) {
		state_t state = interpret_input(perception);
		decide_and_act(state);
		return state;
	}

protected:
	/** Interpreta a percepção, transformando-a em uma representação do ambiente
	 * (estado).
	 *
	 * @param percept a percepção do agente.
	 * @return state_t estado que representa a percepção do agente. */
	virtual state_t interpret_input(const perception_t &percept) const = 0;

	/** Escolhe a ação a tomar com base no estado dado
	 *
	 * @param state o estado em questão.
	 * @return Action<state_t> * referência para uma <b>nova</b> instância da ação
	 * escolhida. */
	virtual Action<state_t>* decide_action(const state_t &state) = 0;

private:
	/** Decide a ação a tomar baseada no estado dado e a executa sobre ele.
	 *
	 * @see Action<state_t>* decide_action(const state_t &) const
	 * @see Action<state_t>::execute(state_t &) const */
	inline void decide_and_act(state_t &state) {
		Action<state_t>* action = decide_action(state);
		action->execute(state);
		delete action;
	}
};
} // namespace Agents
} // namespace IIA

#endif // IIA_AGENTS_AGENT_HPP
