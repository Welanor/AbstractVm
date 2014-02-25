#ifndef _OPERAND_HPP_
# define _OPERAND_HPP_

# include <sstream>
# include <string>
# include <stdint.h>
# include <map>
# include <cmath>
# include "IOperand.hpp"
# include "FactoryIOperand.hpp"
# include "Exception.hpp"

template <typename T>
class Operand : public IOperand
{
public:
  Operand(const std::string &, eOperandType);
  Operand(const IOperand &);
  virtual ~Operand();

  Operand &operator=(IOperand const &);

  std::string const& toString() const;

  int getPrecision() const;
  eOperandType getType() const;
  IOperand *operator+(const IOperand &rhs) const;
  IOperand *operator-(const IOperand &rhs) const;
  IOperand *operator*(const IOperand &rhs) const;
  IOperand *operator/(const IOperand &rhs) const;
  IOperand *operator%(const IOperand &rhs) const;

  T getNbr(const std::string &str) const;
  IOperand *prec_add(const IOperand &rhs) const;
  IOperand *prec_sub(const IOperand &rhs) const;
  IOperand *prec_mul(const IOperand &rhs) const;
  IOperand *prec_div(const IOperand &rhs) const;
  IOperand *prec_mod(const IOperand &rhs) const;

private:
  eOperandType	_type;
  std::string	_val;
};

#endif /* _OPERAND_HPP_ */
