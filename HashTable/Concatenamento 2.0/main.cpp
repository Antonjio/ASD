#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>

using namespace std;
template<typename K, typename V>
class Item{
private:
    K key;
    V val;
public:
    Item(K k, V v) : key(k), val(v){}

    K getK(){return key;}
    V getV(){return val;}
};

template<typename K, typename V>
class Hash{
private:
    vector<list<Item<K,V>*>> ht;
    int hashsize;

    int h(K key){return key%hashsize;}

    void load(ifstream&in){
        string totalToken;

        while (getline(in,totalToken)){
            if(totalToken.front() == '<') totalToken = totalToken.substr(1);
            if(totalToken.back() =='>') totalToken.pop_back();

            for(char& c : totalToken) c = c == ',' ? ' ' : c;
            istringstream stream(totalToken);

            K k; V v;
            while (stream >> k >> v)
                insert(new Item<K,V>(k,v));
        }
    }

public:
    Hash(ifstream& in, int size) : hashsize(size) {ht.resize(hashsize); load(in);}

    void insert(Item<K,V>* item){
        int index = h(item->getK());
        ht[index].push_back(item);
    }

    void deleteH(K key){
        int index = h(key);
        for(auto it = ht[index].begin(); it != ht[index].end(); it++){
            if((*it)->getK() == key){
                ht[index].erase(it);
                return;
            }
        }
        cerr<<"element not found"<<endl;
    }

    Item<K,V>* search(K key){
        int index = h(key);

        for(auto& item : ht[index]){
            if(item->getK() == key) return item;
        }
        cerr<<"element not found"<<endl;
        return nullptr;
    }

    void printF(ofstream& out){
        for(int i = 0; i < hashsize; i++){
            out<<"index: "<<i;

            if(ht[i].empty())
                out<<" -> empty bucket"<<endl;
            else{
                for(auto& item : ht[i])
                    out<<" -> [key: "<<item->getK()<<" - value: "<<item->getV()<<"]";
                out<<endl;
            }
        }
    }
    void print() {
        for (int i = 0; i < hashsize; i++) {
            std::cout << "Index: " << i;

            if (ht[i].empty())
                std::cout << " -> empty bucket" << std::endl;
            else {
                for (auto& item : ht[i]) {
                    std::cout << " -> [key: " << item->getK() << " - value: " << item->getV() << "]";
                }

                std::cout << std::endl;
            }
        }
    }
};

int main(int argc, char** argv) {
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");

    Hash<int, string> ht(input_file,10);

    ht.printF(output_file);


    int key_searched = 10;
    Item<int, string>* item = ht.search(10);

    item ? cout << endl
                << "Item with key " << key_searched << " found! Value " << item->getV() << endl
                << endl
         : cout << endl
                << "Item with key " << key_searched << " not found";

    ht.deleteH(10);
    ht.print();

    return 0;
}

