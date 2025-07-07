#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>

using namespace std;
enum Color{white,gray,black};
class Node{
    Node* parent;
    int f;
    int d;
    int val;
    Color colore;
    vector<Node*>adj;

public:
    Node(int v) : val(v), f(INT_MAX), d(INT_MAX), parent(nullptr),colore(white) {}

    void setP(Node* n){parent=n;}
    void setF(int time){f = time;}
    void setD(int time){d = time;}
    void setV(int v){val = v;}
    void setC(Color c){colore=c;}
    void setAdj(Node* n){adj.push_back(n);}

    Node* getParent(){return parent;}
    int getF(){return f;}
    int getD(){return d;}
    int getVal(){return val;}
    Color getC(){return colore;}
    vector<Node*> getAdj(){return adj;}
};
class Edge{
    Node* src;
    Node* dest;
    int weight;
    string type;
public:
    Edge(Node* n1, Node* n2, int w) : src(n1), dest(n2), weight(w), type("") {}

    Node* getSrc(){return src;}
    Node* getDest(){return dest;}
    int getW(){return weight;}
    string getType(){return type;}

    void setType(string tipo) {type = tipo;}
};

class Graph{
    vector<Node*> nodes;
    vector<Edge*> edges;
    int V, E, time, cycles;

    void load(ifstream& in){
        string tokens;
        getline(in,tokens);
        if(tokens.front() == '<') tokens = tokens.substr(1);
        if(tokens.back() == '>') tokens.pop_back();
        for(char& c : tokens) c = c == ',' ? ' ' : c;

        istringstream stream(tokens);
        stream >> V >> E;
        for(int i = 0; i < V; i++)
            addNode(new Node(i));
        while(getline(in,tokens)){
            if(tokens.front() == '<') tokens = tokens.substr(1);
            if(tokens.back() == '>') tokens.pop_back();
            for(char& c : tokens) c = c == ',' ? ' ' : c;
            int u, v, w;
            istringstream stream(tokens);
            while (stream >> u >> v >> w){
                Node* src = getNode(u);
                Node* dest = getNode(v);
                if(src && dest)
                    addEdge(new Edge(src,dest,w));
            }
        }
    }

    void dfsVisit(Node* node, vector<Node*> path){
        time++;
        node->setC(gray);
        node->setD(time);
        path.push_back(node);

        for(auto& adj : node->getAdj()){
            Edge* edge = getEdge(node, adj);

            if(adj->getC() == white){
                edge->setType("albero");
                adj->setP(node);
                dfsVisit(adj,path);
            } else if(adj->getC() == gray){
                cout<<"ciclo trovato"<<endl;
                edge->setType("all'indietro");
                int index = -1;
                for(int i =0; i < path.size(); i++){
                    if(path[i] == adj){
                        index = i;
                        break;
                    }
                }
                if(index != -1){
                    for(int i = index; i < path.size(); i++)
                        cout<<path[i]->getVal()<<" ";
                    cout<< adj->getVal()<< endl;
                    cycles++;
                }
            } else if(adj->getC() == black && node->getD() < adj->getD())
                edge->setType("in avanti");
            else if(adj->getC() == black && node->getD() > adj->getD())
                edge->setType("trasversale");
        }
        time++;
        node->setC(black);
        node->setF(time);
        path.pop_back();
    }
public:
    Graph(ifstream& in) : time(0), cycles(0){ load(in);}

    void addNode(Node* n){
        nodes.push_back(n);
        if(V < nodes.size())
            V = nodes.size();
    }
    Node* getNode(int k){
        for(auto& node : nodes){
            if(node->getVal() == k)
                return node;
        }
        return nullptr;
    }
    void addEdge(Edge* edge){
        edges.push_back(edge);
        if(E < edges.size())
            E = edges.size();
        edge->getSrc()->setAdj(edge->getDest());
    }
    Edge* getEdge(Node* src, Node* dest){
        for(auto& edge : edges){
            if(edge->getSrc() == src && edge->getDest() == dest)
                return edge;
        }
        return nullptr;
    }
    void dfs(){
        for(auto& node : nodes){
            node->setC(white);
            node->setP(nullptr);
        }
        vector<Node*> path;
        cycles = 0;

        for(auto& node : nodes){
            if(node->getC() == white)
                dfsVisit(node,path);
        }
    }

    void printEdges(){
        for(auto& edge : edges)
            cout<<"src: "<<edge->getSrc()->getVal()<<" dest: "<<edge->getDest()->getVal()<<" weight: "<<edge->getW()<<" type: "<<edge->getType()<<endl;
    }
    void printGraph(ofstream& out){
        for(auto& node : nodes){
            if(node->getParent())
                out<<"node: "<<node->getVal()<<" parent: "<<node->getParent()->getVal()<<" d time: "<<node->getD()<<" f time: "<<node->getF()<<endl;
            else
                out<<"node: "<<node->getVal()<<" parent: NULLPTR d time: "<<node->getD()<<" f time: "<<node->getF()<<endl;

        }

    }
    int getCycleCount (){return cycles;}
};
int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");
    Graph graph(in);

    graph.dfs();
    graph.printGraph(out);
    cout << endl << endl;
    graph.printEdges();
    cout<< "Numero di cicli: " << graph.getCycleCount() << endl;

}