#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

template<typename K, typename V>
class Item{
private:
    K key;
    V value;
public:
    Item(K k, V v) : key(k), value(v){}
    K getK(){return key;}
    V getV(){return value;}
};

template<typename K, typename V>
class Hash{
private:
    vector<Item<K,V>*> hash;
    int size;

    int h(int key, int i){
        return (i+key) % size;
    }
    void load(ifstream& in){
        string totalToken;

        while (getline(in,totalToken)){
            if(totalToken.front() == '<') totalToken = totalToken.substr(1);

            if(totalToken.back() == '>') totalToken.pop_back();


            for(char& c : totalToken) c = c == ',' ? ' ' : c;
            istringstream stream(totalToken);
            K k; V v;
            while (stream >> k >> v){
                insertH(new Item<K,V>(k,v));
            }
        }
    }
public:
    Hash(ifstream& in, int s) : size(s) {hash.resize(size, nullptr);load(in);}
    void insertH(Item<K,V>* item){
        int i = 0;
        while (i < size){
            int index = h(item->getK(),i);
            if(hash[index] == nullptr){
                hash[index] = item;
                return;
            }
            if(hash[index]->getK() == item->getK()){
                cout<<"elemento gia inserito"<<endl;
                return;
            }
            i++;
        }
        cout<<"overflow"<<endl;
    }

    void deleteH(K key){
        int i =0;
        int index;
        while (i < size){
            index = h(key,i);
            if(hash[index]->getK() == key){
                hash[index] = nullptr;
                return;
            }
            if(!hash[index]){
                cout<<"element not found"<<endl;
                return;
            }
            i++;
        }
        cout<<"element not found"<<endl;
        return;
    }

    string search(K key){
        int i =0;
        int index;
        while (i < size){
            index = h(key,i);
            if(hash[index]->getK() == key){
                return hash[index]->getV();
            }
            if(hash[index] == nullptr){
                cout<<"element not found"<<endl;
                return "";
            }
            i++;
        }
        cout<<"element not found"<<endl;
        return "";
    }

    void printF(ofstream& out){
        for(int i = 0; i < size; i++){
            if(hash[i])
                out<<"index: "<<i<<" key: "<<hash[i]->getK()<<" Value: "<<hash[i]->getV()<<endl;
        }
    }


};
int main() {

    ifstream in("input.txt");
    ofstream out("output.txt");

    Hash<int, string>ht(in,10);
    ht.printF(out);


    return 0;
}
