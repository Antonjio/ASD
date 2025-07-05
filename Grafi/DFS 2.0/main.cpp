#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <climits>
#include <set>

using namespace std;
enum Color{white,gray,black};

class Node{
private:
    Node* parent;
    int val;
    int f;
    int d;
    Color colore;
    vector<Node*> adj;

public:
    Node(int v) : val(v), f(INT_MAX), d(INT_MAX), parent(nullptr),colore(white){}
    void setP(Node* n){parent = n;}
    void setVal(int v){val = v;}
    void setF(int time){f = time;}
    void setD(int time){d = time;}
    void setColor(Color c){colore = c;}
    void setAdj(Node* n){adj.push_back(n);}

    Node* getP(){return parent;}
    int getV(){return val;}
    int getF(){return f;}
    int getD(){return d;}
    Color getC(){return colore;}
    vector<Node*> getAdj(){return adj;}
};

class Edge{
private:
    Node* src;
    Node* dest;
    int weight;
    string type;
public:
    Edge(Node* n1, Node* n2, int w) : src(n1), dest(n2), weight(w){}

    void setSrc(Node* n){src = n;}
    void setDest(Node* n){dest = n;}
    void setW(int w){weight = w;}
    void setType(string s){type = s;}

    Node* getSrc(){return src;}
    Node* getDest(){return dest;}
    int getW(){return weight;}
    string getType(){return type;}
};

class Graph{
private:
    vector<Node*> nodes;
    vector<Edge*> edges;

    int V, E,time,cycleCount;
    void load(ifstream& in){
        string totalToken;
        getline(in,totalToken);
        if(totalToken.front() == '<') totalToken = totalToken.substr(1);
        if(totalToken.back() == '>') totalToken.pop_back();
        for(char& c : totalToken) c = c == ',' ? ' ' : c;

        istringstream stream(totalToken);
        stream >> V >> E;
        for(int i = 0; i < V; i++){
            addNode(new Node(i));
        }
        stream.clear();
        while (getline(in,totalToken)){
            if(totalToken.front() == '<') totalToken = totalToken.substr(1);
            if(totalToken.back() == '>') totalToken.pop_back();
            for(char& c : totalToken) c = c == ',' ? ' ' : c;

            istringstream stream(totalToken);
            int u, v,w;
            while(stream >> u >> v >> w){
                Node* src = getNode(u);
                Node* dest = getNode(v);
                if(src && dest) addEdge(new Edge(src, dest, w));
            }
        }
    }
    void DFSVISIT(Node* node){
        time++;
        node->setD(time);
        node->setColor(gray);
        for(auto& adj : node->getAdj()){
            Edge* edge = getEdge(node,adj);
            if(adj->getC() == white){
                edge->setType("Dell'albero");
                adj->setP(node);
                DFSVISIT(adj);
            }else if(adj->getC() == gray)
                edge->setType("All'indietro");
            else if(adj->getC() == black && node->getD() < adj->getD())
                edge->setType("in avanti");
            else if(adj->getC() == black && node->getD() > adj->getD())
                edge->setType("trasversale");
        }
        time++;
        node->setF(time);
        node->setColor(black);
    }

    void cycleRec(Node* node, set<Node*>& visited, vector<Node*>& path){
        node->setColor(gray);
        visited.insert(node);
        path.push_back(node);

        for(auto& adj : node->getAdj()){
            if(adj->getC() == white){
                adj->setP(node);
                cycleRec(adj,visited,path);
            }else if(adj->getC() == gray){
                cout<<"ciclo trovato: "<<endl;

                int startIndex = -1;

                for(int i = 0; i < path.size(); i++){
                    if(path[i] == adj){
                        startIndex = i;
                        break;
                    }
                }
                if(startIndex != -1){
                    for(int i = startIndex; i < path.size(); i++)
                        cout<<path[i]->getV()<<" ";
                    cout<<adj->getV()<<endl;
                    cycleCount++;
                }
            }
        }
        node->setColor(black);
        path.pop_back();
    }

public:
    Graph(ifstream& in) : cycleCount(0) {load(in);}

    void addNode(Node* n){
        nodes.push_back(n);
        if(V < nodes.size())
            V = nodes.size();
    }
    void addEdge(Edge* edge){
        edges.push_back(edge);
        if(E < edges.size())
            E = edges.size();
        edge->getSrc()->setAdj(edge->getDest());
    }
    Node* getNode(int i){
        for(auto& node : nodes){
            if(i == node->getV())
                return node;
        }
        return nullptr;
    }
    Edge* getEdge(Node* n1, Node* n2){
        for(auto& edge : edges){
            if(edge->getDest() == n2 && edge->getSrc() == n1)
                return edge;
        }
        return nullptr;
    }
    void DFS(){
        time = 0;
        for(auto& node : nodes){
            node->setColor(white);
            node->setP(nullptr);
        }
        for(auto& node : nodes){
            if(node->getC() == white)
                DFSVISIT(node);
        }

    }
    void print(ofstream& out){
        for(auto& node : nodes){
            if(!node->getP())
                out<<"node: "<<node->getV()<<" parent: NULLPTR "<<"discovery time: "<<node->getD()<<" finish time: "<<node->getF()<<endl;
            else
                out<<"node: "<<node->getV()<<" parent: "<<node->getP()->getV()<<" discovery time: "<<node->getD()<<" finish time: "<<node->getF()<<endl;

        }
    }
    void printEdges() {
        for (auto& edge : edges) {
            cout << "L'arco (" << edge->getSrc()->getV() << "," << edge->getDest()->getV() << ") e' un arco "
                 << edge->getType() << endl;
        }
    }
    void printCycle(){
        set<Node*> visited;
        vector<Node*> path;

        for(auto& node : nodes){
            node->setColor(white);
            node->setP(nullptr);
        }
        for(auto& node : nodes){
            if(node->getC() == white)
                cycleRec(node,visited,path);
        }
        cout<<"\nNumero cicli: "<<cycleCount<<endl;
    }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    Graph grafo(in);
    grafo.DFS();
    grafo.print(out);
    grafo.printEdges();
    grafo.printCycle();
}