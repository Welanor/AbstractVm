#include "Operand.hpp"

template <typename T>
Operand<T>::Operand(const std::string &val, eOperandType type)
{
  _type = type;
  _val = val;
  getNbr(val);
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
T Operand<T>::getNbr(const std::string &str) const
{
  T ret;
  std::stringstream ss(str);

  if (!(ss >> ret))
    throw(Exception("Overflow/Underflow", __FILE__ ": line " TOSTRING(__LINE__)));
  return (ret);
}

template <>
int8_t Operand<int8_t>::getNbr(const std::string &str) const
{
  int ret;
  std::stringstream ss(str);

  ret = 0;
  if (!(ss >> ret) || ret > std::numeric_limits<int8_t>::max()
      || ret < std::numeric_limits<int8_t>::min())
    throw(Exception("Overflow/Underflow", __FILE__ ": line " TOSTRING(__LINE__)));
  return (ret);
}

template <typename T>
IOperand *Operand<T>::operator+(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  std::stringstream ss("");
  T nb1;
  T nb2;
  T min;

  min = std::numeric_limits<T>::min();
  if (std::numeric_limits<T>::has_denorm)
    min = -std::numeric_limits<T>::max();
  if (rhs.getType() > _type)
    return (prec_add(rhs));
  nb1 = getNbr(_val);
  nb2 = getNbr(rhs.toString());
  ss << (nb1 + nb2);
  if ((nb2 > 0) && (nb1 > std::numeric_limits<T>::max() - nb2))
    throw(Exception("Overflow", __FILE__ ": line " TOSTRING(__LINE__)));
  if ((nb2 < 0) && (nb1 < min - nb2))
    throw(Exception("Underflow", __FILE__ ": line " TOSTRING(__LINE__)));
  return (fact.createOperand(_type, ss.str()));
}

template <typename T>
IOperand *Operand<T>::operator-(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  std::stringstream ss("");
  T nb1;
  T nb2;
  T min;

  min = std::numeric_limits<T>::min();
  if (std::numeric_limits<T>::has_denorm)
    min = -std::numeric_limits<T>::max();
  if (rhs.getType() > _type)
    return (prec_sub(rhs));
  nb1 = getNbr(_val);
  nb2 = getNbr(rhs.toString());
  ss << (nb1 - nb2);
  if ((nb2 < 0) && (nb1 > std::numeric_limits<T>::max() + nb2))
    throw(Exception("Overflow", __FILE__ ": line " TOSTRING(__LINE__)));
  if ((nb2 > 0) && (nb1 < min + nb2))
    throw(Exception("Underflow", __FILE__ ": line " TOSTRING(__LINE__)));
  return (fact.createOperand(_type, ss.str()));
}

template <typename T>
IOperand *Operand<T>::operator*(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  std::stringstream ss("");
  T nb1;
  T nb2;
  T min;

  min = std::numeric_limits<T>::min();
  if (std::numeric_limits<T>::has_denorm)
    min = -std::numeric_limits<T>::max();
  if (rhs.getType() > _type)
    return (prec_mul(rhs));
  nb1 = getNbr(_val);
  nb2 = getNbr(rhs.toString());
  if ((nb1 > 1 && nb2 < -1) && (nb1 > min / nb2))
    throw(Exception("Underflow", __FILE__ ": line " TOSTRING(__LINE__)));
  if ((nb1 > 1 && nb2 > 1) && (nb1 > std::numeric_limits<T>::max() / nb2))
    throw(Exception("Overflow", __FILE__ ": line " TOSTRING(__LINE__)));
  if ((nb1 < -1 && nb2 > 1) && (nb1 < min / nb2))
    throw(Exception("Underflow", __FILE__ ": line " TOSTRING(__LINE__)));
  if ((nb1 < -1 && nb2 < -1) && (nb1 < std::numeric_limits<T>::max() / nb2))
    throw(Exception("Overflow", __FILE__ ": line " TOSTRING(__LINE__)));
  ss << (nb1 * nb2);
  return (fact.createOperand(_type, ss.str()));
}

template <typename T>
IOperand *Operand<T>::operator/(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  std::stringstream ss("");
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    return (prec_div(rhs));
  nb1 = getNbr(_val);
  nb2 = getNbr(rhs.toString());
  if (nb2 == 0)
    throw(Exception("Division by 0", __FILE__ ": line " TOSTRING(__LINE__)));
  ss << (nb1 / nb2);
  return (fact.createOperand(_type, ss.str()));
}

template <typename T>
IOperand *Operand<T>::operator%(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  std::stringstream ss("");
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    return (prec_mod(rhs));
  nb1 = getNbr(_val);
  nb2 = getNbr(rhs.toString());
  if (nb2 == 0)
    throw(Exception("Modulo by 0", __FILE__ ": line " TOSTRING(__LINE__)));
  ss << (nb1 % nb2);
  return (fact.createOperand(_type, ss.str()));
}

template <typename T>
bool Operand<T>::operator==(const IOperand &rhs) const
{
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    {
      const FactoryIOperand &fact = FactoryIOperand::getInstance();
      IOperand *pnb1;
      IOperand *pnb2;
      bool ret;

      pnb1 = fact.createOperand(rhs.getType(), _val);
      pnb2 = fact.createOperand(rhs.getType(), rhs.toString());
      ret = *pnb1 == *pnb2;
      delete pnb1;
      delete pnb2;
      return (ret);
    }
  nb1 = getNbr(_val);
  nb2 = getNbr(rhs.toString());
  return (nb1 == nb2);
}

template <typename T>
bool Operand<T>::operator!=(const IOperand &rhs) const
{
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    {
      const FactoryIOperand &fact = FactoryIOperand::getInstance();
      IOperand *pnb1;
      IOperand *pnb2;
      bool ret;

      pnb1 = fact.createOperand(rhs.getType(), _val);
      pnb2 = fact.createOperand(rhs.getType(), rhs.toString());
      ret = *pnb1 != *pnb2;
      delete pnb1;
      delete pnb2;
      return (ret);
    }
  nb1 = getNbr(_val);
  nb2 = getNbr(rhs.toString());
  return (nb1 != nb2);
}

template <typename T>
bool Operand<T>::operator<(const IOperand &rhs) const
{
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    {
      const FactoryIOperand &fact = FactoryIOperand::getInstance();
      IOperand *pnb1;
      IOperand *pnb2;
      bool ret;

      pnb1 = fact.createOperand(rhs.getType(), _val);
      pnb2 = fact.createOperand(rhs.getType(), rhs.toString());
      ret = *pnb1 < *pnb2;
      delete pnb1;
      delete pnb2;
      return (ret);
    }
  nb1 = getNbr(_val);
  nb2 = getNbr(rhs.toString());
  return (nb1 < nb2);
}

template <typename T>
bool Operand<T>::operator>(const IOperand &rhs) const
{
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    {
      const FactoryIOperand &fact = FactoryIOperand::getInstance();
      IOperand *pnb1;
      IOperand *pnb2;
      bool ret;

      pnb1 = fact.createOperand(rhs.getType(), _val);
      pnb2 = fact.createOperand(rhs.getType(), rhs.toString());
      ret = *pnb1 > *pnb2;
      delete pnb1;
      delete pnb2;
      return (ret);
    }
  nb1 = getNbr(_val);
  nb2 = getNbr(rhs.toString());
  return (nb1 > nb2);
}

template <typename T>
IOperand *Operand<T>::operator&(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  std::stringstream ss("");
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    {
      IOperand *pnb1;
      IOperand *pnb2;
      IOperand *ret;

      pnb1 = fact.createOperand(rhs.getType(), _val);
      pnb2 = fact.createOperand(rhs.getType(), rhs.toString());
      ret = *pnb1 & *pnb2;
      delete pnb1;
      delete pnb2;
      return (ret);
    }
  nb1 = getNbr(_val);
  nb2 = getNbr(rhs.toString());
  ss << (nb1 & nb2);
  return (fact.createOperand(_type, ss.str()));
}

template <typename T>
IOperand *Operand<T>::operator|(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  std::stringstream ss("");
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    {
      IOperand *pnb1;
      IOperand *pnb2;
      IOperand *ret;

      pnb1 = fact.createOperand(rhs.getType(), _val);
      pnb2 = fact.createOperand(rhs.getType(), rhs.toString());
      ret = *pnb1 | *pnb2;
      delete pnb1;
      delete pnb2;
      return (ret);
    }
  nb1 = getNbr(_val);
  nb2 = getNbr(rhs.toString());
  ss << (nb1 | nb2);
  return (fact.createOperand(_type, ss.str()));
}

template <typename T>
IOperand *Operand<T>::operator^(const IOperand &rhs) const
{
  const FactoryIOperand &fact = FactoryIOperand::getInstance();
  std::stringstream ss("");
  T nb1;
  T nb2;

  if (rhs.getType() > _type)
    {
      IOperand *pnb1;
      IOperand *pnb2;
      IOperand *ret;

      pnb1 = fact.createOperand(rhs.getType(), _val);
      pnb2 = fact.createOperand(rhs.getType(), rhs.toString());
      ret = *pnb1 ^ *pnb2;
      delete pnb1;
      delete pnb2;
      return (ret);
    }
  nb1 = getNbr(_val);
  nb2 = getNbr(rhs.toString());
  ss << (nb1 ^ nb2);
  return (fact.createOperand(_type, ss.str()));
}

template <>
IOperand *Operand<double>::operator%(const IOperand &) const
{
  throw(Exception("Can't do modulo with Double", __FILE__ ": line " TOSTRING(__LINE__)));
}

template <>
IOperand *Operand<float>::operator%(const IOperand &) const
{
  throw(Exception("Can't do modulo with Float", __FILE__ ": line " TOSTRING(__LINE__)));
}

template <>
IOperand *Operand<float>::operator&(const IOperand &) const
{
  throw(Exception("Can't do Bitwise operation with a float",
		  __FILE__ ": line " TOSTRING(__LINE__)));
}

template <>
IOperand *Operand<float>::operator|(const IOperand &) const
{
  throw(Exception("Can't do Bitwise operation with a float",
		  __FILE__ ": line " TOSTRING(__LINE__)));
}

template <>
IOperand *Operand<float>::operator^(const IOperand &) const
{
  throw(Exception("Can't do Bitwise operation with a float",
		  __FILE__ ": line " TOSTRING(__LINE__)));
}

template <>
IOperand *Operand<double>::operator&(const IOperand &) const
{
  throw(Exception("Can't do Bitwise operation with a double",
		  __FILE__ ": line " TOSTRING(__LINE__)));
}

template <>
IOperand *Operand<double>::operator|(const IOperand &) const
{
  throw(Exception("Can't do Bitwise operation with a double",
		  __FILE__ ": line " TOSTRING(__LINE__)));
}

template <>
IOperand *Operand<double>::operator^(const IOperand &) const
{
  throw(Exception("Can't do Bitwise operation with a double",
		  __FILE__ ": line " TOSTRING(__LINE__)));
}

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;
