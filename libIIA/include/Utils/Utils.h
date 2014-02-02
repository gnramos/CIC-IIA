/** @file Utils.h
 *
 * Definição de classes/funções auxiliares para a libIIA.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 30/10/2011 */

#ifndef IIA_UTILS_H
#define IIA_UTILS_H

#include <map>
#include <set>
// #include <sstream>

 #include "RandomUtils.h"
 #include "StringUtils.h"
 #include "TimeUtils.h"

namespace IIA {
/** Define o escopo de classes/funções auxiliares. */
namespace Utils {
/** Libera a memória de cada ponteiro antes de liberar o container. */
template <class container_t>
void empty(container_t &container) {
	while(!container.empty()) delete container.back(), container.pop_back(); 
}

// Especialização para conjuntos.
/** Libera a memória de cada ponteiro antes de liberar o container. */
template <class ptr_item_t>
void empty(std::set<ptr_item_t> &container) {
	while(!container.empty()) delete *(container.begin()), container.erase(container.begin()); 
}
// Especialização para mapas.
/** Libera a memória de cada ponteiro antes de liberar o container. */
template <class K, class T>
void empty(std::map<K, T *> &container) {
	for(std::pair<K, T *> item : container) delete item.second;
	container.clear();
}

/** Verifica se o container dado contem o item. O primeiro argumento deve ser
 * iterável. */
template <class container_t, class type_t>
bool contains(const container_t &container, const type_t &item) {
	for(type_t t : container) if(t == item) return true;
	return false;
}
} // namespace Utils
} // namespace IIA

#endif	/* IIA_UTILS_H */
