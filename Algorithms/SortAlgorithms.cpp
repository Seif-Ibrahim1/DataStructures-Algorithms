/*
    Author: Youssef Moataz, Ahmed Hanfy
    Project: Sort Algorithms
    Description: 7 Sorting algorithms implementation

    Last Updated: 2/6/2023

    Github: YoussefMoataz, ahanfybekheet

*/

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

/**
 * @author Youssef Moataz
 * @tparam T The datatype.
 */
template<typename T>
class SortAlgorithms {

private:

    /**
     *
     * This is the merge function, used in mergeSort.
     *
     * @param arr The sub-array to be merged.
     * @param l The start index of the sub-array.
     * @param mid The middle index of the sub-array.
     * @param r The end index of the sub-array.
     */
    void merge(T *arr, int l, int mid, int r) {

        int lSubArrSize = mid - l + 1;
        int rSubArrSize = r - mid;

        int mainCounter = l;
        int lCounter = 0;
        int rCounter = 0;

//    cout << lSubArrSize << " " << rSubArrSize << endl;

        T leftArray[lSubArrSize];
        T rightArray[rSubArrSize];

        for (int i = 0; i < lSubArrSize; ++i) {

            leftArray[i] = arr[l + i];

        }

        for (int j = 0; j < rSubArrSize; ++j) {

            rightArray[j] = arr[mid + j + 1];

        }

        while (lCounter < lSubArrSize && rCounter < rSubArrSize) {

            if (leftArray[lCounter] <= rightArray[rCounter]) {
                arr[mainCounter] = leftArray[lCounter];
                lCounter++;
                mainCounter++;
            } else {
                arr[mainCounter] = rightArray[rCounter];
                rCounter++;
                mainCounter++;
            }

        }

        while (lCounter < lSubArrSize) {
            arr[mainCounter] = leftArray[lCounter];
            lCounter++;
            mainCounter++;
        }

        while (rCounter < rSubArrSize) {
            arr[mainCounter] = rightArray[rCounter];
            rCounter++;
            mainCounter++;
        }

    }

    /**
     *
     * This is the partition function, used in quickSort.
     *
     * @param arr The sub-array to be partitioned.
     * @param l The start index of the sub-array.
     * @param r The end index of the sub-array.
     */
    int partition(T *arr, int l, int r) {

        T item = arr[l];

        int i = l;

        for (int j = l + 1; j <= r; ++j) {

            if (arr[j] < item) {
                i++;
                swap(arr[i], arr[j]);
            }

        }
        swap(arr[i], arr[l]);

        return i;

    }

public:

    /**
     * Default constructor.
     */
    SortAlgorithms() = default;

    /**
     *
     * This is the implementation of Insertion Sort algorithm on any data type.
     *
     * @attention The array is sorted and kept in the same pointer.
     * @param arr The array to be sorted.
     * @param n The size of the array.
     */
    void insertionSort(T *arr, int n) {

        for (int i = 1, j; i < n; ++i) {

            T temp = arr[i];

            for (j = i; j > 0; j--) {

                // shift all elements greater than temp after temp
                if (temp < arr[j - 1]) {
                    arr[j] = arr[j - 1];
                } else {
                    break;
                }

            }

            // place the temp to its sorted position
            arr[j] = temp;

        }

    }

    /**
     * This is the implementation of Selection Sort algorithm on any data type.
     *
     * @attention The array is sorted and kept in the same pointer.
     * @param arr The array to be sorted.
     * @param n The size of the array.
     */
    void selectionSort(T *arr, int n) {

        for (int i = 0, j, smallest; i < n - 1; ++i) {

            for (j = i + 1, smallest = i; j < n; j++) {

                // find the smallest unsorted element
                if (arr[j] < arr[smallest]) {
                    smallest = j;
                }

            }
            // swap the current element with the smallest element
            swap(arr[smallest], arr[i]);

        }

    }

    /**
     * This is the implementation of Bubble Sort algorithm on any data type.
     *
     * @attention The array is sorted and kept in the same pointer.
     * @param arr The array to be sorted.
     * @param n The size of the array.
     */
    void bubbleSort(T *arr, int n) {

        for (int i = 0; i < n - 1; ++i) {

            for (int j = n - 1; j > i; --j) {

                // swap each element with its previous element if the previous is smaller
                if (arr[j] < arr[j - 1]) {
                    swap(arr[j], arr[j - 1]);
                }

            }

        }

    }

