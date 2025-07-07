#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
enum Color {white, gray, black};

class Node{

    int val;
    Node* parent;
    int distance;
    vector<Node*> adj;
    Color colore;
public:
    Node(int val) : parent(nullptr), distance(INT_MAX), colore(white), val(val) {}

    void setVal(int v){val = v;}
    void setP(Node* n){parent = n;}
    void setDistance(int time){distance = time;}
    void setAdj(Node* node){adj.push_back(node);}
    void setColor(Color c){colore = c;}

    int getVal(){return val;}
    Node* getParent(){return parent;}
    int getDistance(){return distance;}
    vector<Node*> getadj(){return adj;}
    Color getColor(){return colore;}

};

class Edge{
    Node* src;
    Node* dest;
    int weight;

public:
    Edge(Node* node1, Node* node2, int w) : src(node1), dest(node2), weight(w){}

    void setSrc(Node * n){src = n;}
    void setDest(Node* n){dest = n;}
    void setW(int w){weight = w;}

    Node* getSrc(){return src;}
    Node* getDest(){return dest;}
    int getW(){return weight;}
};

class Graph{
    vector<Node*> nodes;
    vector<Edge*> edges;

    int V, E, time;
    void load(ifstream& in){
        string tokens;
        getline(in, tokens);
        if(tokens.front() == '<') tokens = tokens.substr(1);
        if(tokens.back() == '>') tokens.pop_back();

        for(char& c : tokens) c = c == ',' ? ' ' : c;
        istringstream stream(tokens);
        stream >> V >> E;

        for(int i =0; i < V; i++)
            addNode(new Node(i));

        while (getline(in, tokens)){
            if(tokens.front() == '<') tokens = tokens.substr(1);
            if(tokens.back() == '>') tokens.pop_back();

            for(char& c : tokens) c = c == ',' ? ' ' : c;
            istringstream stream(tokens);
            int u, v, w;
            while(stream >> u >> v >> w){
                Node* node1 = getNode(u);
                Node* node2 = getNode(v);
                if(node1 && node2)
                    addEdge(new Edge(node1,node2,w));
            }
        }

    }

public:
    Graph(ifstream& in) {load(in);}

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
    void addEdge(Edge* e){
        edges.push_back(e);
        if(E < edges.size())
            E = edges.size();
        e->getSrc()->setAdj(e->getDest());
        e->getDest()->setAdj(e->getSrc());
    }

    void BFS(ofstream& out, Node* s){
        for(auto& node : nodes){
            node->setColor(white);
            node->setP(nullptr);
        }
        s->setDistance(0);
        s->setColor(gray);
        queue<Node*> q;
        q.push(s);
        while(!q.empty()){
            Node* node = q.front();
            q.pop();
            for(auto& adj : node->getadj()){
                if(adj->getColor() == white){
                    adj->setP(node);
                    adj->setDistance(node->getDistance() + 1);
                    adj->setColor(gray);
                    q.push(adj);
                }
            }
            node->setColor(black);
        }
        for(auto& node : nodes){
            if(node->getParent())
                out<<"node: "<<node->getVal()<<" parent: "<<node->getParent()->getVal()<<" distance: "<<node->getDistance()<<endl;
            else
                out<<"node: "<<node->getVal()<<" parent: NULLPTR"<<" distance: "<<node->getDistance()<<endl;
        }
    }
};
int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    Graph grafo(in);
    grafo.BFS(out,grafo.getNode(0));
}