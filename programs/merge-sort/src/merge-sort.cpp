#include <iostream>
#include <vector>
#include <random>




void merge(std::vector<int>& arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  vector<int> L(n1);
  vector<int> R(n2);

  for (int i = 0; i < n1; i++) {
    L[i] = arr[left + i];
  }
  for (int i = 0; i < n2; i++) {
    R[i] = arr[mid + 1 + i];
  }


  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i< n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(std::vector<int>& arr, int start, int end) {
  if (start >= end) {
    return;
  }

  int mid = start + (end - start) / 2;
  mergeSort(arr, start, mid);
  mergeSort(arr, mid + 1, end);
  merge(arr, start, mid, end);
}

int main() {

  const int SIZE = 100;

  vector<int> arr(SIZE);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, SIZE - 1);

  for (int i = 0; i < SIZE; i++) {
    arr[i] = dis(gen);
  }
  
  return 0;
} 
