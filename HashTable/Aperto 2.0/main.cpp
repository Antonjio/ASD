#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
template<typename K, typename V>
class Item{
    K key;
    V value;
public:

    Item(K k, V v) : key(k), value(v) {}
    K getKey(){return key;}
    V getValue(){return value;}
};

template<typename K, typename V>
class Hash{
    vector<Item<K,V>*> data;
    int hashsize;

    int h(K key, int i){return (key + i) % hashsize;}

    void load(ifstream& in){
        string tokens;
        while (getline(in,tokens)){
            if(tokens.front() == '<') tokens = tokens.substr(1);
            if(tokens.back() == '>') tokens.pop_back();
            for(char& c : tokens) c = c == ',' ? ' ' : c;

            K k; V v;
            istringstream stream(tokens);
            while(stream >> k >> v)
                insertH(new Item<K,V>(k,v));
        }

    }

public:
    Hash(ifstream& in, int size) : hashsize(size) {data.resize(hashsize, nullptr); load(in);}

    void insertH(Item<K,V> * item){
        int i = 0;
        while (i < hashsize){
            int index = h(item->getKey(), i);
            if(!data[index]){
                data[index] = item;
                cout<<"elemento inserito"<<endl;
                return;
            }
            if(data[index]->getKey() == item->getKey()){
                cout<<"elemento gia inserito"<<endl;
                return;
            }
            i++;
        }
        cout<<"overflow"<<endl;
    }

    void deleteH(K key){
        int i = 0;
        while (i < hashsize){
            int index = h(key,i);
            if(data[index] == nullptr){
                cout<<"element not found in the delete"<<endl;
                return;
            }
            if(data[index]->getKey() == key){
                data[index] = nullptr;
                cout<<"elemento eliminato stampa senza quell'elemento:"<<endl;
                for(int i = 0; i < hashsize; i++){
                    if(data[i])
                        cout<<"index: "<<i<<" key: "<<data[i]->getKey()<<" value: "<<data[i]->getValue()<<endl;
                }
                return;
            }
            i++;
        }
    }

    Item<K,V>* search(K key){
        int i =0;
        while (i < hashsize){
            int index = h(key,i);
            if(data[index] == nullptr){
                cout<<"element not found in the search"<<endl;
                return nullptr;
            }
            if(data[index]->getKey() == key)
                return data[index];
            i++;
        }
        return nullptr;
    }

    void print(ofstream& out){
        for(int i = 0; i < hashsize; i++){
            if(data[i])
                out<<"index: "<<i<<" key: "<<data[i]->getKey()<<" value: "<<data[i]->getValue()<<endl;
        }
    }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    Hash<int,string> ht(in,10);

    ht.print(out);
    ht.deleteH(100);
    Item<int,string>* item = ht.search(11);
    if(item)
        cout<<"item trovato, chiave: "<<item->getKey()<<" value: "<<item->getValue()<<endl;

}