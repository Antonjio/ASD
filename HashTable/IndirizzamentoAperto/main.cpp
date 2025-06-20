#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

template<typename T, typename X>
class Item{
private:
    T key;
    X value;
public:
    Item(T key, X value) : key(key), value(value){}
    T getK(){return key;}
    X getV(){return value;}

};
template<typename T, typename X>
class HashTable{
private:
    vector<Item<T,X>*> table;
    int tableSize;
public:
    HashTable(int dim) : tableSize(dim) { table.resize(dim ,nullptr);}
    int hash(T key, int i){return (key + i) % tableSize;}
    int quadraticHash(int key, int i){return (key + i + i * i) %tableSize;}

    int doubleHash(int key, int i){
        int hash1 = key % tableSize;
        int hash2 = 1 + (key % (tableSize - 1));
        return (hash1 + i * hash2) % tableSize;
    }

    void insert(Item<T,X>* item){
        int i =0;
        int index;

        while (i < tableSize){
            index = hash(item->getK(), i);

            if(table[index] == nullptr){
                table[index] = item;
                cout<<"elemento inserito"<<endl;
                return;
            }
            if(table[index]->getK() == item->getK()){
                cout<<"elemento gia inserito"<<endl;
                return;
            }
            i++;
        }
        cout<<"OVERFLOW"<<endl;
    }

    void print(ofstream& out){
        for(int i = 0; i < tableSize; i++){
            if(table[i] != nullptr)
                out<<"index: "<< i << ", key: "<< table[i]->getK()<<", value: " << table[i]->getV()<<endl;
        }
    }
    string find(T key){
        int i = 0;
        int index;

        while (i < tableSize){
            index = hash(key,i);

            if(table[index] == nullptr){
                cout<<"elemento non trovato"<<endl;
                return "";
            }
            if(table[index]->getK() == key )
                return table[index]->getV();
            i++;
        }
        cout<<"elemento non trovato"<<endl;
        return "";
    }

    void deleteH(T key){
        int i =0;
        int index;
        while (i < tableSize){
            index = hash(key,i);
            if(table[index] == nullptr){
                cout<<"elemento non trovato"<<endl;
                return;
            }
            if(table[index]->getK() == key ){
                table[index] = nullptr;
                cout << "Hash table dopo l'eliminazione:" << endl;
                for (int i=0; i<tableSize; i++)
                    if (table[i] != nullptr)
                        cout << "Index: " << i << ", key: " << table[i]->getK() << ", value: " << table[i]->getV() << endl;
                return;
            }
            i++;
        }
    }
};


int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    HashTable<int, string> ht(10);
    while (!in.eof()){
        int i;
        string s;
        in >> i >> s;
        ht.insert(new Item<int,string>(i,s));
    }

    ht.print(out);
    in.close();out.close();

    int keyS = 6;
    string str = ht.find(keyS);
    if(str.length() == 0){
        cout<<"stringa non trovata per chiave: "<<keyS<<endl;
    }else
        cout<<"stringa per la chiave: "<<keyS<<" è: "<<str<<endl;

    ht.deleteH(12);
    return 0;
}
