#ifndef _IOPERAND_H_
#define _IOPERAND_H_

#include <string>

enum eOperandType
  {
    Int8 = 0,
    Int16,
    Int32,
    Float,
    Double
  };

class IOperand
{
 public :
  virtual std::string const& toString() const = 0;

  virtual int getPrecision() const = 0;
  virtual eOperandType getType() const = 0;
  virtual IOperand *operator+(const IOperand &rhs) const = 0;
  virtual IOperand *operator-(const IOperand &rhs) const = 0;
  virtual IOperand *operator*(const IOperand &rhs) const = 0;
  virtual IOperand *operator/(const IOperand &rhs) const = 0;
  virtual IOperand *operator%(const IOperand &rhs) const = 0;

  virtual ~IOperand() {}
};

#endif /* _IOPERAND_H_ */
