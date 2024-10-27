// Name: Kevin Van
// Class: CECS 325-02
// Program 4 - Sorting Constest (thread)
// Due Date: 10/31/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

using namespace std;

long long global_swap_count = 0;
mutex swap_mutex;

void bubble(int A[], int size, string process_name) {
    long long local_swap_count = 0;

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
                local_swap_count++;
            }
        }
    }
    
    // Use mutex to safely update global swap count
    lock_guard<mutex> lock(swap_mutex);
    global_swap_count += local_swap_count;

    cout << process_name << " swap count: " << local_swap_count << endl;
}

void merge(int *arr, int left, int mid, int right) {
    int i = left; 
    int j = mid; 
    int k = 0;
    int *temp = new int[right - left];

    // Merge the two halves into temp[]
    while (i < mid && j < right) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Copy remaining elements of left half
    while (i < mid) {
        temp[k++] = arr[i++];
    }

    // Copy remaining elements of right half
    while (j < right) {
        temp[k++] = arr[j++];
    }

    // Copy the merged elements back to arr[]
    for (int x = left, y = 0; x < right; x++, y++) {
        arr[x] = temp[y];
    }

    // Free memory
    delete[] temp;
}

int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2], ios::out | ios::trunc);
    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    int n;
    int index = 0;
    const int MAX = 1000000;
    int* A = new int[MAX];

    // Read numbers from the input file
    while (fin >> n && index < MAX) {
        A[index++] = n;
    }

    const int THREADS = 16;
    int SECTIONS = (index + THREADS - 1) / THREADS; 
    thread threads[THREADS];

    // Create threads to sort sections of the array
    for (int i = 0; i < THREADS; i++) {
        int left = i * SECTIONS;
        int right = (i + 1) * SECTIONS;
        if (i == THREADS - 1) {
            right = index;
        }

        threads[i] = thread(bubble, A + left, right - left, "Process " + to_string(i + 1));
    }
    
    // Join threads
    for (int i = 0; i < THREADS; i++) {
        threads[i].join();
    }

    // Merge sorted sections
    for (int i = 1; i < THREADS; i++) {
        merge(A, 0, i * SECTIONS, min(index, (i + 1) * SECTIONS));
    }

    // Write sorted numbers to the output file
    for (int i = 0; i < index; i++) {
        fout << A[i] << endl;
    }

    cout << "Total swaps: " << global_swap_count << endl;

    fout.close();
    fin.close();
    delete[] A;

    return 0;
}

