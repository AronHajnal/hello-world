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
        /*if( ( (i%M) >1 ) && (i > M) && ( i < ( M*(M-1) ) ) ){
            return std::vector<int> {i-1, i+1, i+M, i-M, i+M+1, i-M-1};
        }
        return std::vector<int> {};*/
        std::vector<int> out;
        int x = i/M;
        int y = i%M;
        if(x<M-1){out.push_back((x+1)*M+y);}
        if(y<M-1){out.push_back(x*M+y+1);}
        if(x>0){out.push_back((x-1)*M+y);}
        if(y>0){out.push_back(x*M+y-1);}
        if(x<M-1 && y>0){
            //cout << (x+1)*M+y-1 << endl;
            out.push_back((x+1)*M+y-1);}
        if(x>0 && y<M-1){
            //cout << (x-1)*M+y+1 << endl;
            out.push_back((x-1)*M+y+1);}
        return out;
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
        
    bool who_won(Value v){
        
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
    cout << g.is_connected(22,34, red);
    /*g.setval(0,5,red);
    g.drawboard();
    cout << g.neighbours(5) << endl;
    cout << g.neighbours(7)  << endl;
    cout << g.neighbours(35)  << endl;*/
    return 0;
}
