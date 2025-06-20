#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
class Heap{
    vector<int> data;
    int heapsize;
    void buildMinHeap(){
        for (int i = heapsize/2; i >= 0; i--){
            minHeapify(i);
        }
    }
    void minHeapify(int i){
        int l = 2*i+1;
        int r = 2*i+2;
        int min = i;

        if(l < heapsize && data[l] < data[min])
            min = l;
        if(r < heapsize && data[r] < data[min])
            min = r;
        if(min != i){
            swap(data[min], data[i]);
            minHeapify(min);
        }
    }
    void shiftUp(int i){
        while(i > 0 && data[(i - 1) /2] > data[i]){
            swap(data[i],data[(i-1)/2]);
            i = (i - 1) / 2;
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
    Heap(vector<int>& value) : data(value), heapsize(value.size()){buildMinHeap();}

    void printF(ofstream& out){
        for(int i = 0; i < heapsize; i++)
            out<< data[i]<< endl;
    }
    void print(){
        for(int i = 0; i < data.size(); i++)
            cout<< data[i]<< endl;
    }
    void printArray(){
        for(int i = 0; i < data.size(); i++)
            cout<<data[i]<<endl;
    }
    void decreaseKey(int k1, int k2){
        if(k2 > k1)
            return;
        int index = search(k1);
        if(index == -1)
            return;
        data[index] = k2;
        shiftUp(index);
    }
    void heapSort(){
        buildMinHeap();
        for (int i = heapsize-1; i > 0; i--){
            swap(data[0],data[i]);
            heapsize--;
            minHeapify(0);
        }
    }
    int extractMin(){
        if(heapsize == 0)
            return -1;
        int min = data[0];
        swap((data[0]), data[heapsize-1]);
        heapsize--;
        data.pop_back();
        minHeapify(0);
        return min;
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    vector<int> values;
    int x;
    while (in >> x)
        values.push_back(x);
    Heap heap(values);
    heap.printF(out);
    in.close();
    out.close();
    heap.decreaseKey(25,14);
    cout<<"\nHeap dopo decrease key: "<<endl;
    heap.print();

    int min = heap.extractMin();
    if(min != -1)
        cout<<"\nvalore minimo: "<<min<<endl;
    else
        cout<<"Heap vuoto"<<endl;
    heap.heapSort();
    cout<<"\nValori ordinati: "<<endl;
    heap.printArray();
    cout<<"\nheap dopo heap sort: "<<endl;
    heap.print();

    return 0;
}
