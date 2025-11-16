#include <vector>
#include <iostream>

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

void merge(std::vector<int>& arr, std::vector<int>& temp, size_t left, size_t mid, size_t right) {
    size_t i = left;
    size_t j = mid;
    size_t k = left;

    while (i < mid && j < right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i < mid)
        temp[k++] = arr[i++];
    while (j < right)
        temp[k++] = arr[j++];

    std::copy(temp.begin() + left, temp.begin() + right, arr.begin() + left);
}

void mergeSortImpl(std::vector<int>& arr, std::vector<int>& temp, size_t l, size_t r) {
    if (r - l > 1) {
        size_t mid = (l + r) / 2;
        mergeSortImpl(arr, temp, l, mid);
        mergeSortImpl(arr, temp, mid, r);
        merge(arr, temp, l, mid, r);
    }
}

void MergeSort(std::vector<int>& arr) {
    std::vector<int> temp(arr.size());
    mergeSortImpl(arr, temp, 0, arr.size());
}

void mergeInsertionSortImpl(std::vector<int>& arr, std::vector<int>& temp, size_t l, size_t r, size_t threshold) {
  if (r - l <= 1) {
    return;
  }

  if (r - l <= threshold) {
    InsertionSort(arr, l, r);
    return;
  }

  size_t mid = (l + r) / 2;
  mergeInsertionSortImpl(arr, temp, l, mid, threshold);
  mergeInsertionSortImpl(arr, temp, mid, r, threshold);
  merge(arr, temp, l, mid, r);
}

void MergeInsertionSort(std::vector<int>& arr, size_t threshold) {
    std::vector<int> temp(arr.size());
    mergeInsertionSortImpl(arr, temp, 0, arr.size(), threshold);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    int threshold = 15;
    MergeInsertionSort(arr, threshold);

    for (auto& e: arr) {
        std::cout << e << ' ';
    }

    return 0;
}