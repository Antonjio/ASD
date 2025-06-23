#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

class Heap{
private:
    vector<int> data;
    int heapsize;

    void buildMaxHeap(){
        for(int i = heapsize / 2; i >= 0; i--)
            maxHeapify(i);
    }
    void maxHeapify(int i){
        int l = i * 2 + 1;
        int r = i * 2 + 2;
        int max = i;

        if(l < heapsize && data[l] > data[max])
            max = l;
        if(r < heapsize && data[r] > data[max])
            max = r;
        if(max != i){
            swap(data[max],data[i]);
            maxHeapify(max);
        }
    }

    void shiftUp(int i){
        while (i > 0 && data[(i-1)/2] < data[i]){
            swap(data[(i-1)/2] , data[i]);
            i = (i-1) / 2;
        }
    }
    int search(int key){
        for(int i = 0; i < heapsize; i++){
            if(data[i] == key)
                return i;
        }
        return -1;
    }
public:
    Heap(vector<int>& values) : data(values), heapsize(values.size()){buildMaxHeap();}

    int extractMax(){
        if(heapsize == 0)
            return -1;
        int max = data[0];
        swap(data[0],data[heapsize-1]);
        heapsize--;
        data.pop_back();
        maxHeapify(0);
        return max;
    }
    void increaseKey(int k1, int k2){
        if(k2 < k1)
            return;

        int index = search(k1);
        if(index == -1)
            return;
        data[index] = k2;
        shiftUp(index);
    }
    void heapSort(){
        buildMaxHeap();
        for(int i = heapsize - 1; i >= 0; i--){
            swap(data[0],data[i]);
            heapsize--;
            maxHeapify(0);
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

    int k;
    vector<int> values;
    while (in >> k)
        values.push_back(k);

    Heap heap(values);
    heap.printF(out);

    heap.print();

    heap.increaseKey(10, 22);
    cout << "\nHeap dopo increase key:" << endl;
    heap.print();

    int max = heap.extractMax();
    if (max != -1)
        cout << "\nValore massimo: " << max << endl;
    else
        cout << "\nL'heap e' vuoto!" << endl;

    heap.heapSort();
    cout << "\nValori ordinati:" << endl;
    heap.print();

    cout << "\nHeap dopo heap sort:" << endl;
    heap.print();

    return 0;
}
