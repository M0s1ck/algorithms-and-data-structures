#include <iostream>
#include <vector>
#include <random>

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

void IntroSortImpl(std::vector<int>& arr, int l, int r, int recCnt, int recLimit, int insThreshold,
                   std::mt19937& rand) {
    if (r - l <= 1) {
        return;
    }

    if (r - l < insThreshold) {
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
    int recLimit = 2 * (31 - __builtin_clz(arr.size())); // 2 * log2 N
    IntroSortImpl(arr, 0, arr.size(), 0, recLimit, insThreshold, gen);
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    int insThreshold = 16;
    IntroSort(arr, insThreshold);

    for (auto& e: arr) {
        std::cout << e << ' ';
    }

    return 0;
}