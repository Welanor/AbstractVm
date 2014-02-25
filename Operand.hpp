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


  IOperand *prec_add(const IOperand &rhs) const;
  IOperand *prec_sub(const IOperand &rhs) const;
  IOperand *prec_mul(const IOperand &rhs) const;
  IOperand *prec_div(const IOperand &rhs) const;
  IOperand *prec_mod(const IOperand &rhs) const;

private:
  eOperandType	_type;
  std::string	_val;
};

template <typename T>
Operand<T>::Operand(const std::string &val, eOperandType type)
{
  _type = type;
  _val = val;
}

template <typename T>
Operand<T>::Operand(const IOperand &cpy)
{
  _type = cpy.getType();
  _val = cpy.toString();
}

template <typename T>
Operand<T>::~Operand()
{

}

template <typename T>
Operand<T> &Operand<T>::operator=(IOperand const &cpy)
{
  _type = cpy.getType();
  _val = cpy.toString();
  return (*this);
}

template <typename T>
std::string const& Operand<T>::toString() const
{
  return (_val);
}

template <typename T>
int Operand<T>::getPrecision() const
{
  return (_type);
}

template <typename T>
eOperandType Operand<T>::getType() const
{
  return (_type);
}

template <typename T>
IOperand *Operand<T>::prec_add(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  IOperand *nb1;
  IOperand *nb2;
  IOperand *ret;

  nb1 = fact.createOperand(rhs.getType(), _val);
  nb2 = fact.createOperand(rhs.getType(), rhs.toString());
  ret = *nb1 + *nb2;
  delete nb1;
  delete nb2;
  return (ret);
}

template <typename T>
IOperand *Operand<T>::prec_sub(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  IOperand *nb1;
  IOperand *nb2;
  IOperand *ret;

  nb1 = fact.createOperand(rhs.getType(), _val);
  nb2 = fact.createOperand(rhs.getType(), rhs.toString());
  ret = *nb1 - *nb2;
  delete nb1;
  delete nb2;
  return (ret);
}

template <typename T>
IOperand *Operand<T>::prec_mul(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  IOperand *nb1;
  IOperand *nb2;
  IOperand *ret;

  nb1 = fact.createOperand(rhs.getType(), _val);
  nb2 = fact.createOperand(rhs.getType(), rhs.toString());
  ret = *nb1 * *nb2;
  delete nb1;
  delete nb2;
  return (ret);
}

template <typename T>
IOperand *Operand<T>::prec_div(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  IOperand *nb1;
  IOperand *nb2;
  IOperand *ret;

  nb1 = fact.createOperand(rhs.getType(), _val);
  nb2 = fact.createOperand(rhs.getType(), rhs.toString());
  ret = *nb1 / *nb2;
  delete nb1;
  delete nb2;
  return (ret);
}

template <typename T>
IOperand *Operand<T>::prec_mod(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  IOperand *nb1;
  IOperand *nb2;
  IOperand *ret;

  nb1 = fact.createOperand(rhs.getType(), _val);
  nb2 = fact.createOperand(rhs.getType(), rhs.toString());
  ret = *nb1 % *nb2;
  delete nb1;
  delete nb2;
  return (ret);
}

template <typename T>
IOperand *Operand<T>::operator+(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  std::stringstream ss(rhs.toString());
  std::stringstream ss1(_val);
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    return (prec_add(rhs));
  nb1 = 0;
  ss >> nb2;
  ss.clear();
  ss.str(_val);
  ss >> nb1;
  ss.clear();
  ss << (nb1 + nb2);
  return (fact.createOperand(_type, ss.str()));
}

#include <iostream>

template <typename T>
IOperand *Operand<T>::operator-(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  std::stringstream ss(rhs.toString());
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    return (prec_sub(rhs));
  ss >> nb2;
  ss.clear();
  ss.str(_val);
  ss >> nb1;
  ss.clear();
  std::cout << (int)nb1 << " | " << (int)nb2 << std::endl;
  if (nb1 - nb2 + nb2 > nb1)
    throw(Exception("UnderFlow", __FILE__ ": line " TOSTRING(__LINE__)));
  else if (nb1 - nb2 + nb2 < nb1)
    throw(Exception("OverFlow", __FILE__ ": line " TOSTRING(__LINE__)));
  ss << nb1 - nb2;
  return (fact.createOperand(_type, ss.str()));
}

template <typename T>
IOperand *Operand<T>::operator*(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  std::stringstream ss(rhs.toString());
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    return (prec_mul(rhs));
  ss >> nb2;
  ss.clear();
  ss.str(_val);
  ss >> nb1;
  ss.clear();
  ss << nb1 * nb2;
  return (fact.createOperand(_type, ss.str()));
}

template <typename T>
IOperand *Operand<T>::operator/(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  std::stringstream ss(rhs.toString());
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    return (prec_div(rhs));
  ss >> nb2;
  ss.clear();
  ss.str(_val);
  ss >> nb1;
  ss.clear();
  if (nb2 == 0)
    throw(Exception("Division by 0", __FILE__ ": line " TOSTRING(__LINE__)));
  ss << nb1 / nb2;
  return (fact.createOperand(_type, ss.str()));
}

template <typename T>
IOperand *Operand<T>::operator%(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  std::stringstream ss(rhs.toString());
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    return (prec_mod(rhs));
  ss >> nb2;
  ss.clear();
  ss.str(_val);
  ss >> nb1;
  ss.clear();
  if (nb2 == 0)
    throw(Exception("Modulo by 0", __FILE__ ": line " TOSTRING(__LINE__)));
  ss << fmod(nb1, nb2);
  return (fact.createOperand(_type, ss.str()));
}

#endif /* _OPERAND_HPP_ */
