#include <stack>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>


using namespace std;
enum Color{white,gray,black};
class Node {
    Node* parent;
    Color colore;
    int val;
    int f;
    int d;
    vector<Node*> adj;

public:
    Node(int v) : val(v), parent(nullptr), colore(white){}

    void setP(Node* n){parent = n;}
    void setC(Color c){colore = c;}
    void setV(int v){val = v;}
    void setF(int time){f = time;}
    void setD(int time){d = time;}
    void setAdj(Node* node){adj.push_back(node);}

    Node* getP(){return parent;}
    Color getC(){return colore;}
    int getV(){return val;}
    int getF(){return f;}
    int getD(){return d;}
    vector<Node*> getAdj(){return adj;}
};

class Edge{
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
    vector<Node*> nodes;
    vector<Edge*> edges;
    stack<Node*> l;
    int V, E, time, cycles;

    void load(ifstream& in){
        string tokens;
        getline(in,tokens);

        if(tokens.front() == '<') tokens = tokens.substr(1);
        if(tokens.back() == '>') tokens.pop_back();

        for(char& c : tokens) c = c == ',' ? ' ' : c;
        istringstream stream(tokens);
        stream >> V >> E;
        for(int i =0; i < V ; i ++)
            insertNode(new Node(i));
        while(getline(in,tokens)){
            if(tokens.front() == '<') tokens = tokens.substr(1);
            if(tokens.back() == '>') tokens.pop_back();

            for(char& c : tokens) c = c == ',' ? ' ' : c;
            istringstream stream(tokens);
            int u, v, w;
            while(stream >> u >> v >> w){
                Node* src = getNode(u);
                Node* dest = getNode(v);
                if(dest && src)
                    insertEdge(new Edge(src, dest, w));
            }
        }


    }

    void dfsVisit(Node* node, vector<Node*> path){
        time++;
        node->setD(time);
        node->setC(gray);
        path.push_back(node);

        for(auto& adj : node->getAdj()){
            Edge* edge = getEdge(node,adj);
            if(adj->getC() == white){
                edge->setType("albero");
                adj->setP(node);
                dfsVisit(adj,path);
            }
            else if(adj->getC() == gray){
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
                        cout<<path[i]->getV()<<" ";
                    cout<<adj->getV()<<endl;
                    cycles++;
                }
            } else if(adj->getC() == black && adj->getD() < node->getD())
                edge->setType("in avanti");
            else if(adj->getC() == black && adj->getD() > node->getD())
                edge->setType("trasversale");
        }
        time++;
        node->setC(black);
        node->setF(time);
        path.pop_back();
        l.push(node);
    }

public:
    Graph(ifstream& in) : time(0), cycles(0) {load(in);}

    void insertNode(Node* node){
        nodes.push_back(node);
        if(V < nodes.size())
            V = nodes.size();
    }

    Node* getNode(int k){
        for(auto& node : nodes){
            if(node->getV() == k)
                return node;
        }
        return nullptr;
    }

    void insertEdge(Edge* edge){
        edges.push_back(edge);
        if(E < edges.size())
            E = edges.size();
        edge->getSrc()->setAdj(edge->getDest());
    }

    Edge* getEdge(Node* n1, Node* n2){
        for(auto& edge : edges){
            if(edge->getDest() == n2 && edge->getSrc() == n1)
                return edge;
        }
        return nullptr;
    }

    void dfs(){
        for(auto& node : nodes){
            node->setC(white);
            node->setP(nullptr);
        }
        time = 0;
        cycles = 0;
        vector<Node*> path;

        for(auto& node : nodes){
            if(node->getC() == white)
                dfsVisit(node,path);
        }
    }

    void printEdges(){
        for(auto& edge : edges)
            cout<<"src: "<<edge->getSrc()->getV()<<" dest: "<<edge->getDest()->getV()<<" peso: "<<edge->getW()<<" type: "<<edge->getType()<<endl;
    }

    void printGraph(ofstream& out){
        for(auto& node : nodes){
            if(node->getP())
                out<<"node: "<<node->getV()<<" parent: "<<node->getP()->getV()<<" d time: "<<node->getD()<<" f time: "<<node->getF()<<endl;
            else
                out<<"node: "<<node->getV()<<" parent: NULLPTR d time: "<<node->getD()<<" f time: "<<node->getF()<<endl;
        }
    }
    int getCycle(){return cycles;}
    void topologicalPrint(){
        while(!l.empty()){
            Node* node = l.top();
            l.pop();
            if(node->getP())
                cout<<"node: "<<node->getV()<<" parent: "<<node->getP()->getV()<<" d time: "<<node->getD()<<" f time: "<<node->getF()<<endl;
            else
                cout<<"node: "<<node->getV()<<" parent: NULLPTR d time: "<<node->getD()<<" f time: "<<node->getF()<<endl;

        }

    }
};

int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");
    Graph graph(in);

    graph.dfs();
    graph.printGraph(out);
    cout << endl << endl;
    cout<< "Stampa degli archi: " << endl;

    graph.printEdges();
    cout<< "Numero di cicli: " << graph.getCycle() << endl;

    cout<< "Stampa topologica: "<< endl;
    graph.topologicalPrint();
}