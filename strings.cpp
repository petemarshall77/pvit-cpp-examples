#include <iostream>

using namespace std;

int main() {
  cout << "This is a string" << endl;
  cout << "\"To be or not to be\" - a string with quotes" << endl;    // \ is the escape character
  cout << "This is a string with a newline\n" << endl;

  const char* my_c_style_str = "This is a C-style string";   // this produces a warning
  cout << my_c_style_str << endl;

  string my_string = "This is a C++ string";
  cout << my_string << endl;
  cout << endl;

  string my_2nd_string = " - which is cool";
  cout << my_string + my_2nd_string << endl;

  auto foo = "foo - a C++ string object"s;
  auto bar = "bar - a C-style string";
  cout << foo << endl << bar << endl << endl;

  cout << "Size of foo, a string object, is " << sizeof(foo) << endl;
  cout << "Size of bar, a const char*, is " << sizeof(bar) << endl;

  string chant = "Let's go Red Sox!";
  cout << chant << endl;


  return 0;
}
