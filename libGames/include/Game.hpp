/** @file Game.hpp
 *
 * Este arquivo define as estruturas comuns a diversos tipos de jogos 
 * (ex: tabuleiros).
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 01/2012 */
 
#ifndef GAMES_GAME_HPP
#define GAMES_GAME_HPP

#include <stdexcept>
#include <vector>

#include "Utils.h"

namespace Games {
/** Define grades (tabuleiros). */
namespace Grids {
/** Define uma coordenada bidimensional. */
struct Coord2D {
	/** Construtor.
	 *
	 * @param r a coordenada da linha.
	 * @param c a coordenada da coluna. */
	Coord2D(int r = 0, int c = 0) : row(r), col(c) {}
	/** A coordenada da linha. */
	int row;
	/** A coordenada da coluna. */
	int col;
};

/** Indica se a instância dada é igual a esta. */
inline bool operator==(const Coord2D &lhs, const Coord2D &rhs) {
	return (lhs.row == rhs.row && lhs.col == rhs.col);
}

inline static std::ostream &operator <<(std::ostream &os, const Coord2D &coord) {
	os << "(" << coord.row << "," << coord.col << ")";
	return os;
}

/** Define uma grade bidimensional. */
template <class cell_t>
class Grid2D {
public:
	/** Construtor de uma grade vazia.
	 *
	 * @param num_rows o número de linhas da grade.
	 * @param num_cols o número de colunas da grade.
	 * @param cell o valor inicial de cada casa da grade.*/
	Grid2D(unsigned int num_rows, unsigned int num_cols, const cell_t &cell) {
		if(num_rows == 0)
			throw std::invalid_argument("Grid2D must have at least one row.");
		if(num_cols == 0)
			throw std::invalid_argument("Grid2D must have at least one column.");

		grid.assign(num_rows, std::vector<cell_t>(num_cols, cell)) ;
	}

	/** Construtor de uma grade como cópia do dado. */
	Grid2D(const Grid2D &grid2d) : grid(grid2d.grid) {}
		
	/** Indica se a instância é igual a grade dads. */
	virtual bool operator== (const Grid2D &that) const {
		return (this->grid == that.grid);
	}

	/** Indica se a coordenada dada é válida, i.e. dentro dos limites de
	 * tamanho da grade.
	 *
	 * @param coord a coordenada. */
	bool valid(const Coord2D &coord) const {
		if(0 > coord.row || coord.row >= grid.size()) 	 return false;
		if(0 > coord.col || coord.col >= grid[0].size()) return false;
		return true;
	}

	/** Retorna uma coordenada inválida, i.e. fora dos limites de tamanho
	 * da grade. */
	virtual Coord2D invalid_coords() const {return Coord2D(grid.size(), grid[0].size());}

	/** Converte a grade em uma string. */
	friend std::ostream &operator <<(std::ostream &os, const Grid2D &grid) {
		for(unsigned int row = 0; row < grid.grid.size(); ++row)
			os << "\n" << IIA::Utils::String::join(grid.grid[row], " ");
		return os;
	}
	
	/** Retorna o número de linhas da grade. */
	unsigned int row_size() const {return grid.size();}
	/** Retorna o número de colunas da grade. */
	unsigned int col_size() const {return grid[0].size();}

	/** Acessa a marca da coordenada dada. */
	cell_t &operator[](const Coord2D &coord) {
		if(!valid(coord)) 
			throw std::invalid_argument("Invalid coord " + IIA::Utils::String::to_string(coord) + ".");
		return grid[coord.row][coord.col];
	}

	/** Acessa a marca da coordenada dada. */
	cell_t operator[](const Coord2D &coord) const {
		if(!valid(coord)) throw std::invalid_argument("Invalid coord " + IIA::Utils::String::to_string(coord) + ".");
		return grid[coord.row][coord.col];
	}

protected:
	/** Grade. */
	std::vector< std::vector<cell_t> > grid;
};
} // namespace Grids
} // namespace Games

#endif // GAMES_GAME_HPP
