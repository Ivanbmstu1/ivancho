#ifndef SORTS_H
#define SORTS_H

#include <cstddef> // for size_t

// Функция сравнения по умолчанию (для сортировки по возрастанию)
inline bool defaultComp(int a, int b) { return a < b; }

// Базовые сортировки
void BubbleSort(int* ar, size_t size, bool (*comp)(int, int) = defaultComp);
void InsertionSort(int* ar, size_t size, bool (*comp)(int, int) = defaultComp);
void SelectionSort(int* ar, size_t size, bool (*comp)(int, int) = defaultComp);

// Улучшенные сортировки
void ShellSort(int* ar, size_t size, bool (*comp)(int, int) = defaultComp);
void CountSort(int* ar, size_t size, bool (*comp)(int, int) = defaultComp);

// Рекурсивные сортировки
void QuickSort(int* ar, size_t size, bool (*comp)(int, int) = defaultComp);
void QuickSortMod(int* ar, size_t size, bool (*comp)(int, int) = defaultComp);
void MergeSort(int* ar, size_t size, bool (*comp)(int, int) = defaultComp);

// Пирамидальная сортировка
void HeapSort(int* ar, size_t size, bool (*comp)(int, int) = defaultComp);

// Дополнительные сортировки
void RadixSort(int* ar, size_t size, bool (*comp)(int, int) = defaultComp);
void TimSort(int* ar, size_t size, bool (*comp)(int, int) = defaultComp);

#endif // SORTS_H
