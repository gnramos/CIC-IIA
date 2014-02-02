/** @file Match.hpp
 *
 * Este arquivo contem a definição da classe abstrata Match, que define
 * a implementação de uma partida entre adversários.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date Janeiro, 2012 */

#ifndef GAMES_MATCH_HPP
#define GAMES_MATCH_HPP

#include <deque>
#include <set>
#include <stdexcept>

#include "GameResult.h"
#include "Utils.h"

namespace Games {
/** Template para uma partida. Cada partida consiste em uma sequência de ações
 * alternadas entre dois jogadores, a serem definidas conforme o estado evolui. */
template <class player_t, class action_t, class state_t>
class Match {
public:
	/** Define uma jogada na partida, que consiste em uma ação e quem a executou. */
	class Move {
	public:
		/** Construtor. */
		Move(const player_t *p, /**< [in] o jogador */
		 	 const action_t *a 	/**< [in] a ação */
		 	) : player(p), action(a) {
			if(!player)
				throw std::invalid_argument("Cannot have move without a player.");
			if(!action)
				throw std::invalid_argument("Cannot have move without an action.");
		}

		/** Executa a jogada no estado dado. */
		void execute(state_t &state) const { action->execute(state); }

		/** Converte em string. */
		friend std::ostream &operator <<(std::ostream &os, const Move &move) {
			os << *(move.player) << ": " << move.action->to_string();
			return os;
		}

		// Attributes
		const player_t *player;	/**< O jogador. */
		const action_t *action; /**< A jogada. */
	};
	
	/** Cria uma partida com os jogadores dados. */
	Match(const std::deque<player_t *> &p /**< [in] jogadores */
		 ) : players(p) {
		if(players.size() < 2)
			throw std::invalid_argument("Not enough players for match.");
	}
	
	/** Cria uma partida com os jogadores dados. */
	Match(const std::set<player_t *> &p /**< [in] jogadores */
		 ) : players(p.begin(), p.end()) {
		if(players.size() < 2)
			throw std::invalid_argument("Not enough players for match.");
	}

	/** Realiza o confronto, alternando os participantes, e retorna o estado 
	 * final da partida.
	 *
	 * @return state_t o estado resultante do confronto.
	 * @see bool allowed(const Move *, const state_t &) const
	 * @see IIA::Action<state_t>* Player::decide_action(const state_t &)
	 * @see void Move::execute(state_t &) const
	 * @see bool over(const state_t &)
	 * @see void setup(const typename std::deque<player_t *> &) */
	state_t play() {
		moves.clear();

		std::deque<player_t *> match_players(players);
		
		state_t state;

		setup(match_players);

		do {
			Move *move = choose_move(match_players.front(), state);
			moves.push_back(move);

			if(!allowed(move, state)) break;

			move->execute(state);
			
			next(match_players);
		} while(!over(state));

		// cleanup(match_players);

		return state;
	}

	/** Converte em string. */
	friend std::ostream &operator <<(std::ostream &os, const Match &match) {
		os << IIA::Utils::String::join_ptrs(match.moves);

		state_t state;
		for(int i = 0; i < match.moves.size() - 1; ++i)
			match.moves[i]->execute(state);

		Move *move = match.moves.back();
		if(!move || !match.allowed(move, state))
			os << "\n Invalid move: " << (*move);
		else
			move->execute(state);
		
		os << "\n" << state << "\n";

		return os;
	}

	/** Retorna o resultado do jogo para o jogador dado. */
	virtual GameResult get_result(const player_t *player) const = 0;

	/** Retorna os jogadores que participaram da partida. */
	std::deque<const player_t *> get_players() const {
		std::deque<const player_t *> players;

		for(Move *move : moves) {
			if(!IIA::Utils::contains(players, move->player))
				players.push_back(move->player);
		}

		return players;
	}

protected:
	/** Executa os preparativos (se houver) necessários para iniciar uma partida. */
	virtual void setup(const typename std::deque<player_t *> &players) {};

	/* * Chamada para preparativos (se houver) necessários ao terminar uma partida. */
	// virtual void cleanup(const typename std::deque<player_t *> &players) {};

	// Pure virtual
	/** Indica se a partida dada terminou. */
	virtual bool over(const state_t &game) = 0;

	/** Verifica se a jogada dada é válida no estado dado. */
	virtual bool allowed(const Move *move, const state_t &state) const = 0;

	/** Retorna a referência para uma nova ação, que é inválida para o
	 * jogador e estado dados. */
	virtual action_t *invalid_action(const player_t *player, const state_t &state) const = 0;
public:
	/** Retorna o resultado das ações executadas na ordem em que estão armazenadas. */
	state_t result() const {
		state_t state;

		for(Move *move : moves) {
			if(!allowed(move, state)) break;
			move->execute(state);
		}

		return state;
	}

	// Attributes
public:
	/** A sequência de ações tomadas no confronto. */
	std::deque<Move *> moves;
	/** Os jogadores envolvidos na partida. */
	const std::deque<player_t *> players;

private:
	// Para o código ficar mais legível
	// Retorna a jogada.
	Move *choose_move(player_t *player, state_t &state) const {
		action_t *action;
		try {
			action = static_cast<action_t *>(player->decide_action(state));
		} catch(std::exception &e) {
			action = invalid_action(player, state);
		}
		return new Move(player, action);
	}

	// seleciona o próximo jogador.
	inline void next(std::deque<player_t *> &match_players) {
		match_players.push_back(match_players.front()), match_players.pop_front();
	}
};
} // namespace Games

#endif // GAMES_MATCH_HPP
