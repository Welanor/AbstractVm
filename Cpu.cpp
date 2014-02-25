#include "Cpu.hpp"

Cpu::Cpu(): _func(), _stack(), _parse()
{
  isJump = 0;
  _func["add"] = &Cpu::add;
  _func["sub"] = &Cpu::sub;
  _func["mul"] = &Cpu::mul;
  _func["div"] = &Cpu::div;
  _func["mod"] = &Cpu::mod;
  _func["push"] = &Cpu::push;
  _func["pop"] = &Cpu::pop;
  _func["dump"] = &Cpu::dump;
  _func["assert"] = &Cpu::assert;
  _func["print"] = &Cpu::print;
  _func["jump"] = &Cpu::jump;
  _func["cmpe"] = &Cpu::cmpe;
  _func["cmpne"] = &Cpu::cmpne;
  _func["cmpl"] = &Cpu::cmpl;
  _func["cmpg"] = &Cpu::cmpg;
  _func["or"] = &Cpu::my_or;
  _func["xor"] = &Cpu::my_xor;
  _func["and"] = &Cpu::my_and;
  _func["inc"] = &Cpu::inc;
  _func["dec"] = &Cpu::dec;
}

Cpu::~Cpu()
{

}

void	Cpu::execute(std::string const &file)
{
  t_param_instrc *inst;

  if (file != "")
    _parse.setInput(file);
  else
    _parse.setInput();
  while ((inst = _parse.getNextInstrc())!= NULL)
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

void Cpu::add()
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

void Cpu::sub()
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

void Cpu::mul()
{
  IOperand *nb1;
  IOperand *ret;

  _val = _stack.pop();
  nb1 = _val;
  _val = _stack.pop();
  ret = (*_val) * (*nb1);
  delete _val;
  delete nb1;
  _stack.push(ret);
}

void Cpu::mod()
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

void Cpu::div()
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

void Cpu::push()
{
  _stack.push(_val);
}

void Cpu::pop()
{
  delete _stack.pop();
}

void Cpu::dump()
{
  std::list<IOperand *>::iterator it;
  std::list<IOperand *>::iterator end;

  end = _stack.end();
  for (it = _stack.begin();it != end;++it)
    std::cout << (*it)->toString() << std::endl;
}

void Cpu::assert()
{
  IOperand *tmp;

  tmp = _stack.pop();
  if (*tmp != *_val)
    throw(Exception("The types aren't the same", __FILE__ ": line " TOSTRING(__LINE__)));
  delete _val;
  _stack.push(tmp);
}

void Cpu::print()
{
  _val = _stack.pop();
  if (_val->getType() == Int8)
    {
      int c;
      std::stringstream ss(_val->toString());

      ss >> c;
      std::cout << static_cast<char>(c);
      _stack.push(_val);
    }
  else
    throw(Exception("The type must be Int8", __FILE__ ": line " TOSTRING(__LINE__)));
}

void Cpu::jump()
{
  if (isJump)
    {
      std::stringstream ss(_val->toString());
      int val;

      ss >> val;

      isJump = 0;
      _parse.moveIndex(val);
      delete _val;
    }
}

void Cpu::cmpe()
{
  IOperand *nb1;

  nb1 = _stack.pop();
  _val = _stack.pop();

  if (*_val == *nb1)
    isJump = 1;

  _stack.push(_val);
  _stack.push(nb1);
}

void Cpu::cmpne()
{
  IOperand *nb1;

  nb1 = _stack.pop();
  _val = _stack.pop();

  if (*_val != *nb1)
    isJump = 1;

  _stack.push(_val);
  _stack.push(nb1);
}

void Cpu::cmpl()
{
  IOperand *nb1;

  nb1 = _stack.pop();
  _val = _stack.pop();

  if (*nb1 < *_val)
    isJump = 1;

  _stack.push(_val);
  _stack.push(nb1);
}

void Cpu::cmpg()
{
  IOperand *nb1;

  nb1 = _stack.pop();
  _val = _stack.pop();

  if (*nb1 > *_val)
    isJump = 1;

  _stack.push(_val);
  _stack.push(nb1);
}

void Cpu::my_or()
{
  IOperand *nb1;
  IOperand *ret;

  _val = _stack.pop();
  nb1 = _val;
  _val = _stack.pop();
  ret = *_val | *nb1;
  delete _val;
  delete nb1;
  _stack.push(ret);
}

void Cpu::my_xor()
{
  IOperand *nb1;
  IOperand *ret;

  _val = _stack.pop();
  nb1 = _val;
  _val = _stack.pop();
  ret = *_val ^ *nb1;
  delete _val;
  delete nb1;
  _stack.push(ret);
}

void Cpu::my_and()
{
  IOperand *nb1;
  IOperand *ret;

  _val = _stack.pop();
  nb1 = _val;
  _val = _stack.pop();
  ret = *_val & *nb1;
  delete _val;
  delete nb1;
  _stack.push(ret);
}

void Cpu::inc()
{
  IOperand *nb1;
  IOperand *ret;

  nb1 = _stack.pop();
  ret = *nb1 + *_val;
  delete _val;
  delete nb1;
  _stack.push(ret);
}

void Cpu::dec()
{
  IOperand *nb1;
  IOperand *ret;

  nb1 = _stack.pop();
  ret = *nb1 - *_val;
  delete _val;
  delete nb1;
  _stack.push(ret);
}
