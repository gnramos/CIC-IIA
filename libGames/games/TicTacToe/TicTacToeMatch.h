/** @file TicTacToeMatch.h
 *
 * Descreve/define uma partida para o \link Games::TicTacToe Jogo-da-Velha\endlink.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#ifndef GAMES_TICTACTOE_MATCH_H
#define GAMES_TICTACTOE_MATCH_H

#include "Match.hpp"
#include "TicTacToePlayer.h"

namespace Games {
namespace TicTacToe {
/** Define uma partida do \link TicTacToe Jogo-da-Velha\endlink. As regras são
 * simples: dois jogadores escolhem uma marcação cada, geralmente um círculo
 * (O) e um xis (X), e se alternam para marcar um espaço vazio no tabuleiro
 * (3x3). Vence o primeiro a conseguir três círculos ou três xis em linha, quer
 * horizontal, vertical ou diagonal. Não havendo possibilidade de vitória,
 * deve-se impedir que o adversário ganhe na próxima jogada. */
class TicTacToeMatch : public Games::Match<TicTacToePlayer, TicTacToeAction, TicTacToeState> {
public:
	/** Construtor. */
	TicTacToeMatch(const std::deque<TicTacToePlayer *> &players)
	: Games::Match<TicTacToePlayer, TicTacToeAction, TicTacToeState>(players) {}
	
	/** Construtor. */
	TicTacToeMatch(const std::set<TicTacToePlayer *> &players)
	: Games::Match<TicTacToePlayer, TicTacToeAction, TicTacToeState>(players) {}

	/** Retorna o resultado da atual sequência de ações para o jogador dado.
	 *
	 * @see GameResult get_result(const TicTacToeState &, const TicTacToePlayer *) */
	GameResult get_result(const TicTacToePlayer *player) const {
		if(moves.size() < 5) return UNKNOWN;
		if(moves[0]->player != player && moves[1]->player != player) return UNKNOWN;

		TicTacToeState game = result();

		return get_result(game, player->mark);
	}

protected:
	/** Verifica se o estado dado como argumento possui uma linha vitoriosa para
	 * o jogador especificado. A linha é vitoriosa se todas as casas estiverem
	 * marcadas com o mesmo símbolo.
	 *
	 * @return bool verdadeiro, se há uma linha vitoriosa, falso caso contrário. */
	bool has_winning_row(const TicTacToeState &game, /**< [in] jogo a ser verificado */
	 					 const Mark mark 			 /**< [in] símbolo a ser verificado */
	 					) const {
		Games::Grids::Coord2D coord;
		bool won = false;
		for(coord.row = 0; coord.row < 3; ++coord.row) {
			won = true;
			for(coord.col = 0; coord.col < 3; ++coord.col) {
				if(game[coord] != mark) {
					won = false;
					break;
				}
			}
			if(won) return true;
		}
		return false;
	}

	/** Verifica se o estado dado como argumento possui uma coluna vitoriosa
	 * para o jogador especificado. A coluna é vitoriosa se todas as casas
	 * estiverem marcadas com o mesmo símbolo.
	 *
	 * @return bool verdadeiro, se há uma coluna vitoriosa, falso caso contrário. */
	bool has_winning_column(const TicTacToeState &game, /**< [in] jogo a ser verificado */
	 					 	const Mark mark 			/**< [in] símbolo a ser verificado */
	 						) const {
		Games::Grids::Coord2D coord;
		bool won = false;
		for(coord.col = 0; coord.col < 3; ++coord.col) {
			won = true;
			for(coord.row = 0; coord.row < 3; ++coord.row) {
				if(game[coord] != mark) {
					won = false;
					break;
				}
			}
			if(won) return true;
		}
		return false;
	}

	/** Verifica se o estado dado como argumento possui uma diagonal vitoriosa
	 * para o jogador especificado. A diagonal é vitoriosa se todas as casas
	 * estiverem marcadas com o mesmo símbolo.
	 *
	 * @return bool verdadeiro, se há uma diagonal vitoriosa, falso caso contrário. */
	bool has_winning_diagonal(const TicTacToeState &game, 	/**< [in] jogo a ser verificado */
	 					 	  const Mark mark 				/**< [in] símbolo a ser verificado */
	 						 ) const {
		if(game[Games::Grids::Coord2D(1, 1)] != mark) return false;
		if(game[Games::Grids::Coord2D(0, 0)] == mark && game[Games::Grids::Coord2D(2, 2)] == mark) return true;
		if(game[Games::Grids::Coord2D(0, 2)] == mark && game[Games::Grids::Coord2D(2, 0)] == mark) return true;

		return false;
	}


	/** Retorna o resultado da atual sequência de ações para o jogador dado.
	 *
	 * @see GameResult get_result(const TicTacToeState &, const TicTacToePlayer *) */
	GameResult get_result(const TicTacToeState &game, const Mark mark) const {
		if(has_winning_row(game, mark) ||
		   has_winning_column(game, mark) ||
		   has_winning_diagonal(game, mark))
			return VICTORY;

		const Mark opponent = opponent_mark(mark);
		if(has_winning_row(game, opponent) ||
		   has_winning_column(game, opponent) ||
		   has_winning_diagonal(game, opponent))
			return DEFEAT;

		Games::Grids::Coord2D coord;
		for(coord.row = 0; coord.row < 3; ++coord.row) {
			for(coord.col = 0; coord.col < 3; ++coord.col) {
				if(game[coord] == TicTacToe::EMPTY) {
					return UNKNOWN;
				}
			}
		}

		return DRAW;
	}

	/** Chamada para preparativos necessários (se houver) antes do início de uma
	 * partida .  */
	void setup(const std::deque<TicTacToePlayer *> &players) {
		if(players.size() != 2)
			throw std::invalid_argument("Cannot setup TicTacToeMatch more (or less) than 2 players.");

		players.back()->mark = opponent_mark(players.front()->mark);
	}

	/** Indica se a partida dada terminou. */
	bool over(const TicTacToeState &game){
		if(moves.size() < 5) return false;

		return (get_result(game, CROSS) != UNKNOWN);
	}

	/** Retorna a referência para uma nova ação, que é inválida para o
	 * jogador e estado dados. */
	TicTacToeAction *invalid_action(const TicTacToePlayer *player, const TicTacToeState &game) const {
		return new TicTacToeAction(game.invalid_coords(), EMPTY, 0);
	}

	/** Verifica se a jogada, feita pelo jogador, é válida para o estado atual. */
	bool allowed(const Move *move, const TicTacToeState &game) const {
		if(!move || !move->action) return false;
		if(move->action->mark == EMPTY) return false;
		if(!game.valid(move->action->coord)) return false;
		if(game[move->action->coord] != EMPTY) return false;
		return true;
	}
};
} // namespace TicTacToe
} // namespace Games

#endif // GAMES_TICTACTOE_MATCH_H
