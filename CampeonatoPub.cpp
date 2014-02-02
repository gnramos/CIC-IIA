/** @file CampeonatoPub.cpp
 *
 * Implementa um campeonato.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#include <algorithm> 
#include <iostream>

#include "PubRandomPlayer.h"
// #include "PubSimplePlayer.h"
#include "RoundRobinTournament.hpp"
#include "MatchStats.hpp"

using namespace Games;
typedef Statistics::PlayerMultipleMatchStat<Pub::PubMatch, Pub::PubPlayer> PMMStat;

// calcula os pontos
inline unsigned int points_win3draw1(const PMMStat &stat) {
	return stat.num_victories*3 + stat.num_draws;
}

// compara os pontos
bool compare_win3draw1(const PMMStat &lhs, const PMMStat &rhs) {
	unsigned int lhs_points = points_win3draw1(lhs);
	unsigned int rhs_points = points_win3draw1(rhs);

	if(lhs_points != rhs_points) return lhs_points > rhs_points;
	return (lhs.avg_cost() < rhs.avg_cost());
}

using namespace Pub;
void testa_uma_partida() {
	// definindo participantes
	PubRandomPlayer	aluno1(WHITE, "Random Lee"), 
	               	aluno2(BLACK, "Ale Atório");
	std::deque<PubPlayer *> pub_players;
	pub_players.push_back(&aluno1);
	pub_players.push_back(&aluno2);

	// criando/executando uma partida
	PubMatch partida(pub_players);
	partida.play();

	// Mostra os resultados
	std::cout << "\n" << partida << "\n\n";

	// Statistics::MatchStat<PubMatch, PubPlayer> stat(partida);
	// std::cout << "\n" << partida << "\n\n";	
}

void testa_campeonato() {
	// definindo participantes
	PubRandomPlayer    	aluno1(WHITE, "Random Lee"), 
	                   	aluno2(BLACK, "Ale Atório"),
	                   	aluno3(WHITE, "E. Stocástico");
	SlowPubRandomPlayer	aluno4(BLACK, "TáLento");

	std::deque<PubPlayer *> pub_players;
	pub_players.push_back(&aluno3);
	pub_players.push_back(&aluno4);
	pub_players.push_back(&aluno1);
	pub_players.push_back(&aluno2);

	// criando/executando o campeonato
	Games::RoundRobin<PubMatch, PubPlayer> pub_rr(pub_players);
	pub_rr.run();
	// std::cout << "\n" << pub_rr << "\n";

	// ordenando os participantes conforme a regra compare_win3draw1
	std::deque<PubMatch *> matches;
	for(std::deque<std::deque<PubMatch *> > round : pub_rr.rounds)
		for(std::deque<PubMatch *> dispute : round)
			for(PubMatch *match : dispute)
				matches.push_back(match);

	Statistics::MultipleMatchStat<PubMatch, PubPlayer> stats(matches);
	std::sort(stats.player_stats.begin(), stats.player_stats.end(), compare_win3draw1);
	// std::cout << "\n" << stats << "\n";

	// Mostra os resultados
	int i = 0;
	std::cout << "\nClassificação:\n";
	for(PMMStat s : stats.player_stats)
		std::cout << "\t" << ++i << ") " << (*s.player) << " (" << points_win3draw1(s) << ")\n";
}

int main(int argc, char **argv) {
	// testa_uma_partida();
	testa_campeonato();

	return 0;
}

 /**
 * @mainpage Projeto Tournament
 *
 * A ideia é realizar um campeonato de Games::Pub.
 */
