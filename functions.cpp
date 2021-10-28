#include <iostream>

using namespace std;

// Function prototypes: the functions are defined later in the code but
// before we use them, we need to declare their names, what type of inputs
// ("arguments") they take in, and what type of outputs they return
//
int factorial(int);       // a function that takes an integer and returns an integer
int factorial_r(int);     // Note: the 'int' before the name is the return type

// A function that calls another function
// The return type is 'void', i.e. it doesn't return a value.
// Note: we don't need a prototype as this definition is above where we call it.
void print_factorial(int value) {
  cout << "Factorial of " << value << " is " << factorial(value) << endl;
}

int main() {  // a function with no arguments that returns an int

  // Call print_factorial
  print_factorial(10);

  // Print the factorial of all integers between 1 and 10
  for (int value = 1; value <= 10; value++) {
    print_factorial(value);
  }

  // Factorial using the factorial_r() function
  int value = 10;
  cout << "Factorial of " << value << " is " << factorial_r(value) << endl;

  // End of main()
  return 0;
}

/* Our main() function is done, we now define the functions we prototyped
   above.
*/

// Compute the factorial of a given number
int factorial(int value) {
  int answer = 1;
  while (value > 1) {
    answer *= value--;
  }
  return answer;
}

// A function that calls itself (a 'recursive' function)
int factorial_r(int value) {
  if (value == 1) return 1;
  return value *= factorial_r(value - 1);
}
