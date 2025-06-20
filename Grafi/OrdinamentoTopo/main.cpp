#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <stack>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

enum Color{white,gray,black};

class Node{
private:
    Node* p;
    Color colore;
    int val;
    int d;
    int f;
    int distance;
    vector<Node*> adj;
public:
    Node(int val) : val(val),p(nullptr),colore(white),d(INT_MAX),f(INT_MAX),distance(INT_MAX){}

    int getVal(){return val;}
    Color getColor(){return colore;}
    Node* getP(){return p;}
    int getD(){return d;}
    int getF(){return f;}
    int getDistance(){return distance;}
    vector<Node*> getAdj(){return adj;}

    void setVal(int valore){ val = valore; }
    void setColor(Color c){ colore = c; }
    void setP(Node* parent){ p = parent; }
    void setD(int time){ d = time; }
    void setF(int time){ f = time; }
    void setDistance(int distanza){ distance = distanza; }
    void setAdj(Node* node){ adj.push_back(node); }

};

class Edge{
private:
    Node* src;
    Node* dest;
    int weight;
public:
    Edge(Node* u, Node* v, int w) : src(u), dest(v), weight(w){}

    Node* getSrc(){return src;}
    Node* getDest(){return dest;}
    int getW(){return weight;}
};

class Graph{
private:
    vector<Node*> nodes;
    vector<Edge*> edges;

    int V,E,time;
    stack<Node*> l;

    void DFS_VISIT(Node* u){
        u->setColor(gray);
        time++;
        u->setD(time);

        for(Node* v : u->getAdj()){
            if(v->getColor() == white){
                v->setP(u);
                DFS_VISIT(v);
            }
        }

        u->setColor(black);
        time++;
        u->setF(time);
        l.push(u);
    }
    bool isSafe(Node *v, vector<Node*>& path, int pos){
        Node* lastNode = path[pos-1];
        bool isAdj = false;

        for(Node* adj : lastNode->getAdj()){
            if(adj == v){
                isAdj = true;
                break;
            }
        }
        if(!isAdj)
            return false;
        for(int i = 0; i < pos; i++){
            if(path[i] == v)
                return false;
        }
        return true;
    }
    bool hamiltonianCycle(vector<Node*>& path, int pos){
        if(pos == V){
            Node* lastNode = getNode(pos-1);
            for(Node* adj : lastNode->getAdj()){
                if( adj == path[0])
                    return true;
            }
            return false;
        }
        for(auto& v : nodes){
            if(isSafe(v,path,pos)){
                path[pos] = v;
                if(hamiltonianCycle(path,pos+1))
                    return true;
                path[pos] = nullptr;
            }
        }
        return false;
    }
    void initializeSingleSource(Node* s){
        for(auto& u : nodes){
            u->setDistance(INT_MAX);
            u->setP(nullptr);
        }
        s->setP(nullptr);
        s->setDistance(0);
    }
    void relax(Edge* e){
        if(e->getDest()->getDistance() > e->getSrc()->getDistance() + e->getW()){
            e->getDest()->setDistance(e->getSrc()->getDistance() + e->getW());
            e->getDest()->setP(e->getSrc());
        }
    }
    struct compare{
        bool operator()(Node* u, Node* v){
            return u->getDistance() > v->getDistance();
        }
    };
public:
    Graph(int v, int e) : V(v), E(e), time(0){}

    void addNode(Node* n){
        nodes.push_back(n);
        if(nodes.size() > V)
            V = nodes.size();
    }
    void addEdge(Node* u, Node* v, int w){
        edges.push_back(new Edge(u,v,w));
        u->setAdj(v);

        if(edges.size() > E){
            E = edges.size();
        }
    }
    Node* getNode(int val){
        for (auto& node : nodes){
            if(node->getVal() == val)
                return node;
        }
        return nullptr;
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
        time++;
        for(auto& u : nodes){
            if(u->getColor() == white)
                DFS_VISIT(u);
        }
    }
    void topologicalPrint(ofstream& out){
        while(!l.empty()){
            Node* node = l.top();
            l.pop();
            out<<node->getVal()<<endl;
        }
    }
    bool findHamiltonianCycle(int pos){
        vector<Node*> path(V, nullptr);
        path[0] = getNode(pos);
        if(hamiltonianCycle(path,pos+1)){
            cout<<"ciclo hamiltoniano trovato"<<endl;

            for(int i = 0; i < V; i++){
                cout<<path[i]->getVal()<<" ";
            }
            cout<<path[0]->getVal()<<endl;
            return true;
        }else {
            cout<<"\n nessun ciclo hamiltoniano trovato"<<endl;
            return false;
        }
    }
    void bellmanFord(Node* s, Node* d){
        initializeSingleSource(s);

        for(int i = 0; i < V; i++){
            for(auto& edge : edges)
                relax(edge);
        }
        vector<int> path;
        Node* n = d;
        while(n != nullptr){
            path.push_back(n->getVal());
            n = n->getP();
        }
        cout<<"\ndistanza tra il nodo " << s->getVal()<<" e il nodo"<< d->getVal()<<": "<<d->getDistance();
        cout<<"\ncammino di pesi minimo: ";
        for(int i = path.size()-1; i >= 0; i--){
            cout<<path[i]<<" ";
        }
        cout<< endl << endl;
    }
    void dijkstra(Node* s) {
        initializeSingleSource(s);

        priority_queue<Node*, vector<Node*>, compare> minPQ;
        minPQ.push(s);

        set<Node*> visited;

        while(!minPQ.empty()) {
            Node* u = minPQ.top();
            minPQ.pop();

            if (visited.find(u) != visited.end())
                continue;

            visited.insert(u);

            for (Node* v : u->getAdj()) {
                Edge* edge = getEdge(u,v);

                if (edge != nullptr) {
                    relax(edge);

                    if (visited.find(v) == visited.end())
                        minPQ.push(v);
                }
            }
        }

        cout << "\nDistanze minime dal nodo " << s->getVal() << ":" << endl;
        for (auto& u : nodes)
            cout << "Node: " << u->getVal() << ", distance: " << u->getDistance() << endl;
    }

};

int main() {

    ifstream in("input.txt");
    ofstream out("output.txt");

    int V, E;
    in>>V>>E;

    Graph grafo(V,E);

    for(int i = 0; i < V; i++){
        grafo.addNode(new Node(i));
    }

    for(int i = 0; i < E; i++){
        int u,v,w;
        in>>u>>v>>w;
        Node* src = grafo.getNode(u);
        Node* dest = grafo.getNode(v);

        if(src != nullptr && dest != nullptr)
            grafo.addEdge(src,dest,w);
        else
            cout<< "Non è stato possibile aggiungere l'arco perché uno o entrambi i nodi non esistono"<< endl;
    }
    grafo.DFS();
    grafo.topologicalPrint(out);
    in.close();
    out.close();

    grafo.findHamiltonianCycle(0);
    Node* s = grafo.getNode(0);
    Node* d = grafo.getNode(3);
    if (s != nullptr && d != nullptr)
        grafo.bellmanFord(s, d);
    else
        cout <<"\nNon e' stato possibile invocare il metodo di Bellman Ford in quanto il nodo 0 e/o il nodo 3 non esistono!" << endl;

    s = grafo.getNode(0);
    if (s != nullptr)
        grafo.dijkstra(s);
    else
        cout <<"\nNon e' stato possibile invocare il metodo di Dijkstra in quanto il nodo 0 non esiste!" << endl;

    return 0;
}
