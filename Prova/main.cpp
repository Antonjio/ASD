#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Node{
private:
    int k;
    Node* p;
    Node* left;
    Node* right;

public:
    Node(int chiave) : k(chiave), p(nullptr), left(nullptr), right(nullptr){}
    void setK(int key){k = key;}
    void setP(Node* n){p = n;}
    void setR(Node* n){right = n;}
    void setL(Node* n){left= n;}

    Node*getP(){return p;}
    Node*getL(){return left;}
    Node*getR(){return right;}
    int getK(){return k;}
};
class ABR{
private:
    Node* root;
    Node* insertRec(Node* node, int key){
        if(node == nullptr)
            return new Node(key);
        if(node->getK() > key){
            Node* leftChild = insertRec(node->getL(),key);
            node->setL(leftChild);
            leftChild->setP(node);
        } else {
            Node* rightChild = insertRec(node->getR(),key);
            node->setR(rightChild);
            rightChild->setP(node);
        }
        return node;
    }
    Node* minimum(Node* node){
        while(node->getL() != nullptr)
            node = node->getL();
        return node;
    }
    Node* maximum(Node* node){
        while(node->getR() != nullptr)
            node = node->getR();
        return node;
    }
    void preOrder(Node* node, ofstream& out){
        if(node == nullptr)
            return;

        out<<"Key: "<<node->getK()<<endl;
        preOrder(node->getL(),out);
        preOrder(node->getR(),out);
    }

public:
    ABR() : root(nullptr) {}
    Node* getRoot(){return root;}
    void insert(int key){root = insertRec(root,key);}
    Node* search(int key, Node* node){
        if (node == nullptr || key == node->getK())
            return node;
        if (key < node->getK())
            return search(key, node->getL());
        else
            return search(key, node->getR());
    }

    Node* getSucc(Node* node){
        if(node == nullptr)
            return nullptr;
        if(node->getR() != nullptr)
            return minimum(node->getR());
        Node* node2 = node->getP();
        while(node2 != nullptr && node == node2->getR()){
            node = node2;
            node2 = node->getP();
        }
        return node2;
    }
    Node* getPre(Node* node){
        if(node == nullptr)
            return node;
        if(node->getL() != nullptr)
            return maximum(node->getL());
        Node* node2 = node->getP();
        while(node2 != nullptr && node == node2->getL()){
            node = node2;
            node2 = node->getP();
        }
        return node2;
    }
    void writeSucc(Node* node, ofstream& out){
        Node* succ = getSucc(node);
        if(succ != nullptr)
            out<< "Chiave del successore: "<<succ->getK()<<endl;
        else
            out<<"Non ha un successore "<<endl;
    }
    void writePredecessor(Node* x, ofstream& out) {
        Node* pred = getPre(x);

        if (pred != nullptr)
            out << "Predecessor's key: " << pred->getK()<< endl;
        else
            out << "This node doesn't have a predecessor!" << endl;
    }
    void preorder(ofstream& out){ preOrder(root,out);}

};
int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    ABR abr;

    int k;
    while (in >> k)
        abr.insert(k);

    abr.preorder(out);

    Node* x = abr.search(15,abr.getRoot());
    abr.writeSucc(x, out);

    x = abr.search(15,abr.getRoot());
    abr.writePredecessor(x, out);

    in.close();
    out.close();

    /*
    abr.generateHuffmanTable();

    string encodedString = abr.encodeString("ACE");
    cout << "Encoded string: " << encodedString << endl;

    string decodedString = abr.decodeString(encodedString);
    cout << "Decoded string: " << decodedString << endl;


    x = abr.search(abr.getRoot(), 30);
    Node* y = abr.search(abr.getRoot(), 50);
    abr.transplant(x,y);
    abr.preorder(out);
    out.close();
    */

    return 0;
}