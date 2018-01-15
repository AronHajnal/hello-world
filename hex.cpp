#include <iostream> 
#include <vector>
#include <list>


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
const int M = (N+1)/2;

enum Value {empty, red, blue};

/*struct Pos{
    int i;
    int j;
    Value v;
    };*/

class Graph{
    
    private:
    
    std::vector<vector<Value>> board;
    Value turn;
    
    public:
    
    Graph(Value starter): board(M, vector<Value>(M, empty)), turn(starter){}
    
    bool setval(int i, int j, Value v){
        if(board[i][j] == empty){
            board[i][j] = v;
            return true;
            }
        return false;
        }
    Value getval(int i, int j){
        return board[i][j];
        }
    Value set_turn(){
        if(turn == red){
            turn = blue;
            return blue;
            }
        if(turn == blue){
            turn = red;
            return red;
            }
        return empty;
        }
    
    std::vector<int> neighbours(int i){
        std::vector<int> out;
        int x = i/M;
        int y = i%M;
        if(x<M-1){out.push_back((x+1)*M+y);}
        if(y<M-1){out.push_back(x*M+y+1);}
        if(x>0){out.push_back((x-1)*M+y);}
        if(y>0){out.push_back(x*M+y-1);}
        if(x<M-1 && y>0){
            out.push_back((x+1)*M+y-1);}
        if(x>0 && y<M-1){
            out.push_back((x-1)*M+y+1);}
        return out;
        }
    std::vector<int> vneighbours(int i, Value v){
        std::vector<int> out;
        std::vector<int> n = this->neighbours(i);
        for(int i : n){
            if(board.at(i/M).at(i%M) == v){
                out.push_back(i);
                }
            }
        return out;
        }
    bool is_connected(int s, int d, Value v){
        
        if(s == d){
            return true;
            }
            
        if(board[s/M][s%M] != v){
            return false;
            }
            
        std::vector<bool> visited(M*M, false);
       
        std::list<int> queue;
        visited[s] = true;
        queue.push_back(s);
        
        while (!queue.empty()){
            
            s = queue.front();
            queue.pop_front();
        
            std::vector<int> adj = this->vneighbours(s, v);
            //cout << s << endl;
            for (int i : adj){
                if (i == d){
                    cout << "connected!!!!!!!!!!!!" << endl;
                    return true;
                    }
                if (!visited[i]){
                    visited[i] = true;
                    queue.push_back(i);
                    }
                }
            }
        return false;
        }
        
    Value who_won(Value v){
        if(v == red){
            for(int i=0;i<M*M;i=i+M){
                for(int j=M-1;j<M*M;j=j+M){
                    if(is_connected(i,j,v)){
                        cout << "red won !!!";
                        return red;
                        }
                    }
                }
            }
        if(v == blue){
            for(int i=0;i<M;i++){
                for(int j=M*(M-1);j<M*M;j++){
                    if(is_connected(i,j,v)){
                        cout << "blue won !!!";
                        return blue;
                        }
                    }
                }
            }
        return empty;
        }
    
    void draw(bool x, const char a, const char b){
    x ? printf("%c",a) : printf("%c",b);
    }

void drawline(std::vector<Value> row, bool x){
    for (unsigned int i = 0; i<row.size(); i++){
            switch(row[i]){
                case empty: draw(x, '\\', '.');
                break;
                case red: draw(x, '\\', 'X');
                break;
                case blue: draw(x, '\\', 'O');
                }
            if(i < row.size()-1){
                draw(x, '/', '-');
                }
        }
    }
    
    
void drawboard(){
    for (int i = 0; i<N; i++){
        for (int j = 0; j<i; j++){
            printf(" ");
            }
        drawline(board[(i+1)/2], i%2);
        printf("\n");
    }
    }
    };
    
Value do_turn(Graph hex){
    Value turn = hex.set_turn();
    int move_x;
    int move_y;
    do{
        std::cout << "Please enter your x move: ";
        std::cin >> move_x;
        std::cout << "Please enter your y move: ";
        std::cin >> move_y;
        } while(hex.setval(move_x,move_y,turn));
    return hex.who_won(turn);
    }
    
void play(){
    std::cout << "Welcome to HEX! Choose your color: ";
    std::string color;
    std::cin >> color;
    Value start;
    if (color == "red"){
        start = red;
        }
    if(color == "blue"){
        start = blue;
        }
    Graph game(start);
    Value winner;
    do{
        winner = do_turn(game);
        } while(winner == empty);
    if(winner == red){
        std::cout << "Red won";
        }
    if(winner == blue){
        std::cout << "Blue won";
        }
    }

int main(){
    Graph g(red);
    g.setval(3,4, blue);
    g.setval(3,5, blue);
    g.setval(4,5, blue);
    g.setval(5,5, blue);
    g.setval(2,5, blue);
    g.setval(1,5, blue);
    g.setval(0,5, blue);
    g.drawboard();
    g.is_connected(22,35, red);
    g.who_won(blue);
    /*g.setval(0,5,red);
    g.drawboard();
    cout << g.neighbours(5) << endl;
    cout << g.neighbours(7)  << endl;
    cout << g.neighbours(35)  << endl;*/
    return 0;
}
