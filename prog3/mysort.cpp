
#include <fstream>
#include <iostream>
using namespace std;

void bubble(int A[], int size) {
  cout << "Starting Bubble Sort" << endl;
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (A[j] > A[j + 1]) {
        int temp = A[j];
        A[j] = A[j + 1];
        A[j + 1] = temp;
      }
    }
  }
  cout << "Bubble Sort Finished" << endl;
}

int main(int argc, char *argv[]) {

  ifstream fin;
  ofstream fout;
  int n;
  int index = 0;
  const int max = 1000000;
  int A[max];

  fin.open(argv[1]);
  fout.open(argv[2], ios::out | ios::trunc);
  while (fin >> n && index < max) {
    A[index] = n;
    index++;
  }

  bubble(A, index);

  for (int i = 0; i < index; i++) {
    fout << A[i] << endl;
  }

  fout.close();
  fin.close();

  return 0;
}
