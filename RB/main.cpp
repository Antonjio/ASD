#include <iostream>

using namespace std;
enum Color {RED,BLACK};

class Node{
public:
    int key;
    Color colore;
    Node* left;
    Node* right;
    Node* parent;
    string get_color() {
        switch (colore) {
            case Color::BLACK:
                return "black";
                break;
            case Color::RED:
                return "red";
                break;
        }

        return "";
    }
    void printNode() { cout << "Node: " << key << " - Color: " << get_color() << endl; };

    Node(int key){
        this->key = key;
        left = right = parent = nullptr;
    }
};


class RB{
private:
    Node* root;

public:
    RB(){root = nullptr;}
    void leftRotate(Node*);
    void rightRotate(Node*);
    Node* getRoot() {return root;}
    void insert(int);
    void printTree(Node* node, string prefix = "", bool is_left = true) {
        if (node != nullptr) {
            cout << prefix;

            cout << (is_left ? "├── " : "└── ");
            node->printNode();

            printTree(node->left, prefix + (is_left ? "│   " : "    "), true);

            printTree(node->right, prefix + (is_left ? "│   " : "    "), false);
        }
    };
    Node* search(int);
    Node* minimum(Node*);
    void transplant(Node*,Node*);
    void deleteFixUp(Node*);
    void deleteNode(int);

};
//cancellazione
Node* RB::search(int key) {
    Node* current = root;
    while (current != nullptr && current->key != key) {
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    return current;
}
Node* RB::minimum(Node* nodo) {
    while (nodo->left != nullptr)
        nodo = nodo->left;
    return nodo;
}
void RB::transplant(Node* u, Node* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}
void RB::deleteFixUp(Node* x) {
    while (x != root && (x == nullptr || x->colore == BLACK)) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->colore == RED) {
                w->colore = BLACK;
                x->parent->colore = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }

            if ((w->left == nullptr || w->left->colore == BLACK) &&
                (w->right == nullptr || w->right->colore == BLACK)) {
                w->colore = RED;
                x = x->parent;
            } else {
                if (w->right == nullptr || w->right->colore == BLACK) {
                    if (w->left)
                        w->left->colore = BLACK;
                    w->colore = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->colore = x->parent->colore;
                x->parent->colore = BLACK;
                if (w->right)
                    w->right->colore = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->colore == RED) {
                w->colore = BLACK;
                x->parent->colore = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }

            if ((w->right == nullptr || w->right->colore == BLACK) &&
                (w->left == nullptr || w->left->colore == BLACK)) {
                w->colore = RED;
                x = x->parent;
            } else {
                if (w->left == nullptr || w->left->colore == BLACK) {
                    if (w->right)
                        w->right->colore = BLACK;
                    w->colore = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->colore = x->parent->colore;
                x->parent->colore = BLACK;
                if (w->left)
                    w->left->colore = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }

    if (x)
        x->colore = BLACK;
}
void RB::deleteNode(int key) {
    Node* nodo = search(key);
    if (!nodo)
        return;

    Node* y = nodo;
    Node* x;
    Color y_originale_colore = y->colore;

    if (nodo->left == nullptr) {
        x = nodo->right;
        transplant(nodo, nodo->right);
    } else if (nodo->right == nullptr) {
        x = nodo->left;
        transplant(nodo, nodo->left);
    } else {
        y = minimum(nodo->right);
        y_originale_colore = y->colore;
        x = y->right;

        if (y->parent == nodo) {
            if (x) x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = nodo->right;
            y->right->parent = y;
        }

        transplant(nodo, y);
        y->left = nodo->left;
        y->left->parent = y;
        y->colore = nodo->colore;
    }

    if (y_originale_colore == BLACK)
        deleteFixUp(x);

    delete nodo;
}



//inserimento
void RB::leftRotate(Node* nodo) {
    Node* y = nodo->right;            // y diventa il nuovo “padre” di x
    nodo->right  = y->left;
    if (y->left) y->left->parent = nodo;

    y->parent = nodo->parent;
    if (!nodo->parent)                // x era la radice
        root = y;                  // ora la radice è y   <-- CORRETTO
    else if (nodo == nodo->parent->left)
        nodo->parent->left  = y;
    else
        nodo->parent->right = y;

    y->left  = nodo;
    nodo->parent = y;
}
void RB::rightRotate(Node* node) {
    Node* y = node->left;
    node->left = y->right;

    if (y->right != nullptr) {
        y->right->parent = node;
    }

    y->parent = node->parent;

    if (node->parent == nullptr) {
        root = y;
    } else if (node == node->parent->left) {
        node->parent->left = y;
    } else {
        node->parent->right = y;
    }

    y->right = node;
    node->parent = y;
}
void RB::insert(int valore) {

    Node* nodo = new Node(valore);
    nodo->colore = RED;

    Node* y = nullptr;      // sarà il futuro padre di nodo
    Node* x = root;

    while (x != nullptr) {  // ricerca posizione
        y = x;
        if (nodo->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    nodo->parent = y;
    if (!y)                 // l’albero era vuoto
        root = nodo;
    else if (nodo->key < y->key)
        y->left = nodo;
    else
        y->right = nodo;

    /* 2) RB-fix-up ------------------------------------------------------- */
    while (nodo != root && nodo->parent->colore == RED) {
        if (nodo->parent == nodo->parent->parent->left) { // controllo se mio padre è figlio sinistro di mio nonno
            Node* uncle = nodo->parent->parent->right;      //assegno mio zio

            // Caso 1: zio rosso --> solo ricolorazioni
            if (uncle && uncle->colore == RED) {
                nodo->parent->colore = BLACK;
                uncle->colore = BLACK;
                nodo->parent->parent->colore = RED;
                nodo = nodo->parent->parent;
            } else {// mio zio è nero
                // Caso 2 triangolo: nodo è figlio destro --> rotazione sinistra sul padre
                if (nodo == nodo->parent->right) {
                    nodo = nodo->parent;
                    leftRotate(nodo);
                }
                // Caso 3 linea: nodo è figlio sinistro --> rotazione destra sul nonno
                nodo->parent->colore = BLACK;
                nodo->parent->parent->colore = RED;
                rightRotate(nodo->parent->parent);
            }
        } else { // simmetrico: padre = figlio destro del nonno
            Node* uncle = nodo->parent->parent->left;

            if (uncle && uncle->colore == RED) {
                nodo->parent->colore = BLACK;
                uncle->colore = BLACK;
                nodo->parent->parent->colore = RED;
                nodo = nodo->parent->parent;
            } else { // zio nero
                //Caso 2 triangolo: nodo è figlio sinistro --> rotazione destra sul padre
                if (nodo == nodo->parent->left) { //sono figlio sinistro di mio padre è c'è un triangolo
                    nodo = nodo->parent;
                    rightRotate(nodo);
                }
                // Caso 3 linea: nodo è figlio destro --> rotazione sinistra sul nonno
                nodo->parent->colore = BLACK;
                nodo->parent->parent->colore = RED;
                leftRotate(nodo->parent->parent);
            }
        }
    }
    root->colore = BLACK;   // proprietà #2: la radice è nera
}



int main() {
    RB albero;

    albero.insert(10);
    albero.insert(20);
    albero.insert(30);
    albero.insert(15);
    albero.insert(25);
    albero.insert(5);
    albero.insert(1);
    albero.insert(21);

    cout << "Albero prima della cancellazione:\n";
    albero.printTree(albero.getRoot());

    cout << "\nCancellazione del nodo 20...\n";
    albero.deleteNode(20);

    cout << "\nAlbero dopo la cancellazione:\n";
    albero.printTree(albero.getRoot());

    return 0;
}
