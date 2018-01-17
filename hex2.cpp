#include <iostream> 
#include <vector>
#include <list>
#include <string>
#include <cstdio>
#include <set>


using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
	for (auto& el : vec)
	{
		os << el << ' ';
	}
	return os;
}

const int N = 11;
const int M = (N + 1) / 2;

enum Value { empty, red, blue };

struct Pos{
int x;
int y;
Value v = empty;
int n = x*M+y;
};

bool operator==(const Pos& p, const Pos& q){
    return p.n == q.n && p.v == q.v;
    }
bool operator>(const Pos& p, const Pos& q){
    return p.n > q.n;
}
bool operator<(const Pos& p, const Pos& q){
    return p.n < q.n;
}


class Graph {

private:

	std::vector<vector<Value>> board;
	Value turn;

public:

	Graph(Value starter) : board(M, vector<Value>(M, Value::empty)), turn(starter) {}

	bool setval(const Pos p) {
		if (board[p.x][p.y] == Value::empty) {
			board[p.x][p.y] = p.v;
			return true;
		}
		std::cout << "Please enter a valid value";
		return false;
	}
	const Value getval(const Pos p) {
		return board[p.x][p.y];
	}
	Value set_turn() {
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
		std::set<Pos> out;
		if (p.x<M - 1) {
		    Pos temp{ p.x+1, p.y };
		    out.insert(temp); 
		    }
		if (p.y<M - 1) {
		    Pos temp{p.x,p.y+1};
		    out.insert(temp);
		    }
		if (p.x>0) {
		    Pos temp{p.x-1,p.y};
		    out.insert(temp);
		}
		if (p.y>0) {
		    Pos temp{p.x,p.y-1};
		    out.insert(temp);
		}
		if (p.x<M - 1 && p.y>0) {
		    Pos temp{p.x+1,p.y-1};
		    out.insert(temp);
		    }
		if (p.x>0 && p.y<M - 1) {
		    Pos temp{p.x-1,p.y+1};
		    out.insert(temp);
		}
		return out;
	}
	const std::set<Pos> vneighbours(const Pos p) {
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
			    cout << i.n << endl;
				if (i == d) {
					cout << "connected!!!!!!!!!!!!" << endl;
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
		
		for (int i = 0; i<M; i++) {
			for (int j = 0; j<M; j++) {
			    if (v == red) {
					if (is_connected(Pos{i,0,v}, Pos{j,M-1,v})) {
						cout << "red won !!!";
						return red;
					    }
				    }
				if (v == blue) {
					if (is_connected(Pos{0,i,v}, Pos{M-1,j,v})) {
						cout << "blue won !!!";
						return blue;
					    }
			        }
			    }
		    }
		return Value::empty;
	    }

	void draw(bool x, const char a, const char b) {
		x ? printf("%c", a) : printf("%c", b);
	}

	void drawline(std::vector<Value> row, bool x) {
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
		for (int i = 0; i<N; i++) {
			for (int j = 0; j<i; j++) {
				printf(" ");
			}
			drawline(board[(i + 1) / 2], i % 2);
			printf("\n");
		}
	}
};

/*class Enemy{
    private:
    
    };*/

Value do_turn(Graph& hex) {
	hex.drawboard();
	Value turn = hex.set_turn();
	if (turn == red) { std::cout << "Red's turn" << std::endl; }
	if (turn == blue) { std::cout << "Blue's turn" << std::endl; }
	int move_x;
	int move_y;
	do {
		std::cout << "Please enter your x move: ";
		std::cin >> move_x;
		std::cout << "Please enter your y move: ";
		std::cin >> move_y;
	} while (!hex.setval(Pos{move_x, move_y, turn}));
	return hex.who_won(turn);
}

void play() {
	std::cout << "Welcome to HEX! Choose your color: ";
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
	Value winner;
	do {
		winner = do_turn(game);
	} while (winner == Value::empty);
	if (winner == red) {
		std::cout << "Red won" << std::endl;
	}
	if (winner == blue) {
		std::cout << "Blue won" << std::endl;
	}
}

int main() {
	/*play();
	std::getchar();*/
	Graph g(red);
	g.setval(Pos{0,0,red});
	g.setval(Pos{0,1,red});
	g.setval(Pos{0,2,red});
	g.setval(Pos{0,3,red});
	g.setval(Pos{0,4,red});
	g.setval(Pos{0,5,red});
	cout << g.who_won(red) << endl;
	g.drawboard();
	return 0;
}
