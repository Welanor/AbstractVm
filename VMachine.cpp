#include "VMachine.hpp"

VMachine::VMachine(): _stack(), func()
{
  func["add"] = &VMachine::add;
  func["sub"] = &VMachine::sub;
  func["mul"] = &VMachine::mul;
  func["div"] = &VMachine::div;
  func["mod"] = &VMachine::mod;
  func["push"] = &VMachine::push;
  func["pop"] = &VMachine::pop;
  func["dump"] = &VMachine::dump;
  func["assert"] = &VMachine::assert;
  func["print"] = &VMachine::print;
}

VMachine::~VMachine()
{

}

void VMachine::run()
{
  try
    {
      IOperand *nb1;
      IOperand *nb2;
      IOperand *result;

      nb1 = createOperand(Int8, "32");
      nb2 = createOperand(Int8, "12");

      result = *nb1 + *nb2;
      std::cout << "Result = " << result->toString() << std::endl;
      delete nb1;
      delete nb2;
      delete result;

      nb1 = createOperand(Int32, "10");
      nb2 = createOperand(Int32, "10");

      result = *nb1 + *nb2;
      std::cout << "Result = " << result->toString() << std::endl;
      delete nb1;
      delete nb2;
      delete result;

      // nb1 = createOperand(Float, "32.45");
      // nb2 = createOperand(Float, "12.61");

      // std::cout << "NB1 -> " << nb1->toString() << std::endl;
      // std::cout << "NB2 -> " << nb2->toString() << std::endl;

      // result = *nb1 % *nb2;

      //throw(Exception("toto", "tata"));
    }
  catch (Exception &e)
    {
      std::cerr << "Error: " << e.what() << " in " << e.where() << std::endl;
    }
}

void VMachine::add()
{

}

void VMachine::sub()
{

}

void VMachine::mul()
{

}

void VMachine::mod()
{

}

void VMachine::div()
{

}

void VMachine::push()
{

}

void VMachine::pop()
{

}

void VMachine::dump()
{

}

void VMachine::assert()
{

}

void VMachine::print()
{

}
