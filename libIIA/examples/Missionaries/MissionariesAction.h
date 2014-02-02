/** @file MissionariesAction.h
 *
 * Descreve as ações do problema dos Missionários e Canibais.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  10/2011 */

#ifndef IIA_EXAMPLES_MISSIONARIES_ACTION_H
#define IIA_EXAMPLES_MISSIONARIES_ACTION_H

#include "MissionariesState.h"
#include "Action.hpp"

namespace IIA {
namespace Examples {
namespace Missionaries {
/** Define a ação de atravessar o rio. */
class Cross : public IIA::Action<MissionariesState> {
public:
	/** Construtor. Inicializa a ação, cujo custo é definido
	 * com o valor 1. */
	Cross(unsigned int m, /**< indica o número de missionários que vão atravessar */
		  unsigned int c /**< indica o número de canibais que vão atravessar */
		  ) : IIA::Action<MissionariesState>(1), cannibals(c), missionaries(m) {}

	/** Retorna uma cópia da ação. */
	Cross *clone() const { return new Cross(missionaries, cannibals); }

	/** Executa a ação no estado dado. */
	void execute(MissionariesState &state) const {
		if(missionaries == 0 && cannibals == 0) return;

		Margin *origem, *destino;
		if(state.left.canoe) {
			origem = &(state.left), destino = &(state.right);
		}else {
			origem = &(state.right), destino = &(state.left);
		}
		origem->missionaries -= missionaries;
		origem->cannibals -= cannibals;
		origem->canoe = false;
		destino->missionaries += missionaries;
		destino->cannibals += cannibals;
		destino->canoe = true;
	}

	/** Retorna uma descrição da ação. */
	std::string to_string() const {
		std::stringstream sstr;
		sstr << "Atravessa" << (missionaries+cannibals > 1 ? "m " : " ");

		if(missionaries > 0)
			sstr << missionaries << (missionaries > 1 ? " missionários" : " missionário" );
		if(cannibals > 0) {
			if(missionaries > 0) sstr << " e ";
			sstr << cannibals << (cannibals > 1 ? " canibais" : " canibal");
		}
		return sstr.str();
	}

private:
	unsigned int cannibals, missionaries;
};
} // namespace Missionaries
} // namespace Examples
} // namespace IIA

#endif	/* IIA_EXAMPLES_MISSIONARIES_ACTION_H */
