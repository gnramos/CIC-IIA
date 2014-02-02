/** @file StringUtils.h
 *
 * Definição de classes/funções auxiliares para a libIIA.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 30/10/2011 */

#ifndef IIA_UTILS_STRING_H
#define IIA_UTILS_STRING_H

#include <sstream>

namespace IIA {
namespace Utils {
/** Define o escopo de funções auxiliares para manipulação de strings. */
namespace String {
/** Converte em string. *
 * @return std::string a representação do objeto em string. */
template <class to_string_t> 
inline std::string to_string(const to_string_t &to_str /**< objeto a ser convertido */) {
	std::stringstream sstr;
	sstr << to_str;
	return sstr.str();
}

/** Itera pelos elementos do container, convertendo-os em strings separados pelo
 * delimitador dado.
 *
 * @param container contém os elementos.
 * @param delim o delimitador.
 * @return string uma string com todos os elemento. */
template<typename container_t> inline
std::string join(const container_t &container, const std::string &delim = ", ") {
	std::stringstream sstr;

	for(typename container_t::const_iterator it = container.begin(); it != container.end(); ++it)
		sstr << (it == container.begin() ? "" : delim) << *it;

	return sstr.str();
}

/** Itera pelos elementos do container, convertendo-os em strings separados pelo
 * delimitador dado.
 *
 * @param container contém os elementos.
 * @param delim o delimitador.
 * @return string uma string com todos os elemento. */
template<typename container_t> inline
std::string join_ptrs(const container_t &container, const std::string &delim = ", ") {
	std::stringstream sstr;

	for(typename container_t::const_iterator it = container.begin(); it != container.end(); ++it)
		if(*it != nullptr) sstr << (it == container.begin() ? "" : delim) << *(*it);

	return sstr.str();
}
} // namespace String
} // namespace Utils
} // namespace IIA

#endif	/* IIA_UTILS_STRING_H */
