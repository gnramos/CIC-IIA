/** @file Player.hpp
 *
 * Definição de da classe abstrata Player, que define um jogador.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 5/2012 */
 
#ifndef GAMES_PLAYER_HPP
#define GAMES_PLAYER_HPP

#include <stdexcept>

#include "Agent.hpp"

namespace Games {
/** Template para um jogador. */
template <class state_t> 
class Player : public IIA::Agents::Agent<state_t, state_t> {
public:
	/** Construtor.
	 *
	 * @param name nome que identifica o jogador. */
	Player(std::string name) : id(name) {}
	
	
	/** Escolhe a ação a tomar com base no estado dado
	 *
	 * @param state o estado em questão.
	 * @return Action<state_t> * referência para uma <b>nova</b> instância da ação
	 * escolhida. */
	virtual IIA::Action<state_t>* decide_action(const state_t &state) = 0;

	/** O jogador sempre percebe o estado. */
	virtual state_t interpret_input(const state_t &percept) const {
		return percept;
	}
	
	/** Retorna a percepção do jogador. */
	virtual state_t percept() const {
		/** @todo trocar a exceção em Games::Player::percept() */
		throw std::invalid_argument("Player::percept() not implemented.");
	}
	
	/** Converte a coordenada em string. */
	friend std::ostream &operator <<(std::ostream &os, const Player &player) {
		os << player.id;
		return os;
	}

protected:
	/** Identifica o jogador. */
	std::string id;
};
} // namespace Games

#endif // GAMES_PLAYER_HPP
