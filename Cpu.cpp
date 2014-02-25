#include "Cpu.hpp"

Cpu::Cpu(): _func(), _stack()
{
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
}

Cpu::~Cpu()
{

}

void	Cpu::execute(std::string const &file)
{
  t_param_instrc *inst;
  Chipset	parse;

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
  if (tmp->getType() != _val->getType())
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
      std::cout << static_cast<char>(c) << std::endl;
      _stack.push(_val);
    }
  else
    throw(Exception("The type must be Int8", __FILE__ ": line " TOSTRING(__LINE__)));
}
