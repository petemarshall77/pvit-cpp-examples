#include <iostream>
#include <math.h>

using namespace std;

int main() {
  int my_int = pow(2, 31) - 1;
  cout << "my_int = " << my_int++ << endl;
  cout << "my_int = " << my_int << endl;
  cout << endl;

  unsigned int my_uint = pow(2, 31) - 1;
  cout << "my_uint = " << my_uint++ << endl;
  cout << "my_uint = " << my_uint << endl;
  cout << endl;

  float my_float = 2.99792e8;
  cout << "my_float = " << my_float << endl;
  cout << endl;

  char my_char = 'a';
  cout << "my_char = " << my_char << endl;

  my_char += 1;
  cout << "my_char = " << my_char << endl;
  cout << endl;

  // Booleans
  bool my_bool = true;
  cout << "my_bool = " << my_bool << endl;
  my_bool += 8;
  cout << "my_bool = " << my_bool << endl;
  my_bool = 0;
  cout << "my_bool = " << my_bool << endl;
  cout << endl;

  // Sizes of datatypes
  cout << "Size of bool = " << sizeof(bool) << endl;
  cout << "Size of char = " << sizeof(char) << endl;
  cout << "Size of int = " << sizeof(int) << endl;
  cout << "Size of float = " << sizeof(float) << endl;
  cout << "Size of long = " << sizeof(long) << endl;
  cout << "Size of long long = " << sizeof(long long) << endl;



  return 0;
}
