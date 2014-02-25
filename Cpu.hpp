#ifndef _CPU_H_
#define _CPU_H_

# include <iostream>
# include <string>
# include "Exception.hpp"
# include "Chipset.hpp"
# include "Memory.hpp"
# include "IOperand.hpp"
# include "Operand.hpp"

class Cpu
{
public:
  Cpu();
  virtual ~Cpu();

  void	execute(std::string const &);

private:

  void add();
  void sub();
  void mul();
  void mod();
  void div();
  void push();
  void pop();
  void dump();
  void assert();
  void print();
  void jump();
  void cmpe();
  void cmpne();
  void cmpl();
  void cmpg();
  void my_or();
  void my_xor();
  void my_and();
  void nand();
  void inc();
  void dec();

private:

  typedef void (Cpu::*function)();
  std::map<std::string, function>	_func;

  Memory<IOperand *>			_stack;
  Chipset				_parse;
  IOperand				*_val;
  bool					isJump;
};

#endif /* _CPU_H_ */
