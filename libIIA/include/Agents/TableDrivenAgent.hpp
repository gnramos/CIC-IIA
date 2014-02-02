/** @file TableDrivenAgent.hpp
 *
 * Definição de um agente (racional).
 *
 * @author Guilherme Ramos
 * @date October, 2012 */

#ifndef IIA_AGENTS_TABLE_DRIVEN_HPP
#define IIA_AGENTS_TABLE_DRIVEN_HPP

#include <deque>
#include <map>

#include "Agent.hpp"

namespace IIA {
namespace Agents {
/** Implementa um agente que decide baseado em uma tabela estado-ação. */
template <class perception_t, class state_t>
class TableDrivenAgent : public Agent<perception_t, state_t> {
public:
	/** Construtor. */
	TableDrivenAgent(const std::map<state_t, const Action<state_t> *> &table)
		: Agent<perception_t, state_t>(), lookup_table(table) {}

	// overload
	virtual state_t act(const perception_t &perception) {
		/** Armazena a sequência de percepções. */
		this->percepts.push_back(perception);

		return Agent<perception_t, state_t>::act(perception);
	}

protected:
	/** Busca a ação associada à última percepção, e retorna uma cópia desta, se
	 * houver, DoNothing caso contrário. */
	virtual Action<state_t> *decide_action(const state_t &state) {
		typename std::map<state_t, const Action<state_t> *>::iterator action_it = lookup_table.find(state);

		if(action_it != lookup_table.end())
			return action_it->second->clone();

		return new DoNothing<state_t>();
	}

	// Attributes
	/** Lista de percepções. */
	std::deque<perception_t> percepts;
	/** Tabela estado-ação. */
	std::map<state_t, const Action<state_t> *> lookup_table;
};
} // namespace Agents
} // namespace IIA

#endif // IIA_AGENTS_TABLE_DRIVEN_HPP
