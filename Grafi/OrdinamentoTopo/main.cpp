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
    int key;
    Node* p;
    int d;
    int f;
    vector<Node*> adj;
    Color colore;
    int time;
    int distance;

public:
    Node(int val) : key(val), d(INT_MAX), f(INT_MAX), p(nullptr), colore(white), time(0){}

    void setP(Node* node){p = node;}
    void setD(int time){d = time;}
    void setK(int val){key = val;}
    void setF(int time){f = time;}
    void setAdj(Node* node){adj.push_back(node);}
    void setColor(Color c){colore = c;}
    void setDistance(int s){distance = s;}

    Node* getP(){return p;}
    int getD(){return d;}
    int getVal(){return key;}
    int getF(){return f;}
    vector<Node*> getAdj(){return adj;}
    Color getC(){return colore;}
    int getDistance(){return distance;}

};
class Edge{
private:
    Node* src;
    Node* dest;
    int w;
public:
    Edge(Node* node1, Node* node2, int weigth) : src(node1), dest(node2), w(weigth){}

    void setSrc(Node* node){src = node;}
    void setDest(Node* node){dest = node;}
    void setW(int peso){w = peso;}

    Node* getSrc(){return src;}
    Node* getDest(){return dest;}
    int getW(){return w;}
};
class Graph{

private:
    vector<Node*> nodes;
    vector<Edge*> edges;
    stack<Node*> l;
    int V,E,time = 0;

    void DFS_VISIT(Node* node){

        node->setColor(gray);
        time++;
        node->setD(time);

        for(auto& adj : node->getAdj()){
            if(adj->getC() == white){
                adj->setP(node);
                DFS_VISIT(adj);
            }
        }

        node->setColor(black);
        time++;
        node->setF(time);
        l.push(node);
    }

public:
    Graph(ifstream& in){

        in >> V >> E;

        for(int i =0; i < V; i++)
            addNode(new Node(i));

        for(int i = 0; i < E; i++){
            int u, v, w;
            in >> u >> v >>w;
            Node * src = getNode(u);
            Node * dest = getNode(v);
            if(src && dest )
                addEdge(src, dest, w);
            else
                cout<<"non è stato possibile inserire l'arco in quanto uno o entrambi i nodi non esistono"<<endl;

        }
        in.close();
    }

    void addNode(Node* node){
        nodes.push_back(node);

        if(V < nodes.size())
            V = nodes.size();
    }

    Node* getNode(int u){
        for(auto& node : nodes){
            if(node->getVal() == u)
                return node;
        }
        return nullptr;
    }
    void addEdge(Node* node1, Node* node2, int w){

        edges.push_back(new Edge(node1, node2,w));
        node1->setAdj(node2);
        //node2->setAdj(node1);

        if(E < edges.size())
            E = edges.size();
    }
    Edge* getEdge(Node* src, Node* dest) {
        for (auto& edge : edges) {
            if ((edge->getSrc() == src && edge->getDest() == dest) ||
                (edge->getSrc() == dest && edge->getDest() == src))
                return edge;
        }

        return nullptr;
    }
    void DFS(){
        for(auto&node : nodes){
            node->setColor(white);
            node->setP(nullptr);
        }
        time = 0;
        for(auto&node : nodes){
            if(node->getC() == white)
                DFS_VISIT(node);
        }
    }
    void print(ofstream& out){

        while(!l.empty()){
            Node* node = l.top();
            l.pop();

            if(node->getP() != nullptr)
                out<<"node: "<<node->getVal()<<", predecessor: "<<node->getP()->getVal()<<", discovery time: "<<node->getD()<<", finish time: "<<node->getF()<<endl;
            else
                out<<"node: "<<node->getVal()<<", predecessor: NULL"<<", discovery time: "<<node->getD()<<", finish time: "<<node->getF()<<endl;
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
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    Graph grafo(in);
    grafo.DFS();
    grafo.print(out);
}