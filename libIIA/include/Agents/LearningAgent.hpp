/** @file LearningAgent.hpp
 *
 * Definição de um agentes (racional) que aprende.
 *
 * @author Guilherme Ramos (gnramos@unb.br)
 * @date 10/2011 */

#ifndef IIA_AGENTS_LEARNING_HPP
#define IIA_AGENTS_LEARNING_HPP

#include "Agent.hpp"

namespace IIA {
namespace Agents {
/** Agentes que aprendem. @todo implementar */
template <class perception_t, class state_t>
class LearningAgent :  public Agent<perception_t, state_t> {
	/** Classe que implementa o <i>Elemento de Desempenho</i>, que analisa a
	 * percepção e seleciona a ação adequada. */
	class PerformanceElement {};

	/** Classe que implementa o <i>Elemento de Aprendizado</i>, que aprimora o
	 * elemento de desempenho. */
	class LearningElement {};

	/** Classe que implementa o <i>Elemento Crítico</i>, que fornece informações
	 * ao de aprendizado (comparação a uma medida de desempenho externa). */
	class CriticElement {};

	/** Classe que implementa o <i>Gerador de Problemas</i>, que sugere ações
	 * que levam a exploração. */
	class ProblemGenerator { };
public:
	LearningAgent();
	virtual ~LearningAgent() throw();

private:
	PerformanceElement performanceElement;
	LearningElement learningElement;
	CriticElement critic;
	ProblemGenerator problemGenerator;
};
} // namespace Agents
} // namespace IIA

#endif // IIA_AGENTS_LEARNING_HPP
