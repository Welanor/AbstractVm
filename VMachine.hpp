#ifndef _VMACHINE_H_
#define _VMACHINE_H_

# include "Memory.hpp"

class VMachine
{
public:
  VMachine();
  virtual ~VMachine();

  void run();

private:
  Memory _stack;
};

#endif /* _VMACHINE_H_ */
