#ifndef _VMACHINE_H_
#define _VMACHINE_H_

# include <iostream>
# include <string>
# include "Exception.hpp"
# include "Memory.hpp"
# include "IOperand.hpp"
# include "Operand.hpp"

class VMachine
{
public:
  VMachine();
  virtual ~VMachine();

  void run();

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
  std::map<std::string, function>	func;

  Memory<IOperand *>					_stack;
  IOperand						*_val;
};

#endif /* _VMACHINE_H_ */
