/** @file RandomUtils.h
 *
 * Definição de classes/funções auxiliares para a libIIA.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 30/10/2011 */

#ifndef IIA_UTILS_RANDOM_H
#define IIA_UTILS_RANDOM_H

#include <time.h>
#include <stdint.h> // uint64_t

namespace IIA {
namespace Utils {
/** Define o escopo de funções auxiliares relacionadas a números aleatórios. A 
 * obtenção dos números é baseada neste
 * <a href="http://www.codeproject.com/KB/recipes/SimpleRNG.aspx">artigo</a>.
 * Eis a descrição original: <i>SimpleRNG is a simple random number generator
 * based on George Marsaglia's MWC (multiply with carry) generator. Although it
 * is very simple, it passes Marsaglia's DIEHARD series of random number
 * generator tests.
 *
 * Written by John D. Cook http://www.johndcook.com</i>*/
namespace Random {
namespace {
namespace {
// These values are not magical, just the default values Marsaglia used.
// Any pair of unsigned integers should be fine.
static uint64_t m_w = 521288629; // semente aleatória
static uint64_t m_z = 362436069; // semente aleatória

/** Retorna um número inteiro aleatório e positivo. */
unsigned int get_uint() {
	/** A descrição original diz: <i>This is the heart
	 * of the generator. It uses George Marsaglia's MWC algorithm to produce an
	 * unsigned integer.
	 * See http://www.bobwheeler.com/statistics/Password/MarsagliaPost.txt</i>*/

	m_z = 36969 * (m_z & 65535) + (m_z >> 16);
	m_w = 18000 * (m_w & 65535) + (m_w >> 16);
	return (m_z << 16) + m_w;
}

/** Retorna um número aleatório entre 0 e 1 (exclusive). */
double get_uniform() {
	/** A descrição original diz: <i>Produce a uniform random sample from the
	 * open interval (0, 1). The method will not return either end point.</i> */

	// 0 <= u < 2^32
	unsigned int u = get_uint();
	// The magic number below is 1/(2^32 + 2).
	// The result is strictly between 0 and 1.
	//return (u + 1.0) * 2.328306435454494e-10;
	constexpr double magicNumber = 2.328306435454494e-10;
	return u * magicNumber;
}

/** Define a semente que inicializa a sequência de números aleatórios. */
void set_seed(uint64_t u, uint64_t v) {
	/** A descrição original diz: <i>The random generator seed can be set three ways:
	 * 1) specifying two non-zero unsigned integers
	 * 2) specifying one non-zero unsigned integer and taking a default value for the second
	 * 3) setting the seed from the system time </i> */

	if(u != 0) m_w = u;
	if(v != 0) m_z = v;
}
} // unnamed namespace

/** Inicializa a semente de números aleatórios a partir do relógio da  CPU
 * (teoricamente, um número diferente a cada chamada e, portanto, uma sequência
 * diferente de números aleatórios). */
void set_seed_from_system_time() {
	uint64_t x = time(nullptr);
	set_seed((uint64_t)(x >> 16), (uint64_t)(x % 4294967296LL));
}

/** Retorna um número aleatório entre os limites dados (inclusive).
 *
 * @param u_bound Limite superior;
 * @param l_bound Limite inferior. */
int get_random_int(int u_bound = 10, int l_bound = 0) {
	return (get_uint() % (u_bound - l_bound + 1)) + l_bound;
}

/** Retorna um número aleatório entre os limites dados (inclusive).
 *
 * @param u_bound Limite superior;
 * @param l_bound Limite inferior. */
double get_random_dbl(double u_bound = 1, double l_bound = 0) {
	return get_uniform() * (u_bound - l_bound) + l_bound;
}
} // unnamed namespace
} // namespace Random
} // namespace Utils
} // namespace IIA

#endif	/* IIA_UTILS_RANDOM_H */
