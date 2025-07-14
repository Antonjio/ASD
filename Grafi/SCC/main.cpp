#include <stack>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

enum Color { white, gray, black };

class Node {
    Node* parent;
    Color colore;
    int val;
    int f;
    int d;
    vector<Node*> adj;

public:
    Node(int v) : val(v), parent(nullptr), colore(white), d(0), f(0) {}

    void setP(Node* n) { parent = n; }
    void setC(Color c) { colore = c; }
    void setV(int v) { val = v; }
    void setF(int time) { f = time; }
    void setD(int time) { d = time; }
    void setAdj(Node* node) { adj.push_back(node); }

    Node* getP() { return parent; }
    Color getC() { return colore; }
    int getV() { return val; }
    int getF() { return f; }
    int getD() { return d; }
    vector<Node*>& getAdj() { return adj; }
};

class Edge {
    Node* src;
    Node* dest;
    int weight;
    string type;

public:
    Edge(Node* n1, Node* n2, int w) : src(n1), dest(n2), weight(w) {}

    void setSrc(Node* n) { src = n; }
    void setDest(Node* n) { dest = n; }
    void setW(int w) { weight = w; }
    void setType(string s) { type = s; }

    Node* getSrc() { return src; }
    Node* getDest() { return dest; }
    int getW() { return weight; }
    string getType() { return type; }
};

class Graph {
    vector<Node*> nodes;
    vector<Edge*> edges;
    stack<Node*> l;
    int V, E, time;

    void load(ifstream& in) {
        string tokens;
        getline(in, tokens);

        if (tokens.front() == '<') tokens = tokens.substr(1);
        if (tokens.back() == '>') tokens.pop_back();

        for (char& c : tokens) c = (c == ',') ? ' ' : c;
        istringstream stream(tokens);
        stream >> V >> E;

        for (int i = 0; i < V; i++)
            insertNode(new Node(i));

        while (getline(in, tokens)) {
            if (tokens.front() == '<') tokens = tokens.substr(1);
            if (tokens.back() == '>') tokens.pop_back();

            for (char& c : tokens) c = (c == ',') ? ' ' : c;
            istringstream stream(tokens);
            int u, v, w;
            while (stream >> u >> v >> w) {
                Node* src = getNode(u);
                Node* dest = getNode(v);
                if (dest && src)
                    insertEdge(new Edge(src, dest, w));
            }
        }
    }

    Graph* getTranspose() {
        Graph* gt = new Graph;
        for (int i = 0; i < V; i++)
            gt->insertNode(new Node(i));
        for (auto& edge : edges) {
            Node* src = gt->getNode(edge->getDest()->getV());
            Node* dest = gt->getNode(edge->getSrc()->getV());
            gt->insertEdge(new Edge(src, dest, edge->getW()));
        }
        return gt;
    }

    void dfs(Node* node) {
        time++;
        node->setD(time);
        node->setC(gray);
        for (auto& adj : node->getAdj()) {
            if (adj->getC() == white) {
                adj->setP(node);
                dfs(adj);
            }
        }
        node->setC(black);
        time++;
        node->setF(time);
        l.push(node);
    }

    void dfsPrint(Node* node, vector<bool>& visited) {
        visited[node->getV()] = true;
        cout << node->getV() << " ";
        for (auto& adj : node->getAdj()) {
            if (!visited[adj->getV()])
                dfsPrint(adj, visited);
        }
    }

public:
    Graph(ifstream& in) : time(0), V(0), E(0) { load(in); }
    Graph() : time(0), V(0), E(0) {}

    ~Graph() {
        for (auto n : nodes) delete n;
        for (auto e : edges) delete e;
    }

    void insertNode(Node* node) {
        nodes.push_back(node);
        if (V < nodes.size())
            V = nodes.size();
    }

    Node* getNode(int k) {
        for (auto& node : nodes) {
            if (node->getV() == k)
                return node;
        }
        return nullptr;
    }

    void insertEdge(Edge* edge) {
        edges.push_back(edge);
        if (E < edges.size())
            E = edges.size();
        edge->getSrc()->setAdj(edge->getDest());
    }

    void printSCC() {
        for (auto& node : nodes) node->setC(white);
        for (auto& node : nodes)
            if (node->getC() == white)
                dfs(node);

        Graph* gt = getTranspose();
        vector<bool> visited(V, false);

        cout << "Componenti fortemente connesse:\n";
        while (!l.empty()) {
            Node* node = l.top(); l.pop();
            if (!visited[node->getV()]) {
                Node* start = gt->getNode(node->getV());
                gt->dfsPrint(start, visited);
                cout << endl;
            }
        }
        delete gt;
    }
};

int main() {
    ifstream in("input.txt");
    if (!in) {
        cerr << "Errore apertura file input.txt\n";
        return 1;
    }

    Graph graph(in);
    graph.printSCC();
    return 0;
}
