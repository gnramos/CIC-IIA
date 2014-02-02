/** @file ModelBasedReflexAgent.hpp
 *
 * Definição de um agentes (racional).
 *
 * @author Guilherme Ramos
 * @date October, 2012 */

#ifndef IIA_AGENTS_MODEL_BASED_REFLEX_HPP
#define IIA_AGENTS_MODEL_BASED_REFLEX_HPP

#include <deque>

#include "Agent.hpp"

namespace IIA {
namespace Agents {
/** Um agente reflexivos simples baseados no modelo tenta lidar com
 * ambientes parcialmente observáveis mantendo um histórico das partes
 * que ele não consegue perceber (no momento). Isso requer dois tipos
 * de conhecimento:
 *  - Como o ambiente muda ao longo do tempo (independentemente do agente).
 *  - Como as ações do agente afetam o ambiente.
 *
 * Portanto, é preciso modelar o ambiente para que o agente possa usá-lo.
 *
 * @todo Implementar */
template <class perception_t, class state_t>
class ModelBasedReflexAgent : public Agent<perception_t, state_t> {
public:
	/** Construtor. */
	ModelBasedReflexAgent() {};

	/** Destrutor. */
	virtual ~ModelBasedReflexAgent() throw() {
		delete last_action;
	}

	Action<state_t> * decide_action(const perception_t *percept) {
		state_t state = interpret_input(percept);
		states.push_back(state);

		/** @see Action<state_t> rule_match(const state_t &) const */
		last_action = rule_match(state);
		return last_action;
	}

protected:
	// overload
	state_t interpret_input(const perception_t &percept) const;

	// Attributes
	/** A última ação executada. */
	Action<state_t> *last_action;
	/** Lista de estados. */
	std::deque<state_t> states;
};
} // namespace Agents
} // namespace IIA

#endif // IIA_AGENTS_MODEL_BASED_REFLEX_HPP
