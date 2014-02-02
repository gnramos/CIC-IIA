/* @file VacuumWorldState.h
 *
 * Descreve um estado do mundo do aspirador.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  02/2012 */

#ifndef IIA_EXAMPLES_VACUUMWORLD_STATE_H
#define IIA_EXAMPLES_VACUUMWORLD_STATE_H

#include <deque>
#include <ostream>

#include "State.hpp"

namespace IIA {
namespace Examples {
/** Define o escopo para o mundo do aspirador de pó. */
namespace VacuumWorld {
class Suck;
class Move;

/** Define o estado para o ambiente do aspirador de pó. */
class VacuumWorldState : public IIA::State<VacuumWorldState> {
public:
	/** Indica as possíveis localizações do ambiente. */
	enum Location {
		A = 0,  /**< A esquerda. */
		B = 1   /**< A direita. */
	};

	/** Converte a localização em string. */
	friend std::ostream &operator <<(std::ostream &os, const Location &location) {
		switch(location) {
		case A:		os << "A"; break;
		case B:		os << "B"; break;
		default:	os << "Unknown";
		}
		return os;
	};

	/** Construtor. */
	VacuumWorldState(Location location, /**< indica a localização do aspirador */ 
		  const std::deque<bool> &dl /**< indica se a localização está suja */
		  )
		  : vc_location(location), dirty_locations(dl) {
		if(dirty_locations.size() != 2)
			throw std::invalid_argument("VacuumWorldState must be of size 2.");
	}

	/** Construtor. */
	VacuumWorldState(const VacuumWorldState &state) : vc_location(state.vc_location), dirty_locations(state.dirty_locations) {}

	/** Indica se a instância é igual ao estado dado. */
	bool operator==(const VacuumWorldState &that) const {
		if(this == &that) return true;
		if(this->vc_location != that.vc_location) return false;
		if(this->dirty_locations != that.dirty_locations) return false;
		return true;
	}

	/** Indica se a instância é menor que o estado dado. */
	bool operator<(const VacuumWorldState &that) const {
		int count = 0;
		for(int i = 0; i < dirty_locations.size(); ++i) {
			if(this->dirty_locations[i]) --count;
			if(that.dirty_locations[i]) ++count;
		}
		if(count == 0) {
			if(this->dirty_locations == that.dirty_locations)
				return (this->vc_location < that.vc_location);
			else return (this->dirty_locations < that.dirty_locations);
		}
		return (count < 0);
	}

	/** Atribui a instância o estado dado. */
	VacuumWorldState &operator= (const VacuumWorldState &that) {
	if(this != &that) {
		this->vc_location = that.vc_location;
		this->dirty_locations = that.dirty_locations;
	}
	return *this;
}

	/** Transforma em string. */
	friend std::ostream &operator <<(std::ostream &os, const VacuumWorldState &state) {
		os << state.vc_location;
		for(bool is_dirty : state.dirty_locations) os << (is_dirty ? "*" : " ");
		return os;
	}

	/** Onde o aspirador está localizado. */
	Location location() const { return vc_location; }
	/** Indica se o local dado está sujo ou não. */
	bool is_dirty(Location l) const { return dirty_locations[l]; }

	friend class Suck;
	friend class Move;

public:
	// Attributes
	/** Indica a localização do aspirador. */
	Location vc_location;
	/** Indica se a localização está suja. */
	std::deque<bool> dirty_locations;
};
} // namespace VacuumWorld
} // namespace Examples
} //namespace IIA

#endif	/* IIA_EXAMPLES_VACUUMWORLD_STATE_H */
