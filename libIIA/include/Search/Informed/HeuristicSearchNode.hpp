/** @file HeuristicSearchNode.hpp
 *
 * Definição de um nó para buscas heurísticas.
 *
 * @author Guilherme Ramos (gnramos@unb.br)
 * @date 05/2012 */

#ifndef IIA_SEARCH_INFORMED_HEURISTIC_NODE_HPP
#define IIA_SEARCH_INFORMED_HEURISTIC_NODE_HPP

#include <set>

#include "Uninformed/UninformedSearchNode.hpp"

namespace IIA {
namespace Search {
/** Define o escopo para implementações relacionadas à busca por soluções em com
 * informações*/
namespace Informed {
/** Define a classe base para cálculo de estimativas de custo do estado dado até
 * o(s) objetivo(s) (funções heurísticas). */
template <class state_t>
class HeuristicCalc {
public:
	/** Construtor. Armazena um ponteiro para os objetivos do problema. */
	HeuristicCalc(const std::set<state_t> *goal_states) : goals(goal_states) {}
	
	/** Calcula a estimativa do custo do estado dado até o(s) objetivo(s). */
	virtual double eval(const state_t &state) const { return 0; }

protected:
	// Attributes
	/** Indica quais são os objetivos. */
	const std::set<state_t> *goals;
};

/** Nó que utiliza uma função heurística para calcular estimar o custo até o objetivo. */
template <class state_t>
class HeuristicNode : public Uninformed::Node<state_t> {
public:
	/** Construtor.
	 *
	 * @param state o estado representado pelo nó.
	 * @param parent nó que gerou esta instância.
	 * @param action ação que gerou esta instância.
	 * @param path_cost o custo do caminho até chegar a este estado.
	 * @param heuristic_cost o custo estimado do estado dado até o objetivo. */
	HeuristicNode(const state_t &state,
				  Uninformed::Node<state_t> *parent = nullptr,
				  Action<state_t> *action = nullptr,
				  double path_cost = 0, double heuristic_cost = 0) :
		Uninformed::Node<state_t>(state, parent, action, path_cost), 
		h_cost(heuristic_cost) {}

	/** Cria uma nova instância como cópia do argumento dado.
	 *
	 * @param node o nó a copiar. */
	HeuristicNode(const HeuristicNode &node) :
		Uninformed::Node<state_t>(node.state, node.parent, node.action, node.path_cost), h_cost(node.h_cost) {}

	/** Destrutor. */
	virtual ~HeuristicNode() {}

	/** Define a instância como cópia do nó dado. */
	virtual HeuristicNode<state_t> &operator= (const HeuristicNode<state_t> &that) {
		if(this != &that) {
			this->state = that.state;
			this->parent = that.parent;
			if(this->action) delete this->action;
			this->action = (that.action ? that.action->clone() : nullptr);
			this->path_cost = that.path_cost;
			this->h_cost = that.h_cost;
		}
		return (*this);
	}

	/** Converte a coordenada em string. */
	friend std::ostream &operator <<(std::ostream &os, const HeuristicNode &node) {
		os << "state: " << node.state
		   << " parent: " << node.parent;
		if(node.action) os << " action: " << node.action->to_string();
		else os << " action: 0";
		os << " path_cost: " << node.path_cost
		   << " h_cost: " << node.h_cost;
		return os;
	}

	/** Retorna a soma de path_cost e h_cost. */
	double f_cost() const { return this->path_cost + this->h_cost; }

	// Attributes
	/** O custo estimado do caminho deste nó até um estado objetivo. */
	double h_cost;
};

/** Retorna a referência para um novo nó como filho da instância, resultante da
 * execução da ação dada como argumento.
 *
 * @param parent o nó pai da nova instância.
 * @param action ação que origina o novo nó.
 * @param h_func ponteiro para a função que calcula a heurística. */
template <class state_t>
static HeuristicNode<state_t> *child_node(HeuristicNode<state_t> *parent, Action<state_t> *action, const HeuristicCalc<state_t> &h_calc) {
	if(!parent)
		throw std::invalid_argument("Child node must have a parent.");
	if(!action)
		throw std::invalid_argument("Child node must result from an action.");

	HeuristicNode<state_t> *node = new HeuristicNode<state_t>(parent->state, parent, action, parent->path_cost + action->cost);
	action->execute(node->state);
	node->h_cost = h_calc.eval(node->state);

	return node;
}

/** Retorna os nós resultantes da execução das ações fornecidas no estado do nó
 * dado.
 *
 * @param parent o nó cujo estado
 * @param actions as ações que podem ser executadas no estado do nó.*/
template <class state_t>
static std::deque<HeuristicNode<state_t> *> children_nodes(HeuristicNode<state_t> *parent,
		const std::deque<Action<state_t> *> &actions, const HeuristicCalc<state_t> &h_calc) {
	std::deque<HeuristicNode<state_t> *> children;
	for(Action<state_t> *action : actions)
		children.push_back(child_node(parent, action, h_calc));
	return children;
}
} // namespace Informed
} // namespace Search
} // namespace IIA

#endif // IIA_SEARCH_INFORMED_HEURISTIC_NODE_HPP
