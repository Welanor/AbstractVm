#include "FactoryIOperand.hpp"
#include "Operand.hpp"

FactoryIOperand FactoryIOperand::_inst = FactoryIOperand();

const FactoryIOperand &FactoryIOperand::getInstance()
{
  return (_inst);
}

FactoryIOperand::FactoryIOperand()
{
  _func[Int8] = &FactoryIOperand::createInt8;
  _func[Int16] = &FactoryIOperand::createInt16;
  _func[Int32] = &FactoryIOperand::createInt32;
  _func[Float] = &FactoryIOperand::createFloat;
  _func[Double] = &FactoryIOperand::createDouble;
}

FactoryIOperand::~FactoryIOperand()
{

}

IOperand *FactoryIOperand::createOperand(eOperandType type, const std::string &value) const
{
  return (this->*_func.at(type))(value);
}

IOperand *FactoryIOperand::createInt8(const std::string &value) const
{
  return (new Operand<int8_t>(value, Int8));
}

IOperand *FactoryIOperand::createInt16(const std::string &value) const
{
  return (new Operand<int16_t>(value, Int16));
}

IOperand *FactoryIOperand::createInt32(const std::string &value) const
{
  return (new Operand<int32_t>(value, Int32));
}

IOperand *FactoryIOperand::createFloat(const std::string &value) const
{
  return (new Operand<float>(value, Float));
}

IOperand *FactoryIOperand::createDouble(const std::string &value) const
{
  return (new Operand<double>(value, Double));
}
