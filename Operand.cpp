#include "Operand.hpp"

IOperand *createOperand(eOperandType type, const std::string & value)
{
  std::map<eOperandType, IOperand *(*)(const std::string &value)> func;

  func[Int8] = createInt8;
  func[Int16] = createInt16;
  func[Int32] = createInt32;
  func[Float] = createFloat;
  func[Double] = createDouble;

  return (func[type](value));
}

IOperand *createInt8(const std::string &value)
{
  return (new Operand<char>(value, Int8));
}

IOperand *createInt16(const std::string &value)
{
  return (new Operand<short>(value, Int16));
}

IOperand *createInt32(const std::string &value)
{
  return (new Operand<int>(value, Int32));
}

IOperand *createFloat(const std::string &value)
{
  return (new Operand<float>(value, Float));
}

IOperand *createDouble(const std::string &value)
{
  return (new Operand<double>(value, Double));
}

template <>
IOperand *Operand<double>::operator%(const IOperand &rhs) const
{
  (void)rhs;
  return (NULL);
}

template <>
IOperand *Operand<float>::operator%(const IOperand &rhs) const
{
  (void)rhs;
  return (NULL);
}
