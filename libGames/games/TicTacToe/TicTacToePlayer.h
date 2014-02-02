/** @file TicTacToePlayer.h
 *
 * Descreve/define um jogador do \link Games::TicTacToe Jogo-da-Velha\endlink.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#ifndef GAMES_TICTACTOE_PLAYER_H
#define GAMES_TICTACTOE_PLAYER_H

#include "Player.hpp"
#include "TicTacToeAction.h"

namespace Games {
namespace TicTacToe {
/** Define um jogador para o \link TicTacToe Jogo-da-Velha\endlink */
class TicTacToePlayer : public Games::Player<TicTacToeState> {
public:
	/** Construtor. */
	TicTacToePlayer(Mark m, std::string name)
	: Games::Player<TicTacToeState>(name), mark(m) {}

	/** Retorna a percepção do jogador. */
	virtual TicTacToeState percept() const {
		throw std::ios_base::failure("Player::percept() not implemented.");
	}

	/** Decide a ação a realizar dado o estado. */
	IIA::Action<TicTacToeState> *decide_action(const TicTacToeState &state) {
		/** Marca o tempo (em nanossegundos) para decisão da jogada e o define
		 * como custo da ação. */
		timespec start_time, end_time;

		IIA::Utils::Time::get_cpu_time(start_time);
		Games::Grids::Coord2D coord = choose_play(state);
		IIA::Utils::Time::get_cpu_time(end_time);

		timespec diff = IIA::Utils::Time::time_diff(start_time, end_time);
		double cost_in_ns = IIA::Utils::Time::to_nano(diff);

		return new TicTacToeAction(coord, mark, cost_in_ns);
	}

	// Attributes
	/** A marca deste jogador. */
	Mark mark;

protected:
	/** Define a jogada em função do estado dado.
	 *
	 * @param state [in] o estado do jogo.
	 * @return Games::Grids::Coord2D a coordenada onde marcar. */
	virtual Games::Grids::Coord2D choose_play(const TicTacToeState &state) = 0;

	/** Verifica se há possibilidade de ganhar em uma linha.
	 *
	 * @param game o estado atual do jogo.
	 * @param mark o jogador a ser verificado.
	 *
	 * @return Games::Grids::Coord2D coordenada em que há condição de vitória,
	 * inválida caso contrário. */
	Games::Grids::Coord2D can_win_in_row(const TicTacToeState &game, const Mark mark) const {
		Games::Grids::Coord2D coord, c1, c2;
		for(; coord.row < 3; ++coord.row, ++c1.row, ++c2.row) {
			for(coord.col = 0; coord.col < 3; ++coord.col) {
				c1.col = (coord.col + 1) % 3;
				c2.col = (coord.col + 2) % 3;
				if(game[coord] == EMPTY && game[c1] == mark && game[c2] == mark) {
					return coord;
				}
			}
		}

		return game.invalid_coords();
	}

	/** Verifica se há possibilidade de ganhar na coluna dada.
	 *
	 * @param game o estado atual do jogo.
	 * @param mark símbolo a ser verificado.
	 *
	 * @return Games::Grids::Coord2D coordenada em que há condição de vitória,
	 * inválida caso contrário. */
	Games::Grids::Coord2D can_win_in_col(const TicTacToeState &game, const Mark mark) const {
		Games::Grids::Coord2D coord, c1, c2;
		for(; coord.col < 3; ++coord.col, ++c1.col, ++c2.col) {
			for(coord.row = 0; coord.row < 3; ++coord.row) {
				c1.row = (coord.row + 1) % 3;
				c2.row = (coord.row + 2) % 3;
				if(game[coord] == EMPTY && game[c1] == mark && game[c2] == mark) {
					return coord;
				}
			}
		}

		return game.invalid_coords();
	}

	/** Verifica se há possibilidade de ganhar na diagonal que vai do canto
	 * superior direito ao inferior esquerdo.
	 *
	 * @param game estado atual do jogo.
	 * @param mark símbolo a ser verificado.
	 *
	 * @return Games::Grids::Coord2D coordenada em que há condição de vitória,
	 * inválida caso contrário. */
	Games::Grids::Coord2D can_win_in_d1(const TicTacToeState &game, const Mark mark) const {
		Games::Grids::Coord2D coord, c1, c2;
		for(; coord.row < 3; ++coord.row, ++coord.col) {
			c1.row = (coord.row + 1) % 3, c1.col = c1.row;
			c2.row = (coord.row + 2) % 3, c2.col = c2.row;
			if(game[coord] == EMPTY && game[c1] == mark && game[c2] == mark) {
				return coord;
			}
		}

		return game.invalid_coords();
	}

	/** Verifica se há possibilidade de ganhar na diagonal que vai do
	 * canto inferior esquerdo ao superior direito.
	 *
	 * @param game estado atual do jogo.
	 * @param mark símbolo a ser verificado.
	 *
	 * @return Games::Grids::Coord2D coordenada em que há condição de vitória,
	 * inválida caso contrário. */
	Games::Grids::Coord2D can_win_in_d2(const TicTacToeState &game, const Mark mark) const {
		Games::Grids::Coord2D coord(0, 2), c1, c2;
		for(; coord.row < 3; ++coord.row, --coord.col) {
			c1.row = (coord.row + 1) % 3, c1.col = (coord.col + 2) % 3;
			c2.row = (coord.row + 2) % 3, c2.col = (coord.col + 1) % 3;
			if(game[coord] == EMPTY && game[c1] == mark && game[c2] == mark) {
				return coord;
			}
		}

		return game.invalid_coords();
	}

	/** Verifica se há possibilidade do jogador definido pela marca dada vencer
	 * a partida representada pelo estado na próxima jogada.
	 *
	 * @param game estado atual do jogo.
	 * @param mark símbolo a ser verificado.
	 *
	 * @return Games::Grids::Coord2D coordenada em que há condição de vitória,
	 * inválida caso contrário.
	 *
	 * @see Games::Grids::Coord2D can_win_in_row(const TicTacToeState &, const Mark)
	 * @see Games::Grids::Coord2D can_win_in_col(const TicTacToeState &, const Mark)
	 * @see Games::Grids::Coord2D can_win_in_d1(const TicTacToeState &, const Mark)
	 * @see Games::Grids::Coord2D can_win_in_d2(const TicTacToeState &, const Mark) */
	Games::Grids::Coord2D can_win(const TicTacToeState &game, const Mark mark) {
		Games::Grids::Coord2D coord;

		coord = can_win_in_row(game, mark);
		if(game.valid(coord)) return coord;

		coord = can_win_in_col(game, mark);
		if(game.valid(coord)) return coord;

		coord = can_win_in_d1(game, mark);
		if(game.valid(coord)) return coord;

		coord = can_win_in_d2(game, mark);
		if(game.valid(coord)) return coord;

		return coord;
	}
};
} // namespace TicTacToe
} // namespace Games

#endif // GAMES_TICTACTOE_PLAYER_H
