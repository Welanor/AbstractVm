#ifndef _VMACHINE_H_
#define _VMACHINE_H_

# include <iostream>
# include <string>
# include "Exception.hpp"
# include "Parser.hpp"
# include "Memory.hpp"
# include "IOperand.hpp"
# include "Operand.hpp"

class VMachine
{
public:
  VMachine();
  virtual ~VMachine();

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

private:

  typedef void (VMachine::*function)();
  std::map<std::string, function>	_func;

  Memory<IOperand *>			_stack;
  IOperand				*_val;
};

#endif /* _VMACHINE_H_ */
