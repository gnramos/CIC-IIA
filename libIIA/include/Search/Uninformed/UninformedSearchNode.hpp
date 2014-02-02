/** @file UninformedSearchNode.hpp
 *
 * Definição de um nó para buscas.
 *
 * @author Guilherme Ramos
 * @date 05/2012 */

#ifndef IIA_SEARCH_UNINFORMED_NODE_HPP
#define	IIA_SEARCH_UNINFORMED_NODE_HPP

#include <deque>
#include <stdexcept>

#include "Action.hpp"
#include "Utils.h"

namespace IIA {
namespace Search {
namespace Uninformed {
/** Define um nó em uma árvore de busca. Cada nó (elemento/nodo) é uma estrutura
* de dados com:
*	- state: configuração a que o nó corresponde dentre os elementos do espaços de estados.
*	- parent: o nó da árvore que gerou a instância.
*	- action: ponteiro para a ação executada no estado do nó ancestral que gerou a instância.
*	- path_cost: custo das ações que levam do estado inicial ao estado da instância. */
template <class state_t>
class Node {
public:
	/** Cria uma nova instância conforme os argumentos dados.
	 *
	 * @todo derivar de Assignable ?
	 *
	 * @param s o estado representado pelo nó.
	 * @param p nó que gerou esta instância.
	 * @param a ação que gerou esta instância.
	 * @param cost o custo do caminho até chegar a este estado.*/
	Node(const state_t &s, Node *p = nullptr, const Action<state_t> *a = nullptr,
		 const double cost = 0) :
		state(s), parent(p), action(a ? a->clone() : nullptr), path_cost(cost) {}

	/** Cria uma nova instância como cópia do argumento dado. */
	Node(const Node &node) :
		state(node.state), parent(node.parent),
		action(node.action ? node.action->clone() : nullptr),
		path_cost(node.path_cost) {}

	/** Destrói a instância, gerenciando a memória conforme necessário. */
	virtual ~Node() { if(action) delete action; }

	/** Define a instância como cópia do nó dado. */
	virtual Node &operator= (const Node &that) {
		if(this != &that) {
			this->state = that.state;
			this->parent = that.parent;
			if(this->action) delete this->action;
			this->action = (that.action ? that.action->clone() : nullptr);
			this->path_cost = that.path_cost;
		}
		return (*this);
	}

	/** Converte a coordenada em string. */
	friend std::ostream &operator <<(std::ostream &os, const Node &node) {
		os << "state: " << Utils::String::to_string(node.state)
		   << " parent: " << node.parent;
		if(node.action) os << " action: " << node.action->to_string();
		else os << " action: 0";
		os << " path_cost: " << node.path_cost;
		return os;
	}

	// Attributes
	/** Estado representado pelo nó. */
	state_t state;
	/** O nó que gerou esta instância. */
	Node *parent;
	/** A ação que gerou este nó. */
	Action<state_t> *action;
	/** O custo do caminho até o estado deste nó. */
	double path_cost;
};

/** Retorna a referência para um novo nó como filho da instância, resultante da
 * execução da ação dada como argumento.
 *
 * @param parent o nó pai da nova instância.
 * @param action ação que origina o novo nó.*/
template <class state_t>
Node<state_t> *child_node(Node<state_t> *parent, Action<state_t> *action) {
	if(!parent)
		throw std::invalid_argument("Child node must have a parent.");
	if(!action)
		throw std::invalid_argument("Child node must result from an action.");

	Node<state_t> *node = new Node<state_t>(parent->state, parent, action, parent->path_cost + action->cost);
	action->execute(node->state);

	return node;
}

/** Retorna os nós resultantes da execução das ações fornecidas no estado do nó
 * dado.
 *
 * @param parent o nó cujo estado
 * @param actions as ações que podem ser executadas no estado do nó.*/
template <class state_t>
std::deque<Node<state_t> *> children_nodes(Node<state_t> *parent, const std::deque<Action<state_t> *> &actions) {
	std::deque<Node<state_t> *> children;
	for(Action<state_t> *action : actions)
		children.push_back(child_node(parent, action));
	return children;
}

/** Dada um conjunto de ponteiros para nós, retorna o nó que contém o estado 
 * dado, se houver. */
template <class node_ptr_container_t, class state_t>
Node<state_t> *find_node(const node_ptr_container_t &node_ptr_container, const state_t &state) {
	for(Node<state_t> *node : node_ptr_container) {
		if(node->state == state)
			return node;
	}
	return nullptr;
}

/** Dada um conjunto de conjuntos de ponteiros para nós, retorna o nó que contém
 * o estado dado, se houver. */
template <class state_t>
Node<state_t> *find_node(std::deque<const std::deque<Node<state_t> *> *> &containers, const state_t &state) {
	Node<state_t> *node = nullptr;
	for(const std::deque<Node<state_t> *> *container : containers) {
		node = find_node(*container, state);
		if(node) return node;
	}
	return nullptr;
}

/** Indica se algum nó tem o estado dado em um ancestral. */
template <class state_t>
bool in_parent_node(const Node<state_t> *parent, const state_t &state) {
	Node<state_t> *ptr = const_cast<Node<state_t> *>(parent);
	while(ptr && ptr->state != state)
		ptr = const_cast<Node<state_t> *>(ptr->parent);
	return (ptr != nullptr);
}
} // namespace Uninformed
} // namespace Search
} // namespace IIA

#endif // IIA_SEARCH_UNINFORMED_NODE_HPP
