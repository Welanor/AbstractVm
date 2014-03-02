#include <string.h>
#include <algorithm>
#include "Chipset.hpp"

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
  this->listGrammarInsctr.push_back("jump");
  this->listGrammarInsctr.push_back("cmpe");
  this->listGrammarInsctr.push_back("cmpne");
  this->listGrammarInsctr.push_back("cmpl");
  this->listGrammarInsctr.push_back("cmpg");
  this->listGrammarInsctr.push_back("dec");
  this->listGrammarInsctr.push_back("inc");
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
  bool				is_jump = false;
  bool				is_inc = false;
  size_t			pos;
  size_t			pos2;

  pos = instrc.find("jump");
  if (pos != std::string::npos && pos == 0)
    is_jump = true;
  pos = instrc.find("inc");
  pos2 = instrc.find("dec");
  if ((pos != std::string::npos && pos == 0) ||
      (pos2 != std::string::npos && pos2 == 0))
    is_inc = true;
  stream >> tmp;
  argument += tmp;
  if (is_inc == true)
    {
      argument += " int8(1)";
      return (argument);
    }
  while (stream >> tmp)
    {
      if (tmp[0] == ';')
	return (argument);
      if (is_arguement == false)
	argument += " ";
      if (is_jump == true)
	argument += "int32(";
      argument += tmp;
      if (is_jump == true)
	argument += ")";
      is_jump = false;
      is_arguement = true;
    }
  return (argument);
}

bool			Chipset::checkFormatArguement(std::string &instrc) const
{
  std::string::iterator	beginBracket;
  std::string::iterator	endBracket;
  std::string		number;
  int			index;

  beginBracket = std::find(instrc.begin(), instrc.end(), '(');
  endBracket = std::find(instrc.begin(), instrc.end(), ')');
  if (beginBracket == instrc.end() || endBracket == instrc.end())
    return (false);
  number = instrc.substr(std::distance(instrc.begin(), beginBracket+1), std::distance(beginBracket, endBracket)-1);
  index = 0;
  while (number[index] != '\0')
    {
      if ((number[index] < '0' || number[index] > '9') &&
	  number[index] != '.' && number[0] != '-')
	{
	  throw(Exception("Must be a numerical value",
			  __FILE__ ": line " TOSTRING(__LINE__)));
	  return (false);
	}
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
		  __FILE__ ": line " TOSTRING(__LINE__)));
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
	  if (*itInstrc == "push" || *itInstrc == "assert" ||
	      *itInstrc == "jump" || *itInstrc == "inc" ||
	      *itInstrc == "dec")
	    {
	      if (this->numberArgInstrc(t) != 2 ||
		  this->parseGrammarType(t) == false)
		{
		  throw(Exception("Error argument",
				  __FILE__ ": line " TOSTRING(__LINE__)));
		}
	    }
	  else if (this->numberArgInstrc(t) != 1)
	    throw(Exception("Error argument, must have only one argument",
			    __FILE__ ": line " TOSTRING(__LINE__)));
	  isInstrc = true;
	}
      itInstrc++;
    }
  if (isInstrc == false)
    throw(Exception("Error instruction not found",
		    __FILE__ ": line " TOSTRING(__LINE__)));
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

  if (this->indexInstrc >= this->listInsctr.size())
    throw(Exception("Error exit missing",
		    __FILE__ ": line " TOSTRING(__LINE__)));
  s = this->listInsctr[this->indexInstrc];
  if (this->checkCurrentInstrc(s) == false)
    {
      throw(Exception("Error syntax",
		      __FILE__ ": line " TOSTRING(__LINE__)));
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
		    __FILE__ ": line " TOSTRING(__LINE__)));
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
  fd.close();
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

void		Chipset::moveIndex(const int index)
{
  this->indexInstrc += index;
  if (this->indexInstrc > this->listInsctr.size())
    throw(Exception("Error value jump",
		    __FILE__ ": line " TOSTRING(__LINE__)));
}

void		Chipset::setInput(std::string const &file)
{
  while (listInsctr.size())
    listInsctr.pop_back();
  indexInstrc = 0;
  this->readInstruction(file);
}

void		Chipset::setInput()
{
  while (listInsctr.size())
    listInsctr.pop_back();
  indexInstrc = 0;
  this->readInstruction();
}

Chipset::Chipset()
{
  this->indexInstrc = 0;
  this->initDefaultGrammar();
}

Chipset::~Chipset(){}
