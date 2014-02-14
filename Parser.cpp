#include "Parser.hpp"
#include <string.h>

void		Parser::initGrammar()
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

void			Parser::displayInstr()
{
  std::vector<std::string>::iterator	it;

  it = this->listInsctr.begin();
  while (it != this->listInsctr.end())
    {
      std::cout << *it << std::endl;
      it++;
    }
}

int			Parser::numberArgInstrc(std::string &instrc)
{
  int			index;
  std::istringstream	iss(instrc);
  std::string		s;

  index = 0;
  while (iss >> s)
    index += 1;
  return (index);
}

bool					Parser::parseGrammarInstrc()
{
  std::vector<std::string>::iterator	it;
  std::vector<std::string>::iterator	itInstrc;
  bool					isInstrc;
  size_t				pos;

  it = this->listInsctr.begin();
  while (it != this->listInsctr.end())
    {
      isInstrc = false;
      itInstrc = this->listGrammarInsctr.begin();
      std::string t = *it;
      std::cout << *it << std::endl;
      while (isInstrc == false && itInstrc != this->listGrammarInsctr.end())
	{
	  pos = ((std::string)*it).find(*itInstrc);
	  if (pos != std::string::npos && pos == 0)
	    {
	      if (strcmp(((std::string)*itInstrc).c_str(), "push") == 0 ||
		  strcmp(((std::string)*itInstrc).c_str(), "assert") == 0)
		{
		  if (this->numberArgInstrc(*it) != 2 ||
		      this->parseGrammarType(*it) == false)
		    throw(Exception("Error argument",
				    "parsegrammarinstrc, line 67"));
		}
	      else if (this->numberArgInstrc(*it) != 1)
		throw(Exception("Error argument, must have only one argument",
				"parsegrammarinstrc, line 74"));
	      isInstrc = true;
	    }
	  itInstrc++;
	}
      if (isInstrc == false)
	throw(Exception("Error instruction not found",
			"parsegrammarinstrc, line 82"));
      it++;
    }
  return (true);
}

bool			Parser::checkFormatArguement(std::string &instrc)
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
  while (number.c_str()[index] != '\0')
    {
      if ((number.c_str()[index] < '0' || number.c_str()[index] > '9') &&
	  number.c_str()[index] != '.')
	return (false);
      index += 1;
    }
  return (true);
}

bool					Parser::parseGrammarType(std::string &instrc)
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
	  if (strcmp(((std::string)*it).c_str(), "int8") == 0 ||
	      strcmp(((std::string)*it).c_str(), "int16") == 0 ||
	      strcmp(((std::string)*it).c_str(), "int32") == 0)
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

eOperandType				Parser::getTypeArgument(std::string &instrc)
{
  int					index;
  std::vector<std::string>::iterator	it;
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

t_param_instrc			*Parser::getNextInstrc()
{
  t_param_instrc		*param;
  std::string			s;
  std::istringstream		iss;
  size_t			beginBracket;
  size_t			endBracket;
  std::string			number;

  if (this->indexInstrc >= (int)this->listInsctr.size())
    return (NULL);
  s = this->listInsctr[this->indexInstrc];
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
  param->operand = createOperand(this->getTypeArgument(s), number);
  return (param);
}

bool					Parser::checkInstrc()
{
  if (this->parseGrammarInstrc() == false)
    {
      throw(Exception("Error syntax instruction",
		      "checkInstrc, line 194"));
      return (false);
    }
  std::cout << "parse ok " << std::endl;
  return (true);
}

void			Parser::readInstruction(const std::string &file)
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
      if (line.c_str()[0] != ';' && this->numberArgInstrc(line) != 0)
	this->listInsctr.push_back(line);
    }
}

void		Parser::readInstruction()
{
  std::string	line;

  while (1)
    {
      std::cin >> line;
      if (strcmp(line.c_str(), ";;") == 0)
	return ;
      if (line.c_str()[0] != ';' && this->numberArgInstrc(line) != 0)
	this->listInsctr.push_back(line);
    }
}

void		Parser::setInput(std::string &file)
{
  this->readInstruction(file);
  this->checkInstrc();
}

void		Parser::setInput()
{
  this->readInstruction();
  this->checkInstrc();
}

Parser::Parser()
{
  this->indexInstrc = 0;
  this->initGrammar();
}

Parser::~Parser(){}
