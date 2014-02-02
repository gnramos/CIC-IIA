/** @file Jug.h
 *
 * Descreve uma jarra.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  10/2011 */

#ifndef IIA_EXAMPLES_JUGS_JUG_H
#define IIA_EXAMPLES_JUGS_JUG_H

#include <ostream>
#include <stdexcept>

namespace IIA {
namespace Examples {
/** Define o escopo do problema das Jarras. */
namespace Jugs {
/** Define uma jarra. */
class Jug {
public:

	/** Construtor. Inicializa a instância conforme os argumentos dados. */
	Jug(const double c,    /**< a capacidade da jarra */
	    const double v = 0 /**< o volume da jarra */
	    ) : capacity(0), volume(0) {
		/** @see put(const double) */
		if(c < 0)
			throw std::out_of_range("Cannot have jug with capacity less than zero.");
		capacity = c;
		put(v);
	}

	/** Retorna o volume armazenado na jarra. */
	double get_volume() const { return this->volume; }

	/** Retorna o valor da capacity da jarra. */
	double get_capacity() const { return this->capacity; }

	/** Retira da jarra o volume dado como argumento e retorna a quantidade
	 * realmente retirada em função do volume armazenado */
	double take(const double v /**< o volume a ser retirado */ ) {
		if(v < 0)
			throw std::out_of_range("Cannot take volume less than zero from jug.");

		double v_out = std::min(volume, v);
		volume -= v_out;
		return v_out;
	}

	/** Coloca na jarra o volume dado como argumento e retorna a quantidade em
	 * excesso em função do volume armazenado */
	double put(double v) {
		if(v < 0)
			throw std::out_of_range("Cannot put volume less than zero into jug.");

		double v_in = std::min(capacity - volume, v);
		volume += v_in;
		return v - v_in;
	}

	/** Enche a jarra até sua capacidades. */
	void fill() { volume = capacity; }

	/** Retira todo o volume da jarra. */
	double empty() {
		double v = volume;
		volume = 0;
		return v;
	}

	/** Indica se a jarra está cheia. */
	bool is_full() const {return volume == capacity;}

	/** Indica se a jarra está vazia. */
	bool is_empty() const {return volume == 0;}

	/** Indica se a instância é menor que a jarra dado. */
	bool operator<(const Jug &that) const {
		if(this->capacity > that.capacity) return false;
		if(this->capacity < that.capacity) return true;
		return this->volume < that.volume;
	}

	/** Indica se a instância é igual a jarra dado. */
	bool operator==(const Jug &that) const {
		if(this != &that) {
			if(this->capacity != that.capacity) return false;
			if(this->volume   != that.volume)   return false;
		}
		return true;
	}

	/** Indica se a instância é diferente da jarra dado. */
	bool operator!=(const Jug &that) const {
		return !(*this == that);
	}

	friend std::ostream &operator <<(std::ostream &os, const Jug &jug) {
		/** Representa a jarra com a razão volume/capacidade. */
		os << jug.volume << "/" << jug.capacity;
		return os;
}

private:
	/** Define a capacity volumétrica da jarra. */
	double capacity;
	/** Define o volume contido na jarra. O valor armazenado deve estar no
	 * intervalo [0, capacity]. */
	double volume;
};
} // namespace Jugs
} // namespace Examples
} // namespace IIA

#endif	/* IIA_EXAMPLES_JUGS_JUG_H */
