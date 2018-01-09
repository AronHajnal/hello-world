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
    
    public:
    
    Graph(): board(M, vector<Value>(M, empty)){}
    
    void setval(int i, int j, Value v){
        board[i][j] = v;
        }
    Value getval(int i, int j){
        return board[i][j];
        }
    std::vector<int> neighbours(int i){
        if(i%M>1 && i > M && i < M*(M-1)){
            return std::vector<int> {i-1, i+1, i+M, i-M, i+M+1, i-M-1};
        }
        return std::vector<int> {};
        }
    std::vector<int> vneighbours(int i, Value v){
        std::vector<int> out;
        std::vector<int> n = this->neighbours(i);
        for(int i : n){
            cout << i << endl;
            cout << i/M << endl;
            cout << i%M << endl;
            if(board.at(i/M).at(i%M) == v){
                cout << "!!" << endl;
                out.push_back(i);
                }
            }
        return out;
        }
    bool is_connected(int s, int d, Value v){
        
        if(s == d){
            return true;
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

int main(){
    Graph g;
    g.setval(3,4, red);
    g.setval(3,5, red);
    g.setval(4,5, red);
    g.setval(5,5, red);
    g.drawboard();
    cout << g.is_connected(28,34, red);
    return 0;
}
