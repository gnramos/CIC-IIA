/** @file MissionariesState.h
 *
 * Descreve um estado para o problema dos Missionários e Canibais.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  10/2011 */

#ifndef IIA_EXAMPLES_MISSIONARIES_STATE_H
#define IIA_EXAMPLES_MISSIONARIES_STATE_H

#include "State.hpp"
#include "Utils.h"

namespace IIA {
namespace Examples {
namespace Missionaries {
/** Define uma margem. */
class Margin {
public:
	/** Construtor. */
	Margin(unsigned int m, unsigned int c, bool can) 
	: cannibals(c), canoe(can),  missionaries(m) {}

	/** Construtor. */
	Margin(const Margin &margin) : cannibals(margin.cannibals), canoe(margin.canoe), missionaries(margin.missionaries) {}

	/** Armazena o número de cannibals na margin. */
	unsigned int cannibals;
	/** Indica se a canoe está nesta margin ou não. */
	bool canoe;
	/** Armazena o número de missionários na margin. */
	unsigned int missionaries;
};
/** Define um estado para o problema dos Missionários e Canibais. */
class MissionariesState : public IIA::State<MissionariesState> {
public:
	/** Construtor. */
	MissionariesState(const Margin &esq, const Margin &dir) : left(esq), right(dir) {}

	/** Construtor. */
	MissionariesState(const MissionariesState &state) : left(state.left), right(state.right) {}

	/** Indica se a instância é igual ao estado dado. */
	bool operator==(const MissionariesState &that) const {
		if(this == &that) return true;
		if(this->left.missionaries != that.left.missionaries) return false;
		if(this->right.missionaries != that.right.missionaries) return false;
		if(this->left.cannibals != that.left.cannibals) return false;
		if(this->right.cannibals != that.right.cannibals) return false;
		if(this->left.canoe != that.left.canoe) return false;
		if(this->right.canoe != that.right.canoe) return false;
		return true;
	}

	/** Indica se a instância é menor que o estado dado. */
	bool operator<(const MissionariesState &that) const {
		if(this == &that) return false;

		if(this->left.missionaries - this->left.cannibals <
		that.left.missionaries - that.left.cannibals) return false;
		if(this->right.missionaries - this->right.cannibals <
		that.right.missionaries - that.right.cannibals) return false;

		return true;
	}

	/** Atribui a instância o estado dado. */
	MissionariesState &operator= (const MissionariesState &that) {
		if(this != &that) {
			this->left = that.left;
			this->right = that.right;
		}

		return *this;
	}
	
	/** Transforma em string. */
	friend std::ostream &operator <<(std::ostream &os, const MissionariesState &state) {
		os << "<" << (state.left.canoe ? "c" : " ") << state.left.missionaries << "," << state.left.cannibals << "|"
		<< state.right.missionaries << "," << state.right.cannibals << (state.right.canoe ? "c" : " ") << ">";
		return os;
	}

	// Attributes
	//private:
	/** As margens do rio. */
	Margin left, right;
};
} // namespace Missionaries
} // namespace Examples
} // namespace IIA

#endif	/* IIA_EXAMPLES_MISSIONARIES_STATE_H */
