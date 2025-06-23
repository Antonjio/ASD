#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Node{
    int key;
    char character;
    Node* left;
    Node* right;
    Node* parent;
public:
    Node(int k, int c) : key(k), character(c), left(nullptr), right(nullptr){}

    int getKey(){return key;}
    char getChar(){return character;}
    Node* Left(){return left;}
    Node* Right(){return right;}
    Node* Parent(){return parent;}

    void setLeft(Node* n){left = n;}
    void setRight(Node* n){right = n;}
    void setParent(Node* n){parent = n;}
};

class ABR{
private:
    Node* root;
    unordered_map<char,string> huffmanTable;

    void buildfHuffmanTable(Node* node, string path){
        if(node == nullptr)
            return;
        if(node->Left() == nullptr && node->Right() == nullptr && node->getChar() != '*')
            huffmanTable[node->getChar()] = path;

        buildfHuffmanTable(node->Left(), path +"0");
        buildfHuffmanTable(node->Right(), path +"1");
    }

    Node* insertRec(Node* node, int key, char character){
        if(node == nullptr)
            return new Node(key,character);
        if (key < node->getKey()){
            Node* leftChild = insertRec(node->Left(), key, character);
            node->setLeft(leftChild);
            leftChild->setParent(node);
        } else{
            Node* rightChild = insertRec(node->Right(), key, character);
            node->setRight(rightChild);
            rightChild->setParent(node);
        }
        return node;
    }

    void preOrder(Node* node, ofstream& out){
        if(node == nullptr)
            return;

        out<<"Key: "<<node->getKey()<< ", character: "<<node->getChar()<<endl;
        preOrder(node->Left(),out);
        preOrder(node->Right(),out);
    }
    Node* minimum(Node* x){
        while(x->Left() != nullptr)
            x = x->Left();
        return x;
    }
    Node* maximum(Node* x){
        while(x->Right() != nullptr)
            x = x->Right();
        return x;
    }
public:
    ABR() : root(nullptr) {}
    Node* getRoot(){return root;}
    void insert(int key,char character){root = insertRec(root,key,character);}
    void preorder(ofstream& out){ preOrder(root,out);}
    Node* search(Node* node, int key){
        if(node == nullptr || node->getKey() == key)
            return node;
        if(key < node->getKey())
            return search(node->Left(),key);
        else
            return search(node->Right(),key);
    }
    Node* getSucc(Node* node){
        if(node == nullptr)
            return nullptr;
        if(node->Right() != nullptr)
            return minimum((node->Right()));
        Node* node2 = node->Parent();
        while (node2 != nullptr && node == node2->Right()){
            node = node2;
            node2 = node2->Parent();
        }
        return node2;
    }
    void writeSucc(Node* node, ofstream& out){
        Node* succ = getSucc(node);
        if(succ != nullptr)
            out<< "Chiave del successore: "<<succ->getKey()<< "Carattere del successore: "<<succ->getChar()<<endl;
        else
            out<<"Non ha un successore "<<endl;
    }
    Node* getPred(Node* node){
        if(node == nullptr)
            return nullptr;
        if(node->Left() != nullptr)
            return maximum(node->Left());
        Node* node2 = node->Parent();
        while (node2 != nullptr && node == node2->Left()){
            node = node2;
            node2 = node2->Parent();
        }
        return node2;
    }
    void writePredecessor(Node* x, ofstream& out) {
        Node* pred = getPred(x);

        if (pred != nullptr)
            out << "Predecessor's key: " << pred->getKey() << ", predecessor's character: " << pred->getChar() << endl;
        else
            out << "This node doesn't have a predecessor!" << endl;
    }
    void generateHuffmanTable() {
        buildfHuffmanTable(root, "");
    }

    string encodeString(string input) {
        string encoded;
        for (char c : input) {
            if (huffmanTable.find(c) != huffmanTable.end())
                encoded += huffmanTable[c];
            else {
                cout << "Il carattere non e' stato trovato!" << endl;
                return "";
            }
        }

        return encoded;
    }

    string decodeString(string encoded) {
        string decoded;
        Node* currentNode = root;

        for (char bit : encoded) {
            if (bit == '0')
                currentNode = currentNode->Left();
            else if (bit == '1')
                currentNode = currentNode->Right();

            if (currentNode->Left() == nullptr && currentNode->Right() == nullptr) {
                decoded += currentNode->getChar();
                currentNode = root;
            }
        }

        return decoded;
    }

    void transplant(Node* x, Node* y) {
        if (x->Parent() == nullptr)
            root = y;
        else if (x == x->Parent()->Left())
            x->Parent()->setLeft(y);
        else
            x->Parent()->setRight(y);

        if (y != nullptr)
            y->setParent(x->Parent());
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    ABR abr;

    int k;
    char c;
    while (in >> k >> c)
        abr.insert(k, c);

    abr.preorder(out);

    Node* x = abr.search(abr.getRoot(), 15);
    abr.writeSucc(x, out);

    x = abr.search(abr.getRoot(), 15);
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