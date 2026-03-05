#include <vector>
#include <cassert>
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif


int siftDown(std::vector<int>& heap, int idx) {
    int l_idx = 2 * idx;   
    int r_idx = 2 * idx + 1;  
    int max_idx = idx;

    if(heap.size() > l_idx && heap[l_idx] > heap[max_idx]){
        max_idx = l_idx;
    }

    if(heap.size() > r_idx && heap[r_idx] > heap[max_idx]){
        max_idx = r_idx;
    }

    if(max_idx != idx){
        std::swap(heap[idx], heap[max_idx]);
        return siftDown(heap, max_idx);
    }
    return idx;
}

#ifndef REMOTE_JUDGE
void test() {
    std::vector<int> sample = {-1, 12, 1, 8, 3, 4, 7};
    assert(siftDown(sample, 2) == 5);
}


int main() {
    test();
}
#endif