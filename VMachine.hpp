#ifndef _VMACHINE_H_
#define _VMACHINE_H_

# include <iostream>
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
  Memory<IOperand *> _stack;
};

#endif /* _VMACHINE_H_ */
