#include <vector>
#include <random>
#include <algorithm>

void InsertionSort(std::vector<int>& a, int l, int r) {
    for (int i = l + 1; i < r; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= l && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

int partition(std::vector<int>& arr, int l, int r, std::mt19937& rand) {
    std::uniform_int_distribution<int> dist(l, r-1);
    int ind = dist(rand);

    int pivot = arr[ind];
    std::swap(arr[ind], arr[r-1]);
    int i = l;

    for (int j = l; j < r - 1; ++j) {
        if (arr[j] < pivot) {
            std::swap(arr[j], arr[i]);
            ++i;
        }
    }

    std::swap(arr[r-1], arr[i]);
    return i;
}

void QuickSortImpl(std::vector<int>& arr, int l, int r, std::mt19937& rand) {
    if (r - l > 1) {
        int pivot = partition(arr, l, r, rand);
        QuickSortImpl(arr, l, pivot, rand);
        QuickSortImpl(arr, pivot+1, r, rand);
    }
}

void QuickSort(std::vector<int>& arr) {
    std::mt19937 gen(8987672);
    QuickSortImpl(arr, 0, arr.size(), gen);
}

void heapify(std::vector<int>& arr, int l, int r, int ind) {
    int left = l + 2 * (ind - l) + 1;
    int right = l + 2 * (ind - l) + 2;
    int max = ind;

    if (left < r && arr[left] > arr[ind]) {
        max = left;
    }

    if (right < r && arr[right] > arr[max]) {
        max = right;
    }

    if (max != ind) {
        std::swap(arr[max], arr[ind]);
        heapify(arr, l, r, max);
    }
}

void buildMaxHeap(std::vector<int>& arr, int l, int r) {
    int parentCnt = (r - l) / 2 - 1;
    for (int i = l + parentCnt; i >= l; --i) {
        heapify(arr, l, r, i);
    }
}

void HeapSort(std::vector<int>& arr, int l, int r) {
    buildMaxHeap(arr, l, r);

    for (int end = r - 1; end > l; --end) {
        std::swap(arr[l], arr[end]);
        heapify(arr, l, end, l);
    }
}

void IntroSortImpl(std::vector<int>& arr, int l, int r, int recCnt, int recLimit, int insThreshold,
                   std::mt19937& rand) {
    if (r - l <= 1) {
        return;
    }

    if (r - l <= insThreshold) {
        InsertionSort(arr, l, r);
        return;
    }

    if (recCnt >= recLimit) {
        HeapSort(arr, l, r);
        return;
    }

    int pivot = partition(arr, l, r, rand);
    IntroSortImpl(arr, l, pivot, recCnt+1, recLimit, insThreshold, rand);
    IntroSortImpl(arr, pivot + 1, r, recCnt+1, recLimit, insThreshold, rand);
}

void IntroSort(std::vector<int>& arr, int insThreshold) {
    std::mt19937 gen(8987672);
    int recLimit = 2 * (31 - __builtin_clz((int)arr.size())); // 2 * log2 N
    IntroSortImpl(arr, 0, arr.size(), 0, recLimit, insThreshold, gen);
}

