#include "stdafx.h" 
#include <iostream> 
#include <vector>
#include <list>
#include <string>
#include <cstdio>
#include <set>
#include <random>

using namespace std;

const int N = 11; //size of the board
const int M = (N + 1) / 2;

//Tools for random number generation - the enemy plays randomly

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, M - 1);

//Value of a field on the Hex board can be red, blue or empty

enum Value { empty, red, blue };

//A position has two coordinates, a value and a unique id

struct Pos {
	int x;
	int y;
	Value v = Value::empty;
	int n = x*M + y;
};

//We want to compare positions when we find connected paths on the Hex board

bool operator==(const Pos& p, const Pos& q) {
	return p.n == q.n && p.v == q.v;
}
bool operator>(const Pos& p, const Pos& q) {
	return p.n > q.n;
}
bool operator<(const Pos& p, const Pos& q) {
	return p.n < q.n;
}

//I represent the Hex board as a graph class

class Graph {

private:

	std::vector<vector<Value>> board; //Contains all the positions on the Hex board
	Value turn; //Which player can play currently

public:

	Graph(Value starter) : board(M, vector<Value>(M, Value::empty)), turn(starter) {}

	bool setval(const Pos p) {
		if (p.x > -1 && p.y > -1 && p.x < M && p.y < M) {
			if (board[p.x][p.y] == Value::empty) {
				board[p.x][p.y] = p.v;
				return true;
			}
		}
		std::cout << "Please enter a valid value \n";
		return false;
	}
	const Value getval(const Pos& p) {

		//get the value of a position on the board

		return board[p.x][p.y];
	}
	Value set_turn() {

		//Change turns: red -> blue, blue -> red, return colour of current player

		if (turn == red) {
			turn = blue;
			return blue;
		}
		if (turn == blue) {
			turn = red;
			return red;
		}
		return Value::empty;
	}

	const std::set<Pos> neighbours(const Pos p) {

		//Find all neighbours of a given position, returns set of positions

		std::set<Pos> out;
		if (p.x<(M - 1)) {
			Pos temp{ p.x + 1, p.y , board[p.x + 1][p.y] };
			out.insert(temp);
		}
		if (p.y<(M - 1)) {
			Pos temp{ p.x,p.y + 1, board[p.x][p.y + 1] };
			out.insert(temp);
		}
		if (p.x>0) {
			Pos temp{ p.x - 1,p.y, board[p.x - 1][p.y] };
			out.insert(temp);
		}
		if (p.y>0) {
			Pos temp{ p.x,p.y - 1, board[p.x][p.y - 1] };
			out.insert(temp);
		}
		if (p.x<(M - 1) && (p.y>0)) {
			Pos temp{ p.x + 1,p.y - 1, board[p.x + 1][p.y - 1] };
			out.insert(temp);
		}
		if ((p.x>0) && p.y<(M - 1)) {
			Pos temp{ p.x - 1,p.y + 1, board[p.x - 1][p.y + 1] };
			out.insert(temp);
		}
		return out;
	}

	const std::set<Pos> vneighbours(const Pos p) {

		//Returns neighbours of a given position with the same value

		std::set<Pos> out;
		std::set<Pos> n = this->neighbours(p);
		for (Pos i : n) {
			if (board[i.x][i.y] == p.v) {
				out.insert(i);
			}
		}
		return out;
	}
	bool is_connected(Pos s, Pos d) {

		//Returns true if s and d are connected by a chain of positions of the same value as s and d

		if (s == d) {
			return true;
		}

		if (board[s.x][s.y] != s.v) {
			return false;
		}

		std::vector<bool> visited(M*M, false);

		std::list<Pos> queue;
		visited[s.n] = true;
		queue.push_back(s);

		while (!queue.empty()) {

			s = queue.front();
			queue.pop_front();

			std::set<Pos> adj = this->vneighbours(s);
			for (Pos i : adj) {

				if (i == d) {

					return true;
				}
				if (!visited[i.n]) {
					visited[i.n] = true;
					queue.push_back(i);
				}
			}
		}
		return false;
	}

	Value who_won(Value v) {

		//Get colour of winner - red is vertical, blue is horizontal

		for (int i = 0; i<M; i++) {
			for (int j = 0; j<M; j++) {
				if (v == red) {
					if (is_connected(Pos{ i,0,v }, Pos{ j,M - 1,v })) {
						cout << " ---------- Red won! ---------- ";
						return red;
					}
				}
				if (v == blue) {
					if (is_connected(Pos{ 0,i,v }, Pos{ M - 1,j,v })) {
						cout << " ---------- Blue won! ---------- ";
						return blue;
					}
				}
			}
		}
		return Value::empty;
	}

	void draw(bool x, const char a, const char b) {

		//Print one field from Hex board

		x ? printf("%c", a) : printf("%c", b);
	}

	void drawline(std::vector<Value> row, bool x) {

		//Draw one line of Hex board

		for (unsigned int i = 0; i<row.size(); i++) {
			switch (row[i]) {
			case Value::empty: draw(x, '\\', '.');
				break;
			case red: draw(x, '\\', 'X');
				break;
			case blue: draw(x, '\\', 'O');
			}
			if (i < row.size() - 1) {
				draw(x, '/', '-');
			}
		}
	}

	void drawboard() {

		//Draw the Hex board

		for (int i = 0; i<N; i++) {
			for (int j = 0; j<i; j++) {
				printf(" ");
			}
			drawline(board[(i + 1) / 2], i % 2);
			printf("\n");
		}
	}
};

//Enemy, currently plays randomly

class Enemy {
public:
	int get_move(std::mt19937& gen, std::uniform_int_distribution<>& dis) {

		//Get random legal move

		return dis(gen);
	}
};

Value do_turn(Graph& hex, Enemy& other, Value start) {

	//Change turns, either human or enemy player enter a move, detects if someone won the game

	hex.drawboard();
	Value turn = hex.set_turn();
	if (turn == red) { std::cout << " ---------- Red's turn ---------- " << std::endl; }
	if (turn == blue) { std::cout << " ---------- Blue's turn ---------- " << std::endl; }
	int move_x;
	int move_y;
	do {
		if (turn == start) {
			std::cout << "Please enter your x move: ";
			std::cin >> move_x;
			std::cout << "Please enter your y move: ";
			std::cin >> move_y;
		}
		else {
			move_x = other.get_move(gen, dis);
			move_y = other.get_move(gen, dis);
		}
	} while (!hex.setval(Pos{ move_x - 1, move_y - 1, turn }));
	return hex.who_won(turn);
}

void play() {

	//Player can choose color, change turns until someone wins

	std::cout << "Welcome to HEX! Choose your color (red or blue): ";
	std::string color;
	std::cin >> color;
	Value start;
	if (color == "red") {
		start = red;
	}
	if (color == "blue") {
		start = blue;
	}
	Graph game(start);
	Enemy other;
	Value winner;
	do {
		winner = do_turn(game, other, start);
	} while (winner == Value::empty);
	if (winner == red) {
		std::cout << "Red won" << std::endl;
	}
	if (winner == blue) {
		std::cout << "Blue won" << std::endl;
	}
}

int main() {
	play();
	std::getchar();
	return 0;
}
