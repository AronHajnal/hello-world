#include <iostream> 
#include <vector>
#include <algorithm>
#include <cstdlib>

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

class Heap{
    private:
    std::vector<int> content;
    int greater(int n,int m){return content[n] > content[m] ? n : m;}
    bool check_down(int n){return (content[n] > content[2*n+1]) && (content[n] > content[2*n+2]) ? true : false;}
    bool check_up(int n){return content[n] < content[(n-1-(1-(n%2)))/2] ? true : false;}
    void sift_down(unsigned int n){
        while(2*n < content.size() && !(this->check_down(n))){
            std::cout << content << std::endl;
            int bigger = this->greater(2*n+1, 2*n+2);
            std::swap(content[n], content[bigger]);
            n = bigger;
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
    Heap(std::initializer_list<int> l): content(l){}
    std::vector<int> get(){return content;}
    int size(){return content.size();}
    int contains(int val){
        if(std::find(content.begin(), content.end(), val) != content.end()) {
            return true;
        }
        else {
            return false;
        }
        }
    void insert(int val){
        content.push_back(val);
        this->sift_up(content.size()-1);
        }
    int top(){
        return content[0];
        }
    int min_priority(){
        int out = content[0];
        content[0] = content.back();
        content.pop_back();
        this->sift_down(0);
        return out;
        }
    void chg_priority(int n, int val){
        content[n] = val;
        this->sift_down(n);
        this->sift_up(n);
        }
    };
    
class Graph{
    private:
    std::vector<std::vector<int>> matrix;
    protected:
    void symmetrize(){
        for(unsigned int i; i<matrix.size(); i++){
            for(unsigned int j; j<i; j++){
                matrix[i][j] = matrix[j][i];
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
    int num_vert(){
        return matrix.size();
        }
    int num_edges(){
        int num = 0;
        for(auto v:matrix){
            for(auto i:v){
                if(i > 0){
                    num++;
                    }
                }
            }
        return num;
        }
    bool is_adjacent(int x, int y){
        return matrix[x][y] > 0 ? true : false;
        }
    std::vector<int> neighbours(int x){
        return matrix[x];
        }
    void add_node(){
        for(auto v:matrix){
            v.push_back(0);
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
    int size;
    double prob;
    int max_w;
    public:
    RandomGraph(int p, int mw, int n): Graph{{}}, prob(p), max_w(mw){
        for(int i = 0; i<n; i++){
            this->add_node();
            }
        }
    void generate(){
        for(int i; i<size; i++){
            for(int j; j<i; j++){
                double p = ((double) rand() / (RAND_MAX));
                double w = ((double) rand() / (RAND_MAX)) * max_w;
                if(p < prob){
                    this->add_edge(i,j,w);
                    }
                }
            }
        }
    };

int main(){
    srand(5323);
    //Heap x{10,7,5,3,4,4,2};
    //std::cout << x.min_priority() <<std::endl;
    //x.insert(6);
    //x.chg_priority(3,12);
    
    Graph g {{1,2},{3,4},{5,6}};
    g.get();
    
    
    return 0;
}
