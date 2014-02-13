#include <iostream>
#include "Operand.hpp"

using namespace std;

int main()
{
  IOperand *nb1;
  IOperand *nb2;
  IOperand *result;

  nb1 = createOperand(Int8, "32");
  nb2 = createOperand(Int8, "12");

  result = *nb1 + *nb2;
  cout << result->toString() << endl;
  delete nb1;
  delete nb2;
  delete result;
  return (0);
}
