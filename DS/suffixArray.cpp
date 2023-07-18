/*
    Author: Seif Ibrahim
    Description: Suffix Array Data Strcture implementation

    Last Updated: 18/7/2023

    Github: Seif-Ibrahim1

*/

#include <iostream>
#include <cstring>

using namespace std;

// Function to print an array
void printArray(const int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// SuffixArray class for constructing suffix arrays and LCP arrays
class SuffixArray {
    int* text;              // Array storing the text
    int size;               // Size of the text
    int alphabetSize = 256; // Size of the alphabet
    int* sa;                // Suffix array
    int* lcp;               // LCP array

    bool constructedSa = false;     // Flag indicating whether the suffix array is constructed
    bool constructedLcp = false;    // Flag indicating whether the LCP array is constructed

    // Function to build the suffix array
    void buildSuffixArr() {
        if (!constructedSa) {
            construct();
            constructedSa = true;
        }
    }

    // Function to build the LCP array
    void buildLcpArr() {
        if (!constructedLcp) {
            buildSuffixArr();
            kasai();
            constructedLcp = true;
        }
    }

    // Function to construct the suffix array
    void construct() {
        sa = new int[size];
        int* sa2 = new int[size];
        int* rank = new int[size];
        int c[max(size, alphabetSize)] = {0};
        
        int i, p, r;
        for (i = 0; i < size; i++) {
            c[rank[i] = text[i]]++;
        }

        for (i = 1; i < alphabetSize; i++) {
            c[i] += c[i-1];
        }

        for (i = size-1; i >= 0; i--) {
            sa[--c[text[i]]] = i;
        }
        
        for (p = 1; p < size; p <<= 1) {
            for (r = 0, i = size-p; i < size; i++) {
                sa2[r++] = i;
            }

            for (i = 0; i < size; i++) {
                if (sa[i] >= p) {
                    sa2[r++] = sa[i] - p;
                }
            }

            for (i = 0; i < alphabetSize; i++) {
                c[i] = 0;
            }

            for (i = 0; i < size; i++) {
                c[rank[i]]++;
            }

            for (i = 1; i < alphabetSize; i++) {
                c[i] += c[i-1];
            }

            for (i = size-1; i >= 0; i--) {
                sa[--c[rank[sa2[i]]]] = sa2[i];
            }

            for (sa2[sa[0]] = r = 0, i = 1; i < size; i++) {
                if (!(rank[sa[i]] == rank[sa[i-1]] && sa[i-1] + p < size && sa[i] + p < size && rank[sa[i] + p] == rank[sa[i-1] + p])) {
                    r++;
                }
                sa2[sa[i]] = r;
            }

            swap(rank, sa2);

            if (r == size-1) {
                break;
            }
            alphabetSize = r+1;
        }

        delete[] rank;
        delete[] sa2;
    }

    // Function to compute the LCP array using the Kasai algorithm
    void kasai() {
        lcp = new int[size];
        int* inv = new int[size];
        for (int i = 0; i < size; i++) {
            inv[sa[i]] = i;
        }

        for (int i = 0, len = 0; i < size; i++) {
            if (inv[i] > 0) {
                int k = sa[inv[i] - 1];
                while (i + len < size && k + len < size && text[i + len] == text[k + len]) {
                    len++;
                }
                lcp[inv[i]] = len;
                if (len > 0) {
                    len--;
                }
            } else {
                lcp[inv[i]] = 0;
            }
        }

        delete[] inv;
    }

public:
    // Constructor to initialize the SuffixArray with the given text
    SuffixArray(string _text) {
        size = _text.length();
        text = new int[size];
        for (int i = 0; i < size; i++) {
            text[i] = _text[i];
        }
    }

    // Destructor to deallocate memory
    ~SuffixArray() {
        delete[] text;
        delete[] sa;
        delete[] lcp;
    }

    // Get the length of the text
    int getTextLen() {
        return size;
    }

    // Get the suffix array
    int* getSuffixArr() {
        buildSuffixArr();
        return sa;
    }

    // Get the LCP array
    int* getLcpArr() {
        buildLcpArr();
        return lcp;
    }
};

int main() {
    // Test Case 1: Basic Input
    {
        SuffixArray sa("banana");
        cout << "Test Case 1: Basic Input\n";
        // Expected Output:
        // 1 3 5 0 2 4
        // 0 1 3 0 0 2
        int* suffixArr = sa.getSuffixArr();
        int* lcpArr = sa.getLcpArr();
        printArray(suffixArr, sa.getTextLen());
        printArray(lcpArr, sa.getTextLen());
        cout << endl;
    }

    // Test Case 2: Empty Input
    {
        SuffixArray sa("");
        cout << "Test Case 2: Empty Input\n";
        // Expected Output: (Empty)
        int* suffixArr = sa.getSuffixArr();
        int* lcpArr = sa.getLcpArr();
        printArray(suffixArr, sa.getTextLen());
        printArray(lcpArr, sa.getTextLen());
        cout << endl;
    }

    // Test Case 3: Input with Single Character
    {
        SuffixArray sa("a");
        cout << "Test Case 3: Input with Single Character\n";
        // Expected Output:
        // 0
        // 0
        int* suffixArr = sa.getSuffixArr();
        int* lcpArr = sa.getLcpArr();
        printArray(suffixArr, sa.getTextLen());
        printArray(lcpArr, sa.getTextLen());
        cout << endl;
    }

    // Test Case 4: Input with Repeated Characters
    {
        SuffixArray sa("cccccc");
        cout << "Test Case 4: Input with Repeated Characters\n";
        // Expected Output:
        // 5 4 3 2 1 0
        // 0 1 2 3 4 5
        int* suffixArr = sa.getSuffixArr();
        int* lcpArr = sa.getLcpArr();
        printArray(suffixArr, sa.getTextLen());
        printArray(lcpArr, sa.getTextLen());
        cout << endl;
    }

    // Test Case 5: Input with Special Characters
    {
        SuffixArray sa("!@#$%^&*");
        cout << "Test Case 5: Input with Special Characters\n";
        // Expected Output:
        // 7 6 5 4 3 2 1 0
        // 0 0 0 0 0 0 0 0
        int* suffixArr = sa.getSuffixArr();
        int* lcpArr = sa.getLcpArr();
        printArray(suffixArr, sa.getTextLen());
        printArray(lcpArr, sa.getTextLen());
        cout << endl;
    }

    return 0;
}