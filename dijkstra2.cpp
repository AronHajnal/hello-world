#include <iostream> 
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <limits>

using namespace std;

double inf = std::numeric_limits<double>::infinity();

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

struct Node{
    int vertex;
    int dist;
    };
    
bool operator <(const Node& x, const Node& y) {
    return x.dist < y.dist;
}
bool operator >(const Node& x, const Node& y) {
    return x.dist > y.dist;
}

template<typename T>
class Heap{
    private:
    std::vector<T> content;
    int smaller(int n,int m){return content[n] < content[m] ? n : m;}
    bool check_down(int n){return (content[n] < content[2*n+1]) && (content[n] > content[2*n+2]) ? true : false;}
    bool check_up(int n){return content[n] > content[(n-1-(1-(n%2)))/2] ? true : false;}
    void sift_down(unsigned int n){
        while(2*n < content.size() && !(this->check_down(n))){
            std::cout << content << std::endl;
            int small = this->smaller(2*n+1, 2*n+2);
            std::swap(content[n], content[small]);
            n = small;
            std::cout << content << std::endl;
            }
        }
    void sift_up(unsigned int n){
        while(n != 0 and !(this->check_up(n))){
            std::cout << content << std::endl;
            int m = (n-1-(1-(n%2)))/2;
            std::swap(content[n], content[m]);
            n = m;
            std::cout << content << std::endl;
            }
        }
    public:
    Heap(std::initializer_list<T> l): content(l){}
    std::vector<T> get(){return content;}
    int size(){return content.size();}
    bool contains(int val){
        for(T i:content){
            if(i.vertex == val){
                return true;
                }
            }
        return false;
        }
    void insert(T val){
        content.push_back(val);
        this->sift_up(content.size()-1);
        }
    T top(){
        return content[0];
        }
    T min_priority(){
        T out = content[0];
        content[0] = content.back();
        content.pop_back();
        this->sift_down(0);
        return out;
        }
    void chg_priority(int n, int val){
        content[n].dist = val;
        this->sift_down(n);
        this->sift_up(n);
        }
    };
    
class Graph{
    private:
    std::vector<std::vector<int>> matrix;
    protected:
    void symmetrize(){
        for(unsigned int i = 0; i<matrix.size(); i++){
            for(unsigned int j = 0; j<i; j++){
                matrix[j][i] = matrix[i][j];
                }
            }
        }
    public:
    Graph(std::initializer_list<std::initializer_list<int>> l){
        for(auto i : l){
            std::vector<int> temp(i);
            matrix.push_back(temp);
            }
        }
    void get(){
        std::cout << matrix;
        }
    void get_edge(int i, int j){
        cout << matrix[i][j];
        }
    int num_vert(){
        return matrix.size();
        }
    int num_edges(){
        int num = 0;
        for(auto v:matrix){
            for(auto i:v){
                if(i > 0 && i < inf){
                    num++;
                    }
                }
            }
        return num;
        }
    bool is_adjacent(int x, int y){
        return (matrix[x][y] > 0) && (matrix[x][y] < inf) ? true : false;
        }
    std::vector<int> neighbours(int x){
        std::vector<int> 
        }
    void add_node(){
        for(unsigned int i = 0; i<matrix.size(); i++){
        matrix[i].push_back(0);
        }
        std::vector<int> temp (matrix.size()+1, 0);
        matrix.push_back(temp);
        }
    void add_edge(int x, int y, int weight){
            matrix[x][y] = weight;
        }
    };
        
class RandomGraph : public Graph{
    private:
    double prob;
    int max_w;
    int size;
    public:
    RandomGraph(double p, int mw, int n): Graph{{0}}, prob(p), max_w(mw), size(n){
        for(int i = 0; i<size; i++){
            this->add_node();
            }
        }
    void generate(){
        for(int i = 0; i<size+1; i++){
            for(int j = 0; j<i; j++){
                double p = ((double) rand() / (RAND_MAX));
                int w = rand();
                if(p < prob){
                    this->add_edge(i,j,w);
                    }
                }
            }
        this->symmetrize();
        }
    };
    
class Dijkstra{
    private:
    Graph graph;
    Heap<Node> heap;
    public:
    Dijkstra(Graph g): graph(g), heap{}{};
    void shortest(int source){
        
        }
    };

int main(){
    srand(time(NULL));
    //Heap x{10,7,5,3,4,4,2};
    //std::cout << x.min_priority() <<std::endl;
    //x.insert(6);
    //x.chg_priority(3,12);
    
    //Graph g {{1,2},{3,4},{5,6}};
    //g.get();
    RandomGraph rg(0.5,2,6);
    rg.generate();
    rg.get();
    return 0;
}
