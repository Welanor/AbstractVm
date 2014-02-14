#include "VMachine.hpp"

VMachine::VMachine(): _func(), _stack()
{
  _func["add"] = &VMachine::add;
  _func["sub"] = &VMachine::sub;
  _func["mul"] = &VMachine::mul;
  _func["div"] = &VMachine::div;
  _func["mod"] = &VMachine::mod;
  _func["push"] = &VMachine::push;
  _func["pop"] = &VMachine::pop;
  _func["dump"] = &VMachine::dump;
  _func["assert"] = &VMachine::assert;
  _func["print"] = &VMachine::print;
}

VMachine::~VMachine()
{

}

void VMachine::run(char *str)
{
  try
    {
      t_param_instrc *inst;
      Parser parse(str);

      while ((inst = parse.getNextInstrc())!= NULL)
	{
	  _val = inst->operand;
	  if (inst->instrc == "exit")
	    return ;
	  (this->*_func[inst->instrc])();
	  delete inst;
	}
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
