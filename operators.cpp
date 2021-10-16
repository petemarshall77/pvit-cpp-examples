#include <iostream>

using namespace std;

int main () {

  int foo{11}, bar{7};
  cout << "foo = " << foo << endl;
  cout << "bar = " << bar << endl;
  cout << endl;

  cout << "foo + bar = " << foo + bar << endl;
  cout << "foo - bar = " << foo - bar << endl;
  cout << "foo * bar = " << foo * bar << endl;
  cout << "foo/bar = " << foo/bar << endl;
  cout << "foo/bar = " << (float) foo/bar << endl;
  cout << "foo % bar = " << foo % bar << endl;
  cout << endl;

  // Comparisons
  cout << "foo == bar = " << (foo == bar) << endl;
  cout << "foo != bar = " << (foo != bar) << endl;
  cout << "foo > bar = " << (foo > bar) << endl;
  cout << "foo <= bar = " << (foo <= bar) << endl;
  cout << endl;

  // Bitwise operators
  cout << "foo & bar = " << (foo & bar) << endl;
  cout << "foo | bar = " << (foo | bar) << endl;
  cout << "foo ^ bar = " << (foo ^ bar) << endl;
  cout << "foo << 2 = " << (foo << 2) << endl;
  cout << "foo >> 1 = " << (foo >> 1) << endl;
  cout << endl;

  // Magic...
  cout << "foo = " << foo << " bar = " << bar << endl;
  foo ^= bar;
  bar ^= foo;
  foo ^= bar;
  cout << "foo = " << foo << " bar = " << bar << endl;


  return 0;
}
