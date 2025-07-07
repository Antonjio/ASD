#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Node{
private:
    Node* right;
    Node* left;
    Node* parent;
    int val;

public:
    Node(int v) : val(v), right(nullptr), parent(nullptr), left(nullptr){}
    void setR(Node* n){right = n;}
    void setL(Node* n){left = n;}
    void setP(Node* n){parent = n;}
    void setVal(int valore){val = valore;}

    Node* getR(){return right;}
    Node* getL(){return left;}
    Node* getP(){return parent;}
    int getVal(){return val;}
};

class ABR{
private:
    Node* root;

    Node* insertRec(Node* node, int val){
        if(node == nullptr)
            return new Node(val);
        if(val < node->getVal()){
            Node* leftChild = insertRec(node->getL(), val);
            node->setL(leftChild);
            leftChild->setP(node);
        }else{
            Node* rightChild = insertRec(node->getR(), val);
            node->setR(rightChild);
            rightChild->setP(node);
        }
        return node;
    }
    Node* minimum(Node* node){
        while (node->getL())
            node = node->getL();
        return node;
    }
    Node* maximum(Node* node){
        while(node->getR())
            node = node->getR();
        return node;
    }
    Node* search(int val, Node* node){
        if(node == nullptr ||val == node->getVal())
            return node;
        if(val < node->getVal())
            return search(val,node->getL());
        else
            return search(val, node->getR());
    }
    void load(ifstream& in){
        string totalToken;
        while (getline(in,totalToken)){
            if(totalToken.front() == '<') totalToken = totalToken.substr(1);
            if(totalToken.back() == '>') totalToken.pop_back();
            for(char& c : totalToken) c = c ==',' ? ' ' : c;
            istringstream stream(totalToken);
            int k;
            while (stream >> k)
                insert(k);
        }

    }
public:
    ABR(ifstream& in) : root(nullptr){load(in);}
    Node* getRoot(){return root;}
    void insert(int val){root = insertRec(root, val);}

    Node* getPre(int key){
        Node* node = search(key,root);
        if(!node)
            return nullptr;
        if(node->getL())
            return maximum((node->getL()));

        Node* y = node->getP();
        while (y && node == y->getL()){
            node = y;
            y = y->getP();
        }

        return y;
    }
    Node* getSucc(int key){
        Node* node = search(key,root);
        if(!node)
            return nullptr;
        if(node->getR())
            return minimum(node->getR());
        Node* y = node->getP();
        while (y && node == y->getR()){
            node = y;
            y = y->getP();
        }
        return y;
    }
    void preorder(ofstream& out, Node* node){
        if(!node)
            return;
        out<<"Valore: "<<node->getVal()<<endl;
        preorder(out,node->getL());
        preorder(out,node->getR());
    }
    void postOrder(ofstream& out, Node* node){
        if(!node)
            return;
        postOrder(out, node->getR());
        postOrder(out, node->getL());
        out<<"nodo: "<<node->getVal()<<endl;
    }

    void inOrder(ofstream& out, Node* node){
        if(!node)
            return;
        inOrder(out,node->getL());
        out<<"Nodo: "<<node->getVal()<<endl;
        inOrder(out, node->getR());
    }

};




int main() {

    ifstream in("input.txt");
    ofstream out("output.txt");

    ABR abr(in);
    abr.preorder(out,abr.getRoot());
    Node* pre = abr.getPre(12);
    if(!pre)
        cout<<"predecessore non trovato"<<endl;
    else
        cout<<"predecessore di: 12 è: "<<pre->getVal()<<endl;
    Node* succ = abr.getSucc(12);
    if(!succ)
        cout<<"successore non trovato"<<endl;
    else
        cout<<"successore di: 22 è: "<<succ->getVal()<<endl;
    return 0;
}
