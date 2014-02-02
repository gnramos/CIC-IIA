/** @file Graph.h
 *
 * Definição de classes/funções auxiliares para a libIIA.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 30/10/2011 */

#ifndef IIA_UTILS_GRAPH_H
#define IIA_UTILS_GRAPH_H

#include <map>

namespace IIA {
namespace Utils {
/** Define a implementação de um grafo. Um grafo é composto por dois conjuntos,
 * o de vértices (que armazenam algum dado),  e o de arestas (que indicam
 * relações entre os vértices.
 *   - key_t identifica o vértice (ex: string).
 *   - vertex_t define o vértice (ex: dados quaisquer).
 *   - edge_t define a relação entre vértices (ex: double).
 *
 * @todo Testar Utils::Graph */
template <class key_t, class vertex_t, class edge_t>
class Graph {
public:
	/** Adiciona um vértice ao grafo, identificando-o pela chave dada. */
	void add_vertex(key_t key, const vertex_t &vertex) {vertices[key] = vertex;}

	/** Adiciona uma aresta que relaciona o vértice definido pela primeira chave
	 * ao vértice definido pela segunda chave. */
	void add_edge(const key_t &from, const key_t &to, const edge_t &edge) {
		edges[from][to] = edge;
	}

	/** Retorna o vértice definido pela chave dada, se existir (nullptr caso
	 * contrário). */
	vertex_t *get_vertex(const key_t &key) const {
		typename std::map<key_t, vertex_t>::const_iterator it = vertices.find(key);
		if(it == vertices.end()) return nullptr;
		return const_cast<vertex_t *>(&(it->second));
	}

	/** Retorna a aresta que relaciona os vértices definidos pela chave dada, se
	 * existir (nullptr caso contrário). */
	edge_t *get_edge(const key_t &from, const key_t &to) const {
		if(!get_vertex(from) || !get_vertex(to)) return nullptr;
		return &(edges[from][to]);
	}

	// Attributes
	/** O conjunto de vértices. */
	std::map<const key_t, vertex_t> vertices;
	/** O conjunto de arestas. */
	std::map<const key_t, std::map<const key_t, edge_t> > edges;
};
} // namespace Utils
} // namespace IIA

#endif	/* IIA_UTILS_GRAPH_H */
