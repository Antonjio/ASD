#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

template<typename T,typename X>
class item{
private:
    T key;
    X val;
public:
    item(T k, X v) : key(k), val(v){}
    T getK(){return key;}
    X getV(){return val;}
};
template<typename T, typename X>
class HashTable{
private:
    vector<list<item<T,X>*>> ht;
    int size;
public:
    HashTable(int size,ifstream& input) : size(size){
        ht.resize(size);
        T key;
        X val;
        while (input >> key >> val) insert(new item<T,X>(key,val));
        input.close();
    }
    int divideHashing(T key){return key%size;}
    int multiplyHashing(T key){
        int a = (sqrt(5) - 1) /2;
        return size *(key * a % 1);
    }
    void insert(item<T,X>* element){
        int index = divideHashing(element->getK());
        ht[index].push_back(element);
    }
    item<T,X>* search(T key){
        int index = divideHashing(key);

        for(auto& item : ht[index]){
            if(item->getK() == key) return item;
        }
        cerr<<"element not found"<<endl;
        return nullptr;
    }
    void deleteH(T key){
        int index = divideHashing(key);

        for(auto it = ht[index].begin(); it != ht[index].end(); it++){
            if((*it)->getK() == key){
                ht[index].erase(it);
                return;
            }
        }
        cerr<<"element not found"<< endl;
    }

    void print_in_file(std::ofstream& output_file) {
        for (int i = 0; i < size; i++) {
            output_file << "Index: " << i;

            if (ht[i].empty())
                output_file << " -> empty bucket" << std::endl;
            else {
                for (auto& item : ht[i]) {
                    output_file << " -> [key: " << item->getK() << " - value: " << item->getV() << "]";
                }

                output_file << std::endl;
            }
        }

        output_file.close();
    }
    void print() {
        for (int i = 0; i < size; i++) {
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

    HashTable<int, string> ht(10, input_file);

    ht.print();
    ht.print_in_file(output_file);

    int key_searched = 6;
    item<int, string>* item = ht.search(6);

    item ? cout << endl
                << "Item with key " << key_searched << " found! Value " << item->getV() << endl
                << endl
         : cout << endl
                << "Item with key " << key_searched << " not found";

    ht.deleteH(12);
    ht.print();

    return 0;
}
