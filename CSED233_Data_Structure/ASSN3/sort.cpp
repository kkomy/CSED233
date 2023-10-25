#include "sort.h"
#include <fstream>
#include <iostream>
#include <string>

sortAlg::sortAlg() {
  arr_size = 0;
  arr = new int[100];  // Each test case will be less than 100 values
  temp = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout) {
  string answer;
  for (int i = 0; i < arr_size - 1; i++)
    answer += to_string(arr[i]) + " ";
  answer += to_string(arr[arr_size - 1]);
  fout << answer << endl;
}

void sortAlg::insertionSort(ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  for (int i = 0; i < arr_size - 1; i++) {
    for (int j = 0; j <= i; j++) {
      if (arr[i + 1] < arr[j]) {
        int tmp = arr[i + 1];
        for (int k = i; k >= j; k--) {
          arr[k + 1] = arr[k];
        }
        arr[j] = tmp;
        break;
      }
    }
    if (i >= temp[99] - 1)
      printArray(fout); // DO NOT ERASE THIS LINE
  }
  temp[99] = arr_size;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void sortAlg::merge(int left, int right, int &count) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (right != 0) {
    int mid = (left + right) / 2;
    int lnum = left;
    int rnum = mid + 1;
    int total = left;
    while (lnum <= mid && rnum <= right) {
      if (arr[lnum] > arr[rnum]) {
        temp[total] = arr[rnum];
        rnum++;
        count++; // drop(왼쪽보다 오른쪽이 작을 경우)
      } else if (arr[lnum] < arr[rnum]) {
        temp[total] = arr[lnum];
        lnum++;
      }
      total++;
    }
    if (lnum > mid) {
      while (total <= right) {
        temp[total] = arr[rnum];
        rnum++;
        total++;
      }
    } else if (rnum > right) {
      while (total <= right) {
        temp[total] = arr[lnum];
        lnum++;
        total++;
      }
    }
    int t = 0;
    for (int i = left; i <= right; i++) {
      arr[i] = temp[i];
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void sortAlg::mergeSort(ofstream &fout, int left, int right, int &count) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int mid;
  if (left < right) {
    mid = (left + right) / 2;
    mergeSort(fout, left, mid, count);
    mergeSort(fout, mid + 1, right, count);
    merge(left, right, count);
    printArray(fout); // DO NOT ERASE THIS LINE
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
