#include <vector>
#include <cassert>
#include <iostream>
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif


int siftUp(std::vector<int>& heap, int idx) {
    int p_idx = idx / 2;

    if(idx == 1 || heap[p_idx] > heap[idx]){
        return idx;
    }

    std::swap(heap[p_idx], heap[idx]);
    return siftUp(heap, p_idx);
}

#ifndef REMOTE_JUDGE
void test() {
    std::vector<int> sample = {-1, 12, 6, 8, 3, 15, 7};
    assert(siftUp(sample, 5) == 1);
}


int main() {
    test();
}
#endif
