/** @file VacuumWorldSimpleProblemSolvingAgent.h
 *
 * Descreve um agente simples para o problema do mundo do aspirador.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  02/2012 */

#ifndef IIA_EXAMPLES_VACUUM_WORLD_SIMPLE_PROBLEM_SOLVING_H
#define IIA_EXAMPLES_VACUUM_WORLD_SIMPLE_PROBLEM_SOLVING_H

#include "SimpleProblemSolvingAgent.hpp"
#include "VacuumWorldProblem.h"

namespace IIA {
namespace Examples {
namespace VacuumWorld {
/** Agente de resolução de problemas. */
class VacuumWorldSimpleProblemSolvingAgent : public IIA::Agents::SimpleProblemSolvingAgent<VacuumWorldState, VacuumWorldState> {
public:
	/** Construtor. */
	VacuumWorldSimpleProblemSolvingAgent(const VacuumWorldProblem &problem, IIA::Search::Result<VacuumWorldState> (*search)(const IIA::Problem<VacuumWorldState> &)):
	IIA::Agents::SimpleProblemSolvingAgent<VacuumWorldState, VacuumWorldState>(problem, search) {}

	/** Retorna a percepção do agente da situação atual. */
	VacuumWorldState percept() const {
		/**@todo "Implement SimpleProblemSolvingAgent::percept" */
		throw std::logic_error("SimpleProblemSolvingAgent::percept() not implemented.");
	}

	/** Interpreta a percepção. */
	VacuumWorldState interpret_input(const VacuumWorldState &percept) const { return percept; }
};
} // namespace VacuumWorld
} // namespace Examples
} //namespace IIA

#endif /* IIA_EXAMPLES_VACUUM_WORLD_SIMPLE_PROBLEM_SOLVING_H */
