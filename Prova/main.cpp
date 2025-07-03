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
        int max = i;
        int l = i * 2 + 1;
        int r = i * 2 + 2;

        if(l < heapsize && data[l] < data[max])
            max = l;
        if(r < heapsize && data[r] < data[max])
            max = r;
        if(max != i){
            swap(data[max],data[i]);
            heapify(max);
        }
    }

    void load(ifstream& in){
        string totalToken;
        getline(in,totalToken);
        if(totalToken.front() == '<') totalToken = totalToken.substr(1);
        if(totalToken.back() == '>') totalToken.pop_back();

        for(char& c : totalToken) c = c ==',' ? ' ': c;

        istringstream stream;
        int k;
        while(stream >> k)
            data.push_back(k);
    }

    int search(int val){
        if(heapsize == 0)
            return -1;
        for(int i = 0; i < heapsize; i++){
            if(val == data[i])
                return data[i];
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
            return
    }



};