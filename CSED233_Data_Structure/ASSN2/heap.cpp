#include "heap.h"
#include <iostream>
#include <string>

using namespace std;

MaxHeap::MaxHeap() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  heap_size = 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string MaxHeap::printHeap() {
  string answer;
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  for (int i = 1; i <= heap_size; i++) { // heap 계산을 위해 1부터 시작
    answer += heapray[i];
    answer += " ";
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
  return answer;
}

void MaxHeap::insertKey(string sen) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  for (int i = 1; i <= sen.length(); i++) {
    maxHeapProp(sen[i-1]);
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MaxHeap::deleteMax() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  heapray[1] = heapray[heap_size]; // 1번노드 마지막 노드 교체
  int next_size = heap_size - 1; // 전체 노드갯수 줄이기
  heap_size = 0; // 새로운 루트노드부터 탐색시작
    for(int i=1;i<=next_size;i++){
      maxHeapProp('X');
    }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MaxHeap::maxHeapProp(char ch) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here   /////////////
    heap_size++;
  if(ch != 'X'){
    heapray[heap_size] = ch;
  }
  int temp_size = heap_size;
  while (temp_size/2 != 0) {
    if (heapray[temp_size] < heapray[temp_size / 2]) {
      char temp;
      temp = heapray[temp_size / 2];
      heapray[temp_size / 2] = heapray[temp_size];
      heapray[temp_size] = temp;
    }
    temp_size /= 2;
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}