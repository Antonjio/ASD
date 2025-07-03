#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;
enum Color{white,gray,black};

class Node{
private:
    int val;
    Color colore;
    Node* p;
    vector<Node*> adj;
    int distance;

public:
    Node(int valore) : val(valore), colore(white), p(nullptr), distance(INT_MAX){}
    int getVal(){return val;}
    Color getColor(){return colore;}
    Node* getP(){return p;}
    vector<Node*> getAdj(){return adj;}
    int getD(){return distance;}


    void setC(Color c){colore = c;}
    void setp(Node* node){p = node;}
    void setAdj(Node* node){adj.push_back(node);}
    void setD(int d){distance = d;}
};

class Edge{
private:
    Node* src;
    Node* dest;
    int weight;
public:
    Edge(Node* n1, Node* n2, int w) : src(n1), dest(n2), weight(w){}

    Node* getSrc(){return src;}
    Node* getDest(){return dest;}
    int getW(){return weight;}

    void setSrc(Node* n){src = n;}
    void setDest(Node* n){dest = n;}
    void setW(int w){weight = w;}
};

class Graph{
private:

    vector<Node*> nodes;
    vector<Edge*> edges;
    int V, E;

public:
    Graph(ifstream& input){load(input);}

    void load(ifstream& input){
        string totalToken;
        getline(input, totalToken);
        if(totalToken.front() == '<') totalToken = totalToken.substr(1);
        if(totalToken.back() == '>') totalToken.pop_back();

        for(char& c : totalToken) c = c == ',' ? ' ' : c;
        istringstream stream(totalToken);
        stream >> V >> E;
        stream.clear();

        for(int i =0; i < V; i++) setNode(new Node(i));

        string line;
        while(getline(input,line)){
            if(line.front() == '<') line = line.substr(1);
            if(line.back() == '>')  line.pop_back();

            for(char& c : line) c = c == ',' ? ' ' : c;
            stream.str(line);
            int u, v, w;
            stream >> u >> v >> w;

            Node* src = getNode(u);
            Node* dest = getNode(v);
            if(src && dest) setEdge(src, dest, w);
            stream.clear();
        }
    }

    void setNode(Node* node){
        nodes.push_back(node);
        if(V < nodes.size())
            V = nodes.size();
    }
    void setEdge(Node* n1, Node* n2, int w){
        Edge* arco = new Edge(n1,n2,w);
        edges.push_back(arco);
        if(E < edges.size())
            E = edges.size();
        n1->setAdj(n2);
        n2->setAdj(n1);
    }

    Node* getNode(int valore){
        for(auto& node : nodes){
            if(valore == node->getVal())
                return node;
        }
        return nullptr;
    }
    Edge* getEdge(Node* n1, Node* n2){
        for(auto& edge : edges){
            if(edge->getSrc() == n1 && edge->getDest() == n2 || edge->getSrc() == n2 && edge->getDest() == n1)
                return edge;
        }
        return nullptr;
    }

    void BFS(Node* s, ofstream& out){
        for(auto& node : nodes){
            node->setC(white);
            node->setD(INT_MAX);
            node->setp(nullptr);
        }
        s->setC(gray);
        s->setD(0);
        queue<Node*> q;
        q.push(s);
        while(!q.empty()){
            Node* node = q.front();
            q.pop();
            for(auto& adj : node->getAdj()){
                if(adj->getColor() == white){
                    adj->setC(gray);
                    adj->setp(node);
                    adj->setD(node->getD() + 1);
                    q.push(adj);
                }
            }
            node->setC(black);
        }
        for(auto& node : nodes){
            if(node->getP() == nullptr)
                out<<"node: "<<node->getVal()<<" predecessor: NULLPTR"<<" Distance: "<<node->getD()<<endl;
            else
                out<<"node: "<<node->getVal()<<" predecessor: "<<node->getP()->getVal()<<" Distance: "<<node->getD()<<endl;
        }
    }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    Graph grafo(in);
    grafo.BFS(grafo.getNode(0),out);
}