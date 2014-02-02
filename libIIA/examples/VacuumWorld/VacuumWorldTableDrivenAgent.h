/** @file VacuumWorldTableDrivenAgent.h
 *
 * Descreve um agente para o mundo do aspirador.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  02/2012 */

#ifndef IIA_EXAMPLES_VACUUMWORLD_TABLE_DRIVEN_AGENT_H
#define IIA_EXAMPLES_VACUUMWORLD_TABLE_DRIVEN_AGENT_H

#include "TableDrivenAgent.hpp"
#include "VacuumWorldState.h"

namespace IIA {
namespace Examples {
namespace VacuumWorld {
/** Define um aspirador de pó que decide baseado em uma tabela estado-ação. */
class VacuumWorldTableDrivenAgent : public IIA::Agents::TableDrivenAgent<VacuumWorldState, VacuumWorldState> {
public:
	/** Construtor. */
	VacuumWorldTableDrivenAgent(const std::map<VacuumWorldState, const IIA::Action<VacuumWorldState> *> &lookup_table)	:  IIA::Agents::TableDrivenAgent<VacuumWorldState, VacuumWorldState>(lookup_table) {
}

	/** Retorna a percepção do agente da situação atual. */
	VacuumWorldState percept() const{
	/** @todo "Implement TableDrivenAgent::percept" */
	throw std::logic_error("TableDrivenAgent::percept() not implemented.");
}

	/** Interpreta a percepção. */
	VacuumWorldState interpret_input(const VacuumWorldState &percept) const {return percept;}
};
} // namespace VacuumWorld
} // namespace Examples
} //namespace IIA

#endif	/* IIA_EXAMPLES_VACUUMWORLD_TABLE_DRIVEN_AGENT_H */
