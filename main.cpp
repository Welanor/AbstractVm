#include <iostream>
#include "Exception.hpp"
#include "Operand.hpp"

using namespace std;

int main()
{
  try
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
      //throw(Exception("toto", "tata"));
    }
  catch (Exception &e)
    {
      std::cout << "Error " << e.what() << " in " << e.where() << std::endl;
    }
  return (0);
}
