#include <iostream>

using namespace std;

int main() {

  // if something is true, do this; else do something else
  if (true) {
    cout << "\"true\" is true" << endl;
  }
  if (0) {
    cout << "0 is true" << endl;
  } else {
    cout << "0 is false" << endl;
  }

  // comparison operators: == != > < >= <=
  if (2 > 1) cout << "2 is greater than 1" << endl; // note - 1 statement, don't need {}

  // Using = instead of == A common practice but be careful
  int my_six = 6;
  if ((my_six = 7)) {    // extra parens supresses commpiler warning
    cout << "6 is equal to 7" << endl;
  } else {
    cout << "6 is not equal to 7" << endl;
  }

  // for loops: doing something multiple times with a counter
  int value = 10;
  int answer = 1;
  for (int i = 1; i <= value; i++) {
    answer *= i;
  }
  cout << "Factorial of " << value << " is " << answer << endl;

  // while loop - keep doing something while a some condition is true
  value = 10;
  answer = 1;
  int original_value = value;  // why do we need a copy of the original value?
  while (value > 1) {
    answer *= value--;
  }
  cout << "Factorial of " << original_value << " is " << answer << endl;

  // do-while: do something at least once, and keep going while some condition is true
  value = 10;
  answer = 1;
  do {
    answer *= value--;
  }
  while (value > 1);
  cout << "Factorial of " << original_value << " is " << answer << endl;

  // End of main()
  return 0;
}
