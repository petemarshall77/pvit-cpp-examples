#include <iostream>

using namespace std;

int main() {
  // define a variable
  int my_integer;      // my_integer = 10;
  cout << "my_integer = " << my_integer << endl;

  // define and assign
  int my_second_integer = my_integer + 1;
  cout << "my_second_integer = " << my_second_integer << endl;

  // add 1
  my_second_integer = my_second_integer + 1;  // not algebra!  my_second_integer <- my_second_integer + 1
  cout << "my_second_integer = " << my_second_integer << endl;

  // increment operator
  my_second_integer++;
  cout << "my_second_integer = " << my_second_integer << endl;

  // post increment
  cout << "my_second_integer = " << my_second_integer++ << endl;
  cout << "my_second_integer = " << my_second_integer << endl;

  // pre-increment
  cout << "my_second_integer = " << ++my_second_integer << endl;

  // decrement
  cout << "my_second_integer = " << --my_second_integer << endl;


  return 0;
}
