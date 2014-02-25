#ifndef _FACTORYIOPERAND_H_
# define _FACTORYIOPERAND_H_

# include <map>
# include <stdint.h>
# include "IOperand.hpp"

class FactoryIOperand
{
public:
  static const FactoryIOperand &getInstance();
  IOperand *createOperand(eOperandType type, const std::string &value) const;

private:

 static FactoryIOperand _inst;

  FactoryIOperand();
  virtual ~FactoryIOperand();

  IOperand *createInt8(const std::string &value) const;
  IOperand *createInt16(const std::string &value) const;
  IOperand *createInt32(const std::string &value) const;
  IOperand *createFloat(const std::string &value) const;
  IOperand *createDouble(const std::string &value) const;

  typedef IOperand *(FactoryIOperand::*my_func)(const std::string &) const;
  std::map<eOperandType, my_func> _func;
};

#endif /* _FACTORYIOPERAND_H_ */
