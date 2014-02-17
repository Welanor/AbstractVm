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

void	VMachine::execute(std::string const &file)
{
  t_param_instrc *inst;
  Parser parse;

  if (file != "")
    parse.setInput(file);
  else
    parse.setInput();
  while ((inst = parse.getNextInstrc())!= NULL)
    {
      _val = inst->operand;
      if (inst->instrc == "exit")
	{
	  delete inst;
	  return ;
	}
      (this->*_func[inst->instrc])();
      delete inst;
    }
}

void VMachine::add()
{
  IOperand *nb1;
  IOperand *ret;

  _val = _stack.pop();
  nb1 = _val;
  _val = _stack.pop();
  ret = *_val + *nb1;
  delete _val;
  delete nb1;
  _stack.push(ret);
}

void VMachine::sub()
{
  IOperand *nb1;
  IOperand *ret;

  _val = _stack.pop();
  nb1 = _val;
  _val = _stack.pop();
  ret = *_val - *nb1;
  delete _val;
  delete nb1;
  _stack.push(ret);

}

void VMachine::mul()
{
  IOperand *nb1;
  IOperand *ret;

  _val = _stack.pop();
  nb1 = _val;
  _val = _stack.pop();
  ret = *_val * *nb1;
  delete _val;
  delete nb1;
  _stack.push(ret);
}

void VMachine::mod()
{
  IOperand *nb1;
  IOperand *ret;

  _val = _stack.pop();
  nb1 = _val;
  _val = _stack.pop();
  ret = *_val % *nb1;
  delete _val;
  delete nb1;
  _stack.push(ret);
}

void VMachine::div()
{
  IOperand *nb1;
  IOperand *ret;

  _val = _stack.pop();
  nb1 = _val;
  _val = _stack.pop();
  ret = *_val / *nb1;
  delete _val;
  delete nb1;
  _stack.push(ret);
}

void VMachine::push()
{
  _stack.push(_val);
}

void VMachine::pop()
{
  delete _stack.pop();
}

void VMachine::dump()
{
  std::list<IOperand *>::iterator it;
  std::list<IOperand *>::iterator end;

  end = _stack.end();
  for (it = _stack.begin();it != end;++it)
    std::cout << (*it)->toString() << std::endl;
}

void VMachine::assert()
{
  IOperand *tmp;

  tmp = _stack.pop();
  if (tmp->getType() != _val->getType())
    throw(Exception("The type aren't the same", __FILE__ ": line " TOSTRING(__LINE__)));
  delete _val;
  _stack.push(tmp);
}

void VMachine::print()
{
  _val = _stack.pop();
  if (_val->getType() == Int8)
    std::cout << _val->toString();
  else
    throw(Exception("The type must be Int8", __FILE__ ": line " TOSTRING(__LINE__)));
  delete _val;
}
