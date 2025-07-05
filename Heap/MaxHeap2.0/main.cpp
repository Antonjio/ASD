#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Heap{
    vector<int> data;
    int heapsize;

    void load(ifstream& in){
        string tokens;
        while(getline(in,tokens)){
            if(tokens.front() == '<') tokens = tokens.substr(1);
            if(tokens.back() == '>') tokens.pop_back();

            for(char& c : tokens) c = c == ',' ? ' ' : c;
            istringstream stream(tokens);
            int k;
            while(stream >> k)
                data.push_back(k);
            heapsize = data.size();
            buildMaxHeap();
        }
    }
    void buildMaxHeap(){
        for(int i = heapsize / 2; i >= 0; i--)
            heapify(i);
    }
    void heapify(int i){
        int max = i;
        int l = i * 2 + 1;
        int r = i * 2 + 2;

        if(l < heapsize && data[l] > data[max])
            max = l;
        if(r < heapsize && data[r] > data[max])
            max = r;
        if(max != i){
            swap(data[max], data[i]);
            heapify(max);
        }
    }
    void shiftUp(int i){
        while(i > 0 && data[(i - 1)/2] < data[i]){
            swap(data[(i - 1) / 2], data[i]);
            i = (i - 1) / 2;
        }
    }
    int search(int k){
        for(int i = 0; i < heapsize; i++){
            if(data[i] == k)
                return i;
        }
        cout<<"elemento non trovato"<<endl;
        return -1;
    }

public:
    Heap(ifstream&in){load(in);}

    void heapSort(){
        for(int i = heapsize - 1; i >= 0; i--){
            swap(data[0],data[i]);
            heapsize--;
            heapify(0);
        }
    }

    int extractMax(){
        if(heapsize == 0)
            return -1;
        int max = data[0];
        swap(data[0], data[heapsize - 1]);
        heapsize--;
        data.pop_back();
        heapify(0);
        return max;
    }

    void increaseKey(int k1, int k2){
        if(k1 > k2){
            cout<<"chiave inferiore al valore di riferimento"<<endl;
            return;
        }

        int index = search(k1);
        if(index == -1)
            return;
        data[index] = k2;
        shiftUp(index);
    }

    void printF(ofstream& out){
        for(auto& i : data)
            out<<i<<endl;
    }
    void print(){
        for(auto& i : data)
            cout<<i<<endl;
    }
};


int main() {

    ifstream in("input.txt");
    ofstream out("output.txt");

    Heap hp(in);
    hp.printF(out);

    hp.increaseKey(10,32);
    cout<<"heap dopo incremento"<<endl;
    hp.print();

    int max = hp.extractMax();
    if(max != -1){
        cout<<"max estratto: "<<max<<endl;
        cout<<"heap dopo estrazione massimo"<<endl;
        hp.print();
    }
    else
        cout<<"heap vuoto"<<endl;

    hp.heapSort();
    cout<<"heap dopo heapsort"<<endl;
    hp.print();

    return 0;
}
