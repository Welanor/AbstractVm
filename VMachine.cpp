#include "VMachine.hpp"

VMachine::VMachine(): func(), _stack()
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
  IOperand *nb1;
  IOperand *ret;

  pop();
  nb1 = _val;
  pop();
  ret = *_val + *nb1;
  delete _val;
  delete nb1;
  _val = ret;
  push();
}

void VMachine::sub()
{
  IOperand *nb1;
  IOperand *ret;

  pop();
  nb1 = _val;
  pop();
  ret = *_val - *nb1;
  delete _val;
  delete nb1;
  _val = ret;
  push();

}

void VMachine::mul()
{
  IOperand *nb1;
  IOperand *ret;

  pop();
  nb1 = _val;
  pop();
  ret = *_val * *nb1;
  delete _val;
  delete nb1;
  _val = ret;
  push();
}

void VMachine::mod()
{
  IOperand *nb1;
  IOperand *ret;

  pop();
  nb1 = _val;
  pop();
  ret = *_val % *nb1;
  delete _val;
  delete nb1;
  _val = ret;
  push();
}

void VMachine::div()
{
  IOperand *nb1;
  IOperand *ret;

  pop();
  nb1 = _val;
  pop();
  ret = *_val / *nb1;
  delete _val;
  delete nb1;
  _val = ret;
  push();
}

void VMachine::push()
{
  _stack.push(_val);
}

void VMachine::pop()
{
  _val = _stack.pop();
}

void VMachine::dump()
{

}

void VMachine::assert()
{
  IOperand *tmp;

  tmp = _stack.pop();
  if (tmp->getType() != _val->getType())
    throw(Exception("", ""));
  delete _val;
  _val = tmp;
  _stack.push(_val);
}

void VMachine::print()
{
  if (_val->getType() == Int8)
    std::cout << _val->toString();
  // else
  //   throw(Exception("The type must be Int8", "void VMachine::print(), line "))
}
