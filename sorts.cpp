#include "sorts.h"
#include <algorithm>
#include <vector>
#include <climits>
#include <cmath>

// Вспомогательные функции
namespace {
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // Для QuickSort
    int partition(int* ar, int low, int high, bool (*comp)(int, int)) {
        int pivot = ar[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (comp(ar[j], pivot)) {
                i++;
                swap(ar[i], ar[j]);
            }
        }
        swap(ar[i + 1], ar[high]);
        return i + 1;
    }

    // Для MergeSort
    void merge(int* ar, int left, int mid, int right, bool (*comp)(int, int)) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        int* L = new int[n1];
        int* R = new int[n2];
        
        for (int i = 0; i < n1; i++)
            L[i] = ar[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = ar[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (comp(L[i], R[j])) {
                ar[k] = L[i];
                i++;
            } else {
                ar[k] = R[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) ar[k++] = L[i++];
        while (j < n2) ar[k++] = R[j++];
        
        delete[] L;
        delete[] R;
    }

    // Для HeapSort
    void heapify(int* ar, int n, int i, bool (*comp)(int, int)) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && comp(ar[largest], ar[left]))
            largest = left;
        
        if (right < n && comp(ar[largest], ar[right]))
            largest = right;
        
        if (largest != i) {
            swap(ar[i], ar[largest]);
            heapify(ar, n, largest, comp);
        }
    }

    // Для RadixSort
    int getMax(int* ar, int n) {
        int mx = ar[0];
        for (int i = 1; i < n; i++)
            if (ar[i] > mx) mx = ar[i];
        return mx;
    }
}

// Реализации сортировок

// 1. Пузырьковая сортировка
void BubbleSort(int* ar, size_t size, bool (*comp)(int, int)) {
    for (size_t i = 0; i < size-1; i++)
        for (size_t j = 0; j < size-i-1; j++)
            if (!comp(ar[j], ar[j+1]))
                swap(ar[j], ar[j+1]);
}

// 2. Сортировка вставками
void InsertionSort(int* ar, size_t size, bool (*comp)(int, int)) {
    for (size_t i = 1; i < size; i++) {
        int key = ar[i];
        int j = i - 1;
        
        while (j >= 0 && !comp(ar[j], key)) {
            ar[j + 1] = ar[j];
            j--;
        }
        ar[j + 1] = key;
    }
}

// 3. Сортировка выбором
void SelectionSort(int* ar, size_t size, bool (*comp)(int, int)) {
    for (size_t i = 0; i < size-1; i++) {
        size_t min_idx = i;
        for (size_t j = i+1; j < size; j++)
            if (comp(ar[j], ar[min_idx]))
                min_idx = j;
        swap(ar[min_idx], ar[i]);
    }
}

// 4. Сортировка Шелла
void ShellSort(int* ar, size_t size, bool (*comp)(int, int)) {
    for (size_t gap = size/2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < size; i++) {
            int temp = ar[i];
            size_t j;
            for (j = i; j >= gap && !comp(ar[j - gap], temp); j -= gap)
                ar[j] = ar[j - gap];
            ar[j] = temp;
        }
    }
}

// 5. Сортировка подсчётом
void CountSort(int* ar, size_t size, bool (*comp)(int, int)) {
    if (size == 0) return;
    
    int max = *std::max_element(ar, ar + size);
    int min = *std::min_element(ar, ar + size);
    int range = max - min + 1;
    
    int* count = new int[range]();
    int* output = new int[size];
    
    for (size_t i = 0; i < size; i++)
        count[ar[i] - min]++;
    
    for (int i = 1; i < range; i++)
        count[i] += count[i-1];
    
    for (int i = size - 1; i >= 0; i--) {
        output[count[ar[i] - min] - 1] = ar[i];
        count[ar[i] - min]--;
    }
    
    for (size_t i = 0; i < size; i++)
        ar[i] = output[i];
    
    delete[] count;
    delete[] output;
    
    if (!comp(1, 2)) // Если сортировка по убыванию
        std::reverse(ar, ar + size);
}

// 6. Быстрая сортировка
void QuickSort(int* ar, size_t size, bool (*comp)(int, int)) {
    if (size <= 1) return;
    
    int pivot = partition(ar, 0, size-1, comp);
    QuickSort(ar, pivot, comp);
    QuickSort(ar + pivot + 1, size - pivot - 1, comp);
}

// 7. Модифицированная быстрая сортировка
void QuickSortMod(int* ar, size_t size, bool (*comp)(int, int)) {
    if (size <= 10) {
        InsertionSort(ar, size, comp);
        return;
    }
    
    int pivot = partition(ar, 0, size-1, comp);
    QuickSortMod(ar, pivot, comp);
    QuickSortMod(ar + pivot + 1, size - pivot - 1, comp);
}

// 8. Сортировка слиянием
void MergeSort(int* ar, size_t size, bool (*comp)(int, int)) {
    if (size <= 1) return;
    
    int mid = size / 2;
    MergeSort(ar, mid, comp);
    MergeSort(ar + mid, size - mid, comp);
    merge(ar, 0, mid - 1, size - 1, comp);
}

// 9. Пирамидальная сортировка
void HeapSort(int* ar, size_t size, bool (*comp)(int, int)) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(ar, size, i, comp);
    
    for (int i = size - 1; i > 0; i--) {
        swap(ar[0], ar[i]);
        heapify(ar, i, 0, comp);
    }
}

// 10. Поразрядная сортировка
void RadixSort(int* ar, size_t size, bool (*comp)(int, int)) {
    int m = getMax(ar, size);
    
    for (int exp = 1; m / exp > 0; exp *= 10) {
        int output[size];
        int count[10] = {0};
        
        for (size_t i = 0; i < size; i++)
            count[(ar[i] / exp) % 10]++;
        
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];
        
        for (int i = size - 1; i >= 0; i--) {
            output[count[(ar[i] / exp) % 10] - 1] = ar[i];
            count[(ar[i] / exp) % 10]--;
        }
        
        for (size_t i = 0; i < size; i++)
            ar[i] = output[i];
    }
    
    if (!comp(1, 2)) // Если сортировка по убыванию
        std::reverse(ar, ar + size);
}

// 11. TimSort (упрощённая версия)
void TimSort(int* ar, size_t size, bool (*comp)(int, int)) {
    const size_t RUN = 32;
    
    for (size_t i = 0; i < size; i += RUN)
        InsertionSort(ar + i, std::min(RUN, size - i), comp);
    
    for (size_t mergeSize = RUN; mergeSize < size; mergeSize *= 2) {
        for (size_t left = 0; left < size; left += 2 * mergeSize) {
            size_t mid = left + mergeSize;
            size_t right = std::min(left + 2 * mergeSize, size);
            
            if (mid < right)
                merge(ar, left, mid - 1, right - 1, comp);
        }
    }
}
