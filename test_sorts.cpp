#include "test_sorts.h"
#include "test.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define ARRAY_SIZE 1000
#define TEST_CASES 5

namespace {
    int* generateRandomArray(size_t size) {
        int* arr = new int[size];
        for (size_t i = 0; i < size; i++) {
            arr[i] = rand() % 1000;
        }
        return arr;
    }

    bool isSorted(const int* arr, size_t size, bool (*comp)(int, int)) {
        for (size_t i = 0; i < size - 1; i++) {
            if (!comp(arr[i], arr[i + 1])) {
                return false;
            }
        }
        return true;
    }

    bool defaultComp(int a, int b) { return a <= b; }

    void testSortAlgorithm(void (*sortFunc)(int*, size_t, bool (*)(int, int)), const char* name) {
        printf("Testing %s...\n", name);
        
        srand(time(nullptr));
        for (int i = 0; i < TEST_CASES; i++) {
            int* arr = generateRandomArray(ARRAY_SIZE);
            int* arrCopy = new int[ARRAY_SIZE];
            memcpy(arrCopy, arr, ARRAY_SIZE * sizeof(int));
            
            sortFunc(arr, ARRAY_SIZE, defaultComp);
            
            if (!isSorted(arr, ARRAY_SIZE, defaultComp)) {
                delete[] arr;
                delete[] arrCopy;
                throw "Array is not sorted";
            }
            
            // Проверяем, что все элементы сохранились
            std::sort(arrCopy, arrCopy + ARRAY_SIZE);
            for (size_t j = 0; j < ARRAY_SIZE; j++) {
                if (arr[j] != arrCopy[j]) {
                    delete[] arr;
                    delete[] arrCopy;
                    throw "Elements are missing or duplicated";
                }
            }
            
            delete[] arr;
            delete[] arrCopy;
        }
    }
}

#define REGISTER_SORT_TEST(sortName) \
    void test_##sortName() { \
        testSortAlgorithm(sortName, #sortName); \
    } \
    struct Register_##sortName { \
        Register_##sortName() { \
            addTest(#sortName, test_##sortName); \
        } \
    } register_##sortName;

REGISTER_SORT_TEST(BubbleSort)
REGISTER_SORT_TEST(InsertionSort)
REGISTER_SORT_TEST(SelectionSort)
REGISTER_SORT_TEST(ShellSort)
REGISTER_SORT_TEST(CountSort)
REGISTER_SORT_TEST(QuickSort)
REGISTER_SORT_TEST(QuickSortMod)
REGISTER_SORT_TEST(MergeSort)
REGISTER_SORT_TEST(HeapSort)
REGISTER_SORT_TEST(RadixSort)
REGISTER_SORT_TEST(TimSort)
