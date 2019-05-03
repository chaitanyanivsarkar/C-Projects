// Maze_Creation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdint>
#include <random>
#include <algorithm>
#include <vector>
#include <stack>
#include <utility>
#include <array>

using std::pair;
using std::vector;
using std::make_pair;
using std::cout;
using std::endl;
using std::array;


/*
Flags for Edges and Visited
grid is a 2D vector of uint8_t
*/
enum {
	SOUTH   = 0x01,
	EAST    = 0x02,
	NORTH   = 0x04,
	WEST    = 0x08,
	VISITED = 0x10
};


#pragma region Grid class definations
class Grid {
public:
	Grid(int LENGTH, int WIDTH);
	~Grid();
	bool is_visited(int x, int y);
	void visit(int x, int y);
	void add_edge(int x1, int y1, int x2, int y2);
	bool has_edge(int x, int y, int direction);
	vector<pair<int, int>> get_neighbours(int x, int y);

private:
	vector<vector<uint8_t>> grid;
	int LENGTH, WIDTH;
};

Grid::Grid(int LENGTH, int WIDTH) : grid(LENGTH, vector<uint8_t>(WIDTH, 0)) {
	this->LENGTH = LENGTH;
	this->WIDTH = WIDTH;
}

Grid ::~Grid()
{
}

bool Grid::is_visited(int x, int y) {
	return grid[x][y] & VISITED;
}

void Grid::visit(int x, int y) {
	grid[x][y] |= VISITED;
}

void Grid::add_edge(int x1, int y1, int x2, int y2) {
	if (x2 == x1 + 1) {
		grid[x1][y1] |= SOUTH;
		grid[x2][y2] |= NORTH;
	}
	else if (x2 == x1 - 1) {
		grid[x1][y1] |= NORTH;
		grid[x2][y2] |= SOUTH;
	}
	else if (y2 == y1 + 1) {
		grid[x1][y1] |= EAST;
		grid[x2][y2] |= WEST;
	}
	else if (y2 == y1 - 1) {
		grid[x1][y1] |= WEST;
		grid[x2][y2] |= EAST;
	}
}

bool Grid::has_edge(int x, int y, int direction) {
	return grid[x][y] & direction;
}

vector<pair<int, int>> Grid::get_neighbours(int x, int y) {
	vector<pair<int, int>> neighbours;

	auto isValid = [this](int x, int y) -> bool {
		return x < LENGTH && x >= 0 && y < WIDTH && y >= 0;
	};

	// South neighbour
	if (isValid(x + 1, y) && !is_visited(x + 1, y)) {
		neighbours.push_back(make_pair(x + 1, y));
	}
	//East neighbour
	if (isValid(x, y + 1) && !is_visited(x, y + 1)) {
		neighbours.push_back(make_pair(x, y + 1));
	}
	// North neighbour
	if (isValid(x - 1, y) && !is_visited(x - 1, y)) {
		neighbours.push_back(make_pair(x - 1, y));
	}
	// West neighbour
	if (isValid(x, y - 1) && !is_visited(x, y - 1)) {
		neighbours.push_back(make_pair(x, y - 1));
	}

	return neighbours;
}

#pragma endregion



/*A randomised Deapth First Search*/
void generate_maze(Grid &maze, std::stack<pair<int, int>> &st) {
	
	int x = st.top().first, y = st.top().second;	st.pop();

	vector<pair<int, int>> neighbours = maze.get_neighbours(x, y);
	
	if (neighbours.size() > 0) {
		std::random_shuffle(std::begin(neighbours), std::end(neighbours));

		for (size_t i = 0; i < neighbours.size(); ++i) {
			st.push(neighbours[i]);

			int x2 = neighbours[i].first, y2 = neighbours[i].second;
			maze.visit(x2, y2);
			maze.add_edge(x, y, x2, y2);
		}
	}
}


/*Replace with something else like the
OLC-Game Engine or some other graphics library*/
void draw_to_console(Grid &maze, int Length, int Width);


int main() {
	// to make the drawing to console faster
	// unsafe if mixed with printf and scanf
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);


	int Length = 10, Width = 40;
	Grid maze(Length, Width);
	std::stack<pair<int, int>> st;

	maze.visit(0, 0);
	st.push(make_pair(0, 0));
	
	while (!st.empty()) {
		generate_maze(maze, st);
		draw_to_console(maze, Length, Width);
	}

	return 0;
}



void draw_to_console(Grid &maze, int Length, int Width) {
	system("cls");
	for (size_t i = 0; i < 2 * Length - 1; ++i) {
		if (i % 2 == 0) {
			for (size_t j = 0; j < 2 * Width - 1; ++j) {
				if (j % 2 == 0) {
					cout << "X";
				}
				else {
					// Check Eastern Connection
					if (maze.has_edge(i / 2, (j - 1) / 2, EAST)) cout << "-";
					else cout << " ";
				}
			}
			cout << endl;
		}

		else {
			for (size_t j = 0; j < 2 * Width - 1; ++j) {
				if (j % 2 == 0) {
					// Check Southern Connection
					if (maze.has_edge((i - 1) / 2, j / 2, SOUTH)) cout << "|";
					else cout << " ";
				}
				else cout << " ";
			}
			cout << endl;
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
