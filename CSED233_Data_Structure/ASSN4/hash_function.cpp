#include "hash_function.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int BinaryMidSquareHash::hashing(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int temp;
  int dgt = 0;
  int size_tmp = key_size;
  while (size_tmp > 0) {
    dgt++;
    size_tmp = size_tmp / 2;
  }

  temp = key * key >> (dgt + 1 - index_size / 2);
  int result = temp % (int)pow(2, index_size);

  return result;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int DigitFoldingHash::hashing(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int sum = 0;
  int temp = key;
  while (temp > 0) {
    sum += temp % 2;
    temp = temp / 2;
  }

  return sum;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int MultiplicationHash::hashing(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  double ka = key * 0.1;
  while (ka > 1) {
    ka = ka - 1;
  }
  int temp = int(pow(2, index_size) * ka);

  return temp;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
