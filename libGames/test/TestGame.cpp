/** @file TestGame.cpp
 * 
 * Implementa testes para a classe Games::Game.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */
 
#include <assert.h>

#include "Game.hpp"

using namespace Games::Grids;

void test_Coord2D_ctor() {
	Coord2D coord;
	assert(coord.row == 0 && coord.col == 0);
	
	coord = Coord2D(1, -2);
	assert(coord.row == 1 && coord.col == -2);
}

void test_Coord2D_operator_eq() {
	Coord2D coord1(1, -2), coord2(1, -2);
	assert(coord1 == coord2);
}

void test_Coord2D_to_string() {
	Coord2D coord(1, -2);
	
	assert("(1,-2)" == IIA::Utils::String::to_string(coord));
}

void test_Coord2D() {
	test_Coord2D_ctor();
	test_Coord2D_operator_eq();
	test_Coord2D_to_string();
}

void test_Grid2D_ctor() {
	try {
		Grid2D<int> grid(0,0,0);
		assert(false);
	} catch (std::invalid_argument e) {}
	try {
		Grid2D<int> grid(1,0,0);
		assert(false);
	} catch (std::invalid_argument e) {}
	try {
		Grid2D<int> grid(0,1,0);
		assert(false);
	} catch (std::invalid_argument e) {}

	Grid2D<int> grid(1,2,3);
	assert(grid.row_size() == 1);
	assert(grid.col_size() == 2);

	Coord2D coord;
	for(coord.row = 0; coord.row < grid.row_size(); ++coord.row)
		for(coord.col = 0; coord.col < grid.col_size(); ++coord.col)
			assert(grid[coord] == 3);

	Grid2D<int> grid1(grid);
	assert(grid1 == grid);
}

void test_Grid2D_operator_eq() {
	Grid2D<int> grid1(1,2,3), grid2(1,2,3);
	assert(grid1 == grid2);

	Coord2D coord;
	grid2[coord] = 0;
	assert(!(grid1 == grid2));
	
	grid2 = Grid2D<int>(1,1,3);
	assert(!(grid1 == grid2));
		
	grid2 = Grid2D<int>(2,2,3);
	assert(!(grid1 == grid2));
	
	grid2 = grid1;
	assert(grid1 == grid2);
}

void test_Grid2D_valid() {
	Grid2D<int> grid(1,2,3);
	
	Coord2D coord;
	assert(grid.valid(coord));

	coord.row = -1;
	assert(!grid.valid(coord));
	
	coord.col = 2;
	assert(!grid.valid(coord));

	coord.row = 0;
	assert(!grid.valid(coord));
	
	coord.col = 0;
	assert(grid.valid(coord));
}

void test_Grid2D_invalid_coords() {
	Grid2D<int> grid(1,2,3);
	Coord2D coord = grid.invalid_coords();
	assert(!grid.valid(coord));
}

void test_Grid2D_to_string() {
	Grid2D<int> grid(2,2,2);
	
	Coord2D coord;
	for(coord.row = 0; coord.row < grid.row_size(); ++coord.row)
		for(coord.col = 0; coord.col < grid.col_size(); ++coord.col)
			grid[coord] = coord.row*2 + coord.col;
	
	assert("\n0 1\n2 3" == IIA::Utils::String::to_string(grid));
}

void test_Grid2D_row_size() {
	Grid2D<int> grid(1,2,3);
	assert(grid.row_size() == 1);
}

void test_Grid2D_col_size() {
	Grid2D<int> grid(1,2,3);
	assert(grid.col_size() == 2);
}

void test_Grid2D() {
	test_Grid2D_ctor();
	test_Grid2D_operator_eq();
	test_Grid2D_valid();
	test_Grid2D_invalid_coords();
	test_Grid2D_to_string();
	test_Grid2D_row_size();
	test_Grid2D_col_size();
}

int main(int argc, char **argv) {
	test_Coord2D();
	test_Grid2D();

	return 0;
}
