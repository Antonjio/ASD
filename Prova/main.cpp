#include <iostream>
#include <fstream>
#include <stack>
#include <climits>
#include <vector>

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

public:
    Node(int val) : key(val), d(INT_MAX), f(INT_MAX), p(nullptr), colore(white), time(0){}

    void setP(Node* node){p = node;}
    void setD(int time){d = time;}
    void setK(int val){key = val;}
    void setF(int time){f = time;}
    void setAdj(Node* node){adj.push_back(node);}
    void setColor(Color c){colore = c;}

    Node* getP(){return p;}
    int getD(){return d;}
    int getK(){return key;}
    int getF(){return f;}
    vector<Node*> getAdj(){return adj;}
    Color getC(){return colore;}

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
            if(node->getK() == u)
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
                out<<"node: "<<node->getK()<<", predecessor: "<<node->getP()->getK()<<", discovery time: "<<node->getD()<<", finish time: "<<node->getF()<<endl;
            else
                out<<"node: "<<node->getK()<<", predecessor: NULL"<<", discovery time: "<<node->getD()<<", finish time: "<<node->getF()<<endl;
        }
    }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    Graph grafo(in);
    grafo.DFS();
    grafo.print(out);
}