    /**
     * This is the implementation of Shell Sort algorithm on any data type.
     *
     * @attention The array is sorted and kept in the same pointer.
     * @param arr The array to be sorted.
     * @param n The size of the array.
     */
    void shellSort(T *arr, int n) {

        // split the data to half each time (shell)
        for (int shell = n / 2; shell > 0; shell /= 2) {

            // loop from each shell till the end
            for (int i = shell; i < n; ++i) {

                int temp = arr[i];

                int j = i;
                for (; j >= shell; j -= shell) {

                    // sort each shell
                    if (temp < arr[j - shell]) {
                        arr[j] = arr[j - shell];
                    } else {
                        break;
                    }

                }
                // place the temp value
                arr[j] = temp;

            }

        }

    }

    /**
     * This is the implementation of Merge Sort algorithm on any data type.
     *
     * @attention The array is sorted and kept in the same pointer.
     * @param arr The array to be sorted.
     * @param l The start index of the array (Mostly: 0).
     * @param r The end index of the array (Mostly: Size - 1).
     */
    void mergeSort(T *arr, int l, int r) {

        if (l >= r) {
            return;
        } else {

            int middle = (l + r) / 2;

            mergeSort(arr, l, middle);
            mergeSort(arr, middle + 1, r);
            merge(arr, l, middle, r);

        }

    }

    /**
     * This is the implementation of Quick Sort algorithm on any data type.
     *
     * @attention The array is sorted and kept in the same pointer.
     * @param arr The array to be sorted.
     * @param l The start index of the array (Mostly: 0).
     * @param r The end index of the array (Mostly: Size - 1).
     */
    void quickSort(T *arr, int l, int r) {

        if (l >= r) {
            return;
        } else {

            int pivot = partition(arr, l, r);
            quickSort(arr, l, pivot - 1);
            quickSort(arr, pivot + 1, r);

        }

    }

    /**
     * This is the implementation of Counting Sort algorithm on Integer data type.
     *
     * @attention The array is sorted and kept in the same pointer.
     * @param arr The integer array to be sorted.
     * @param n The size of the array.
     */
    void countingSort(int *arr, int n) {

        T max = arr[0];

        // find the maximum value
        for (int m = 0; m < n; ++m) {
            if (arr[m] > max) {
                max = arr[m];
            }
        }

        T count[max + 1];

        // set count to zeroes
        for (int i = 1; i <= max; ++i) {
            count[i] = 0;
        }

        // count the values
        for (int j = 0; j < n; ++j) {
            count[arr[j]] += 1;
        }

        // apply cumulative sum
        for (int k = 2; k <= max; ++k) {
            count[k] += count[k - 1];
        }

        T sorted[n];
        // place every element in its sorted position
        for (int i = n - 1; i >= 0; --i) {
            sorted[count[arr[i]] - 1] = arr[i];
            count[arr[i]] -= 1;
        }

        // return elements to the main array
        for (int i = 0; i < n; ++i) {
            arr[i] = sorted[i];
        }

    }
//----------------------------------------------------------------
//                    Radix Sort Function
//----------------------------------------------------------------
    /**
     * Radix sort algorithm for sorting an array of elements.
     * 
     * @tparam T The type of the elements in the array.
     * @param arr Pointer to the array to be sorted.
     * @param size The number of elements in the array.
     * @param max The maximum element in the array (optional).
     */
    void radixSort(T *arr, int size, int max = 0) {
        // If max is not provided, find the maximum element in the array
        if (max == 0) {
            max = arr[0];
            for (int i = 1; i < size; i++) {
                if (max < arr[i]) {
                    max = arr[i];
                }
            }
        }

        // Calculate the number of digits in the maximum element
        int maxLenght = std::to_string(max).length();

        // Create a temporary array to store sorted elements
        T *output = new T[size];

        // Perform counting sort for each digit
        for (int i = 0; i < maxLenght; i++) {
            // Initialize count array with zeros
            int count[10] = { 0 };

            // Count the frequency of each digit at current position
            for (int j = 0; j < size; j++) {
                int iDigitOfArr = (arr[j] % static_cast<int>(std::pow(10, i + 1))) / static_cast<int>(std::pow(10, i));
                count[iDigitOfArr]++;
            }

            // Calculate the cumulative count to determine the positions of elements
            for (int j = 1; j < 10; j++) {
                count[j] += count[j - 1];
            }

            // Build the output array by placing elements in sorted order
            for (int j = size - 1; j >= 0; j--) {
                int iDigitOfArr = (arr[j] % static_cast<int>(std::pow(10, i + 1))) / static_cast<int>(std::pow(10, i));
                output[count[iDigitOfArr] - 1] = arr[j];
                count[iDigitOfArr]--;
            }

            // Copy the sorted elements back to the original array
            for (int j = 0; j < size; j++) {
                arr[j] = output[j];
            }
        }

        // Free the memory allocated for the temporary array
        delete[] output;
    }
};
