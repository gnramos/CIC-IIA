/** @file RomaniaProblem.h
 *
 * Define o problema de movinmentação na Romênia.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 06/2012 */
 
#ifndef IIA_EXAMPLES_ROMANIA_PROBLEM_H
#define IIA_EXAMPLES_ROMANIA_PROBLEM_H

#include "Problem.hpp"
#include "Graph.h"
#include "RomaniaAction.h"

namespace IIA {
namespace Examples {
namespace Romania {
/** Define o problema de movimentação na Romênia. Dado um mapa do país, como 
 * encontrar uma rota entre duas cidades? */
class RomaniaProblem : public IIA::Problem<RomaniaState> {
public:
	/** Construtor. Inicializa o problema com uma cidade de origem (estado 
	 * inicial) e um destino (estado objetivo). */
	RomaniaProblem(std::string from, std::string to)
	: IIA::Problem<RomaniaState>(from, to) {
		add_undirected_connection("Arad", "Zerind", 75);
		add_undirected_connection("Zerind", "Oradea", 71);
		add_undirected_connection("Oradea", "Sibiu", 151);
		add_undirected_connection("Arad", "Timisoara", 118);
		add_undirected_connection("Timisoara", "Lugoj", 111);
		add_undirected_connection("Lugoj", "Mehadia", 70);
		add_undirected_connection("Mehadia", "Dobreta", 75);
		add_undirected_connection("Dobreta", "Craiova", 120);
		add_undirected_connection("Arad", "Sibiu", 140);
		add_undirected_connection("Sibiu", "Fagaras", 99);
		add_undirected_connection("Fagaras", "Bucharest", 211);
		add_undirected_connection("Sibiu", "Rimnicu Vilcea", 80);
		add_undirected_connection("Rimnicu Vilcea", "Craiova", 146);
		add_undirected_connection("Rimnicu Vilcea", "Pitesti", 97);
		add_undirected_connection("Craiova", "Pitesti", 138);
		add_undirected_connection("Pitesti", "Bucharest", 101);
		add_undirected_connection("Bucharest", "Giurgiu", 90);
		add_undirected_connection("Bucharest", "Urziceni", 85);
		add_undirected_connection("Urziceni", "Vaslui", 142);
		add_undirected_connection("Vaslui", "Iasi", 92);
		add_undirected_connection("Iasi", "Neamt", 87);
		add_undirected_connection("Urziceni", "Hirsova", 98);
		add_undirected_connection("Hirsova", "Eforie", 86);

		if(!graph.get_vertex(from)) throw std::invalid_argument("Invalid \"from\" argument.");
		if(!graph.get_vertex(to)) throw std::invalid_argument("Invalid \"to\" argument.");
	}

	/** Define as acoes possiveis conforme o estado dado. */
	std::deque<IIA::Action<RomaniaState>* > actions(const RomaniaState&state) const {
		std::deque<IIA::Action<RomaniaState>* > result;
		if(!graph.get_vertex(state.key))
			result.push_back(new DoNothing<RomaniaState>());
		else {
			for(const std::pair<const std::string, std::map<const std::string, double> > from_pair : graph.edges)
				if(from_pair.first == state.key) {
					for(const std::pair<const std::string, double> &to_pair : from_pair.second)
						result.push_back(new Move(state.key, to_pair.first, to_pair.second));
					break;
				}
		}
		return result;
	}
	
	/** Define os possíveis pares estado/ação de modo que a ação aplicada ao 
	 * estado associado resultaria no estado dado como parâmetro. */
	std::deque<std::pair<RomaniaState, Action<RomaniaState> *> > predecessors(const RomaniaState &state) const {
		std::deque<std::pair<RomaniaState, Action<RomaniaState> *> > pairs;
		
		/** @todo verificar porque a busca bidirecional não funciona em Romania::Problem::predecessors se retornar vazio. */
		//return pairs;
		
		for(const std::pair<const std::string, std::map<const std::string, double> > from_pair : graph.edges) {
			for(const std::pair<const std::string, double> &to_pair : from_pair.second) {
				if(to_pair.first == state.key)
					pairs.push_back(std::pair<RomaniaState, Action<RomaniaState> *> (from_pair.first, new Move(from_pair.first, state.key, to_pair.second)));
			}
		}

		return pairs;
	}


private:
	void add_directed_connection(std::string from, std::string to, double weight) {
		graph.add_vertex(from, from);
		graph.add_vertex(to, to);
		graph.add_edge(from, to, weight);
	}


	void add_undirected_connection(std::string from, std::string to, double weight) {
		add_directed_connection(from, to, weight);
		add_directed_connection(to, from, weight);
	}

	// Attributes
public:
	/** Armazena o mapa da Romênia. */
	Utils::Graph<std::string, std::string, double> graph;
};
} // namespace Romania
} // namespace Examples
} // namespace IIA

#endif // IIA_EXAMPLES_ROMANIA_PROBLEM_H
