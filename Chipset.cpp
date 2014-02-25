#include "Chipset.hpp"
#include <string.h>

void		Chipset::initDefaultGrammar()
{
  this->listGrammarInsctr.push_back("push");
  this->listGrammarInsctr.push_back("pop");
  this->listGrammarInsctr.push_back("dump");
  this->listGrammarInsctr.push_back("assert");
  this->listGrammarInsctr.push_back("add");
  this->listGrammarInsctr.push_back("sub");
  this->listGrammarInsctr.push_back("mul");
  this->listGrammarInsctr.push_back("div");
  this->listGrammarInsctr.push_back("mod");
  this->listGrammarInsctr.push_back("print");
  this->listGrammarInsctr.push_back("exit");
  this->listGrammarType.push_back("int8");
  this->listGrammarType.push_back("int16");
  this->listGrammarType.push_back("int32");
  this->listGrammarType.push_back("float");
  this->listGrammarType.push_back("double");
}

int			Chipset::numberArgInstrc(std::string &instrc) const
{
  int			index;
  std::istringstream	iss(instrc);
  std::string		s;

  index = 0;
  while (iss >> s)
    index += 1;
  return (index);
}

std::string			Chipset::getArgumentFormat(std::string &instrc)
{
  std::istringstream		stream(instrc);
  std::string			tmp;
  std::string			argument;
  bool				is_arguement = false;

  stream >> tmp;
  argument += tmp;
  while (stream >> tmp)
    {
      if (is_arguement == false)
	argument += " ";
      argument += tmp;
      is_arguement = true;
    }
  return (argument);
}

bool			Chipset::checkFormatArguement(std::string &instrc) const
{
  size_t		beginBracket;
  size_t		endBracket;
  std::string		number;
  int			index;

  beginBracket = instrc.find("(");
  endBracket = instrc.find(")");
  if (beginBracket == std::string::npos || endBracket == std::string::npos)
    return (false);
  number = instrc.substr(beginBracket + 1,
			 (endBracket - (beginBracket + 1)));
  index = 0;
  while (number[index] != '\0')
    {
      if ((number[index] < '0' || number[index] > '9') &&
	  number[index] != '.' && number[index] != '-')
	return (false);
      index += 1;
    }
  return (true);
}

bool					Chipset::parseGrammarType(std::string &instrc)
{
  std::vector<std::string>::iterator	it;
  size_t				pos;

  it = this->listGrammarType.begin();
  if (this->checkFormatArguement(instrc) == false)
    return (false);
  while (it != this->listGrammarType.end())
    {
      pos = instrc.find(*it);
      if (pos != std::string::npos)
	{
	  if (*it == "int8" || *it == "int16" || *it == "int32")
	    {
	      pos = instrc.find(".");
	      if (pos != std::string::npos)
		return (false);
	    }
	  return (true);
	}
      it++;
    }
  return (true);
}

eOperandType				Chipset::getTypeArgument(std::string &instrc)
{
  std::vector<std::string>::iterator	it;
  int					index;
  size_t				pos;

  index = 0;
  it = this->listGrammarType.begin();
  while (it != this->listGrammarType.end())
    {
      pos = instrc.find(*it);
      if (pos != std::string::npos)
	return ((eOperandType)index);
      ++it;
      ++index;
    }
  throw(Exception("Error type not found",
		  "getTypeArgument, line 150"));
  return ((eOperandType)0);
}

bool					Chipset::checkCurrentInstrc(std::string &instrc)
{
  std::vector<std::string>::iterator	itInstrc;
  bool					isInstrc;
  size_t				pos;
  std::stringstream			stream;

  isInstrc = false;
  itInstrc = this->listGrammarInsctr.begin();
  std::string t = instrc;
  while (isInstrc == false && itInstrc != this->listGrammarInsctr.end())
    {
      pos = t.find(*itInstrc);
      if (pos != std::string::npos && pos == 0)
	{
	  if (*itInstrc == "push" ||
	      *itInstrc == "assert")
	    {
	      if (this->numberArgInstrc(t) != 2 ||
		  this->parseGrammarType(t) == false)
		{
		  std::cout << "Error argument  = " << t << std::endl;
		  throw(Exception("Error argument",
				  "parsegrammarinstrc, line 67"));
		}
	    }
	  else if (this->numberArgInstrc(t) != 1)
	    throw(Exception("Error argument, must have only one argument",
			    "parsegrammarinstrc, line 74"));
	  isInstrc = true;
	}
      itInstrc++;
    }
  if (isInstrc == false)
    throw(Exception("Error instruction not found",
		    "parsegrammarinstrc, line 82"));
  return (true);
}

t_param_instrc			*Chipset::getNextInstrc()
{
  t_param_instrc		*param;
  std::string			s;
  std::istringstream		iss;
  size_t			beginBracket;
  size_t			endBracket;
  std::string			number;
  const FactoryIOperand		&fact = FactoryIOperand::getInstance();

  if (this->indexInstrc >= (int)this->listInsctr.size())
    return (NULL);
  s = this->listInsctr[this->indexInstrc];
  if (this->indexInstrc == (int)this->listInsctr.size() - 1 &&
      (this->listInsctr[this->listInsctr.size() - 1] == "exit") == false)
    {
      throw(Exception("Error exit missing",
		      "getNextInstrc, line 227"));
      return (NULL);
    }
  if (this->checkCurrentInstrc(s) == false)
    {
      throw(Exception("Error syntax",
		      "getNextInstrc, line 233"));
      return (NULL);
    }
  iss.str(s);
  this->indexInstrc += 1;
  param = new t_param_instrc;
  param->operand = NULL;
  iss >> s;
  param->instrc = s;
  iss >> s;
  beginBracket = s.find("(");
  endBracket = s.find(")");
  if (beginBracket == std::string::npos || endBracket == std::string::npos)
    return (param);
  number = s.substr(beginBracket + 1,
		    (endBracket - (beginBracket + 1)));
  param->operand = fact.createOperand(this->getTypeArgument(s), number);
  return (param);
}

void			Chipset::readInstruction(const std::string &file)
{
  std::ifstream		fd(file.c_str());
  std::istringstream	input;

  if (!fd.is_open())
    throw(Exception("Error open file",
		    "readInstruction, line 209"));
  std::string str(std::istreambuf_iterator<char>(fd),
	     (std::istreambuf_iterator<char>()));
  input.str(str);
  for (std::string line; std::getline(input, line);)
    {
      if (line[0] != ';' && this->numberArgInstrc(line) != 0)
	{
	  line = this->getArgumentFormat(line);
	  this->listInsctr.push_back(line);
	}
    }
}

void		Chipset::readInstruction()
{
  std::string	line;

  while (true)
    {
      std::getline(std::cin, line);
      if (line == ";;")
	return ;
      if (line[0] != ';' && this->numberArgInstrc(line) != 0)
	this->listInsctr.push_back(line);
    }
}

void		Chipset::setInput(std::string const &file)
{
  this->readInstruction(file);
}

void		Chipset::setInput()
{
  this->readInstruction();
}

Chipset::Chipset()
{
  this->indexInstrc = 0;
  this->initDefaultGrammar();
}

Chipset::~Chipset(){}
