#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
enum Color{white,gray,black};
class Node{
    int val;
    Node* predecessor;
    Color colore;
    int distance;
    int start;
    int finish;
    vector<Node*> adj;

public:
    Node(int v) : val(v) {}

    void setVal(int v){val = v;}
    void setPre(Node* node){predecessor = node;}
    void setColor(Color c){colore = c;}
    void setD(int d){distance = d;}
    void setAdj(Node* node){adj.push_back(node);}
    void setStart(int time){start = time;}
    void setFinish(int time){finish = time;}

    int getVal(){return val;}
    Node* getPre(){return predecessor;}
    Color getColor(){return colore;}
    int getDistance(){return distance;}
    vector<Node*> getAdj(){return adj;}
    int getStart(){ return start;}
    int getFinish(){return finish;}
};

class Edge{
    Node* src;
    Node* dest;
    int weight;
    string type;

public:
    Edge(Node* n1, Node* n2, int w) : src(n1), dest(n2), weight(w){}

    void setSrc(Node* n1){src = n1;}
    void setDest(Node* node){dest = node;}
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
    vector<Node*> path;
    stack<Node*> l;
    stack<Node*> topo;
    queue<Node*> coda;

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

    void dfsVisit(Node* node){
        node->setColor(gray);
        node->setStart(++time);
        path.push_back(node);
        for(auto& adj : node->getAdj()){
            Edge* edge = getEdge(node,adj);
            if(adj->getColor() == white){
                edge->setType("albero");
                adj->setPre(node);
                dfsVisit(adj);
            }
            else if(adj->getColor() == gray){
                edge->setType("indietro");
                cout<<"ciclo trovato"<<endl;
                int index = -1;
                cycles++;
                for(int i = 0; i < path.size(); i++){
                    if(path[i] == adj){
                        index = i;
                        break;
                    }
                }
                if(index != -1){
                    for(int i = index; i < path.size(); i++)
                        cout<<path[i]->getVal() <<" ";
                    cout<<path[index]->getVal()<<endl;
                }
            }else if(adj->getColor() == black && adj->getStart() < node->getStart())
                edge->setType("trasversale");
            else if(adj->getColor() == black && adj->getStart() > node->getStart())
                edge->setType("in avanti");
        }
        node->setColor(black);
        node->setFinish(++time);
        l.push(node);
        path.pop_back();
    }

    Graph* transpose(){
        Graph* tg = new Graph();
        for(int i = 0; i < V; i++)
            tg->insertNode(new Node(i));
        for(auto& edge : edges){
            Node* src = tg->getNode(edge->getDest()->getVal());
            Node* dest = tg->getNode(edge->getSrc()->getVal());
            tg->insertEdge(new Edge(src,dest,edge->getW()));
        }
        return tg;
    }
    void dfsT(Node* node){
        node->setColor(gray);
        for(auto& adj : node->getAdj()){
            if(adj->getColor() == white){
                adj->setPre(node);
                dfsT(adj);
            }
        }
        node->setColor(black);
        l.push(node);
    }

    void dfsTPrint(Node* node, vector<bool>& visited){
        visited[node->getVal()] = true;
        cout<<node->getVal()<<" ";
        for(auto& adj : node->getAdj()){
            if(!visited[adj->getVal()])
                dfsTPrint(adj,visited);
        }
    }

public:
    Graph() : time(0), cycles(0){}
    Graph(ifstream& in) : time(0), cycles(0){load(in);}

    void insertNode(Node* node){
        nodes.push_back(node);
        if(V < nodes.size())
            V = nodes.size();
    }
    Node* getNode(int k){
        for(auto& node : nodes)
            if(node->getVal() == k)
                return node;
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

    void bfs(int val){
        for(auto& node : nodes){
            node->setColor(white);
            node->setPre(nullptr);
        }
        Node* start = getNode(val);
        start->setColor(gray);
        start->setD(0);
        coda.push(start);
        while (!coda.empty()){
            Node* node = coda.front(); coda.pop();

            for(auto& adj : node->getAdj()){
                if(adj->getColor() == white){
                    adj->setPre(node);
                    adj->setD(node->getDistance() + 1);
                    adj->setColor(gray);
                    coda.push(adj);
                }
            }
            node->setColor(black);
        }
    }
    void printBFS(){
        for(auto& node : nodes){
            if(node->getPre())
                cout<<"node-> "<<node->getVal()<<" predecessor: "<<node->getPre()->getVal()<<" distance: "<<node->getDistance()<<endl;
            else
                cout<<"node-> "<<node->getVal()<<" predecessor: NULLPTR distance: "<<node->getDistance()<<endl;
        }
    }

    void dfs(){
        for(auto& node : nodes){
            node->setColor(white);
            node->setPre(nullptr);
        }
        time = 0;
        cycles = 0;
        for(auto&node : nodes){
            if(node->getColor() == white)
                dfsVisit(node);
        }
    }
    void printDFS(){
        for(auto& node : nodes){
            if(node->getPre())
                cout<<"node-> "<<node->getVal()<<" predecessor: "<<node->getPre()->getVal()<<" start: "<<node->getStart()<<" finish: "<<node->getFinish()<<endl;
            else
                cout<<"node-> "<<node->getVal()<<" predecessor: NULLPTR distance: "<<" start: "<<node->getStart()<<" finish: "<<node->getFinish()<<endl;
        }
    }
    int getCycle(){return cycles;}
    void topologicalPrint(){
        while(!l.empty()){
            Node* node = l.top();
            l.pop();
            if(node->getPre())
                cout<<"node: "<<node->getVal()<<" parent: "<<node->getPre()->getVal()<<" d time: "<<node->getStart()<<" f time: "<<node->getFinish()<<endl;
            else
                cout<<"node: "<<node->getVal()<<" parent: NULLPTR d time: "<<node->getStart()<<" f time: "<<node->getFinish()<<endl;

        }

    }

    void printSCC(){
        for(auto& node : nodes) node->setColor(white);
        for(auto& node : nodes)
            if(node->getColor() == white)
                dfsT(node);

        vector<bool> visited(V, false);
        Graph* tg = transpose();
        cout<<"scc"<<endl;
        while(!l.empty()){
            Node* node = l.top(); l.pop();
            if(!visited[node->getVal()]){
                Node* start = tg->getNode(node->getVal());
                dfsTPrint(start,visited);
                cout<<endl;
            }
        }
        delete tg;
    }
    void printEdges(){
        for(auto& edge : edges)
            cout<<"src: "<<edge->getSrc()->getVal()<<" dest: "<<edge->getDest()->getVal()<<" weight: "<<edge->getW()<<" type: "<<edge->getType()<<endl;
    }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    Graph grafo(in);

    cout<<"stampa bfs"<<endl;
    grafo.bfs(0);
    grafo.printBFS();

    cout<<"stampa dfs"<<endl;
    grafo.dfs();
    cout<<"cicli trovati: "<<grafo.getCycle()<<endl;
    grafo.printDFS();

    cout<<"stampa topologica"<<endl;
    grafo.topologicalPrint();

    grafo.printSCC();
    cout<<"stampa archi"<<endl;
    grafo.printEdges();


}