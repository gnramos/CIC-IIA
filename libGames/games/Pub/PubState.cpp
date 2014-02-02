/** @file PubState.cpp
 *
 * Definição de um estado do jogo Pub.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#include "PubState.h"
#include "PubAction.h"

namespace Games {
namespace Pub {
PubState::PubState() : Games::Grids::Grid2D<Mark>(8, 5, EMPTY), last_action(nullptr) {}

PubState::PubState(const PubState &state) : 
	Games::Grids::Grid2D<Mark>(state), 
	last_action(state.last_action ? state.last_action->clone() : nullptr) {}

PubState::~PubState() {if(last_action) delete last_action;}

bool PubState::operator< (const PubState &that) const {
	if(this == &that) return false;
	return (this->grid < that.grid);
}

bool PubState::operator== (const PubState &that) const {
	if(this == &that) return true;
	return (this->grid == that.grid);
}

PubState &PubState::operator= (const PubState &that) {
	if(this != &that) {
		this->grid.assign(that.grid.begin(), that.grid.end());
		if(this->last_action) delete this->last_action;
		this->last_action = (that.last_action ? that.last_action->clone() : nullptr);
	}
	return *this;
}
} // namespace Pub
} // namespace Games
