/** @file SimpleProblemSolvingAgent.hpp
 *
 * Definição de agentes (racionais).
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 10/2011 */

#ifndef IIA_AGENTS_SIMPLE_PROBLEM_SOLVING_HPP
#define IIA_AGENTS_SIMPLE_PROBLEM_SOLVING_HPP

#include "TableDrivenAgent.hpp"
#include "Problem.hpp"
#include "SearchResult.hpp"

namespace IIA {
namespace Agents {
/** Um agente simples para resolução de problemas. Primeiro, formula o objetivo
 * e o problema, e busca por uma sequência de ações que resolveria o problema.
 * Depois executa as ações, uma por vez. Quando terminar, formula outro objetivo
 * e recomeça. */
template <class perception_t, class state_t>
class SimpleProblemSolvingAgent : public TableDrivenAgent<perception_t, state_t> {
public:
	/** Constructor. */
	SimpleProblemSolvingAgent(const IIA::Problem<state_t> &problem,
							  IIA::Search::Result<state_t> (*search)(const IIA::Problem<state_t> &)) :
		TableDrivenAgent<perception_t, state_t>(std::map<state_t, const Action<state_t> *>()) {
		using namespace IIA::Search;
		Result<state_t> result = search(problem);
		if(result.status != Result<state_t>::SUCCESS)
			throw std::runtime_error("Unable to find solution.");

		state_t state = problem.initial_state;
for(Action<state_t> *action : result.actions) {
			this->lookup_table[state] = action->clone();
			action->execute(state);
		}
	}
};
} // namespace Agents
} // namespace IIA

#endif // IIA_AGENTS_SIMPLE_PROBLEM_SOLVING_HPP
