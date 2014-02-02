/** @file examples.hpp
 *
 * Descreve/define testes genéricos.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 06/2012 */

#ifndef IIA_EXAMPLES_HPP
#define IIA_EXAMPLES_HPP

#include <iostream> // std::cout, std::endl
#include <iomanip>  // std::setw

#include "libIIA.h"

namespace IIA {
/** Escopo para implementação de exemplos. Cada exemplo deve ser criado em seu
 * próprio diretório. A ideia é gerar um executável a partir de <b>todos</b> os 
 * arquivos dentro do diretório, portanto cuidado com a presença de arquivos 
 * "desnecessários". Um exemplo mínimo com organização por arquivos é:
 * Joguim
 *   |- JoguimState - derivado de IIA::State<State>
 *   |- JoguimAction - derivado de IIA::Action<JoguimState>
 *   |- JoguimProblem - derivado de IIA::Problem<JoguimState>
 *   `- Joguim - implementa estados iniciais e objetivos para JoguimProblem e 
 * exemplica sua utilização.
 *
 * Claro, todos os arquivos poderiam ser condensados em um só (Joguim.cpp), mas 
 * certa modularização ajuda na criação/manutenção.
 *
 * A forma mais simples de demonstrar é gerar uma instância de um problema e 
 * executar as funções void Examples::show_problem_info(const IIA::Problem<state_t> &, const char *)
 * e void Examples::run_uniformed_searches(const IIA::Problem<state_t> &). */
namespace Examples {
/** Escreve, na saída padrão, os argumentos dados transformando o tempo
 * em um formato mais amigável para o usuário (de nanossegundos a minutos). */
void show_time(const char *name, /**< [in] nome do que está sendo medido */
			   const timespec &diff /**< [in] tempo gasto na execução */
			   ) {
	std::cout << "\n\t\t" << name << " (" << diff.tv_sec << "."
			  << std::setfill('0') << std::setw(9) << diff.tv_nsec << " s)" 
			  << std::endl;
}

/** Cronometra e mostra o tempo gasto na execução da função de busca dada na 
 * resolução do problema.
 *
 * @see void IIA::Utils::Time::get_cpu_time(timespec &) 
 * @see void show_time(const char *name, const timespec &) */
template <class state_t>
void time_search(const char *search_name, /**< [in] nome da função de busca */
				 IIA::Search::Result<state_t> (*search)(const IIA::Problem<state_t> &), /**< [in] função que executa a busca */
				 const IIA::Problem<state_t> &p /**< [in] problema a ser resolvido */
				) {
	timespec start_time, end_time;

	using namespace IIA::Utils::Time;
	get_cpu_time(start_time);
	IIA::Search::Result<state_t> result = search(p);
	get_cpu_time(end_time);

	show_time(search_name, time_diff(start_time, end_time));
	std::cout << result << std::endl;
}

/** Cronometra e mostra o tempo gasto na execução da função de busca dada na 
 * resolução do problema.
 *
 * @see void IIA::Utils::Time::get_cpu_time(timespec &) 
 * @see void show_time(const char *name, const timespec &) */
template <class state_t>
void time_search(const char *search_name, /**< [in] nome da função de busca */
				 IIA::Search::Result<state_t> (*search)(const IIA::Problem<state_t> &, const IIA::Search::Informed::HeuristicCalc<state_t> &), /**< [in] função que executa a busca */
				 const IIA::Problem<state_t> &p, /**< [in] problema a ser resolvido */
				 const IIA::Search::Informed::HeuristicCalc<state_t> &h_calc /**< [in] heurística a ser usada */
				 ) {
	timespec start_time, end_time;

	using namespace IIA::Utils::Time;
	get_cpu_time(start_time);
	IIA::Search::Result<state_t> result = search(p, h_calc);
	get_cpu_time(end_time);

	show_time(search_name, time_diff(start_time, end_time));
	std::cout << result << std::endl;
}

/** Mostra as informações do problema. */
template <class state_t>
void show_problem_info(const IIA::Problem<state_t> &p, /**< [in] problema em questão */
	         		   const char *problem_name /**< [in] nome do problema */) {
	std::cout	<< std::endl << problem_name 
	         			<< ":\n\n\tinitial_state:\t" << p.initial_state
	         			<< "\n\tgoal_states:";
	for(state_t state : p.goal_states)
		std::cout << "\n\t\t\t" << state;
}

/** Aplica as funções de busca @em sem conhecimento (IIA::Search::Uninformed) para 
 * resolução do problema dado.
 * 
 * @see void time_search(const char *, IIA::Search::Result<state_t> (*search)(const IIA::Problem<state_t> &), const IIA::Problem<state_t> &) */
template <class state_t>
void run_uniformed_searches(const IIA::Problem<state_t> &p  /**< [in] problema a ser resolvido */) {
	std::cout << "\n\n\tUninformed:";

	using namespace IIA::Search::Uninformed;
	time_search("BreadthFirst::search_tree", BreadthFirst::search_tree, p);
	time_search("BreadthFirst::search_graph", BreadthFirst::search_graph, p);
	time_search("DepthLimited", DepthLimited::search, p);
	time_search("IterativeDeepening", IterativeDeepening::search, p);
	time_search("UniformCost", UniformCost::search, p);
	time_search("Bidirectional", Bidirectional::search, p);
}

/** Aplica as funções de busca @em com conhecimento (IIA::Search::Informed) para 
 * resolução do problema dado.
 *
 * @see void time_search(const char *, IIA::Search::Result<state_t> (*search)(const IIA::Problem<state_t> &, const IIA::Search::Informed::HeuristicCalc<state_t> &), const IIA::Problem<state_t> &, const IIA::Search::Informed::HeuristicCalc<state_t> &)*/
template <class state_t>
void run_informed_searches(IIA::Problem<state_t> &p  /**< [in] problema a ser resolvido */, 
						   const IIA::Search::Informed::HeuristicCalc<state_t> &h_calc  /**< [in] heurística a ser usada */
						  ) {
	std::cout << "\n\n\tInformed:";

	using namespace IIA::Search::Informed;
	time_search("BestFirst", BestFirst::search, p, h_calc);
}


/** Aplica as funções de busca local (IIA::Search::Local) para 
 * resolução do problema dado.
 * 
 * @see void time_search(const char *, IIA::Search::Result<state_t> (*search)(const IIA::Problem<state_t> &), const IIA::Problem<state_t> &)*/
template <class state_t>
void run_local_searches(IIA::Problem<state_t> &p /**< [in] problema a ser resolvido */) {
	/** @todo Implementar funções de busca local */
	std::cout << "\n\n\tLocal:";

	using namespace IIA::Search::Local;
	//time_search("HillClimbing::search", HillClimbing::search, p);
}

/** Cronometra  e mostra o tempo gasto pelo agente para alcançar um objetivo.
 *
 * @see void IIA::Utils::Time::get_cpu_time(timespec &) 
 * @see void show_time(const char *name, const timespec &) */
template <class perception_t, class state_t>
void time_agent(const char *agent_name, /**< [in] nome do agente */
				IIA::Agents::Agent<perception_t, state_t> &agent, /**< [in] instância do agente */
				const state_t &initial, /**< [in] estado inicial do agente */
				const std::deque<state_t> &goals /**< [in] conjunto de objetivos */
				) {
	timespec start_time, end_time;

	state_t state = initial;

	using namespace IIA::Utils::Time;

	get_cpu_time(start_time);
	do {
		perception_t perception(state);
		state = agent.act(perception);
		//std::cout << "\t<|[" << perception << "] -> [" << state << "]|>";

		/** @todo contador de ações para garantir término de time_agent */
	} while(!IIA::Utils::contains(goals, state));
	get_cpu_time(end_time);

	show_time(agent_name, time_diff(start_time, end_time));
}
} // namespace Examples
} // namespace IIA
#endif /* IIA_EXAMPLES_HPP */
