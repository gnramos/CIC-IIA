/** @file SearchResult.hpp
 *
 * Definição de o resultado de uma busca.
 *
 * @author Guilherme Ramos
 * @date 05/2012 */

#ifndef IIA_SEARCH_RESULT_HPP
#define	IIA_SEARCH_RESULT_HPP

#include "Uninformed/UninformedSearchNode.hpp"
#include "Informed/HeuristicSearchNode.hpp"

namespace IIA {
namespace Search {
/** Define o resultado de busca por soluções. Uma solução é uma sequência de
* ações que leva do estado inicial ao objetivo. */
template <class state_t>
class Result {
public:
	/** Define os possíveis resultados da busca. */
	enum Status {
		CUTOFF, 	/**< A busca for interrompida. */
		FAILURE, 	/**< Solução não encontrada. */
		SUCCESS 	/**< Solução encontrada. */
	};

	/** Converte o status em string. */
	friend std::ostream &operator <<(std::ostream &os, const Status &status) {
		switch(status) {
		case CUTOFF: 	os << "Cut-off"; break;
		case FAILURE:	os << "Failure"; break;
		case SUCCESS:	os << "Success"; break;
		default:     	os << "Unknown";
		}
		return os;
	};

	/** Construtor.
	 *
	 * @param stat o status do resultado.
	 * @param last_node o último nó do caminho.
	 * @param nodes_expanded número de nós criados durante a busca. */
	Result(	const Status stat = FAILURE, 
	       	const Uninformed::Node<state_t> *last_node = nullptr, 
	       	long unsigned int nodes_expanded = 0) :
	    status(stat), 
	    expanded_nodes(nodes_expanded) {
		if(last_node) {
			Uninformed::Node<state_t> *node = const_cast<Uninformed::Node<state_t> *>(last_node);
			while(node && node->action) {
				actions.push_front(node->action->clone());
				node = node->parent;
			}
		} else if(status == SUCCESS)
			throw std::invalid_argument("Cannot have successful result without a last_node.");
	}

	/** Destrutor. Gerencia a memória conforme necessário. */
	virtual ~Result() { Utils::empty(actions); }

	/** Define a instância como cópia do nó dado. */
	Result &operator= (const Result &that) {
		if(this != &that) {
			this->status = that.status;
			Utils::empty(this->actions);
			for(auto action : that.actions) this->actions.push_back(action->clone());
			this->expanded_nodes = that.expanded_nodes;
		}
		return *this;
	}

	/** Converte o resultado em string. */
	friend std::ostream &operator <<(std::ostream &os, const Result &result) {
		os << result.status
		   << " (" << result.expanded_nodes << " nós)\n[";
		double total_cost = 0;
		for(auto action : result.actions) {
			os << action->to_string() << ", "; 
			total_cost += action->cost;
		}
		os << "] custo: " << total_cost;
		return os;
	}

	// Attributes
	/** Indica o status do resultado. */
	Status status;
	/** Armazena a solução, se houver. */
	std::deque<Action<state_t> *> actions;
	/** Indica quantos nós foram criados para executar a busca. */
	long unsigned int expanded_nodes;
};
} // namespace Search
} // namespace IIA

#endif // IIA_SEARCH_RESULT_HPP
