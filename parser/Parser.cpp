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

void			Parser::readInstruction(const std::string &file)
{
  std::ifstream		fd(file.c_str());
  std::istringstream	input;

  if (!fd.is_open())
    {
      std::cout << "Error open file" << std::endl;
      return ;
    }
  std::string str(std::istreambuf_iterator<char>(fd),
	     (std::istreambuf_iterator<char>()));
  input.str(str);
  for (std::string line; std::getline(input, line);)
    {
      if (line.c_str()[0] != ';')
	this->listInsctr.push_back(line);
    }
}

int			Parser::numberArgInstrc(std::string &instrc)
{
  int			index;
  std::istringstream	iss(instrc.c_str());
  std::string		s;

  index = 0;
  while (std::getline( iss, s, ' ' ))
    {
      if (strcmp(s.c_str(), " ") != 0)
	index += 1;
    }
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
	    isInstrc = true;
	  itInstrc++;
	}
      if (isInstrc == false)
	{
	  std::cout << "Error not [" << *it << "] found" << std::endl;
	  return (false);
	}
      it++;
    }
  return (true);
}



bool					Parser::parseGrammarType()
{
  std::vector<std::string>::iterator	it;

  it = this->listInsctr.begin();
  while (it != this->listInsctr.end())
    {

      it++;
    }
  return (true);
}

bool					Parser::checkInstrc()
{
  if (this->parseGrammarInstrc() == false || this->parseGrammarType() == false)
    return (false);
  return (true);
}

void		Parser::readInstruction()
{
  std::string	line;

  while (1)
    {
      std::cin >> line;
      if (strcmp(line.c_str(), ";;") == 0)
	return ;
      if (line.c_str()[0] != ';')
	this->listInsctr.push_back(line);
    }
}

Parser::Parser()
{
  this->initGrammar();
  this->readInstruction();
  this->displayInstr();
}

Parser::Parser(const std::string &file)
{
  this->initGrammar();
  this->readInstruction(file);
  this->displayInstr();
}

Parser::~Parser(){}
