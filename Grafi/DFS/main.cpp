#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <set>
#include <string>

using namespace std;
enum Color {white,gray,black};

class Node{
private:
    int val;
    Color colore;
    Node* p;
    int d;
    int f;
    vector<Node*> adj;
public:
    Node(int val) : val(val),colore(white), p(nullptr),d(INT_MAX),f(INT_MAX){}

    int getVal() { return val; }
    int getColor() {return colore;}
    Node* getP() {return  p;}
    int getD(){return d;}
    int getF(){return f;}
    vector<Node*>& getAdj(){ return adj;}

    void setColor(Color c){colore = c;}
    void setP(Node* node){p = node;}
    void setD(int time){d = time;}
    void setF(int time){f = time;}
    void addAdj(Node* n) { adj.push_back(n); }
};
class Edge{
private:
    Node* src;
    Node* dest;
    int weight;
    string type;
public:
    Edge(Node* u, Node* v, int w) : src(u), dest(v), weight(w){}

    Node* getSrc(){return src;}
    Node* getDest(){return dest;}
    int getWeight(){return weight;}
    string getType(){return type;}
    void setType(string s){type = s;}
};

class Graph{
private:
    vector<Node*> nodes;
    vector<Edge*> edges;

    int V,E,time,cycleCount;

    void DFS_Visit(Node* u){
        u->setColor(gray);
        time++;
        u->setD(time);

        for(Node* v : u->getAdj()){
            Edge* edge = getEdge(u,v);

            if(v->getColor() == white){
                edge->setType("DELL'ALBERO");
                v->setP(u);
                DFS_Visit(v);
            }else if(v->getColor() == gray)
                edge->setType("ALL'INDIETRO");
            else if(v->getColor() == black && u->getD() < v->getD())
                edge->setType("IN AVANTI");
            else if(v->getColor()==black && u->getD() > v->getD())
                edge->setType("TRASVERSALE");
        }

        u->setColor(black);
        time++;
        u->setF(time);
    }
    void cycleRec(Node* u, set<Node*>& visited, vector<Node*>& path){
        u->setColor(gray);
        visited.insert(u);
        path.push_back(u);

        for(Node* v : u->getAdj()){
            if(v->getColor() == white){
                v->setP(u);
                cycleRec(v,visited,path);
            } else if (v->getColor() == gray){
                cout<<"Ciclo trovato: "<<endl;

                int startIndex = -1;

                for(int i = 0; i < path.size(); i++){
                    if(path[i] == v){
                        startIndex = i;
                        break;
                    }
                }
                if(startIndex != -1){
                    for( int i = startIndex; i < path.size(); i++){
                        cout<<path[i]->getVal()<<" ";
                    }
                    cout<< v->getVal()<< endl;
                    cycleCount++;
                }
            }
        }
        u->setColor(black);
        path.pop_back();
    }
public:
    Graph(int v, int e) : V(v), E(e),time(0),cycleCount(0) {}

    void addNode(Node* node){
        nodes.push_back(node);
        if(nodes.size() > V)
            V = nodes.size();
    }

    Node* getNode(int val){
        for(auto& node : nodes){
            if(node->getVal() == val)
                return node;
        }
        return nullptr;
    }

    void addEdge(Node* u, Node* v, int w){
        edges.push_back(new Edge(u,v,w));
        u->addAdj(v);

        if(edges.size() > E){
            E = edges.size();
        }
    }

    Edge* getEdge(Node* u, Node* v){
        for(auto& edge : edges){
            if(edge->getSrc() == u && edge->getDest() == v)
                return edge;
        }
        return nullptr;
    }
    void DFS(){
        for(auto& u : nodes){
            u->setColor(white);
            u->setP(nullptr);
        }

        for(auto& u : nodes){
            if(u->getColor() == white)
                DFS_Visit(u);
        }
    }

    void print(ofstream& out) {
        for (auto& node : nodes) {
            if (node->getP() == nullptr)
                out << "Node: " << node->getVal() << ", Start visit time: " << node->getD() << ", End visit time: " <<node->getF()
                    << ", predecessor: NULL" << endl;
            else
                out << "Node: " << node->getVal() << ", Start visit time: " << node->getD() << ", End visit time: " <<node->getF()
                    << ", predecessor: " << node->getP()->getVal()<< endl;
        }
    }

    void printEdges() {
        for (auto& edge : edges) {
            cout << "L'arco (" << edge->getSrc()->getVal() << "," << edge->getDest()->getVal() << ") e' un arco "
                 << edge->getType() << endl;
        }
    }

    void printCycles() {
        set<Node*> visited;
        vector<Node*> path;

        for (auto& u : nodes) {
            u->setColor(white);
            u->setP(nullptr);
        }

        for (auto& u : nodes) {
            if (u->getColor() == white) {
                cycleRec(u, visited, path);
            }
        }

        cout << "\nNumero cicli: " << cycleCount << endl;
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int V, E;
    in >> V >> E;

    Graph graph(V, E);

    for (int i=0; i<V; i++)
        graph.addNode(new Node(i));

    for (int i=0; i<E; i++) {
        int u, v, w;
        in >> u >> v >> w;

        Node* src = graph.getNode(u);
        Node* dest = graph.getNode(v);
        if (src != nullptr && dest != nullptr)
            graph.addEdge(src, dest, w);
        else
            cout << "Non e' stato possibile aggiungere l'arco poiche' il nodo " << u << " e/o il nodo " << v
                 << " non esistono!" << endl;
    }

    graph.DFS();
    graph.print(out);

    in.close();
    out.close();

    graph.printEdges();
    graph.printCycles();

    return 0;
}
