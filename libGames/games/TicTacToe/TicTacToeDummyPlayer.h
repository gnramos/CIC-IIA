/** @file TicTacToeDummyPlayer.h
 *
 * Descreve/define o jogador DummyPlayer para o \link Games::TicTacToe Jogo-da-Velha\endlink.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#ifndef GAMES_TICTACTOE_DUMMYPLAYER_H
#define GAMES_TICTACTOE_DUMMYPLAYER_H

#include "TicTacToePlayer.h"

namespace Games {
namespace TicTacToe {
/** Jogador DummyPlayer, que escolhe a primeira casa vazia disponível. */
class DummyPlayer : public TicTacToePlayer {
public:
	/** Construtor. */
	DummyPlayer(Mark mark, /**< marca do jogador */
			    std::string id = "DummyPlayer" /**< identifica o jogador */
				)
	: TicTacToePlayer(mark, id) {}

protected:
	/** Escolhe a jogada a ser feita. */
	Games::Grids::Coord2D choose_play(const TicTacToeState &game) {
		Games::Grids::Coord2D coord;
		for(coord.row = 0; coord.row < 3 ; ++coord.row) {
			for(coord.col = 0; coord.col < 3; ++coord.col) {
				if(game[coord] == EMPTY)
					return coord;
			}
		}

		/** @todo Alterara exceção em DummyPlayer::choose_play */
		throw std::invalid_argument("DummyPlayer could not choose a play.");
	}
};
} // namespace TicTacToe
} // namespace Games

#endif // GAMES_TICTACTOE_DUMMYPLAYER_H
