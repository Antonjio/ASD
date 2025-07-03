#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Heap{

private:
    vector<int> data;
    int heapsize;

    void buildMinHeap(){
        for(int i = heapsize / 2; i >= 0; i--)
            heapify(i);
    }

    void heapify(int i){
        int min = i;
        int l = i * 2 + 1;
        int r = i * 2 + 2;

        if(l < heapsize && data[l] < data[min])
            min = l;
        if(r < heapsize && data[r] < data[min])
            min = r;
        if(min != i){
            swap(data[min],data[i]);
            heapify(min);
        }
    }

    void load(ifstream& in){
        string totalToken;
        getline(in,totalToken);
        if(totalToken.front() == '<') totalToken = totalToken.substr(1);
        if(totalToken.back() == '>') totalToken.pop_back();

        for(char& c : totalToken) c = c ==',' ? ' ': c;

        istringstream stream(totalToken);
        int k;
        while(stream >> k){
            data.push_back(k);
        }

    }

    int search(int val){
        for(int i = 0; i < heapsize; i++){
            if(val == data[i])
                return i;
        }
        return -1;
    }

    void shiftUp(int i){
        while(i > 0 && data[(i-1) / 2] > data[i]){
            swap(data[(i-1) / 2] , data[i]);
            i = (i-1)/2;
        }
    }
public:

    Heap(ifstream& in){
        load(in);
        heapsize = data.size();
        buildMinHeap();
    }

    void heapSort(){
        for(int i = heapsize - 1; i >= 0; i--){
            swap(data[0],data[i]);
            heapsize--;
            heapify(0);
        }
    }

    int extractMin(){
        if(heapsize == 0)
            return -1;
        int min = data[0];
        swap(data[0],data[heapsize-1]);
        heapsize--;
        data.pop_back();
        heapify(0);
        return min;
    }

    void decreaseKey(int k1, int k2){
        if(k1 < k2)
            return;

        int indice = search(k1);
        if(indice == -1)
            cout<<"elemento non trovato"<<endl;
        else{
            data[indice] = k2;
            shiftUp(indice);
        }
    }

    void printF(ofstream& out){
        for(int & i : data)
            out<< i <<endl;
    }
    void print(){
        for(int & i : data)
            cout<< i <<endl;
    }

};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    Heap heap(in);
    heap.printF(out);

    heap.print();

    heap.decreaseKey(17, 12);
    cout << "\nHeap dopo decrease key:" << endl;
    heap.print();

    int max = heap.extractMin();
    if (max != -1)
        cout << "\nValore min: " << max << endl;
    else
        cout << "\nL'heap e' vuoto!" << endl;

    cout << "\nHeap dopo estrazione minimo:" << endl;
    heap.print();

    heap.heapSort();

    cout << "\nHeap dopo heap sort:" << endl;
    heap.print();

    return 0;
}