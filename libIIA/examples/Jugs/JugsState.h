/** @file JugsState.h
 *
 * Define um estado.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  10/2011 */

 #ifndef IIA_EXAMPLES_JUGS_STATE_H
 #define IIA_EXAMPLES_JUGS_STATE_H

#include <deque>

#include "Utils.h"
#include "Jug.h"
#include "State.hpp"

namespace IIA {
namespace Examples {
namespace Jugs {
/** Define um estado para o problema das jarras. */
class JugsState : public IIA::State<JugsState> {
public:
	/** Construtor. */
	JugsState() {}

	/** Construtor. */
	JugsState(const JugsState &state) : jugs(state.jugs) {}

	/** Indica se a instância é igual ao estado dado. */
	bool operator==(const JugsState &that) const {
		if(this != &that) {
			if(this->jugs.size() != that.jugs.size()) return false;
			for(unsigned int i = 0; i < this->jugs.size(); ++i)
				if(this->jugs[i] != that.jugs[i]) return false;
		}
		return true;
	}

	/** Indica se a instância é menor que o estado dado. */
	bool operator<(const JugsState &that) const {
		if(this == &that) return false;
		return this->jugs < that.jugs;
	}
	/** Atribui a instância o estado dado. */
	JugsState &operator= (const JugsState &that) {
		if(this != &that) {
			this->jugs.assign(that.jugs.begin(), that.jugs.end());
		}

		return *this;
	}
	
	/** Transforma em string. */
	friend std::ostream &operator <<(std::ostream &os, const JugsState &state) {
		os << "[" << Utils::String::join(state.jugs) << "]";
		return os;
	}

	// Attributes
	//private:
	/** Armazena as jarras do problema. */
	std::deque<Jug> jugs;
};
} // namespace Jugs
} // namespace Examples
} // namespace IIA

#endif /* IIA_EXAMPLES_JUGS_STATE_H */
