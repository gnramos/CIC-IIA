/** @file PubMatch.h
 *
 * Descreve uma partida do jogo Pub.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#ifndef GAMES_PUB_MATCH_H
#define GAMES_PUB_MATCH_H

#include "Match.hpp"
#include "PubPlayer.h"

namespace Games {
namespace Pub {

constexpr double MAX_TIME_COST_IN_NANOSECONDS = 500000000;

/** Define uma partida do Pub. */
class PubMatch : public Games::Match<PubPlayer, PubAction, PubState> {
public:
	/** Construtor. */
	PubMatch(const std::deque<PubPlayer *>players) : Games::Match<PubPlayer, PubAction, PubState>(players) {}

	/** Retorna o resultado da atual sequência de ações para o jogador dado.
	 *
	 * @see Result get_result(const PubState &, const Player *) */
	GameResult get_result(const PubPlayer *player) const {
		if(!IIA::Utils::contains(players, player)) return UNKNOWN;

		if(moves.size() >= 20) {
			PubState game = result();
			return get_result(game, player->mark);
		}

		PubState game;
		for(PubMatch::Move *move : moves) {
			if(allowed(move, game)) move->execute(game);
			else return (move->player == player ? DEFEAT : VICTORY);
		}

		return UNKNOWN;
	}

public:
	/** Conta o número de pontos por linha do estado dado como argumento.
	 *
	 * @param game jogo a ser verificado
	 * @param mark símbolo a ser verificado. */
	static unsigned int count_in_row(const PubState &game, const Mark mark)  {
		unsigned int points = 0;
		for(unsigned int r = 0; r < game.row_size(); ++r) {
			Games::Grids::Coord2D c1(r, 1), c2(r,3);
			if(game[c1] == mark && game[c2] == mark) {
				c1.col = 0, c2.col = 2;
				if(game[c1] == mark && game[c2] == mark) ++points;
				c1.col = 4;
				if(game[c1] == mark && game[c2] == mark) ++points;
			}
		}

		return points;
	}

	/** Conta o número de pontos por coluna do estado dado como argumento.
	 *
	 * @param game jogo a ser verificado
	 * @param mark símbolo a ser verificado. */
	static unsigned int count_in_col(const PubState &game, const Mark mark) {
		unsigned int points = 0;
		for(unsigned int c = 0; c < game.col_size(); ++c) {
			for(unsigned int r = 3; r < game.row_size(); ++r) {
				Games::Grids::Coord2D c1(r, c), c2(r - 3, c);
				if(game[c1] == mark && game[c2] == mark) {
					c1.row--, c2.row++;
					if(game[c1] == mark && game[c2] == mark) ++points;
				}
			}
		}

		return points;
	}

	/** Conta o número de pontos nas diagonais do estado dado como argumento.
	 *
	 * @param game jogo a ser verificado
	 * @param mark símbolo a ser verificado. */
	static unsigned int count_in_diag(const PubState &game, const Mark mark)  {
		unsigned int points = 0;

		for(unsigned int c = 3; c < game.col_size(); ++c) {
			for(unsigned int r = 3; r < game.row_size(); ++r) {
				Games::Grids::Coord2D c1(r, c), c2(r - 3, c - 3);
				if(game[c1] == mark && game[c2] == mark) {
					c1.row--, c1.col--, c2.row++, c2.col++;
					if(game[c1] == mark && game[c2] == mark) ++points;
				}
				c1.row = r - 3, c1.col = c, c2.row = r, c2.col = c - 3;
				if(game[c1] == mark && game[c2] == mark) {
					c1.row++, c1.col--, c2.row--, c2.col++;
					if(game[c1] == mark && game[c2] == mark) ++points;
				}
			}
		}

		return points;
	}

	/** Conta o número total de pontos do estado dado como argumento.
	 *
	 * @param game jogo a ser verificado
	 * @param mark símbolo a ser verificado. */
	static unsigned int count_points(const PubState &game, const Mark mark)  {
		return count_in_row(game, mark) + count_in_col(game, mark) + count_in_diag(game, mark);
	}

	/** Retorna o resultado da atual sequência de ações para o jogador dado.
	 *
	 * @see Result get_result(const PubState &, const Player *) */
	GameResult get_result(const PubState &game, const Mark mark) const  {
		unsigned int points = count_points(game, mark);
		unsigned int opponent_points = count_points(game, opponent_mark(mark));

		if(points > opponent_points) return VICTORY;
		if(points < opponent_points) return DEFEAT;
		return DRAW;
	}

protected:
	/** Chamada para preparativos necessários (se houver) antes do início de uma
	 * partida .  */
	void setup(const std::deque<PubPlayer *> &players) {
		if(players.size() != 2)
			throw std::invalid_argument("Cannot setup PubMatch with " + IIA::Utils::String::to_string(players.size()) + " player(s).");

		players.back()->mark = opponent_mark(players.front()->mark);
		
		for(PubPlayer *player : players) player->start_new_match();
	}


	/** Indica se a partida dada terminou. */
	bool over(const PubState &game) {
		Games::Grids::Coord2D coord;
		for(coord.row = 0; coord.row < game.row_size(); ++coord.row) {
			for(coord.col = game.col_size() - 1; coord.col >= 0; --coord.col) {
				if(game[coord] == EMPTY) return false;
			}
		}
		return true;
	}

	/** Retorna a referência para uma nova ação, que é inválida para o
	 * jogador e estado dados. */
	PubAction *invalid_action(const PubPlayer *player, 
							  const PubState &game) const {
		int invalid_col = game.invalid_coords().col;
		return new PubAction(invalid_col, invalid_col, EMPTY, 0);
	}

	/** Verifica se a jogada, feita pelo jogador, é válida para o estado atual. */
	bool allowed(const Move *move, const PubState &state) const {
		if(!move || !move->action) return false;
		if(move->action->cost > Games::Pub::MAX_TIME_COST_IN_NANOSECONDS) return false;
		if(move->action->mark == EMPTY) return false;

		Games::Grids::Coord2D coord(state.row_size() - 1, move->action->first);
		if(!state.valid(coord) || state[coord] != EMPTY) return false;

		if(coord.col == move->action->second) coord.row--;
		else coord.col = move->action->second;

		if(!state.valid(coord) || state[coord] != EMPTY) return false;

		return true;
	}
};
} // namespace Pub
} // namespace Games

#endif // GAMES_PUB_MATCH_H
